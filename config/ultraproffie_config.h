// This config file contains all the things should be the same for all
// proffie lite  proffiboard configurations. In most cases there should be no need
// to change anything in this file.
#ifndef PROFFIELITE_CONFOG_HW
#define PROFFIELITE_CONFOG_HW

    #define VERSION_MAJOR 6    
    #define VERSION_MINOR 1
    #define V2
    #define V3
    #define PROFFIEBOARD

    #define INVALID_PIN 32  // it is the pin specially created to g_APinDescription to indicate a invalid , no use // as 29
    // Proffieboard pin map
    enum SaberPins {
            // I2S
        bclkPin = INVALID_PIN,             // NOT USED ON HW TODO // BCLK (digital audio)   PB13  was = 3
        txd0Pin = INVALID_PIN,             // NOT USED ON HW TODO // TXD0 (digital audio)   PA10  was = 26
        lrclkPin = INVALID_PIN,            // NOT USED ON HW TODO // LRCLK (digital audio)  PB12 was = 2

        // I2C
        i2cDataPin = 22,                   // I2C bus, Used by motion sensors  PB9 - I2C1_SDA
        i2cClockPin = 21,                  // I2C bus, Used by motion sensors  PB8 - I2C1_SCL

        // Buttons
        powerButtonPin = 11,               // power button  PB6
        auxPin = 12,                       // AUX button    PB5
        aux2Pin = INVALID_PIN,             // AUX2 button   PB4

        // Memory card
        sdCardSelectPin = INVALID_PIN,     // PB14

        amplifierPin = 18,                  // Amplifier enable pin PB4
        boosterPin = 13,                    // Booster enable pin   PH0        INVALID_PIN
        motionSensorInterruptPin = 28,      // motion sensor interrupt PC13

        // No fastled support yet
        spiLedSelect = INVALID_PIN,         
        spiLedDataOut =INVALID_PIN,
        spiLedClock = INVALID_PIN,

        // Neopixel pins
        bladePin = 27,                  // blade control, either WS2811 or PWM PA0
        bladeIdentifyPin = 27,          // blade identify input / FoC
            blade2Pin = 25,                 // PB8
        blade3Pin = INVALID_PIN,        // PB3
        blade4Pin = INVALID_PIN,        // PA4
        blade5Pin = INVALID_PIN,        // PA15 (also UART)
        blade6Pin = INVALID_PIN,        // PA02 (also UART)
        // bladeDAT2PB14 = 26,
        // bladeDAT2PB13 = 25,
        // Blade power control
        bladePowerPin1 = 5,             // blade power control PA1
        bladePowerPin2 = 17,            // blade power control PB8
        bladePowerPin3 = 23,            // blade power control PA8
        bladePowerPin4 = 24,            // blade power control PB3
        bladePowerPin5 = INVALID_PIN,   // blade power control PB15
        bladePowerPin6 = INVALID_PIN,   // blade power control PB0

        // If there is no neopixels, these can be used as PWM output
        // If neopixels are present, but not on these pins, PWM may still
        // be possible at 800kHz.
        // You can drive 20mA LEDs with a resistor from these pins, or
        // hook up an external FET to drive more powerful LEDs
        bladePowerPin7 = INVALID_PIN,   // PB03 (also neopix4)
        bladePowerPin8 = INVALID_PIN,   // PB10 (also neopix2)
        bladePowerPin9 = INVALID_PIN,   // PB11 (also neopix3)
        bladePowerPin10 = INVALID_PIN,  // PA00 (also blade ID / neopixels)

        // Analog pins
        batteryLevelPin = 29,           // battery level input PA04 was 1
        batteryRefPin = 30,             // battery level input PA04 was 1
        // UART
        rxPin = 20,                      // PA15
        txPin = 19,                      // PA02

        statusLEDPin = INVALID_PIN,      // no fw status led 
        chargeDetectPin = 20,            // charge detect 
        chargeCurrentPin = 8,            // charge current (0=0.85A, 1=1.0A) 
        chargeEnablePin =  31,              // charge enable
        // MiCOM setup
        trigger1Pin = INVALID_PIN,      // power button
        trigger2Pin = INVALID_PIN,      // aux button
        trigger3Pin = INVALID_PIN,      // aux2 button
        trigger4Pin = INVALID_PIN,      // data2
        trigger5Pin = INVALID_PIN,      // data3
        trigger6Pin = INVALID_PIN,      // data4
        trigger7Pin = INVALID_PIN,      // RX
        trigger8Pin = INVALID_PIN,      // TX
    };

    // -------------- Define Tester ----------------------------------
        // Helper DEFINES to CHECK the CONFIGURATION    // do not erase 
    #define XSTR(x) STR(x)          
    #define STR(x) #x
    #define MQUOATE '

    // Concatenate preprocessor tokens Q0, .., Q1 without expanding macro definitions
    // (however, if invoked from a macro, macro arguments are expanded).
    #define HWID_CONCAT_NX(Q0, L1, L2, L3, L4, Q1) Q0 ## L1 ## L2 ## L3 ## L4 ## Q1
    // Concatenate preprocessor tokens A and B after macro-expanding them.
    #define HWID_CONCAT(Q0, L1, L2, L3, L4, Q1) HWID_CONCAT_NX(Q0, L1, L2, L3, L4, Q1)
    #define HWL_CONCAT_NX(q1, l2, q3) q1 ## l2 ## q3
    #define HWL_CONCAT(q1, l2, q3) HWL_CONCAT_NX(q1, l2, q3)

    #define FORMED_HWVER HWID_CONCAT(MQUOATE, HW_PREFIX, HW_LETTER1, HW_LETTER2, HW_LETTER3, MQUOATE)

    #ifdef HWVER                    
       #ifdef TEST_PRAGMA_MSG 
        #pragma message (XSTR(HWVER))
       #endif
    #endif

    #if HWVER == FORMED_HWVER
        #ifdef TEST_PRAGMA_MSG  
            #pragma message ("HW VERSION == FORMED HW VERSION")
        #endif
    #else
        #error HW VERSION ERROR
    #endif

    #if HWL_CONCAT(MQUOATE, HW_LETTER3, MQUOATE) == 'L'
        #ifdef TEST_PRAGMA_MSG 
            #pragma message ("LSM6DS3")
        #endif
        #define GYRO_CLASS LSM6DS3H     // gyro class 
    #else
        #error error SNS DEFINE NOT FOUND
    #endif

    #if HW_LETTER4 == 2
        #ifdef TEST_PRAGMA_MSG
            #pragma message ("PWMCH 2")
        #endif
        #define PF_PWM_CH   2   // number of PWM channels
        #define PF_PIX_CH   1   // number of pixel channels
        #define BOARDTYPE_ZERO // UltraProffie Zero
    #elif HW_LETTER4 == 4
        #ifdef TEST_PRAGMA_MSG
            #pragma message ("PWMCH 4")
        #endif
        #define PF_PWM_CH   4   // number of PWM channels
        #define PF_PIX_CH   2   // number of pixel channels
        #define BOARDTYPE_LITE  // UltraProffie Lite

    #else
        #error error PWM CH NOt OKAY
    #endif

    #if HW_LETTER5 == 1
        #ifdef TEST_PRAGMA_MSG
            #pragma message ("BOOSTER EQ")
        #endif
        #define PF_BOOSTER  1
    #elif HW_LETTER5 == 0
        #ifdef TEST_PRAGMA_MSG
            #pragma message ("NO BOOSTER")
        #endif
        #define PF_BOOSTER  0
    #else
        #error error BOOSTEr define not FoUND
    #endif

    #if HW_LETTER1 == 2
        #ifdef TEST_PRAGMA_MSG
            #pragma message ("Analog amp 2W")
        #endif
        #define USE_DAC                 
    #elif HW_LETTER1 == 3
        #ifdef TEST_PRAGMA_MSG
            #pragma message ("Analog amp 3W")
        #endif
        #define USE_DAC               
    #else
        #error error AMP NOT FOUND 
    #endif

    #if HW_LETTER2 == 1
        #ifdef TEST_PRAGMA_MSG
            #pragma message ("Charger eq")
        #endif
        #define ULTRA_PROFFIE_CHARGER_EQ
    #elif HW_LETTER2 == 0
        #ifdef TEST_PRAGMA_MSG
            #pragma message ("NO CHARGER")
        #endif
        // #define PF_CHARGER_EQ   0
    #else
        #error error NO CHARGER DEFINE
    #endif


    #ifdef TEST_PRAGMA_MSG
        #ifdef ULTRA_PROFFIE               
            #pragma message ( "ULTRA_PROFFIE ! Yey  " )
        #endif

        #ifdef HW_NUM_BUTTONS 
            #pragma message ( "HW_NUM_BUTTONS  " XSTR(HW_NUM_BUTTONS) )
        #endif

        #if DOSFS_SFLASH - 0 == 1
            #pragma message ( "Memory Type : Serial Flash" )
        #endif

        #if DOSFS_SDCARD - 0 == 1
            #pragma message ( "Memory Type : SD Card " )
        #endif

        #ifdef HW_NUM_BLADES
            #pragma message ( "HW_NUM_Blades " XSTR(HW_NUM_BLADES) )
        #endif
    #endif

#endif
// -------------- Define Tester ---------------------------------- 
