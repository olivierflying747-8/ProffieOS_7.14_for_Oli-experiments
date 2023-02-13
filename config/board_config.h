/********************************
 * ULTRAPROFFIE Configuration   *
 ********************************/
#ifdef ULTRA_PROFFIE
//#define TEST_PRAGMA_MSG
#ifdef CONFIG_TOP
    #include "ultraproffie_config.h"
    // defaults of OSx     


    // =============    DEVELOPER MODE  ============================= 
    // ----- DEVELOPER MODE ON : enable additional developer cmds 
    //                           and dont deactivate diagnostic cmds 
    #ifdef PF_DEVELOPER_MODE_ON 
        #ifdef TEST_PRAGMA_MSG               
            #pragma message ( "AI_DEVELOPER_MODE_ON  " )
        #endif
        #define ENABLE_DEVELOPER_MODE 
    #elif defined(PF_DEVELOPER_MODE_OFF)
        #ifdef TEST_PRAGMA_MSG               
            #pragma message ( "AI_DEVELOPER_MODE_OFF  " )
        #endif
        #undef  ENABLE_DEVELOPER_MODE       // undifined developer commands
        // #define DISABLE_DIAGNOSTIC_COMMANDS     // disable diagnostic commands

    #endif
    // ============     END OF DEVELOPER MODE =======================
    
    // ============     STATUS REPORT       ============================
    // ----- STATUS REPORT ON : Enables status reporting when installing 
    //                          or initing different components          
    #ifdef PF_STATUS_REPORT_ON
        #ifdef TEST_PRAGMA_MSG               
            #pragma message ( "AI STATUS REPORT ON " )
        #endif
    #elif defined(PF_STATUS_REPORT_OFF)   // ----- STATUS REPORT OFF : Disables status reporting when installing 
                                        // or initing different components 
        #ifdef TEST_PRAGMA_MSG               
            #pragma message ( "AI_STATUS REPORT OFF ")
        #endif
    #endif
    // ============ END STATUS REPORT =====================================

    // ============     VOICE MSGs       ============================          
    #ifdef PF_VOICE_MSG_DISABLED // ----- VOICE_MSG : Disables talking status msgs
        #ifdef TEST_PRAGMA_MSG               
            #pragma message ( "AI_VOICE MSGS DISABLED " )
        #endif                        
    #elif defined(PF_VOICE_FEMALE)     // ----- VOICE_MSG_MALE : Enables talking status msgs with male voice
        #ifdef TEST_PRAGMA_MSG               
            #pragma message ( "AI_VOICE MSGS FEMALE ")
        #endif                         
    #elif defined(PF_VOICE_MALE)  // ----- VOICE_MSG_MALE : Enables talking status msgs with male voice  
        #ifdef TEST_PRAGMA_MSG               
            #pragma message ( "AI_VOICE MSGS MALE ")
        #endif
    #endif
    // ============ END STATUS REPORT =====================================
    



    #define NO_STATUS_LED                                       // PFL and PFZ specific (we do not have a controlled status led)
    #define GYRO_MEASUREMENTS_PER_SECOND  1600                   // default Measuremnts per second , default do not remove 
    #define ACCEL_MEASUREMENTS_PER_SECOND 1600                  // default Measuremnts per second , default do not remove 

    #define NUM_BLADES 2
    #ifdef HW_NUM_BLADES 
        #define NUM_BLADES HW_NUM_BLADES
    #endif
    #define NUM_BUTTONS HW_NUM_BUTTONS
    #define HW_NOMINAL_VOLUME 3000  // don't change this unless you change the hardware (0-3 V max dac output) !!!
    #define VOLUME HW_NOMINAL_VOLUME                            // redefined at runtime for OSx 
    
    const unsigned int maxLedsPerStrip = 144;                   // max led per strip supported 
    #define CLASH_THRESHOLD_G 3.0                               //  default clash threshold
    #define ENABLE_AUDIO                                        // enable the audio 
    #define ENABLE_MOTION                                       // enable motion
    #define ENABLE_WS2811                                       // enable ws2811 , only this supported on PFL and PFZ 
    #define ENABLE_SD                                           // enable storage (sd or extern flash , board PFL and PBZ specific)
    #define SAVE_STATE                                          // enables save feather of volume, preset, color , dynamic diming
    #define ENABLE_ALL_EDIT_OPTIONS                             // enables save feathers of volume, preset, color , dynamic diming, clash diming and save , blade lenght and dimiing

    // #define OSX_ENABLE_MTP
    #define SERIAL_ASCII_BAUD 9600
    #define SERIAL_BIN_BAUD  921600   
    
    #ifdef OSx
        #include <stdint.h>
        #include "../motion/sensitivities.h"
        // =============    INSTALL CONFIGURATION  =============================       
        #define INSTALL_FILE "_osx_/install.cod"    // installation file
        #define OFFLINE_FILE "_osx_/offline.txt"    // publish conent here for offline use
        #define LEDLIB_FILE "_osx_/ledlib.cod"    // LED library file
        #ifndef OLDINSTALL
            static struct  {
                uint16_t audioFSR = VOLUME;
                uint16_t chargerCurrent = 0; // 0, 850 or 1000 [mA]
                uint8_t nBlades = 0;        // number of installed blades
                bool monochrome = true;     // assume monochrome, set true at install time
                uint32_t APOtime;           // auto power off time [ms]
            } installConfig;
            #undef VOLUME
            #define VOLUME installConfig.audioFSR
        #endif // OLDINSTALL
        // =============    END INSTALL CONFIGURATION  ==========================


        // =====================   USER PROFILE  ================================
        #define PRESETS_FILE "_osx_/presets.cod"    // Presets file
        #define PROFILE_FILE "_osx_/profile.cod"    // User profile file
        #ifndef OLDPROFILE  
            
            #undef  SAVE_STATE
            #undef ENABLE_ALL_EDIT_OPTIONS
            static struct {
                // float clashThreshold = CLASH_THRESHOLD_G;   // this is a number when userProfile is created, afterwards CLASH_THRESHOLD_G is redefined as clashThreshold
                // uint16_t clashSensitivity_old = 50970;          // that's for the default CLASH_THRESHOLD_G = 3
                uint16_t masterVolume = 65535;              // active volume
                uint16_t masterBrightness = 65535;          // active brightness
                uint8_t preset = 0;
                uint16_t apID = 0;   // active presets ID (to know which entry to overwrite in COD)
                ClashSensitivity clashSensitivity;          // all sensitivities inherit from 'Sensitivity' clash and hold both the user setting (0...65535) and the derived working parameters 
                uint16_t combatVolume = 65535;             // master Volume when stealth = off
                uint16_t combatBrightness = 65535;         // master Brightness when stealth = off
                uint16_t stealthVolume = 10000;             // master Volume when stealth = on
                uint16_t stealthBrightness = 10000;         // master Brightness when stealth = off
                SwSensitivity swingSensitivity;
                StabSensitivity stabSensitivity;
                ShakeSensitivity shakeSensitivity;
                TapSensitivity tapSensitivity;
                TwistSensitivity twistSensitivity;
                MenuSensitivity menuSensitivity;
            } userProfile;
            #undef CLASH_THRESHOLD_G
            // #define CLASH_THRESHOLD_G userProfile.clashThreshold
            #define CLASH_THRESHOLD_G userProfile.clashSensitivity.clashThreshold
            
        #endif // OLDPROFILE
        // ==================   END USER PROFILE  =============================== 
        #ifdef TEST_PRAGMA_MSG
            #pragma message ( "OSx  " )
        #endif
        #define OSX_SUBVERSION       "009"       // Fork version 

        #define X_MOTION_TIMEOUT        60000    // 
        #define X_POWER_MAN
        #ifdef X_POWER_MAN
            #define X_PM_MOTION_MS 10
            #define X_PM_WS_MS     10000
            #define X_PM_BOOST_MS  10000
            #define X_PM_AMP_MS    10000
            #define X_PM_SER_MS    60000
            #define X_PM_SSER_MS   300000
            #define X_PM_SD_MS     10000
            #define X_PM_PROP_MS   X_MOTION_TIMEOUT // sync it 
        #endif
        #define OSX_ENABLE_MTP              // enables proffieOSx serial transfer protcol                 

        #ifdef ENABLE_DEVELOPER_MODE
            #define ENABLE_DEVELOPER_COMMANDS       // ProffieOS developer commands
            #define X_PROBECPU                      // Enable CPU probes (results reported at STDOUT under "top"). Adds 3k program memory
            #define X_BROADCAST                      // Enable broadcasting of binary monitoring data. For debug only
            #ifdef X_BROADCAST
                #define OBSIDIANFORMAT  // reuse matlabs
                // #define BROADCAST_MOTION             // Broadcast acc & gyro
                // #define BROADCAST_THETA              // Broadcast data for twist navigation
                // #define BROADCAST_SHAKE             // Broadcast data for shake detection
                // #define BROADCAST_2TAP             // Broadcast data for double-tap detection
            #endif
            #define DIAGNOSE_EVENTS            
            #define X_LIGHTTEST                       // Enable parsing LED test commands
            #define X_MENUTEST                      // Enable parsing xMenu commands
        #endif

        #ifdef PF_STATUS_REPORT_ON
            #define ENABLE_DIAGNOSE_COMMANDS
            #define DIAGNOSE_SENSOR
            #define DIAGNOSE_STORAGE
            #define DIAGNOSE_AUDIO
            #define DIAGNOSE_BLADES
            #define DIAGNOSE_POWER
            #define DIAGNOSE_BOOT                      
            // #define DIAGNOSE_EVENTS
            #define DIAGNOSE_PRESETS
            #define DIAGNOSE_PROP        
        #endif

    #else 
        #ifdef TEST_PRAGMA_MSG
            #pragma message ( "Hubbe OS  " )
        #endif
    #endif // OSx
