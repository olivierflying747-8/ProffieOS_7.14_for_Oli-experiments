// ProffieOS7.14 Config File
#ifdef CONFIG_TOP
#include "proffieboard_v3_config.h"
//PROFFIECONFIG ENABLE_MASS_STORAGE
//PROFFIECONFIG ENABLE_WEBUSB

// == Blade ==

#define NUM_BLADES 4
const unsigned int maxLedsPerStrip = 144;
#define ENABLE_MOTION
#define ENABLE_WS2811
#define SHARED_POWER_PINS
#define BLADE_DETECT_PIN blade5Pin

// == Bluetooth/RFID ==

#define ENABLE_SERIAL
#define BLE_PASSWORD "66"                    //Because why not !
#define BLE_NAME "oli_chassi"
#define BLE_SHORTNAME "olisaber"
//#define RFID_SERIAL Serial3

// == OLED ==

#define INCLUDE_SSD1306
//#define ENABLE_SSD1306
//#define OLED_FLIP_180
//#define OLED_MIRRORED
//#define ENABLE_SPIDISPLAY                  //"For the color screen", see "CONFIG_BOTTOM" (in my notes)
#define USE_AUREBESH_FONT 

// == Time Outs == (milisec * sec * min)     //max value 2147483647 (= +/- 25 days)

#define PLI_OFF_TIME 1000 * 60 * 1          
#define IDLE_OFF_TIME 1000 * 60 * 20
#define MOTION_TIMEOUT 1000 * 60 * 15

// == Memory / Save Memory ==

#define DISABLE_DIAGNOSTIC_COMMANDS
//#define ENABLE_DEBUG
//#define DISABLE_BASIC_PARSER_STYLES
#define KILL_OLD_PLAYERS
//#define DISABLE_TALKIE

// == Buttons ==

#define NUM_BUTTONS 2
#define FETT263_HOLD_BUTTON_OFF
#define FETT263_POWER_LOCK
#define FETT263_MOTION_WAKE_POWER_BUTTON
#define FETT263_BM_DISABLE_OFF_BUTTON

// == Editing ==

#define ENABLE_ALL_EDIT_OPTIONS
#define FETT263_EDIT_MODE_MENU
#define KEEP_SAVEFILES_WHEN_PROGRAMMING
#define FETT263_CIRCULAR_DIM_MENU
#define SAVE_STATE
//#define FETT263_SAVE_CHOREOGRAPHY
#define FETT263_QUICK_SELECT_ON_BOOT
#define FETT263_MULTI_PHASE
//#define FETT263_DISABLE_CHANGE_FONT
//#define FETT263_DISABLE_CHANGE_STYLE
//#define FETT263_DISABLE_COPY_PRESET

// == Sound/Volume/Audio ==

#define ENABLE_AUDIO
#define VOLUME 1000
#define BOOT_VOLUME 300
//#define AUDIO_CLASH_SUPPRESSION_LEVEL 10
//#define FILTER_CUTOFF_FREQUENCY 200
//#define FILTER_ORDER 8
#define CLASH_THRESHOLD_G 4.0     //was 2.0
#define FEMALE_TALKIE_VOICE
#define FETT263_DUAL_MODE_SOUND
#define FETT263_CLASH_STRENGTH_SOUND
#define FETT263_SAY_COLOR_LIST
#define FETT263_SAY_COLOR_LIST_CC
//#define FETT263_SAY_BATTERY_PERCENT
#define FETT263_BC_SAY_BATTERY_VOLTS_PERCENT
#define FETT263_CIRCULAR_VOLUME_MENU
#define FETT263_TRACK_PLAYER_NO_PROMPTS
#define FETT263_QUOTE_PLAYER_START_ON
#define FETT263_BM_CLASH_DETECT 4.0
#define FETT263_RANDOMIZE_QUOTE_PLAYER
#define NO_REPEAT_RANDOM

//  == Colors ==

#define COLOR_CHANGE_DIRECT
#define EXTRA_COLOR_BUFFER_SPACE 60

// == BATTLE MODE OPTIONS == Battle Mode is enabled via controls by default in this prop

//#define FETT263_BATTLE_MODE_START_ON
//#define FETT263_MAX_CLASH 1276800
//#define FETT263_SPIN_MODE                  //Cannot be used with FETT263_SAVE_CHOREOGRAPHY or FETT263_HOLD_BUTTON_LOCKUP
#define FETT263_USE_BC_MELT_STAB
#define FETT263_LOCKUP_DELAY 1500

// == Swing On == Gesture Ignition via Swing

#define FETT263_SWING_ON_PREON
#define FETT263_SWING_ON_NO_BM
#define FETT263_SWING_ON_SPEED 250           //Swing Speed required for Ignition 250 ~ 500 recommended

// == Twist On == Gesture Ignition via Twist (back and forth)

#define FETT263_TWIST_ON

// == Stab On == Gesture Ignition via Stab (linear movement + clash at tip of blade)

//#define FETT263_STAB_ON
#define FETT263_STAB_ON_PREON

// == Thrust On == Gesture Ignition via Thrust (linear movement)

#define FETT263_THRUST_ON

// == Gesture Sleep == Toggle Gesture Ignition and Retraction detection to disable or enable gesture options

#define FETT263_SAVE_GESTURE_OFF

// == Force Push == Push movement triggers push.wav (or force.wav if push.wav is not present)

#define FETT263_FORCE_PUSH_ALWAYS_ON
#define FETT263_FORCE_PUSH_LENGTH 5          //Recommended range 1 ~ 10, 1 = shortest, easiest to trigger, 10 = longest

// == Bullets for Blaster Mode ==

#define BLASTER_SHOTS_UNTIL_EMPTY 20         //Not defined = unlimited shots.
#define BLASTER_JAM_PERCENTAGE 10            //0 = NO JAM
#define BLASTER_ENABLE_AUTO
#define BLASTER_DEFAULT_MODE MODE_STUN       //MODE_STUN|MODE_KILL|MODE_AUTO.

// == BC define's ==

/*
---------------------------------------------------------------------------
Optional #defines:
#define ENABLE_AUTO_SWING_BLAST  // - Multi-blast initiated by simply swinging
                                 //   within 1 second of last blast.
                                 //   Exit by not swinging for 1 second.
#define NO_VOLUME_MENU           // - Option to omit On-the-fly Volume menu control with buttons.
---------------------------------------------------------------------------
Gesture Controls:
#define BC_SWING_ON
#define BC_STAB_ON
#define BC_THRUST_ON
#define BC_TWIST_ON
#define BC_TWIST_OFF
#define NO_BLADE_NO_GEST_ONOFF
#define BC_FORCE_PUSH
#define BC_FORCE_PUSH_LENGTH 5               //1 = shortest, easiest to trigger, 10 = longest. Default value is 5.
#define BC_NO_BM
#define BC_GESTURE_AUTO_BATTLE_MODE          //Cannot be used if #define BC_NO_BM is active.
#define BC_LOCKUP_DELAY 200
*/
   // Added in "../common/saber_base.h" on line 105 to 106
   // BC Blaster prop effect (added by oli)
   // DEFINE_EFFECT(DESTRUCT) // <-- This define needs to be added to "../common/saber_base.h"
                              // in order for blaster_BC_buttons.h to work (08 September 2024)
                              // But it might become "stock" in the future ?
