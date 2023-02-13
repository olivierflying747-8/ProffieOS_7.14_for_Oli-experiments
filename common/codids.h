#ifndef CODIDS_H
#define CODIDS_H

/* COD IDs
    0 = null
    1 ... 999 = local IDs
    1000 ... 1999 = Analog LED emitter drivers
    2000 ... 2999 = Color renderers & Transfer functions
    3000 ... 3999 = Analog LED channels
    4000 ... 4999 = Analog LEDs
    5000 ... 5999 = Digital blade drivers
    6000 ... 9999 = Presets


*/

#define HANDLER_xUpdate 1

// Handlers
#define  HANDLER_xBladeInstaller                10      // Blade install 
#define  HANDLER_xInstaller                     11      // Install settings
#define  HANDLER_xProfile                       12      // User profile
#define  HANDLER_xPreset                        13      // Preset
#define  HANDLER_xPresetList                    14      // List of active presets



#define  HANDLER_xInterpolator                  99      // Any interpolator reference data
#define  HANDLER_xAnalogLED_Driver_Legacy       100     // Legacy driver
#define  HANDLER_xAnalogLED_Driver_pPWL         101     // pPWL driver

#define  HANDLER_xColorRenderer_HSLe            110     // HSL enhancer
#define  HANDLER_xColorRenderer_CRM             111     // Color rendering matrix
#define  HANDLER_xAnalogLED_Channel             112     // Single/multi-emitter LED Channel
#define  HANDLER_xAnalogLED                     113     // Single/multi-channel LED Module

#define  HANDLER_PixelDriver                    120     // Pixel driver configuration


#endif // CODIDS_H





