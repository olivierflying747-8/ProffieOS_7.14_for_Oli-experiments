#ifdef CONFIG_TOP
#include "proffieboard_v3_config.h"
#define NUM_BLADES 2
#define NUM_BUTTONS 2
#define VOLUME 1800
const unsigned int maxLedsPerStrip = 128;
#define CLASH_THRESHOLD_G 4.5
#define ENABLE_AUDIO
#define ENABLE_MOTION
#define ENABLE_WS2811
#define ENABLE_SD
#define ENABLE_SERIAL
#define ORIENTATION ORIENTATION_USB_TOWARDS_BLADE

#define DISABLE_DIAGNOSTIC_COMMANDS
#define FETT263_MULTI_PHASE

#define FETT263_TWIST_ON_NO_BM 
#define FETT263_TWIST_ON 
#define FETT263_TWIST_OFF    

#define FETT263_STAB_ON_NO_BM                                              
#define FETT263_STAB_ON                                

#define FETT263_SWING_ON_SPEED 500
#define FETT263_SWING_ON_NO_BM
#define FETT263_SWING_ON
#define FETT263_SWING_OFF

#define MOTION_TIMEOUT 60 * 3 * 1000  

#define FETT263_THRUST_ON
#define FETT263_THRUST_OFF
#define FETT263_DISABLE_COPY_PRESET

// #define ENABLE_SSD1306
// // Max 20 characters
// #define BLE_PASSWORD "your password"
// // Max 32 characters.
// #define BLE_NAME "Your Saber Name"
// // Max 9 characters
// #define BLE_SHORTNAME "Saber"

#define MOTION_TIMEOUT 60 * 3 * 800               
#endif

#ifdef CONFIG_PROP
#include "../props/saber_fett263_buttons.h"

#endif