#endif // CONFIG_TOP

#ifdef CONFIG_PROP
//#include "../props/dual_prop.h"               //use SaberBlasterProp <Saber*, Blaster*> "in PROP_TYPE"
#include "../props/multi_prop.h"                //use MultiProp <Saber*, Blaster*, Detonator, Jetpack, MorseCode>
                                                // (* choose only 1 saber & 1 blaster)
//#include "../props/saber_caiwyn_buttons.h"    //use CaiwynButtons   <-- works alone   | NOT compiling with multi_prop.h
//#include "../props/saber.h"                   //use Saber                | compiling with multi_prop.h
//#include "../props/saber_BC_buttons.h"        //use SaberBCButtons       | compiling with multi_prop.h
#include "../props/saber_fett263_buttons.h"     //use SaberFett263Buttons  | compiling with multi_prop.h
//#include "../props/saber_sa22c_buttons.h"     //use SaberSA22CButtons    | compiling with multi_prop.h
//#include "../props/saber_shtok_buttons.h"     //use SaberShtokButtons    | compiling with multi_prop.h
//#include "../props/blaster.h"                 //use Blaster              | compiling with multi_prop.h (works with or without "bullet count")

// IMPORTANT NOTE: blaster_BC_buttons.h (at the time of writing) is not "stock" compatible with multi_prop.h
// A small modification needs to be added to it's code. I will let NoSloppy decide for the best course of action
// to modify his prop. I do have "my version" of blaster_BC_buttons.h working, so it is possible.

//These 4 EFFECT need to be here before #include "../props/blaster_BC_buttons.h" or it will not compile with multi_prop.h
//=======================================================================================================================
#if !defined(PROPS_SABER_BC_BUTTONS_H)
EFFECT(volup);      // for increse volume
EFFECT(voldown);    // for decrease volume
EFFECT(volmin);     // for minimum volume reached
EFFECT(volmax);     // for maximum volume reached
#endif
#include "../props/blaster_BC_buttons.h"        //use BlasterBC              | compiling with multi_prop.h
#include "../props/detonator.h"                 //use Detonator              | compiling with multi_prop.h
#include "../props/jetpack_prop.h"              //use Jetpack                | compiling with multi_prop.h (V-30?)
#include "../props/morsecode_prop_blank.h"            //use MorseCode - In progress (type morse code on the buttons & it plays on LEDs, speaker & OLED)
//#include "../props/droids_prop.h"             //In progress (plays with droids sounds)
//#include "../props/vehicle_prop.h"            //To be created (find better name - plays with SW vehicles sounds and their weapons - ships, speeders, walkers, pod-racers, ...)
#undef PROP_TYPE
//#define PROP_TYPE Detonator            // To test it alone (but desable "Bullet Counts" first)
#define PROP_TYPE MultiProp <SaberFett263Buttons, BlasterBC, Detonator, Jetpack, MorseCode>
                  //Attempt 025 is one Saber + one Blaster     //, Droid, Tron
                  //SaberFett263Buttons, BlasterBC, Detonator & "../common/saber_base.h" are all modified by Oli
                  //Attempt 028 is one Saber + one Blaster + Detonater & sound effects
                  //Attempt 029 is sound effects & one Saber + one Blaster + Detonater + Jetpack
                  //Attempt 030 is trying to fix/solve button mapping (for Blaster)
//#define PROP_TYPE SaberBlasterProp <SaberFett263Buttons, BlasterBC>
//#define PROP_TYPE SaberBlasterProp <SaberBCButtons, BlasterBC>
#endif // CONFIG_TOP

#ifdef CONFIG_PRESETS
Preset presets[] = {
   { "Crispity;common", "Crispity/tracks/track1.wav",
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),  "crispity" },
   { "TeensySF;common", "tracks/venus.wav",
    StyleNormalPtr<CYAN, WHITE, 300, 800>(),
 // Marble style from Proffezzorn
StylePtr<Mix<CircularSectionF<MarbleF<Int<-2000>,Int<40000>,Ifon<Int<827680>,Int<0>>,Int<1276800>>,ChangeSlowly<Ifon<Int<32768>,Int<3276>>,Int<2048>>>,Black,Mix<InOutFuncX<Int<2000>,Int<2000>>,Rgb<0,0,20>,Rgb<0,255,255>>>>(),
 // Marble style from Proffezzorn
StylePtr<Mix<CircularSectionF<MarbleF<Int<-2000>,Int<40000>,Ifon<Int<827680>,Int<0>>,Int<1276800>>,ChangeSlowly<Ifon<Int<32768>,Int<3276>>,Int<2048>>>,Black,Mix<InOutFuncX<Int<2000>,Int<2000>>,Rgb<0,0,20>,Rgb<0,255,255>>>>(),
    StyleNormalPtr<CYAN, WHITE, 300, 800>(), "cyan"},
   { "SmthJedi;common", "tracks/mars.wav",
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(), "blue"},
   { "SmthGrey;common", "tracks/mercury.wav",
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 1>(),
    StyleFirePtr<RED, YELLOW, 2>(),
    StyleFirePtr<RED, YELLOW, 3>(), "fire"},
   { "SmthFuzz;common", "tracks/uranus.wav",
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(), "red"},
   { "RgueCmdr;common", "tracks/venus.wav",
    StyleFirePtr<BLUE, CYAN, 0>(),
    StyleFirePtr<BLUE, CYAN, 1>(),
    StyleFirePtr<BLUE, CYAN, 2>(),
    StyleFirePtr<BLUE, CYAN, 3>(), "blue fire"},
   { "TthCrstl;common", "tracks/mars.wav",
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(), "green"},
   { "TeensySF;common", "tracks/mercury.wav",
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(), "white"},
   { "SmthJedi;common", "tracks/uranus.wav",
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(), "yellow"},
   { "SmthGrey;common", "tracks/venus.wav",
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(), "magenta"},
   { "SmthFuzz;common", "tracks/mars.wav",
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(), "gradient"},
   { "RgueCmdr;common", "tracks/mercury.wav",
    StyleRainbowPtr<300, 800>(),
    StyleRainbowPtr<300, 800>(),
    StyleRainbowPtr<300, 800>(),
    StyleRainbowPtr<300, 800>(), "rainbow"},
   { "TthCrstl;common", "tracks/uranus.wav",
    StyleStrobePtr<WHITE, Rainbow, 15, 300, 800>(),
    StyleStrobePtr<WHITE, Rainbow, 15, 300, 800>(),
    StyleStrobePtr<WHITE, Rainbow, 15, 300, 800>(),
    StyleStrobePtr<WHITE, Rainbow, 15, 300, 800>(), "strobe"},
   { "SmthJedi;common", "tracks/mars.wav",
    StylePtr<InOutHelperX<Gradient<Red,Orange,Yellow,Green,Green,Green,Green>, BatteryLevel>>(),
    &style_charging,
    StylePtr<InOutHelperX<Gradient<Red,Orange,Yellow,Green,Green,Green,Green>, BatteryLevel>>(),
    StyleNormalPtr<BLACK, BLACK, 300, 800>(), "battery\nlevel"},