#endif // CONFIG_TOP

#ifdef CONFIG_BUTTONS
    Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
#endif

/********************************
 * PROFFIEBOARD Configuration   *
 ********************************/
#else
    #if PROFFIEBOARD_VERSION - 0 == 1
    #include "proffieboard_v1_config.h"
    #elif PROFFIEBOARD_VERSION - 0 == 2
    #include "proffieboard_v2_config.h"
    #elif PROFFIEBOARD_VERSION - 0 == 3
    #include "proffieboard_v3_config.h"
    #else
    #error UNKNOWN PROFFIEBOARD
    #endif

    #ifdef OSx
        #include <stdint.h>
        #include "../motion/sensitivities.h"
        // =============    INSTALL CONFIGURATION  ============================= 
        #define INSTALL_FILE "_osx_/install.cod"    // installation file
        #define OFFLINE_FILE "_osx_/offline.txt"    // publish conent here for offline use
        #define LEDLIB_FILE "_osx_/ledlib.cod"    // LED library file
        #define HW_NOMINAL_VOLUME 3000
        #define VOLUME HW_NOMINAL_VOLUME

        #define PF_PWM_CH   4   // number of PWM channels
        #define PF_PIX_CH   2   // number of pixel channels

        #ifndef OLDINSTALL
            static struct  {
                uint16_t audioFSR = VOLUME;
                uint16_t chargerCurrent = 0; // 0, 850 or 1000 [mA]
                uint8_t nBlades = 0;        // number of installed blades
                bool monochrome = true;     // assume monochrome, set true at install time
                uint32_t APOtime;           // auto power off time [ms]
            } installConfig;
            #undef VOLUME
            #define VOLUME installConfig.audioFSR
        #endif // OLDINSTALL
        // =============    END INSTALL CONFIGURATION  ==========================


        // =====================   USER PROFILE  ================================
        #define PRESETS_FILE "_osx_/presets.cod"    // Presets file
        #define PROFILE_FILE "_osx_/profile.cod"    // User profile file


        #ifndef OLDPROFILE  
            
            #undef  SAVE_STATE
            #undef ENABLE_ALL_EDIT_OPTIONS
            static struct {
                // float clashThreshold = CLASH_THRESHOLD_G;   // this is a number when userProfile is created, afterwards CLASH_THRESHOLD_G is redefined as clashThreshold
                // uint16_t clashSensitivity_old = 50970;          // that's for the default CLASH_THRESHOLD_G = 3
                uint16_t masterVolume = 65535;              // active volume
                uint16_t masterBrightness = 65535;          // active brightness
                uint8_t preset = 0;
                uint16_t apID = 0;   // active presets ID (to know which entry to overwrite in COD)
                ClashSensitivity clashSensitivity;          // all sensitivities inherit from 'Sensitivity' clash and hold both the user setting (0...65535) and the derived working parameters 
                uint16_t combatVolume = 65535;             // master Volume when stealth = off
                uint16_t combatBrightness = 65535;         // master Brightness when stealth = off
                uint16_t stealthVolume = 10000;             // master Volume when stealth = on
                uint16_t stealthBrightness = 10000;         // master Brightness when stealth = off
                SwSensitivity swingSensitivity;
                StabSensitivity stabSensitivity;
                ShakeSensitivity shakeSensitivity;
                TapSensitivity tapSensitivity;
                TwistSensitivity twistSensitivity;
                MenuSensitivity menuSensitivity;
            } userProfile;
            #undef CLASH_THRESHOLD_G
            // #define CLASH_THRESHOLD_G userProfile.clashThreshold
            #define CLASH_THRESHOLD_G userProfile.clashSensitivity.clashThreshold
            
        #endif // OLDPROFILE
        
        // ==================   END USER PROFILE  =============================== 

        #ifdef TEST_PRAGMA_MSG
            #pragma message ( "OSx  " )
        #endif
        #define OSX_SUBVERSION       "009"       // Fork version 
        
        // #define INSTALL_FILE "_osx_/testled.cod"    // installation file
        // #define LEDLIB_FILE "_osx_/ledlib.cod"    // LED library file

        #define PF_PROP_ULTRASABERS         // define  ultrasabers props 
        // #define PF_PROP_SABER
        #define ENABLE_DEVELOPER_MODE       // developer mode
        #define PF_STATUS_REPORT_ON         // status report ON , comment to off 
        #define PF_VOICE_MSG_DISABLED       // talkie : 0- VOICE MSG DISABLED
                                            //          1- VOICE MSG FEMALE 
                                            //          2- VOICE MSG MALE
        #define X_MOTION_TIMEOUT        60000
        // #define X_POWER_MAN
        #ifdef X_POWER_MAN
            #define X_PM_MOTION_MS 10
            #define X_PM_WS_MS     10000
            #define X_PM_BOOST_MS  10000
            #define X_PM_AMP_MS    10000
            #define X_PM_SER_MS    60000
            #define x_PM_SSER_MS   300000
            #define X_PM_SD_MS     10000
            #define X_PM_PROP_MS   X_MOTION_TIMEOUT // sync it 
        #endif

        #define OSX_ENABLE_MTP              // enables proffieOSx serial transfer protcol   
		    #ifdef OSX_ENABLE_MTP
                #define SERIAL_ASCII_BAUD 9600
                #define SERIAL_BIN_BAUD  921600   
            #endif              
       #ifdef ENABLE_DEVELOPER_MODE
            // #define ENABLE_DEVELOPER_COMMANDS       // ProffieOS developer commands
            #define DIAGNOSE_EVENTS            
            #define X_PROBECPU                      // Enable CPU probes (results reported at STDOUT under "top"). Adds 3k program memory
            //#define X_BROADCAST                      // Enable broadcasting of binary monitoring data. For debug only
            #ifdef X_BROADCAST
                // #define OBSIDIANFORMAT  // reuse matlabs
                // #define BROADCAST_MOTION             // Broadcast acc & gyro
                // #define BROADCAST_THETA              // Broadcast data for twist navigation
                // #define BROADCAST_SHAKE             // Broadcast data for shake detection
                // #define BROADCAST_2TAP             // Broadcast data for double-tap detection
            #endif            
            // #define X_LIGHTTEST                       // Enable parsing LED test commands
        #endif

        #ifdef PF_STATUS_REPORT_ON
            #define ENABLE_DIAGNOSE_COMMANDS
            #define DIAGNOSE_SENSOR
            #define DIAGNOSE_STORAGE
            // #define DIAGNOSE_EVENTS
            #define DIAGNOSE_AUDIO
            #define DIAGNOSE_POWER        
            #define DIAGNOSE_BOOT                      // Enable developer stream on serial port
        #endif

    #else // OSx
        #ifdef TEST_PRAGMA_MSG
            #pragma message ( "Hubbe OS  " )
        #endif
    #endif // OSx
#endif // ULTRA_PROFFIE

