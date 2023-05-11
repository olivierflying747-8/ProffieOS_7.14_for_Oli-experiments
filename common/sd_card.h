#ifndef COMMON_SDCARD_H
#define COMMON_SDCARD_H

#include "lsfs.h"

// #ifdef OSX_ENABLE_MTP
//   #include "serial.h"
// #endif

#if defined(ENABLE_SD) && VERSION_MAJOR >= 4

 #if DOSFS_SDCARD == 1 && DOSFS_SFLASH == 0
    #define STORAGE_RES "SD Card"
  #elif DOSFS_SDCARD == 0 && DOSFS_SFLASH == 1
    #define STORAGE_RES "FLASH"
  #endif
// Unmount sdcard when we don't need it anymore.

#if defined(ULTRA_PROFFIE) && defined(OSx) 
class SDCard : Looper , xPowerSubscriber {
#else // nULTRA_PROFFIE
class SDCard : Looper {
#endif // ULTRA_PROFFIE
public:
  
  #if defined(ULTRA_PROFFIE) && defined(OSx) 
    SDCard() : Looper(), xPowerSubscriber(pwr4_SD) {}
  #else
    SDCard() : Looper()  {}
  #endif
  
  const char* name() override { return STORAGE_RES; }


  #if defined(ULTRA_PROFFIE) && defined(OSx) 
    bool Active() {
      // if (amplifier.Active() || AudioStreamWork::sd_is_locked() || AudioStreamWork::SDActive()) return true;
      if (SoundActive() || AudioStreamWork::sd_is_locked() || AudioStreamWork::SDActive()) return true;
      // TODO add define here
      #ifdef OSX_ENABLE_MTP 
      if (Serial_Protocol<SerialAdapter>::GetSession()) return true;
      #endif
      if (SaberBase::IsOn()) return true;
      return false;
    }
  #else // nOSx
    bool Active() {
    #ifdef ENABLE_AUDIO    
        if (amplifier.Active() || AudioStreamWork::sd_is_locked() || AudioStreamWork::SDActive()) {
          last_enabled_ = millis();
          return true;
        }
    #endif    
        if (SaberBase::IsOn()) {
          last_enabled_ = millis();
          return true;
        }
    #ifdef USB_CLASS_MSC
        if (USBD_Configured()) return false;
    #endif
        uint32_t t = millis() - last_enabled_;
        if (t < 1000) return true;
        return false;
      }  
  #endif // OSx

  

  void Mount() {
    #if defined(ULTRA_PROFFIE) && defined(OSx)
      uint32_t mountTimeout = PWRMAN_SDMOUNTTIMEOUT;
      RequestPower(&mountTimeout);   // allow longer time for pre-loop initializations
    #endif    
    last_enabled_ = millis();
    if (LSFS::IsMounted()) return;

    // Wait for card to become available, up to 1000ms
    uint32_t start = millis();
    while (!LSFS::CanMount() && millis() - start < 1000)
      armv7m_core_yield();
    if (!LSFS::CanMount()) {
      char tmp[128];
      LSFS::WhyBusy(tmp);
      #if (defined(OSx) && defined(DIAGNOSE_STORAGE)) || !defined(OSx)
      STDOUT.print(STORAGE_RES" is busy, flags= ");
      STDOUT.println(tmp);
      #endif
      return;
    }
    
    if (!LSFS::Begin()) {
      #if (defined(OSx) && defined(DIAGNOSE_STORAGE)) || !defined(OSx)
      STDOUT.println("Failed to mount " STORAGE_RES);
      #endif
      return;
    }
  }

protected:
  void Setup() override {
    last_enabled_ = millis();
  }

#if defined(ULTRA_PROFFIE) && defined(OSx) 
  void Loop() override {
      if (Active()) 
          RequestPower();   // for all subscribed domains       
      if(!Serial_Protocol<SerialAdapter>::GetSession()) 
      {        
         if(!LSFS::IsMounted()) {   // attempt to mount once every secondm if it should be active
          if (Active() && millis() - last_mount_try_ > 1000) {
            last_mount_try_ = millis();
            AudioStreamWork::LockSD_nomount(true);
            if (LSFS::CanMount()) Mount();
            AudioStreamWork::LockSD_nomount(false);
          }
        }   
      }
  }
#else // nULTRA_PROFFIE
  void Loop() override {
      if (LSFS::IsMounted()) {
        if (!Active()) {
          AudioStreamWork::LockSD_nomount(true);
          AudioStreamWork::CloseAllOpenFiles();                 
          STDOUT.println("Unmounting " STORAGE_RES);
          LSFS::End();
          AudioStreamWork::LockSD_nomount(false);
        } 
      } else {
        if (Active() && millis() - last_mount_try_ > 1000) {
          last_mount_try_ = millis();
          AudioStreamWork::LockSD_nomount(true);
          if (LSFS::CanMount()) Mount();
          AudioStreamWork::LockSD_nomount(false);
        }
      }
  }
#endif // ULTRA_PROFFIE

  
  

#if defined(ULTRA_PROFFIE) && defined(OSx) 
        void PwrOn_Callback() override { 
          #ifdef DIAGNOSE_POWER
            STDOUT.println(" sd+ "); 
          #endif
          }         
        void PwrOff_Callback() override { 
            AudioStreamWork::LockSD_nomount(true);
            AudioStreamWork::CloseAllOpenFiles();
            #ifdef DIAGNOSE_STORAGE
              STDOUT.println("Unmounting " STORAGE_RES);
            #endif          
            LSFS::End();
            AudioStreamWork::LockSD_nomount(false);
            #ifdef DIAGNOSE_POWER
              STDOUT.println(" sd- "); 
            #endif
        }         
#endif // ULTRA_PROFFIE

private:
  uint32_t last_enabled_;
  uint32_t last_mount_try_;
};

SDCard sdcard;
inline void MountSDCard() { sdcard.Mount(); }
#else  // v4 && enable_sd
inline void MountSDCard() {  }
#endif // v4 && enable_sd

#endif