/*
   { "TeensySF;common", "tracks/venus.wav",              //
    &style_pov,                                          //
    StyleNormalPtr<BLACK, BLACK, 300, 800>(),            // Disable this to save memory
    StyleNormalPtr<BLACK, BLACK, 300, 800>(),            //
    StyleNormalPtr<BLACK, BLACK, 300, 800>(), "pov"},    //
*/
/*
   { "SmthJedi;common", "tracks/mars.wav",               // Charging style but I have no charge port
    &style_charging,
    StyleNormalPtr<BLACK, BLACK, 300, 800>(),
    &style_charging,
    StyleNormalPtr<BLACK, BLACK, 300, 800>(), "battery\nlevel"},
*/
};

BladeConfig blades[] = {
 { 0, WS281XBladePtr<144, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),
    SubBladeWithStride(0, 15, 2, WS281XBladePtr<16, blade2Pin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >()),
    SubBladeWithStride(1, 15, 2, NULL),
    WS281XBladePtr<1, blade3Pin, Color8::GRB, PowerPINS<bladePowerPin1> >(),
    CONFIGARRAY(presets) },
};

//RFID_Command RFID_Commands[] = {
//  { 0x0000000C04ULL,    "change_preset", "0" },
//  { 0x09003A8CDCULL,    "change_preset", "1" },
//};

#endif // CONFIG_PRESETS

#ifdef CONFIG_BUTTONS
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
#endif // CONFIG_BUTTONS

#ifdef CONFIG_BOTTOM
    DisplayHelper<128, uint32_t,             //OLED additional features: "Bullet Counts"
    BaseLayerOp<StandardDisplayController>,
    ClearRectangleOp<10, 80, 8, 24>,
    WriteBulletCountOp<10, 20, 5> >
    display_controller;
    //IfImageOp<OP>       // <-- What do I need instead of <OP> ??? <OP> gives compile error !
    SSD1306Template<128, uint32_t> display(&display_controller);
#endif // CONFIG_BOTTOM

/*
Generated with Fett263 Config Helper v3.10d https://fett263.com/fett263-os7-config-helper.html
&
Build with ProffieConfig 1.6.9, created by Ryryog25.
The tool can be found here: https://github.com/ryryog25/ProffieConfig/wiki/ProffieConfig
ProffieConfig is an All-In-One utility for managing your Proffieboard.
                    //I can't wait for ProffieConfig 2.x, it seems it will be amazing !!!
*/


