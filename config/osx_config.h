// Formally known as 'default_proffieboard_config'.
// Under OSx most configurations are done at runtime, so this file configures mostly ProffieOS


#ifdef CONFIG_TOP
#define NUM_BLADES 2
#define NUM_BUTTONS 2
#define VOLUME 3000	// 3000
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 3.0
#define ENABLE_AUDIO
#define ENABLE_MOTION
#define ENABLE_WS2811
#define ENABLE_SD
#define SAVE_STATE
#define ENABLE_ALL_EDIT_OPTIONS
#include "board_config.h"
#endif


    




#ifdef CONFIG_PRESETS

#ifdef OSx
  #include <vector>
  #ifndef OLDPROFILE
    #include "../styles/styles.h"
  #endif // OLDPROFILE
#endif // OSx

  #if !defined(OSx) || defined(OLDPROFILE)
    // ProffieOS presets
    Preset presets[] = {
      { "default", "tracks/venus.wav",
        StylePtr<Layers<RotateColorsX<Variation,Red>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipe<300>,TrWipeIn<500>,Black>>>(),
        StyleNormalPtr<Red,SimpleClash<Lockup<BlastFadeout<Blue,White>,AudioFlicker<HumpFlicker<Red,GhostWhite,75>,Blue>,AudioFlicker<Blue,White>>,White,80>,300,800>(), "UltraDefault" },
      { "SmthJedi", "tracks/mars.wav",
        StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
        StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(), "blue"},
      { "SmthGrey", "tracks/mercury.wav",
        StyleFirePtr<RED, YELLOW, 0>(),
        StyleFirePtr<RED, YELLOW, 1>(), "fire"},
      { "SmthFuzz", "tracks/uranus.wav",
        StyleNormalPtr<RED, WHITE, 300, 800>(),
        StyleNormalPtr<RED, WHITE, 300, 800>(), "red"},
      { "RgueCmdr", "tracks/venus.wav",
        StyleFirePtr<BLUE, CYAN, 0>(),
        StyleFirePtr<BLUE, CYAN, 1>(), "blue fire"},
      { "TthCrstl", "tracks/mars.wav",
        StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
        StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(), "green"},
      { "TeensySF", "tracks/mercury.wav",
        StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
        StyleNormalPtr<WHITE, RED, 300, 800, RED>(), "white"},
      { "SmthJedi", "tracks/uranus.wav",
        StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
        StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(), "yellow"},
      { "SmthGrey", "tracks/venus.wav",
        StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
        StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(), "magenta"},
      { "SmthFuzz", "tracks/mars.wav",
        StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
        StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(), "gradient"},
      { "RgueCmdr", "tracks/mercury.wav",
        StyleRainbowPtr<300, 800>(),
        StyleRainbowPtr<300, 800>(), "rainbow"},
      { "TthCrstl", "tracks/uranus.wav",
        StyleStrobePtr<WHITE, Rainbow, 15, 300, 800>(),
        StyleStrobePtr<WHITE, Rainbow, 15, 300, 800>(), "strobe"},
      { "TeensySF", "tracks/venus.wav",
        &style_pov,
        StyleNormalPtr<BLACK, BLACK, 300, 800>(), "POV"},
      { "SmthJedi", "tracks/mars.wav",
        &style_charging,
        StyleNormalPtr<BLACK, BLACK, 300, 800>(), "Battery\nLevel"}
    }; 
  #else // OSx
    // ProffieOSx presets: nothing to do here, use presets XML
    vector<xPreset> presets;
  #endif // OSx



  #if !defined(OSx) || defined(OLDINSTALL)
    // ProffieOS configuration
    BladeConfig blades[] = {
    { 0, 
    WS2811BladePtr<131, WS2811_800kHz|WS2811_GRB>(),    // 1st blade = pixel blade, all boards
    #ifdef ULTRA_PROFFIE                                 // 2nd blade on Lite: RGBW
        #if HWL_CONCAT(MQUOATE, HW_PREFIX, MQUOATE) == 'L'
          SimpleBladePtr<CreeXPE2RedTemplate<680>,
                                CreeXPE2GreenTemplate<0>,
                                CreeXPE2BlueTemplate<0>, 
                                CreeXPE2WhiteTemplate<0>, bladePowerPin1, bladePowerPin2, bladePowerPin3, bladePowerPin4>(),
        #else                                           // 2nd blade on Zero: RW
          SimpleBladePtr<CreeXPE2RedTemplate<680>,    
                        CreeXPE2WhiteTemplate<0>,
                        NoLED, 
                        NoLED, bladePowerPin1, bladePowerPin2, -1, -1>(),

        #endif
    #else // nULTRA_PROFFIE                            // 2nd blade on ProffieBoard: RGBW
      SimpleBladePtr<CreeXPE2RedTemplate<680>,
                        CreeXPE2GreenTemplate<0>,
                        CreeXPE2BlueTemplate<0>, 
                        CreeXPE2WhiteTemplate<0>, bladePowerPin1, bladePowerPin2, bladePowerPin3, bladePowerPin4>(),
    #endif // ULTRA_PROFFIE
     CONFIGARRAY(presets) },
  };
  #else 
    // ProffieOSx configuration: nothing to do here, use install XML.
    #ifdef OLDPROFILE
      BladeConfig blades[] = {
      { 0, 
        DECLARE_NULL_BLADES,  
        presets,
        NELEM(presets) }
      };
    #else
      BladeConfig blades[] = {
      { 0, 
        DECLARE_NULL_BLADES,  
        &presets }  
      };    
    #endif
  #endif // OSx




#endif // CONFIG_PRESETS

#ifdef CONFIG_BUTTONS 
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
// Button AuxButton(BUTTON_AUX, auxPin, "aux");  
#endif