#ifdef CONFIG_PRESETS
Preset presets[] = {  
   { "luke5;common", "tracks/venus.wav",
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Green,White>,AudioFlicker<Green,White>>,White>,300,800>>(),
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Green,White>,AudioFlicker<Green,White>>,White>,300,800>>(), "chungreen"},
   { "SmthJedi;common", "tracks/venus.wav",
    StylePtr<InOutHelper<EasyBlade<OnSpark<InOutTr<Azure,TrColorCycle<3000>,TrFade<500>,Green>>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<OnSpark<InOutTr<Azure,TrColorCycle<3000>,TrFade<500>,Green>>,White>,300,800>>(), "greenflash"},
   { "Graflex;common", "tracks/venus.wav",
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Blue,White>,AudioFlicker<Blue,White>>,White>,300,800>>(),
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Blue,White>,AudioFlicker<Blue,White>>,White>,300,800>>(), "chunblue"},
   { "QGJ;common", "tracks/venus.wav",
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Green,White>,AudioFlicker<Green,White>>,White>,300,800>>(),
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Green,White>,AudioFlicker<Green,White>>,White>,300,800>>(), "chungreen"},
   { "SmthGrey;common", "tracks/mercury.wav",
    StylePtr<InOutHelper<EasyBlade<OnSpark<GhostWhite,Black>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<OnSpark<GhostWhite,Black>,White>,300,800>>(),"white1"},
   { "AhsokaTM;common", "tracks/mars.wav",
    StylePtr<InOutHelper<EasyBlade<OnSpark<BrownNoiseFlicker<Snow,Blue,50>>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<OnSpark<BrownNoiseFlicker<Snow,Blue,50>>,White>,300,800>>(), "snowblue"},
   { "luke;common", "tracks/venus.wav",
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Cyan,White>,AudioFlicker<Blue,White>>,White>,400,800>>(),
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Cyan,White>,AudioFlicker<Blue,White>>,White>,400,800>>(), "Cyan"},
   { "Vader;common", "tracks/mars.wav",
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Red,White>,AudioFlicker<Red,White>>,White>,400,800>>(),
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Red,White>,AudioFlicker<Red,White>>,White>,400,800>>(), "chunRed"},
   { "SmthFuzz;common", "tracks/uranus.wav",
    StyleFirePtr<Red,Yellow>(),
    StyleFirePtr<Red,Yellow>(), "fire"},
   { "Windu;common", "tracks/uranus.wav",
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Magenta,White>,AudioFlicker<Blue,White>>,White>,300,800>>(),
    StylePtr<InOutHelper<SimpleClash<Lockup<Blast<Magenta,White>,AudioFlicker<Blue,White>>,White>,300,800>>(), "chunzise"},
   { "DV3;common", "tracks/mars.wav",
    StyleFirePtr<RandomBlink<3,Red,Red>,Yellow,1,0,10>(),
    StyleFirePtr<RandomBlink<3,Red,Red>,Yellow,1,0,10>(), "KYLO"},
   { "luke5;common", "tracks/venus.wav",
    StylePtr<InOutHelper<RandomPerLEDFlicker<Pulsing<Blue,InOutHelper<White,300,800>,800>,Blue>,300,800>>(),
    StylePtr<InOutHelper<RandomPerLEDFlicker<Pulsing<Blue,InOutHelper<White,300,800>,800>,Blue>,300,800>>(), "BLUEFLASH"},
   { "TthCrstl;common", "tracks/venus.wav",
    StylePtr<InOutHelper<EasyBlade<OnSpark<Sparkle<HotPink,Yellow>>,GreenYellow>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<OnSpark<Sparkle<HotPink,Yellow>>,GreenYellow>,300,800>>(), "PINK"},
   { "Fire;common", "tracks/mars.wav",
    StylePtr<InOutHelper<EasyBlade<OnSpark<Gradient<Cylon<Red,5,20,Red,30,20,1>,GhostWhite,Cylon<Red,5,20,Red,5,20,1>>>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<OnSpark<Gradient<Cylon<Red,5,20,Red,30,20,1>,GhostWhite,Cylon<Red,5,20,Red,5,20,1>>>,White>,300,800>>(), "Cylonwhite"},
   { "TeensySF;common", "tracks/mars.wav",
    StylePtr<InOutHelper<EasyBlade<Stripes<1000,1000,Cyan,Magenta,Yellow,Blue>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<Stripes<1000,1000,Cyan,Magenta,Yellow,Blue>,White>,300,800>>(), "rainbow"},
   { "RgueCmdr;common", "tracks/venus.wav",
    StylePtr<InOutHelper<EasyBlade<OnSpark<TransitionLoop<Red,TrConcat<TrFade<1000>,GreenYellow,TrFade<200>>>>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<OnSpark<TransitionLoop<Red,TrConcat<TrFade<1000>,GreenYellow,TrFade<200>>>>,White>,300,800>>(), "CC"},
   { "TeenysSF;common", "tracks/mars.wav",
    StylePtr<InOutHelper<EasyBlade<OnSpark<HumpFlicker<Green,Magenta,50>>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<OnSpark<HumpFlicker<Green,Magenta,50>>,White>,300,800>>(), "EE"},
   { "luke4;common", "tracks/mars.wav",
    StylePtr<InOutHelper<EasyBlade<OnSpark<Gradient<Blue,AudioFlicker<White,Blue>,Red,RandomFlicker<Yellow,Blue>>>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<OnSpark<Gradient<Blue,AudioFlicker<White,Blue>,Red,RandomFlicker<Yellow,Blue>>>,White>,300,800>>(), "KK"},
   { "Rey;common", "tracks/mars.wav",
    StylePtr<InOutHelper<EasyBlade<Sparkle<OrangeRed>,White>,300,800>>(),
    StylePtr<InOutHelper<EasyBlade<Sparkle<OrangeRed>,White>,300,800>>(), "sparkstar"},
   { "Vortex;common", "tracks/uranus.wav",
    StylePtr<Layers<StyleFire<Stripes<2500,-5000,BrownNoiseFlicker<RotateColorsX<Variation,Rgb<255,0,0>>,Black,20>,RotateColorsX<Variation,Rgb<4,0,8>>,
    BrownNoiseFlicker<Black,RotateColorsX<Variation,Rgb<115,15,220>>,70>,RotateColorsX<Variation,Rgb<42,0,105>>>,RotateColorsX<Variation,Rgb<30,0,66>>,0,5,FireConfig<2,3000,0>,FireConfig<2,3000,0>,
    FireConfig<2,3000,0>,FireConfig<2,3000,0>>,AlphaL<Stripes<2500,-3000,Red,Rgb<60,0,0>,Pulsing<Rgb<30,0,0>,Black,800>>,SwingSpeed<600>>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,
    Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,
    Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrJoinR<TrWipe<100>,TrWipeIn<100>>,White,TrJoinR<TrWipe<100>,TrWipeIn<100>>>,
    SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,
    HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,SparkleL<White,100,400>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,
    ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
    TransitionEffectL<TrConcat<TrInstant,AudioFlickerL<White>,TrFade<800>>,EFFECT_IGNITION>,TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,40>,TrFade<1000>>,
    EFFECT_RETRACTION>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,
    SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrConcat<TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<400>,Int<300>,Int<400>,Int<32768>>,
    Mix<SmoothStep<Int<5500>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<350>,Int<300>,Int<350>,Int<32768>>,Mix<SmoothStep<Int<11000>,Int<-2000>>,
    Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<300>,Int<300>,Int<300>,Int<32768>>,Mix<SmoothStep<Int<16500>,Int<-2000>>,
    Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<250>,Int<300>,Int<250>,Int<32768>>,Mix<SmoothStep<Int<22000>,Int<-2000>>,
    Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<200>,Int<300>,Int<200>,Int<32768>>,Mix<SmoothStep<Int<27500>,Int<-2000>>,
    Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWipeIn<200>,Mix<SmoothStep<Int<33000>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrFade<300>>,
    TrConcat<TrWipe<200>,Mix<SmoothStep<Int<27500>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<200>,Int<300>,Int<200>,Int<0>>,
    Mix<SmoothStep<Int<22000>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<250>,Int<300>,Int<250>,Int<0>>,
    Mix<SmoothStep<Int<16500>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<300>,Int<300>,Int<300>,Int<0>>,
    Mix<SmoothStep<Int<11000>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<350>,Int<300>,Int<350>,Int<0>>,
    Mix<SmoothStep<Int<5500>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<400>,Int<300>,Int<400>,Int<0>>,Black,
    TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<400>,Int<300>,Int<400>,Int<0>>,Black,TrInstant>,Black>,TransitionEffectL<TrConcat<TrInstant,AlphaL<White,Bump<Int<0>,Int<10000>>>,TrFade<3000>,
    AlphaL<Orange,Bump<Int<0>,Int<8000>>>,TrFade<3000>,AlphaL<Red,Bump<Int<0>,Int<6000>>>,TrFade<2000>>,EFFECT_RETRACTION>,TransitionEffectL<TrConcat<TrFade<2000>,
    AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<255,0,0>>,10>,Bump<Int<0>,Int<4000>>>,TrFade<2950>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<255,0,0>>,15>,Bump<Int<0>,Int<5000>>>,TrFade<3000>,
    AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<255,0,0>>,20>,Bump<Int<0>,Int<6000>>>,TrBoing<1000,3>>,EFFECT_PREON>>>(),
    StylePtr<Layers<StyleFire<Stripes<2500,-5000,BrownNoiseFlicker<RotateColorsX<Variation,Rgb<255,0,0>>,Black,20>,RotateColorsX<Variation,Rgb<4,0,8>>,
    BrownNoiseFlicker<Black,RotateColorsX<Variation,Rgb<115,15,220>>,70>,RotateColorsX<Variation,Rgb<42,0,105>>>,RotateColorsX<Variation,Rgb<30,0,66>>,0,5,FireConfig<2,3000,0>,FireConfig<2,3000,0>,
    FireConfig<2,3000,0>,FireConfig<2,3000,0>>,AlphaL<Stripes<2500,-3000,Red,Rgb<60,0,0>,Pulsing<Rgb<30,0,0>,Black,800>>,SwingSpeed<600>>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,
    Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,
    Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrJoinR<TrWipe<100>,TrWipeIn<100>>,White,TrJoinR<TrWipe<100>,TrWipeIn<100>>>,
    SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,
    HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,SparkleL<White,100,400>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,
    ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
    TransitionEffectL<TrConcat<TrInstant,AudioFlickerL<White>,TrFade<800>>,EFFECT_IGNITION>,TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,40>,TrFade<1000>>,
    EFFECT_RETRACTION>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,
    SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrConcat<TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<400>,Int<300>,Int<400>,Int<32768>>,
    Mix<SmoothStep<Int<5500>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<350>,Int<300>,Int<350>,Int<32768>>,Mix<SmoothStep<Int<11000>,Int<-2000>>,
    Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<300>,Int<300>,Int<300>,Int<32768>>,Mix<SmoothStep<Int<16500>,Int<-2000>>,
    Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<250>,Int<300>,Int<250>,Int<32768>>,Mix<SmoothStep<Int<22000>,Int<-2000>>,
    Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<200>,Int<300>,Int<200>,Int<32768>>,Mix<SmoothStep<Int<27500>,Int<-2000>>,
    Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWipeIn<200>,Mix<SmoothStep<Int<33000>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrFade<300>>,
    TrConcat<TrWipe<200>,Mix<SmoothStep<Int<27500>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<200>,Int<300>,Int<200>,Int<0>>,
    Mix<SmoothStep<Int<22000>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<250>,Int<300>,Int<250>,Int<0>>,
    Mix<SmoothStep<Int<16500>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<300>,Int<300>,Int<300>,Int<0>>,
    Mix<SmoothStep<Int<11000>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<350>,Int<300>,Int<350>,Int<0>>,
    Mix<SmoothStep<Int<5500>,Int<-2000>>,Black,RotateColorsX<Variation,Rgb<255,0,0>>>,TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<400>,Int<300>,Int<400>,Int<0>>,Black,
    TrWaveX<RotateColorsX<Variation,Rgb<255,0,0>>,Int<400>,Int<300>,Int<400>,Int<0>>,Black,TrInstant>,Black>,TransitionEffectL<TrConcat<TrInstant,AlphaL<White,Bump<Int<0>,Int<10000>>>,TrFade<3000>,
    AlphaL<Orange,Bump<Int<0>,Int<8000>>>,TrFade<3000>,AlphaL<Red,Bump<Int<0>,Int<6000>>>,TrFade<2000>>,EFFECT_RETRACTION>,TransitionEffectL<TrConcat<TrFade<2000>,
    AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<255,0,0>>,10>,Bump<Int<0>,Int<4000>>>,TrFade<2950>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<255,0,0>>,15>,Bump<Int<0>,Int<5000>>>,TrFade<3000>,
    AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<255,0,0>>,20>,Bump<Int<0>,Int<6000>>>,TrBoing<1000,3>>,EFFECT_PREON>>>(),"tsb"},
};

BladeConfig blades[] = {
 { 0, WS281XBladePtr<128, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),
    WS281XBladePtr<30, blade2Pin, Color8::GRB, PowerPINS<bladePowerPin4, bladePowerPin5> >()
  , CONFIGARRAY(presets) },
};
#endif

#ifdef CONFIG_BUTTONS
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
#endif