/*
++++++++++++++++++++++++++++
++++++++++++++++++++++++++++
+++ Bellow are my notes: +++
++++++++++++++++++++++++++++
++++++++++++++++++++++++++++

Documentation:
==============
https://pod.hubbe.net/
https://github.com/profezzorn
https://github.com/profezzorn/ProffieOSDocs
https://github.com/profezzorn/ProffieOS/wiki
https://fredrik.hubbe.net/lightsaber/style_editor_beta.html
https://www.fett263.com/index.html
https://www.fett263.com/proffieOS7-fett263-prop-file.html
https://www.fett263.com/fett263-os7-config-helper.html
https://github.com/NoSloppy/SoundFontNamingConverter
https://therebelarmory.com/board/97/profezzorns-lab
https://therebelarmory.com/thread/11354/welcome-profezzorns-lab
                                            
(note for self) I am using /"*" ... "*"/ instead of /asterix ... asterix/ to avoid re-activating the code (asterix = *)

#ifdef CONFIG_TOP                            // https://pod.hubbe.net/config/the-config_top-section.html
#include "proffieboard_v3_config.h"
//PROFFIECONFIG ENABLE_MASS_STORAGE          //Do not remove the "//" 
//PROFFIECONFIG ENABLE_WEBUSB                //This is a ProfieConfig setting from @Ryryog25 (Ryan ) program.
                                             //==============================================================
                                             //It can also work as a reminder to turn it on in Arduino (if you wish)
                                             //=====================================================================

// == Blade ==

#define NUM_BLADES 4                         //I have: Main blade + NPXL connector (2 SubBlades) + Crystal chamber
const unsigned int maxLedsPerStrip = 144;    //144 per meter, only change the number if more than 144/m !
#define ENABLE_MOTION
#define ENABLE_WS2811
#define SHARED_POWER_PINS
#define BLADE_DETECT_PIN blade5Pin

// == Bluetooth/RFID ==

#define ENABLE_SERIAL                        //Don't use "Serial + Mass Storage" if not neccessary. (To save memory)
                                             //Serial port can be used to talk to a BLE chip. I use BT909 so do not comment out #define ENABLE_SERIAL, unless absolutely necessary!
#define BLE_PASSWORD "66"                    //Max 20 characters
#define BLE_NAME "oli_chassi"                //Max 32 characters
#define BLE_SHORTNAME "olisaber"             //Max 9 characters
//#define RFID_SERIAL Serial3                //Add an RFID reader. To configure, you will need an RFID_Commands array in the CONFIG_PRESETS section.

// == OLED ==
                                             // https://github.com/profezzorn/ProffieOS/blob/6173b290d05a2b90ada6e00c6ebb6f9362963567/display/ssd1306.h#L24
#define INCLUDE_SSD1306                      //INCLUDE instead of ENABLE to make it work for "Bullet Counts" from CONFIG_BOTTOM
//#define ENABLE_SSD1306                     //To activate OLED <-- What does "activate" mean ?
                                             // @profezzorn "Yes, it might not be super obvious because of the wonky C++ syntax, 
                                             //but this creates two global objects, one called display_controller and one called 
                                             //display. I split it up like this based on the idea that in the future, different 
                                             //presets could use different display controllers."

                                             //I still don't know if OLED will display "*.bmp" from font folders if 
                                             //"INCLUDE_SSD1306" is used instead of "ENABLE_SSD1306"

//#define OLED_FLIP_180                      //To flip the OLED displayed content 180 degrees.
//#define OLED_MIRRORED                      //Shows the OLED displayed content in reverse
//#define ENABLE_SPIDISPLAY                  //For the color screen (see "CONFIG_BOTTOM")
#define USE_AUREBESH_FONT                    //To see "presets" (or fonts - if presets are named by their font name) name 
                                             //in Aurabesh on OLED

// == Time Outs == (milisec * sec * min)     //max value is 2147483647 (= +/- 25 days)(24 days, 20 hours, 31 min, 23sec, 647 milisec)

#define PLI_OFF_TIME 1000 * 60 * 1           //Duration that Power Level Indicator will show on OLED when blade is turned off. Set for 10 seconds.
#define IDLE_OFF_TIME 1000 * 60 * 20         //Timeout for accent LEDs (in milliseconds), this example would set it to 20 minutes
                                             //This is when the MOSFETS (all 6 of them) turn off, so it’s not necessarily just accent LEDs.
#define MOTION_TIMEOUT 1000 * 60 * 15        //keeps motion chip active for 15 minutes while blade is Off

// == Board Orientation ==

/"*"
No need to include any "ORIENTATION" if orientation is default.
#define ORIENTATION_ROTATION 0,20,0       // X,Y,Z          //For Curved hilts, or where the board is not parallel with the blade.
                                                            //This will rotate the orientation of the board 20 degrees around the Y axis.
#define ORIENTATION ORIENTATION_FETS_TOWARDS_BLADE          //Default is USB connector points away from blade
#define ORIENTATION ORIENTATION_USB_TOWARDS_BLADE           // https://pod.hubbe.net/config/the-config_top-section.html#optional-defines
#define ORIENTATION ORIENTATION_USB_CCW_FROM_BLADE
#define ORIENTATION ORIENTATION_USB_CW_FROM_BLADE
#define ORIENTATION ORIENTATION_TOP_TOWARDS_BLADE
#define ORIENTATION ORIENTATION_BOTTOM_TOWARDS_BLADE
"*"/

// == Memory / Memory Save ==

#define DISABLE_DIAGNOSTIC_COMMANDS          //To save memory
                                             // https://pod.hubbe.net/tools/serial-monitor-commands.html
                                             // https://pod.hubbe.net/tools/serial-monitor-additional-commands.html
//#define ENABLE_DEBUG
//#define DISABLE_BASIC_PARSER_STYLES        //Memory Saving. This will disable the "named" legacy default styles to allow more room for your custom styles. Edit Mode styles replace these.
#define KILL_OLD_PLAYERS                     //The result is that the new sound always plays.
//#define DISABLE_TALKIE                     //To save memory, ProffieOS will use short melodies to indicate an error instead.
                                             // https://pod.hubbe.net/troubleshooting/beep_codes.html
                                             // https://pod.hubbe.net/troubleshooting/what-is-it-saying.html
                                             // https://github.com/profezzorn/ProffieOSDocs/blob/main/troubleshooting/status-led.md
//#define POV_INCLUDE_FILE "star_wars_logo_pov_data.h"       //Disable all "POV" entries to save memory
//Disable in == Bluetooth == #define ENABLE_SERIAL  //Don't use "Serial + Mass Storage" if not neccessary. (To save memory)
                                             //Serial port can be used to talk to a BLE chip. I use BT909 so do not disable SERIAL, 
                                             //unless absolutely necessary!
//#define ENABLE_DEVELOPER_COMMANDS          //Some commands (only useful for developers are normally not compiled), if you want them, add this define to enable them.

// == Buttons ==

#define NUM_BUTTONS 2
//#define DUAL_POWER_BUTTONS                 //The AUX will also turn the saber on. If not defined, AUX will go to next preset when off.
#define FETT263_HOLD_BUTTON_OFF              //Changes to Hold PWR to turn Off / Retract
//#define FETT263_HOLD_BUTTON_LOCKUP         //Enables Hold AUX for Lockup* Cannot be used with FETT263_SAVE_CHOREOGRAPHY
                                             //*Clash Strength / Clash Impact effects and sounds for Lockup negated
                                             //*Battle Mode control changes to hold AUX + Swing
#define FETT263_POWER_LOCK                   //enable Power Lock Mode to change 2 button Retraction from click PWR to
                                             //hold PWR & AUX (can be enabled/disabled in Edit Mode)
#define FETT263_MOTION_WAKE_POWER_BUTTON     //Enables a click on POWER Button to Wake Up Gestures after MOTION_TIMEOUT without igniting blade. Saber will play boot sound and gestures will be active.
#define FETT263_BM_DISABLE_OFF_BUTTON        //During Battle Mode Power Button Retraction is disabled
/"*"
#define BUTTON_DOUBLE_CLICK_TIMEOUT 500      //
#define BUTTON_SHORT_CLICK_TIMEOUT 500       //
#define BUTTON_HELD_TIMEOUT 300              //For overwriting value of buttons timeout (defined in "../buttons/button_base.h")
#define BUTTON_HELD_MEDIUM_TIMEOUT 800       //
#define BUTTON_HELD_LONG_TIMEOUT 2000        //
"*"/
#define BUTTON_HELD_X_LONG_TIMEOUT 4000      //For multi_prop.h
#ifndef TWO_BUTTONS_X_LONG_PUSH
#define TWO_BUTTONS_X_LONG_PUSH
#endif
// Define this if your power button is a touch button.
// #define POWER_TOUCHBUTTON_SENSITIVITY 1700
// #define AUX_TOUCHBUTTON_SENSITIVITY 1700
// #define AUX2_TOUCHBUTTON_SENSITIVITY 1700

// If your electonics inverts the bladePin for some reason, define this.
// #define INVERT_WS2811


// == Editing ==

#define ENABLE_ALL_EDIT_OPTIONS              //This will enable the components for Edit Mode used thorugh the Edit Mode Menu or ProffieOS Workbench (WebUSB).
/"*"
These are not needed since I use ENABLE_ALL_EDIT_OPTIONS
#define DYNAMIC_BLADE_DIMMING                //controllable from ProffieOS Workbench or some props.
#define DYNAMIC_BLADE_LENGTH                 //controllable from ProffieOS Workbench or some props.
#define DYNAMIC_CLASH_THRESHOLD              //controllable from ProffieOS Workbench or some props.
#define SAVE_BLADE_DIMMING
#define SAVE_CLASH_THRESHOLD
"*"/
#define FETT263_EDIT_MODE_MENU               //Enable Edit Mode Menu System *Requires ENABLE_ALL_EDIT_OPTIONS define
#define KEEP_SAVEFILES_WHEN_PROGRAMMING      // https://github.com/profezzorn/ProffieOSDocs/blob/main/config/keeping-edits-when-uploading.md    
//#defineFETT263_EDIT_SETTINGS_MENU          //Enable Edit Settings Menu (Volume, Clash Threshold, Blade Length, Gestures/Controls, Brightness)
                                             //I recommend setting USB Type = "Serial + WebUSB" under Arduino > Tools to allow for style, font, track, color editing via ProffieOS Workbench
                                             //Cannot be combined with FETT263_EDIT_MODE_MENU Requires ENABLE_ALL_EDIT_OPTIONS
#define FETT263_CIRCULAR_DIM_MENU            //Changes Brightness Menu to Circular Control
//#define DISABLE_COLOR_CHANGE
/"*"
These are not needed since I use SAVE_STATE
#define SAVE_COLOR_CHANGE                    //to save the color change state
#define SAVE_VOLUME                          //Start with the volume used last
#define SAVE_PRESET                          //Start at the last preset when you turn the saber on
"*"/
#define SAVE_STATE                           //to encompass SAVE_COLOR_CHANGE, SAVE_BLADE_DIMMING, SAVE_VOLUME and SAVE_PRESET 
//#define FETT263_SAVE_CHOREOGRAPHY          //Enables Enhanced Battle Mode with Saved Choreography
#define FETT263_QUICK_SELECT_ON_BOOT         //Enables Preset Selection Menu on Boot (when power is first applied)
                                             //Use Dial Menu to turn to desired preset, click PWR to select or hold PWR to select and ignite
//#define FETT263_SPECIAL_ABILITIES          //This enables 8 "Special Ability" controls (style controlled), 4 while ON, 4 while OFF.
                                             //Special Abilities are controlled by the style and can vary in every preset, they are "user" defined effects/capabilities.
                                             //Allows "Multi-Phase" to be style based, replaces FETT263_MULTI_PHASE.
                                             //Cannot be used with FETT263_MULTI_PHASE or FETT263_SAVE_CHOREOGRAPHY
/"*" "Special Abilities are user effects such as EFFECT_USER1 that a prop file can set to do anything, 
as opposed to like “EFFECT_CLASH” which would always be a clash.
By using the Fett263 Style Library, many different features and effects can be set to use them with 
a ton of flexibility in your blade styles created there." @NoSloppy "*"/
#define FETT263_MULTI_PHASE                  //enable a preset change while blade is ON to create a "Multi-Phase" saber effect

// == Sound/Volume/Audio ==

#define ENABLE_AUDIO
#define VOLUME 1000
#define BOOT_VOLUME 300
//#define AUDIO_CLASH_SUPPRESSION_LEVEL 10
//#define FILTER_CUTOFF_FREQUENCY 200
//#define FILTER_ORDER 8
#define CLASH_THRESHOLD_G 4.0     //was 2.0
#define FEMALE_TALKIE_VOICE                  //only affects built-in error messages
#define FETT263_DUAL_MODE_SOUND              //Enables odd/even out.wav ignition sound selection based on blade angle
                                             //Up = odd number sounds, Down = even numbered sounds
#define FETT263_CLASH_STRENGTH_SOUND         //Enables selection of clash, stab and lockup sounds based on clash strength
                                             //Light clash = 01.wav, Hard clash = highest number.wav
#define FETT263_SAY_COLOR_LIST               //Spoken Color Names replace default sounds during Color List Mode
#define FETT263_SAY_COLOR_LIST_CC            //Spoken Color Names replace default sounds during Color Change "CC" Color List Mode
//#define FETT263_SAY_BATTERY_PERCENT        //Spoken Battery Level percentage during On Demand Battery Level effect
#define FETT263_BC_SAY_BATTERY_VOLTS_PERCENT //Spoken Battery Level in volts and percent (point down for volts, parallel or up for percent)
#define FETT263_CIRCULAR_VOLUME_MENU         //Changes Volume Menu to Circular Control
#define FETT263_TRACK_PLAYER_NO_PROMPTS      //Disables spoken voice prompts in Track Player
//#define FETT263_DISABLE_QUOTE_PLAYER       //Disables Force/Quote player, only uses Force. This will allow Quotes to be controlled by style.
                                             //Use FETT263_SPECIAL_ABILITIES to set EFFECT_QUOTE or EFFECT_NEXT_QUOTE in style
                                             //Cannot be used with FETT263_RANDOMIZE_QUOTE_PLAYER and FETT263_QUOTE_PLAYER_START_ON
#define FETT263_QUOTE_PLAYER_START_ON        //This will set Force / Quote to play Quote by default (if in font)
#define FETT263_BM_CLASH_DETECT 4.0          //max value to use clashes in Battle Mode 2.0, clashes used on clash strength below this value
                                             //allows light clashes to produce clash effects instead of using Begin/End Lockup
                                             //(above this value Clash is performed by quick pull away using Begin/End Lockup sounds and effect)
                                             //Range 0 ~ 8 (note 0 will use Battle Mode 1.0 with all clashes being Begin/End Lockup)
#define FETT263_RANDOMIZE_QUOTE_PLAYER       //is specific to using the saber_fett263.buttons.h prop file, and deals with whether quote sound files are randomized or played sequentially. @NoSloppy
#define NO_REPEAT_RANDOM                     //is OS System level define that prevents the same effect file from playing back-to-back. @NoSloppy

//  == Colors ==

#define COLOR_CHANGE_DIRECT                  //This enables "Click to Change" capability for styles with ColorChange<>, used with Dual Phase Library styles and other specialty styles in my library. Does not affect normal styles or Edit Mode functionality
#define EXTRA_COLOR_BUFFER_SPACE 60          //is a define that can speed up processing a bit. Basically, it can calculate the colors for the next blade (or the next frame for the same blade) even though it’s not done feeding out the data for the data in the color buffer yet. It’s the equivalent of just increasing maxLedsPerStrip. @NoSloppy


// == BATTLE MODE OPTIONS == Battle Mode is enabled via controls by default in this prop

//#define FETT263_BATTLE_MODE_ALWAYS_ON      //Battle Mode is always on, toggle controls deactivated
                                             //This will disable traditional Clash and Stab effects (cannot be used with FETT263_BATTLE_MODE_START_ON)
//#define FETT263_BATTLE_MODE_START_ON       //Battle Mode is active with each ignition by default but can be toggled using Aux + Swing control
                                             //(cannot be used with FETT263_BATTLE_MODE_ALWAYS_ON)
//#define FETT263_MAX_CLASH 1276800          //optional define to set the hardest clash on saber range 8 ~ 16, defaults to 16 if not defined
//#define FETT263_SPIN_MODE                  //Enables toggle for "Spin" Mode* which disables all clash/stab/lockup effects to allow for spinning and flourishes.
                                             //Cannot be used with FETT263_SAVE_CHOREOGRAPHY or FETT263_HOLD_BUTTON_LOCKUP *Not the same as ENABLE_SPINS
#define FETT263_USE_BC_MELT_STAB             //Allows MELT to be gesture controlled full-time, uses Thrust for Stab effect

#define FETT263_LOCKUP_DELAY 1500            //"delay" in millis to determine Clash vs Lockup

// == Motion ==

//#define DISABLE_MOTION                     //ENABLE_MOTION is on by default in latest ProffieOS, to turn it off

// == Swing On == Gesture Ignition via Swing

//#define FETT263_SWING_ON                   //To enable Swing On Ignition control (automatically enters Battle Mode, uses Fast On)
#define FETT263_SWING_ON_PREON               //Disables Fast On ignition for Swing On so Preon is used (cannot be used with FETT263_SWING_ON)
#define FETT263_SWING_ON_NO_BM               //To enable Swing On Ignition control but not activate Battle Mode
                                             //(Combine with FETT263_SWING_ON or FETT263_SWING_ON_PREON,
                                             //cannot be used with FETT263_BATTLE_MODE_ALWAYS_ON or FETT263_BATTLE_MODE_START_ON)
#define FETT263_SWING_ON_SPEED 250           //Adjust Swing Speed required for Ignition 250 ~ 500 recommended

// == Twist Off == Gesture Retraction via Twist (back and forth)

//#define FETT263_TWIST_OFF                  //To enable Twist Off Retraction control <-- I don't like it.

// == Twist On == Gesture Ignition via Twist (back and forth)

#define FETT263_TWIST_ON                     //To enable Twist On Ignition control (automatically enters Battle Mode, uses Fast On)
//#define FETT263_TWIST_ON_PREON             //Disables Fast On ignition for Twist On so Preon is used (cannot be used with FETT263_TWIST_ON)
//#define FETT263_TWIST_ON_NO_BM             //To enable Twist On Ignition control but not activate Battle Mode
                                             //(Combine with FETT263_TWIST_ON or FETT263_TWIST_ON_PREON,
                                             //cannot be used with FETT263_BATTLE_MODE_ALWAYS_ON or FETT263_BATTLE_MODE_START_ON)

// == Stab On == Gesture Ignition via Stab (linear movement + clash at tip of blade)

//#define FETT263_STAB_ON                    //To enable Stab On Ignition control (automatically enters Battle Mode, uses Fast On)
#define FETT263_STAB_ON_PREON                //Disables Fast On ignition for Stab On so Preon is used (cannot be used with FETT263_STAB_ON)
//#define FETT263_STAB_ON_NO_BM              //To enable Stab On Ignition control but not activate Battle Mode
                                             //(Combine with FETT263_STAB_ON or FETT263_STAB_ON_PREON,
                                             //cannot be used with FETT263_BATTLE_MODE_ALWAYS_ON or FETT263_BATTLE_MODE_START_ON)

// == Thrust On == Gesture Ignition via Thrust (linear movement)

#define FETT263_THRUST_ON                    //To enable Thrust On Ignition control (automatically enters Battle Mode, uses Fast On)
//#define FETT263_THRUST_ON_PREON            //Disables Fast On ignition for Thrust On so Preon is used (cannot be used with FETT263_THRUST_ON)
//#define FETT263_THRUST_ON_NO_BM            //To enable Thrust On Ignition control but not activate Battle Mode
                                             //(Combine with FETT263_THRUST_ON or FETT263_THRUST_ON_PREON,
                                             //cannot be used with FETT263_BATTLE_MODE_ALWAYS_ON or FETT263_BATTLE_MODE_START_ON)

// == Gesture Sleep == Toggle Gesture Ignition and Retraction detection to disable or enable gesture options

#define FETT263_SAVE_GESTURE_OFF             //Save "Gesture Sleep" setting to turn gesture ignitions and retractions off on boot

// == Force Push == Push movement triggers push.wav (or force.wav if push.wav is not present)

//#define FETT263_FORCE_PUSH                 //To enable gesture controlled Force Push during Battle Mode (will use push.wav or force.wav if not present)
#define FETT263_FORCE_PUSH_ALWAYS_ON         //To enable gesture controlled Force Push full time (will use push.wav or force.wav if not present)
#define FETT263_FORCE_PUSH_LENGTH 5          //Allows for adjustment to Push gesture length in millis needed to trigger Force Push
                                             //Recommended range 1 ~ 10, 1 = shortest, easiest to trigger, 10 = longest

// == Blade ID (if ever needed) ==

/"*"
#define BLADE_ID_SCAN_MILLIS 1000            //To activate Blade ID constant monitoring
#define BLADE_ID_TIMES 1000                  // https://github.com/profezzorn/ProffieOSDocs/blob/main/howto/blade-id-constant-monitoring.md
#define ENABLE_POWER_FOR_ID PowerPINS<bladePowerPin1,bladePowerPin2,bladePowerPin3>
#define BLADE_ID_CLASS                       // https://github.com/profezzorn/ProffieOSDocs/blob/main/howto/blade-id.md
#define BLADE_ID_CLASS BridgedPullupBladeID<bladeIdentifyPin, BRIDGED_PIN>          //
                                                                                    //Chose one of:
#define BLADE_ID_CLASS ExternalPullupBladeID<bladeIdentifyPin, PULLUP_RESISTANCE>   //
"*"/

// == Bullets for Blaster Mode ==

#define BLASTER_SHOTS_UNTIL_EMPTY 20         //Whatever number. Not defined = unlimited shots.
#define BLASTER_JAM_PERCENTAGE 10            //If this is not defined, random from 0-100%.
                                             //@profezzorn :"A value of 0 is valid, and means zero percent chance of jamming."
#define BLASTER_ENABLE_AUTO                  //Enable Autofire/rapid fire mode.
#ifndef BLASTER_DEFAULT_MODE                 //MODE_STUN|MODE_KILL|MODE_AUTO.
#define BLASTER_DEFAULT_MODE MODE_KILL
#endif


// == More #define == that I found but have no idea what they do ???

// #define ENABLE_SNOOZE
// #define ENABLE_FASTLED                    // FASTLED is experimental and untested right now
// #define ENABLE_WATCHDOG
// #define ENABLE_SD                         //I think I read this is not needed anymore ???
// #define ENABLE_SERIALFLASH

// == Even More Obscure #define == that I found in the ProffieOS_7.14|Arduino_1.8.19 code

// #define ENABLE_DEBUG
// #define CLASH_RECORDER                    // Define this to record clashes to sd card as CSV files

// == More - More #define == that I found (in crossguard_config.h) but have no idea what they do ???

// #define FIRE1_SPEED 2                     // Fire speed, valid values are 1 - 10
// #define FIRE1_DELAY 800                   // How long to wait before firing up crossguards.
                                             // Each of these have three values: A, B, C
                                             // A = non-random intensity
                                             // B = random intensity
                                             // C = cooling
                                             // The first two control temperature, and as we add
                                             // A + rnd(B) to the base of the blade each animation frame.
                                             // The second controls how rapidly the fire cools down
// #define FIRE1_NORMAL 0, 1000, 2           // This is used during normal operation.
// #define FIRE1_CLASH  3000, 0, 0           // This is used when a clash occurs
// #define FIRE1_LOCKUP 0, 5000, 10          // This is used during lockup.
/"*" #define FIRE1PTR(NUM, DELAY) \          // Helper
  StyleFirePtr<RED, YELLOW, NUM, DELAY, FIRE1_SPEED, \
    FIRE1_NORMAL, FIRE1_CLASH, FIRE1_LOCKUP>()
"*"/

// == BC define's ==

---------------------------------------------------------------------------
Optional #defines:
#define ENABLE_AUTO_SWING_BLAST  // - Multi-blast initiated by simply swinging
                                 //   within 1 second of last blast.
                                 //   Exit by not swinging for 1 second.
#define NO_VOLUME_MENU           // - Option to omit On-the-fly Volume menu control with buttons.
---------------------------------------------------------------------------
Gesture Controls:
#define BC_SWING_ON
#define BC_STAB_ON
#define BC_THRUST_ON
#define BC_TWIST_ON
#define BC_TWIST_OFF
#define NO_BLADE_NO_GEST_ONOFF
#define BC_FORCE_PUSH
#define BC_FORCE_PUSH_LENGTH 5               //1 = shortest, easiest to trigger, 10 = longest. Default value is 5.
#define BC_NO_BM
#define BC_GESTURE_AUTO_BATTLE_MODE          //Cannot be used if #define BC_NO_BM is active.
#define BC_LOCKUP_DELAY 200

   // BC Blaster prop effect (added by oli in "../common/saber_base.h")
   DEFINE_EFFECT(DESTRUCT)

#endif // CONFIG_TOP

//How To: Back Up A Proffieboard             // https://github.com/profezzorn/ProffieOSDocs/blob/main/howto/how-to-back-up-a-proffieboard.md
//Workbench                                  // https://github.com/profezzorn/ProffieOSDocs/blob/main/tools/workbench.md
//Web-Bluetooth                              // https://profezzorn.github.io/lightsaber-web-bluetooth/app.html  (<-- Open in Chrome not Firefox)
//Web-USB                                    // https://fredrik.hubbe.net/lightsaber/webusb.html
                                             // https://pod.hubbe.net/troubleshooting/webusb.html

#ifdef CONFIG_PROP
//#include "../props/dual_prop.h"            // https://github.com/profezzorn/ProffieOSDocs/blob/main/props/using-dual_prop.h.md
#include "../props/multi_prop.h"
//#include "../props/saber.h"
#include "../props/saber_fett263_buttons.h"  // https://github.com/profezzorn/ProffieOS/blob/master/props/saber_fett263_buttons.h
//#include "../props/saber_BC_buttons.h"
#include "../props/blaster.h"                // https://github.com/profezzorn/ProffieOS/blob/master/props/blaster.h
//#include "../props/blaster_BC_buttons.h"   // https://github.com/NoSloppy/ProffieOS-1/blob/bea29101131f4b949baba0f5954edae493d15ceb/props/blaster_BC_buttons.h
#include "../props/detonator.h"              // https://github.com/profezzorn/ProffieOS/blob/master/props/detonator.h
//#include "../props/jetpack.h"              //To be created (in progress)
//#include "../props/droid_prop.h"           //To be created (play with droids sounds)
//#include "../props/morse_code_prop.h"      //To be created (do morse code on the button & play it on led & sound) (another of my crazy idea!)
//#include "../props/tron_prop.h"            //to be created for the Tron Motorcycle Stick/Disk "Thingy"
                                             //(Why ? Because I have a very wild imagination & it sounds fun!)
#undef PROP_TYPE
//#define PROP_TYPE MultiProp <SaberFett263Buttons, Blaster, Detonator, Jetpack> //
                                                         //, Droid, MorseCode Tron
#define PROP_TYPE SaberBlasterProp<SaberFett263Buttons, Blaster>
#endif // CONFIG_PROP

#ifdef CONFIG_PRESETS
Preset presets[] = {
   { "Crispity;common", "Crispity/tracks/track1.wav",
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),  "crispity" },
   { "TeensySF;common", "tracks/venus.wav",
    StyleNormalPtr<CYAN, WHITE, 300, 800>(),
 // Marble style from Proffezzorn
StylePtr<Mix<CircularSectionF<MarbleF<Int<-2000>,Int<40000>,Ifon<Int<827680>,Int<0>>,Int<1276800>>,ChangeSlowly<Ifon<Int<32768>,Int<3276>>,Int<2048>>>,Black,Mix<InOutFuncX<Int<2000>,Int<2000>>,Rgb<0,0,20>,Rgb<0,255,255>>>>(),
 // Marble style from Proffezzorn
StylePtr<Mix<CircularSectionF<MarbleF<Int<-2000>,Int<40000>,Ifon<Int<827680>,Int<0>>,Int<1276800>>,ChangeSlowly<Ifon<Int<32768>,Int<3276>>,Int<2048>>>,Black,Mix<InOutFuncX<Int<2000>,Int<2000>>,Rgb<0,0,20>,Rgb<0,255,255>>>>(),
    StyleNormalPtr<CYAN, WHITE, 300, 800>(), "cyan"},
//   { "TeensySF;common", "tracks/venus.wav",              //
//    &style_pov,                                          //
//    StyleNormalPtr<BLACK, BLACK, 300, 800>(),            // Disable this to save memory
//    StyleNormalPtr<BLACK, BLACK, 300, 800>(),            //
//    StyleNormalPtr<BLACK, BLACK, 300, 800>(), "pov"},    //
   { "SmthJedi;common", "tracks/mars.wav",
    &style_charging,
    StyleNormalPtr<BLACK, BLACK, 300, 800>(),
    &style_charging,
    StyleNormalPtr<BLACK, BLACK, 300, 800>(), "battery\nlevel"}
};
BladeConfig blades[] = {
 { 0, WS281XBladePtr<144, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),
    SubBladeWithStride(0, 15, 2, WS281XBladePtr<16, blade2Pin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >()),
    SubBladeWithStride(1, 15, 2, NULL),
    WS281XBladePtr<1, blade3Pin, Color8::GRB, PowerPINS<bladePowerPin1> >(),
    CONFIGARRAY(presets) },
};
//RFID_Command RFID_Commands[] = {                    //To investigate if this could be used as "using the force" like the 
//  { 0x0000000C04ULL,    "change_preset", "0" },     //magnetic activation ring for CFX board & what "hardware" would I need ? 
//  { 0x09003A8CDCULL,    "change_preset", "1" },     //(or as a whish for Proffie V8.x to add Magnetic Switch)
//};

#endif // CONFIG_PRESETS

#ifdef CONFIG_BUTTONS
                                             // There are currently three available button classes:
                                             // Button (standard momentary button)
                                             // TouchButton (similar to momentary button, but reacts to touch).
                                             // LatchingButton (on/off button, always controls ignition)
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
Button AuxButton(BUTTON_AUX, auxPin, "aux");
                //BUTTON_AUX2                // https://github.com/profezzorn/ProffieOSDocs/blob/main/config/the-config_buttons-section.md
                //BUTTON_UP                  //
                //BUTTON_DOWN                //
                //BUTTON_LEFT                //UP, DOWN, LEFT, RIGHT & SELECT could be defined if wanting to use a "Potentiometer"/"Joystick"
                //BUTTON_RIGHT               //
                //BUTTON_SELECT              //
#endif // CONFIG_BUTTONS

/"*"
#ifndef CONFIG_STYLES
using BatteryLevelStyle = InOutHelperX<Gradient<Red,Orange,Yellow,Green,Green,Green,Green>, BatteryLevel>; //"error: 'InOutHelperX' does not name a type" and does not compile
//more stuff can come here
#endif // CONFIG_STYLES
"*"/

#ifdef CONFIG_BOTTOM
    DisplayHelper<128, uint32_t,             //OLED additional features: "Bullet Counts" - Code needed to activate the display.
    BaseLayerOp<StandardDisplayController>,  // https://github.com/profezzorn/ProffieOSDocs/blob/main/display/bullet-counts.md
    ClearRectangleOp<10, 80, 8, 24>,         //
    WriteBulletCountOp<10, 20, 5> >          // https://github.com/profezzorn/ProffieOSDocs/blob/main/display/images-and-animations.md
    display_controller;
    /"*"1 oli"*"/IfImageOp<OP>     //I don't know what this means ???: "This executes OP if the base layer is showing an image, but not otherwise. 
                        //The idea is that you could have a bullet count that draws over images, but not messages and battery monitors."

    /"*"2 oli"*"/IfImageOp<OP>       // <-- What do I need instead of <OP> ???
                                        ==================================
      If uncommented, gives error:
        In file included from C:\Users\Olivier\Desktop\LightSabers\ProffieOS_7.14\ProffieOS_7.14.ino:1560:
        C:\Users\Olivier\Desktop\LightSabers\ProffieOS_7.14\config\olicomplex1.5.004_test_multi_prop.h:261:15: error: 'OP' was not declared in this scope
          261 |     IfImageOp<OP>
              |               ^~
        C:\Users\Olivier\Desktop\LightSabers\ProffieOS_7.14\config\olicomplex1.5.004_test_multi_prop.h:261:17: error: template argument 1 is invalid
          261 |     IfImageOp<OP>
              |                 ^
        C:\Users\Olivier\Desktop\LightSabers\ProffieOS_7.14\config\olicomplex1.5.004_test_multi_prop.h:262:36: error: invalid declarator before 'display'
          262 |     SSD1306Template<128, uint32_t> display(&display_controller);
              |                                    ^~~~~~~
        Using library Wire at version 1.0 in folder: C:\Users\Olivier\AppData\Local\Arduino15\packages\proffieboard\hardware\stm32l4\3.6\libraries\Wire 
        exit status 1
        Error compiling for board Proffieboard V3.                         


SSD1306Template<128, uint32_t> display(&display_controller);
#endif // CONFIG_BOTTOM

/"*"
// == Color Display ==
//In CONFIG_TOP, add: #define ENABLE_SPIDISPLAY

//In CONFIG_BOTTOM, add ONE of these (depending on display size):
SPIDisplay_DFRobot096<3> display;                                                                                           
StandarColorDisplayController<160, 80> display_controller(&display);                                                        

SPIDisplay_AdaFruit358<3> display;                                                                                          
StandarColorDisplayController<160, 128> display_controller(&display);                                                       

SPIDisplay_AdaFruit5206<3> display;                                                                                         
StandarColorDisplayController<280, 240> display_controller(&display);                                                       

SPIDisplay_AdaFruit4311<3> display;
StandarColorDisplayController<320, 240> display_controller(&display);
                                             // https://crucible.hubbe.net/t/color-display-progress/4429/84
                                             // https://github.com/profezzorn/ProffieColorImages
                                             // https://github.com/Cairon/ProffieColorImages
                                             // https://www.dfrobot.com/product-2445.html
                                             // https://github.com/Cairon/ProffieColorImages/tree/main/virtual_crystal_chamber/scene
                                             // https://www.youtube.com/watch?v=wcSiNcCtR2I
                                             // https://github.com/Cairon/ProffieColorImages/tree/main/virtual_crystal_chamber/images/effects
                                             //
                                             //For this to work, I need to have in Arduino IDE: Files, Preferences, Additional Boards Manager URLs:
                                             // https://profezzorn.github.io/arduino-proffieboard/package_proffieboard_index.json,https://profezzorn.github.io/arduino-proffieboard/package_proffieboard_experimental_index.json
                                             //The first one will let you install in Tools, Board: "your board", Board Manager..., 
                                             //Proffieboard V3.6.0 (at the time of writing)
                                             //The second one will let you install in Tools, Board: "your board", Board Manager..., 
                                             //Proffieboard Experimental V4.0.0 (at the time of writing)
                                             //using Arduino IDE 1.8.19 (at the time of writing)
                                             //
                                             //@prefezzorn "I suggest at least upgrading to 1.8.19 at the very least.
                                             //Soon, new versions of the arduino-proffieboard plugin will require the 2.x versions 
                                             //of arduino to download though, so it might be better to start using that now. 
                                             //(2.x was pretty bad in the beginning, but nowadays it tends to work quite well, 
                                             //even if the UI is still a bit confusing.)
                                             //
                                             //You can also use 2.x to install the arduino-proffieboard plugin and then use 1.8.19 
                                             //to do the actual compilation. I think you can have both 1.x and 2.x installed at the 
                                             //same time on all platforms."
"*"/
*/
