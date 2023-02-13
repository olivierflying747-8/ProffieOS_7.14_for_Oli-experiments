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
class SDCard : Looper 
#if defined(ULTRA_PROFFIE) && defined(OSx) && defined(X_POWER_MAN)
, xPowerManager {
#else 
  {
#endif
public:
  SDCard() : Looper() 
  #if defined(ULTRA_PROFFIE) && defined(OSx) && defined(X_POWER_MAN) 
    ,xPowerManager(xPower_SDCard, X_PM_SD_MS, name()) 
#endif
  {}
  const char* name() override { return STORAGE_RES; }

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

  void Mount() {
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

  void Loop() override {
#ifdef OSX_ENABLE_MTP
    if(!Serial_Protocol<SerialAdapter>::GetSession()) 
    {
#endif
      if (LSFS::IsMounted()) {
        if (!Active()) {
	        AudioStreamWork::LockSD_nomount(true);
	        AudioStreamWork::CloseAllOpenFiles();
          #if (defined(OSx) && defined(DIAGNOSE_STORAGE)) || !defined(OSx)
	        STDOUT.println("Unmounting " STORAGE_RES);
          #endif
	        LSFS::End();
	        AudioStreamWork::LockSD_nomount(false);
        } 
        #if defined(ULTRA_PROFFIE) && defined(OSx) && defined(X_POWER_MAN)
         else {
          requestPower(); // from Xpower Manager
          } 
        #endif
      } else {
        if (Active() && millis() - last_mount_try_ > 1000) {
	        last_mount_try_ = millis();
	        AudioStreamWork::LockSD_nomount(true);
	        if (LSFS::CanMount()) Mount();
	        AudioStreamWork::LockSD_nomount(false);
        }
      }
#ifdef OSX_ENABLE_MTP      
    }
#endif

  }

#if defined(ULTRA_PROFFIE) && defined(OSx) && defined(X_POWER_MAN)
    void xKillPower() override
    {
       #if DOSFS_SDCARD == 1 && DOSFS_SFLASH == 0
        // stm32l4_gpio_pin_configure(PIN_SPI_SD_POWER, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_OUTPUT));
        // stm32l4_gpio_pin_write(PIN_SPI_SD_POWER, 1);
       #endif
    }
    void xRestablishPower() override
    {  
       #if DOSFS_SDCARD == 1 && DOSFS_SFLASH == 0
        // stm32l4_gpio_pin_configure(PIN_SPI_SD_POWER, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_OUTPUT));
        // stm32l4_gpio_pin_write(PIN_SPI_SD_POWER, 0);
      #endif
      requestPower(); 
    }
#endif

private:
  uint32_t last_enabled_;
  uint32_t last_mount_try_;
};

SDCard sdcard;
inline void MountSDCard() { sdcard.Mount(); }
#else
inline void MountSDCard() {  }
#endif // v4 && enable_sd

#endif
