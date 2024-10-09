// ProffieOS7.14 Config File

/*
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
*/

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
#define BLE_PASSWORD "66"                    //Because why not ! Max 20 characters
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

// == Time Outs == (milisec * sec * min)     //max value 2147483647 (= +/- 25 days)(24 days, 20 hours, 31 min, 23sec, 647 milisec)

#define PLI_OFF_TIME 1000 * 60 * 1           //Duration that Power Level Indicator will show on OLED when blade is turned off. Set for 10 seconds.
#define IDLE_OFF_TIME 1000 * 60 * 20         //Timeout for accent LEDs (in milliseconds), this example would set it to 20 minutes
                                             //This is when the MOSFETS (all 6 of them) turn off, so it’s not necessarily just accent LEDs.
#define MOTION_TIMEOUT 1000 * 60 * 15        //keeps motion chip active for 15 minutes while blade is Off

// == Board Orientation ==

/*
No need to include any "ORIENTATION" if orientation is default.
#define ORIENTATION_ROTATION 0,20,0       // X,Y,Z          //For Curved hilts, or where the board is not parallel with the blade.
                                                            //This will rotate the orientation of the board 20 degrees around the Y axis.
#define ORIENTATION ORIENTATION_FETS_TOWARDS_BLADE          //Default is USB connector points away from blade
#define ORIENTATION ORIENTATION_USB_TOWARDS_BLADE           // https://pod.hubbe.net/config/the-config_top-section.html#optional-defines
#define ORIENTATION ORIENTATION_USB_CCW_FROM_BLADE
#define ORIENTATION ORIENTATION_USB_CW_FROM_BLADE
#define ORIENTATION ORIENTATION_TOP_TOWARDS_BLADE
#define ORIENTATION ORIENTATION_BOTTOM_TOWARDS_BLADE
*/

// == Memory / Save Memory ==

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
/*
#define BUTTON_DOUBLE_CLICK_TIMEOUT 500      //
#define BUTTON_SHORT_CLICK_TIMEOUT 500       //
#define BUTTON_HELD_TIMEOUT 300              //For overwriting value of buttons timeout (defined in "../buttons/button_base.h")
#define BUTTON_HELD_MEDIUM_TIMEOUT 800       //
#define BUTTON_HELD_LONG_TIMEOUT 2000        //
*/
//#define BUTTON_HELD_X_LONG_TIMEOUT 4000      //For multi_prop.h
// Define this if your power button is a touch button.
//#define POWER_TOUCHBUTTON_SENSITIVITY 1700
//#define AUX_TOUCHBUTTON_SENSITIVITY 1700
//#define AUX2_TOUCHBUTTON_SENSITIVITY 1700

// If your electonics inverts the bladePin for some reason, define this.
//#define INVERT_WS2811

// == Editing ==

#define ENABLE_ALL_EDIT_OPTIONS              //This will enable the components for Edit Mode used thorugh the Edit Mode Menu or ProffieOS Workbench (WebUSB).
/*
These are not needed since I use ENABLE_ALL_EDIT_OPTIONS
#define DYNAMIC_BLADE_DIMMING                //controllable from ProffieOS Workbench or some props.
#define DYNAMIC_BLADE_LENGTH                 //controllable from ProffieOS Workbench or some props.
#define DYNAMIC_CLASH_THRESHOLD              //controllable from ProffieOS Workbench or some props.
#define SAVE_BLADE_DIMMING
#define SAVE_CLASH_THRESHOLD
*/
#define FETT263_EDIT_MODE_MENU               //Enable Edit Mode Menu System *Requires ENABLE_ALL_EDIT_OPTIONS define
#define KEEP_SAVEFILES_WHEN_PROGRAMMING      // https://github.com/profezzorn/ProffieOSDocs/blob/main/config/keeping-edits-when-uploading.md    
//#defineFETT263_EDIT_SETTINGS_MENU          //Enable Edit Settings Menu (Volume, Clash Threshold, Blade Length, Gestures/Controls, Brightness)
                                             //I recommend setting USB Type = "Serial + WebUSB" under Arduino > Tools to allow for style, font, track, color editing via ProffieOS Workbench
                                             //Cannot be combined with FETT263_EDIT_MODE_MENU Requires ENABLE_ALL_EDIT_OPTIONS
#define FETT263_CIRCULAR_DIM_MENU            //Changes Brightness Menu to Circular Control
//#define DISABLE_COLOR_CHANGE
/*
These are not needed since I use SAVE_STATE
#define SAVE_COLOR_CHANGE                    //to save the color change state
#define SAVE_VOLUME                          //Start with the volume used last
#define SAVE_PRESET                          //Start at the last preset when you turn the saber on
*/
#define SAVE_STATE                           //to encompass SAVE_COLOR_CHANGE, SAVE_BLADE_DIMMING, SAVE_VOLUME and SAVE_PRESET 
//#define FETT263_SAVE_CHOREOGRAPHY          //Enables Enhanced Battle Mode with Saved Choreography
#define FETT263_QUICK_SELECT_ON_BOOT         //Enables Preset Selection Menu on Boot (when power is first applied)
                                             //Use Dial Menu to turn to desired preset, click PWR to select or hold PWR to select and ignite
//#define FETT263_SPECIAL_ABILITIES          //This enables 8 "Special Ability" controls (style controlled), 4 while ON, 4 while OFF.
                                             //Special Abilities are controlled by the style and can vary in every preset, they are "user" defined effects/capabilities.
                                             //Allows "Multi-Phase" to be style based, replaces FETT263_MULTI_PHASE.
                                             //Cannot be used with FETT263_MULTI_PHASE or FETT263_SAVE_CHOREOGRAPHY
/* "Special Abilities are user effects such as EFFECT_USER1 that a prop file can set to do anything, 
as opposed to like “EFFECT_CLASH” which would always be a clash.
By using the Fett263 Style Library, many different features and effects can be set to use them with 
a ton of flexibility in your blade styles created there." @NoSloppy */
#define FETT263_MULTI_PHASE                  //enable a preset change while blade is ON to create a "Multi-Phase" saber effect
//#define FETT263_DISABLE_CHANGE_FONT
//#define FETT263_DISABLE_CHANGE_STYLE
//#define FETT263_DISABLE_COPY_PRESET
//#define FETT263_DISABLE_MULTI_BLAST_TOGGLE

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
#define FETT263_SWING_ON_SPEED 250           //Swing Speed required for Ignition 250 ~ 500 recommended

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

/*
#define BLADE_ID_SCAN_MILLIS 1000            //To activate Blade ID constant monitoring
#define BLADE_ID_TIMES 1000                  // https://github.com/profezzorn/ProffieOSDocs/blob/main/howto/blade-id-constant-monitoring.md
#define ENABLE_POWER_FOR_ID PowerPINS<bladePowerPin1,bladePowerPin2,bladePowerPin3>
#define BLADE_ID_CLASS                       // https://github.com/profezzorn/ProffieOSDocs/blob/main/howto/blade-id.md
#define BLADE_ID_CLASS BridgedPullupBladeID<bladeIdentifyPin, BRIDGED_PIN>          //
                                                                                    //Chose one of:
#define BLADE_ID_CLASS ExternalPullupBladeID<bladeIdentifyPin, PULLUP_RESISTANCE>   //
*/

// == Bullets for Blaster Mode ==

#define BLASTER_SHOTS_UNTIL_EMPTY 20         //Not defined = unlimited shots.
#define BLASTER_JAM_PERCENTAGE 10            //0 = NO JAM. If this is not defined, random from 0-100%.
#define BLASTER_ENABLE_AUTO
#define BLASTER_DEFAULT_MODE MODE_STUN       //MODE_STUN|MODE_KILL|MODE_AUTO.
#define OLED_USE_BLASTER_IMAGES


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
/* #define FIRE1PTR(NUM, DELAY) \            // Helper
  StyleFirePtr<RED, YELLOW, NUM, DELAY, FIRE1_SPEED, \
    FIRE1_NORMAL, FIRE1_CLASH, FIRE1_LOCKUP>()
*/

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

//How To: Back Up A Proffieboard             // https://github.com/profezzorn/ProffieOSDocs/blob/main/howto/how-to-back-up-a-proffieboard.md
//Workbench                                  // https://github.com/profezzorn/ProffieOSDocs/blob/main/tools/workbench.md
//Web-Bluetooth                              // https://profezzorn.github.io/lightsaber-web-bluetooth/app.html  (<-- Open in Chrome not Firefox)
//Web-USB                                    // https://fredrik.hubbe.net/lightsaber/webusb.html
                                             // https://pod.hubbe.net/troubleshooting/webusb.html

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
/*
#if !defined(PROPS_SABER_BC_BUTTONS_H)
EFFECT(volup);      // for increse volume
EFFECT(voldown);    // for decrease volume
EFFECT(volmin);     // for minimum volume reached
EFFECT(volmax);     // for maximum volume reached
#endif
*/
#include "../props/blaster_BC_buttons.h"        //use BlasterBC              | compiling with multi_prop.h | Needs bullet count
#include "../props/detonator.h"                 //use Detonator              | compiling with multi_prop.h
#include "../props/jetpack_prop.h"              //use Jetpack                | compiling with multi_prop.h (V-30?)
#include "../props/morsecode_prop.h"            //use MorseCode              | compiling with multi_prop.h (type morse code on the buttons & it plays on OLED & speaker or LEDs)
//#include "../props/droids_prop.h"             //In progress - but very far from "ready" (plays with droids sounds)
//#include "../props/vehicle_prop.h"            //To be created (find better name - plays with SW vehicles sounds and their weapons - ships, speeders, walkers, pod-racers, ...)
#undef PROP_TYPE
#define PROP_TYPE MultiProp <SaberFett263Buttons, BlasterBC, Detonator, Jetpack, MorseCode>
                  //Attempt 025 is one Saber + one Blaster
                  //BlasterBC & "../common/saber_base.h" are modified by Oli
                  //Attempt 028 is one Saber + one Blaster + Detonater & sound effects
                  //Attempt 029 is one Saber + one Blaster + Detonater + Jetpack & sound effects
                  //Attempt 030 is trying to fix/solve button mapping (for Blaster)
                  //Version 035 is one Saber + one Blaster with buttons mapping + Detonator + Jetpack + MorseCode & sound effects
//#define PROP_TYPE SaberBlasterProp <SaberFett263Buttons, BlasterBC>
//#define PROP_TYPE SaberBlasterProp <SaberBCButtons, BlasterBC>
#endif // CONFIG_TOP

#ifdef CONFIG_PRESETS
Preset presets[] = {

   { "crispity;common", "tracks/track1.wav",
    //Theory2Button.h "F1Pod"
    StylePtr<Layers<Layers<AudioFlicker<RotateColorsX<Variation,HotPink>,RotateColorsX<BlinkingF<Int<1000>,Int<500>>,Rgb<50,0,150>>>,TransitionLoopL<TrWaveX<RandomPerLEDFlickerL<White>,Int<250>,Int<100>,Int<200>,Int<0>>>,TransitionLoopL<TrWaveX<StrobeL<White,Int<15>,Int<1>>,Int<350>,Int<100>,Int<300>,Int<0>>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red>,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,40>,TrFade<1000>>,EFFECT_RETRACTION>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipe<300>,TrColorCycle<1000>>>>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(), "crispity" },

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

   { "altereactor101;common", "tracks/track1.wav",
    //  Main Blade:
    StylePtr<Layers<Layers<ColorChange<TrInstant,DeepSkyBlue,Blue,Cyan,DodgerBlue,Green,Rgb<28,255,28>,Red,Magenta,Rgb<255,80,154>,Yellow,Orange,Rgb<185,212,212>>,RandomL<ColorChange<TrInstant,Rgb<0,107,205>,Rgb<0,0,205>,Rgb<0,205,205>,Rgb<0,60,205>,Rgb<0,205,0>,Rgb<22,205,22>,Rgb<205,0,0>,Rgb<205,0,205>,Rgb<205,62,115>,Rgb<205,205,0>,Rgb<205,79,0>,Rgb<178,205,205>>>>,TransitionEffectL<TrConcat<TrInstant,BrownNoiseFlickerL<AlphaL<White,Int<16000>>,Int<50>>,TrSmoothFade<600>>,EFFECT_LOCKUP_END>,LockupTrL<Strobe<White,Black,25,28>,TrConcat<TrInstant,White,TrFade<200>>,TrFade<300>,SaberBase::LOCKUP_NORMAL>,LockupTrL<AlphaL<White,LayerFunctions<Bump<Scale<SlowNoise<Int<2000>>,Int<3000>,Int<16000>>,Scale<BrownNoiseF<Int<10>>,Int<14000>,Int<8000>>>,Bump<Scale<SlowNoise<Int<2300>>,Int<26000>,Int<8000>>,Scale<NoisySoundLevel,Int<5000>,Int<10000>>>,Bump<Scale<SlowNoise<Int<2300>>,Int<20000>,Int<30000>>,Scale<IsLessThan<SlowNoise<Int<1500>>,Int<8000>>,Scale<NoisySoundLevel,Int<5000>,Int<0>>,Int<0>>>>>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,ResponsiveStabL<Red>,BlastL<LemonChiffon>,SimpleClashL<Strobe<Yellow,Black,25,28>,200>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,RandomFlicker<Red,Black>,RandomFlicker<Yellow,Red>>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipe<800>,TrWipeIn<1100>>,TransitionEffectL<TrConcat<TrWipe<1000>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<BatteryLevel,Int<-10>>>,TrDelay<2000>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<BatteryLevel,Int<-10>>>,TrWipeIn<1000>>,EFFECT_BATTERY_LEVEL>>>(),
    // NPXL inner ring:
    StyleFirePtr<RED, YELLOW, 0>(),
    // NPXL outer ring:
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    //  Crystal Chamber:
    StylePtr<Layers<Layers<ColorChange<TrInstant,DeepSkyBlue,Blue,Cyan,DodgerBlue,Green,Rgb<28,255,28>,Red,Magenta,Rgb<255,80,154>,Yellow,Orange,Azure>,RandomL<Black>>,BlastFadeoutL<ColorChange<TrInstant,Red,Red,Red,Red,Red,Red,LightYellow,Blue,Blue,Red,Blue,Red>>,LockupL<Strobe<ColorChange<TrInstant,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Rgb<200,255,255>,Yellow>,Black,20,16>,Strobe<ColorChange<TrInstant,White,White,White,White,White,White,White,White,White,Red,Rgb<200,255,255>,Red>,Black,20,16>>,SimpleClashL<Strobe<ColorChange<TrInstant,Yellow,Yellow,Yellow,Yellow,LemonChiffon,Red,Yellow,Yellow,Yellow,Cyan,White,Yellow>,Black,28,25>,260>,InOutHelperL<InOutFuncX<Int<700>,Int<1100>>,Pulsing<ColorChange<TrInstant,Rgb<0,68,125>,Rgb<0,0,125>,Rgb<0,125,125>,Rgb<0,35,125>,Rgb<0,125,0>,Rgb<14,125,14>,Rgb<125,0,0>,Rgb<125,0,125>,Rgb<125,40,77>,Rgb<125,125,0>,Rgb<125,48,0>,Rgb<110,125,125>>,Black,2800>>>>(),
    "altereactor"},

   {"analog;common", "tracks/track1.wav",
    // === Main Blade: ===
    StylePtr<Layers<
    AudioFlicker<RotateColorsX<Variation,Rgb16<0,38402,65535>>,RotateColorsX<Variation,Rgb<0,85,200>>>,
      //Ice blue audioflicker
    AlphaL<RotateColorsX<Variation,Rgb16<882,65535,31206>>,SwingSpeed<500>>,
      //Bright cyan color swing
    AlphaL<Stripes<2500,-4000,RotateColorsX<Variation,Rgb16<0,38402,65535>>,RotateColorsX<Variation,Rgb<0,26,60>>,Pulsing<RotateColorsX<Variation,Rgb<0,13,30>>,Black,800>>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,
      //Hard swing ripple effect
    LockupTrL<Layers<
    AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,
    AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<600>,AlphaL<Mix<SmoothStep<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<1000>>,Stripes<1500,2000,RotateColorsX<Variation,DeepSkyBlue>,RotateColorsX<Variation,Rgb16<0,65535,30086>>>,Stripes<1500,-2500,RotateColorsX<Variation,DeepSkyBlue>,RotateColorsX<Variation,Rgb16<0,65535,30086>>>>,Int<18000>>,TrFade<800>,AlphaL<Mix<SmoothStep<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<1000>>,Stripes<1500,1000,RotateColorsX<Variation,Rgb16<1514,65535,52727>>,RotateColorsX<Variation,Rgb16<3934,65535,38402>>>,Stripes<1500,-1250,RotateColorsX<Variation,Rgb16<1514,65535,52727>>,RotateColorsX<Variation,Rgb16<3934,65535,38402>>>>,Int<18000>>,TrFade<1100>>,SaberBase::LOCKUP_NORMAL>,
      //Responsive lockup with click calibration effect
      //AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<2100>>,SaberBase::LOCKUP_NORMAL>,
      //Alternate lockup ending with white fade out, replace the second AlphaL line above (ending in LOCKUP_NORMAL)
    ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,
      //Responsive lightning block
    AlphaL<RotateColorsX<Variation,Rgb16<0,65535,30086>>,SmoothStep<Scale<SlowNoise<Int<2300>>,Int<1200>,Int<4500>>,Int<-4000>>>,
      //Sparking emitter flare
    ResponsiveStabL<Red>,
      //Responsive stab
    EffectSequence<EFFECT_BLAST,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,LocalizedClashL<White,80,30,EFFECT_BLAST>,ResponsiveBlastWaveL<White,Scale<SwingSpeed<400>,Int<500>,Int<200>>,Scale<SwingSpeed<400>,Int<100>,Int<400>>>,BlastL<White,200,200>,ResponsiveBlastFadeL<White,Scale<SwingSpeed<400>,Int<6000>,Int<12000>>,Scale<SwingSpeed<400>,Int<400>,Int<100>>>,ResponsiveBlastL<White,Scale<SwingSpeed<400>,Int<400>,Int<100>>,Scale<SwingSpeed<400>,Int<200>,Int<100>>,Scale<SwingSpeed<400>,Int<400>,Int<200>>>>,
      //Multi-blast, blaster reflect cycles through different responsive effects
    ResponsiveClashL<TransitionEffect<Rgb<255,240,80>,LemonChiffon,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
      //Responsive clash
    TransitionEffectL<TrConcat<TrInstant,Stripes<3000,-3500,White,RandomPerLEDFlicker<Rgb<60,60,60>,Black>,BrownNoiseFlicker<White,Rgb<30,30,30>,200>,RandomPerLEDFlicker<Rgb<80,80,80>,Rgb<30,30,30>>>,TrFade<1000>>,EFFECT_IGNITION>,
      //Bright HumpFlicker ignition effect
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<RotateColorsX<Variation,Rgb<90,180,255>>,40>,TrFade<1200>>,EFFECT_RETRACTION>,
      //Bright HumpFlicker retraction effect
    LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,
      //Drag
    LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,
      //Responsive melt
    EffectSequence<EFFECT_POWERSAVE,AlphaL<Black,Int<8192>>,AlphaL<Black,Int<16384>>,AlphaL<Black,Int<24576>>,AlphaL<Black,Int<0>>>,
      //Power save, if using fett263's prop file hold Aux and click PWR while ON (pointing up) to dim blade in 25% increments.
    InOutTrL<TrConcat<TrWipe<200>,AudioFlicker<RotateColorsX<Variation,DeepSkyBlue>,RotateColorsX<Variation,Rgb<0,0,128>>>,TrWipe<100>,Black,TrBoing<550,2>>,TrColorCycle<790>>,
      //Glitch out ignition and cycle down retraction
    TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RotateColorsX<Variation,Rgb16<0,38402,65535>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2200>>,Int<1500>,Int<5000>>,Int<-4000>>>,TrFade<1400>,AlphaL<RotateColorsX<Variation,Rgb16<0,11150,20996>>,Bump<Int<0>,Int<10000>>>,TrFade<1500>,AlphaL<Rgb16<20393,20393,20393>,Bump<Int<0>,Int<7000>>>,TrFade<2100>>,EFFECT_RETRACTION>,
      //Retraction cool down effect
    //TransitionEffectL<TrConcat<TrDelay<1500>,Black,TrFade<1000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_BOOT>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_NEWFONT>,
      //Optional/alternate passive battery monitor, on boot (1st line) or font change (2nd line) you will get a visual indicator at the emitter of your current battery level. This also works without a blade if you have a lit emitter or blade plug. Green is Full, Red is Low (the color will blend from Green to Red as the battery is depleted), the indicator will fade out after 3000 ms and not display again until powered down and back up or fonts change.
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrDelay<2000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrFade<1000>>,EFFECT_BATTERY_LEVEL>,
      //On demand battery level, if using fett263's prop file Hold AUX and click PWR while OFF, the battery level is represented by the location on the blade; tip = full, hilt = low and color; green = full, yellow = half, red = low
    TransitionEffectL<TrConcat<TrFade<100>,AlphaL<Pulsing<Rgb<120,120,165>,Rgb<50,50,80>,500>,Bump<Int<0>,Int<6000>>>,TrBoing<600,9>>,EFFECT_PREON>
      //Clickity preon
    >>(),
    // === NPXL inner ring: ===
    StyleFirePtr<RED, YELLOW, 1>(),
    // === NPXL outer ring: ===
    StyleFirePtr<RED, YELLOW, 1>(),
    // === Crystal Chamber: ===
    StyleFirePtr<RED, YELLOW, 1>(), "analog"},

   { "ancient-tech;common",  "tracks/track1.wav",
/* copyright Fett263 Greyscale (Primary Blade) OS7 Style
https://www.fett263.com/fett263-proffieOS7-style-library.html#Greyscale
OS7.14 v2.242p
This Style Contains 6 Unique Combinations
Style Options:
Default (0): Crispity (Unstable Blade - AudioFlicker Swing)
1: Mercenary (Smoke Blade with Ripple Swing)
2: Apocalypse (Swing Speed - Split Blade)
3: CODA (Rolling Pulse with Unstable Swing)
4: Masterless (Rotoscope with Color Swing)
5: Decay (Inverted Rolling Pulse with Ripple Swing)

Base Color: BaseColorArg (0)

--Effects Included--
Ignition Effect: Standard Ignition [Color: IgnitionColorArg]
Retraction Effect: Standard Retraction [Color: RetractionColorArg]
Lockup Effect:
0: mainLockMulti0Shape - Begin: Real Clash - Style: Intensity AudioFlicker - End: Full Blade Absorb
[Color: LockupColorArg]
Lightning Block Effect:
0: mainLBMulti0Shape - Begin: Responsive Impact - Style: Strobing AudioFlicker - End: Full Blade Absorb
[Color: LBColorArg]
Drag Effect:
0: mainDragMulti0Shape - Begin: Wipe In - Style: Intensity Sparking Drag - End: Wipe Out
[Color: DragColorArg]
Melt Effect:
0: mainMeltMulti0Shape - Begin: Wipe In - Style: Intensity Melt - End: Wipe Out
[Color: StabColorArg]
Blast Effect: Blast Wave (Random) [Color: BlastColorArg]
Clash Effect: Real Clash V1 [Color: ClashColorArg]
*/
    StylePtr<Layers<ColorSelect<IntArg<STYLE_OPTION_ARG,0>,TrInstant,Layers<StaticFire<BrownNoiseFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,RandomPerLEDFlicker<Mix<Int<6000>,Black,RotateColorsX<Int<32000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,300>,Mix<Int<10772>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,6,10,1000,2>,AlphaL<AudioFlickerL<RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,SwingSpeed<400>>>,Layers<StripesX<Sin<Int<12>,Int<3000>,Int<7000>>,Scale<SwingSpeed<100>,Int<75>,Int<125>>,StripesX<Sin<Int<10>,Int<1000>,Int<3000>>,Scale<SwingSpeed<100>,Int<75>,Int<100>>,Pulsing<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<1265>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,1200>,Mix<SwingSpeed<200>,Mix<Int<16000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Pulsing<Mix<Int<6425>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,StripesX<Sin<Int<10>,Int<2000>,Int<3000>>,Sin<Int<10>,Int<75>,Int<100>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<12000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,2000>,Pulsing<Mix<Int<16448>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<642>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,3000>>,AlphaL<StaticFire<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<256>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,1,10,2000,2>,Int<10000>>,AlphaL<Stripes<2500,-3000,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<5654>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Pulsing<Mix<Int<2322>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black,800>>,SwingSpeed<375>>>,Layers<Mix<SmoothStep<Scale<SwingSpeed<400>,Int<6000>,Int<24000>>,Int<10000>>,Mix<Sin<Int<30>>,StaticFire<BrownNoiseFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<8167>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,300>,Mix<Int<4032>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,6,10,1000,2>,StaticFire<BrownNoiseFlicker<RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>,Mix<Int<8167>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>>,300>,Mix<Int<4032>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>,0,6,10,1000,2>>,HumpFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,40>>,AlphaL<AlphaL<AudioFlickerL<RotateColorsX<Int<800>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,SwingSpeed<350>>,SmoothStep<Scale<SwingSpeed<450>,Int<29000>,Int<9500>>,Int<16000>>>>,Layers<Mix<Sin<Int<3>>,AudioFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Stripes<5000,-90,Mix<Int<21200>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<16384>,Black,RotateColorsX<Int<30000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<12632>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>,AudioFlicker<RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Stripes<5000,-90,Mix<Int<21672>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<26736>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<26736>,Black,RotateColorsX<Int<28000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<21000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>>,AlphaL<Stripes<1000,-2000,RandomPerLEDFlicker<RotateColorsX<Int<31600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>,Black,RotateColorsX<Int<31600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>,SwingSpeed<525>>>,Layers<Stripes<15000,-300,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Pulsing<Mix<Int<3855>,Mix<Int<21845>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,White>,Mix<Int<23130>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,800>,Mix<Int<23130>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,AlphaL<RotateColorsX<Int<28600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Scale<IsLessThan<SwingSpeed<300>,Int<13600>>,Scale<SwingSpeed<300>,Int<-19300>,Int<32768>>,Int<0>>>>,Layers<StripesX<Int<3500>,Int<1200>,Mix<Sin<Int<20>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<25746>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Sin<Int<23>>,Mix<Int<19504>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RotateColorsX<Int<32000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Sin<Int<16>>,Mix<Int<3167>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,White>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Sin<Int<18>>,Mix<Int<11000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<22000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>,AlphaL<Stripes<1000,2000,RandomPerLEDFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Black>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Black>,SwingSpeed<500>>>>,TransitionEffectL<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectRandomF<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,EFFECT_BLAST>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<12000>,Int<60000>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrWaveX<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Int<100>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>,EFFECT_CLASH>>,LockupTrL<TransitionEffect<AlphaL<AlphaMixL<Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>,AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,BrownNoiseFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>,300>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>>,AlphaL<AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<20000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,TrExtend<5000,TrInstant>,TrFade<5000>,EFFECT_LOCKUP_BEGIN>,TrConcat<TrJoin<TrDelay<50>,TrInstant>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<20000>,Int<60000>>>>>,TrFade<300>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,SaberBase::LOCKUP_NORMAL,Int<1>>,ResponsiveLightningBlockL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrConcat<TrExtend<200,TrInstant>,AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Int<10000>,Int<21000>>,Int<10000>>>,TrFade<200>>,TrConcat<TrInstant,RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,Int<1>>,LockupTrL<AlphaL<TransitionEffect<RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>>,BrownNoiseFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>,Int<300>>,TrExtend<4000,TrInstant>,TrFade<4000>,EFFECT_DRAG_BEGIN>,SmoothStep<Scale<TwistAngle<>,IntArg<DRAG_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrWipeIn<200>,TrWipe<200>,SaberBase::LOCKUP_DRAG,Int<1>>,LockupTrL<AlphaL<Stripes<2000,4000,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,Mix<Sin<Int<50>>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,Mix<Int<4096>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrConcat<TrExtend<4000,TrWipeIn<200>>,AlphaL<HumpFlicker<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,RotateColorsX<Int<3000>,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,100>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrFade<4000>>,TrWipe<200>,SaberBase::LOCKUP_MELT,Int<1>>,InOutTrL<TrWipeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeInX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,Black>>>(),

/* copyright Fett263 Greyscale (Primary Blade) OS7 Style
https://www.fett263.com/fett263-proffieOS7-style-library.html#Greyscale
OS7.14 v2.242p
This Style Contains 21600 Unique Combinations
Style Options:
Default (0): Crispity (Unstable Blade - AudioFlicker Swing)
1: Mercenary (Smoke Blade with Ripple Swing)
2: Apocalypse (Swing Speed - Split Blade)
3: CODA (Rolling Pulse with Unstable Swing)
4: Masterless (Rotoscope with Color Swing)
5: Decay (Inverted Rolling Pulse with Ripple Swing)

Base Color: BaseColorArg (0)

--Effects Included--
Interactive Preon: Faulty Core [Color: PreonColorArg]
Interactive Preon Control = active Preon (auto times to sound), Clash to ignite. Requires/uses tr00.wav (glitchy ignition)
Note: Allow at least 30 seconds after initial boot for motion/clash detection to stabilize.
Ignition Effect Options: Default (0): Standard Ignition, 1: SparkTip Ignition, 2: Metal Forge (Heat Up), 3: Lightning Strike, 4: Wipe In, 5: Glitch On [Color: IgnitionColorArg]
PowerUp Effect Options: Default (0): Power Flash, 1: Power Burst Center Out, 2: Power Surge (Stable), 3: Power Surge (Unstable V1), 4: Power Surge (Unstable V2) [Color: IgnitionColorArg]
Retraction Effect Options: Default (0): Standard Retraction, 1: SparkTip Retraction, 2: Metal Forge (Cool Down), 3: Wipe In + Fade, 4: Cycle Down, 5: Run Up [Color: RetractionColorArg]
CoolDown Effect Options: Default (0): Unstable Cool Down Reverse, 1: Unstable Cool Down Forward, 2: Power Burst Forward, 3: Power Burst Reverse, 4: Power Flash [Color: RetractionColorArg]
PostOff Effect Options: Default (0): Exit Hyperspace, 1: Emitter Glow (Emitter Size), 2: Emitter Spark (Preon Size), 3: Emitter Cool Off (Preon Size) [Color: PostOffColorArg]
Lockup Effect:
0: mainLockMulti0Shape - Begin: Real Clash - Style: Intensity AudioFlicker - End: Full Blade Absorb
[Color: LockupColorArg]
Lightning Block Effect:
0: mainLBMulti0Shape - Begin: Responsive Impact - Style: Strobing AudioFlicker - End: Full Blade Absorb
[Color: LBColorArg]
Drag Effect:
0: mainDragMulti0Shape - Begin: Wipe In - Style: Intensity Sparking Drag - End: Wipe Out
[Color: DragColorArg]
Melt Effect:
0: mainMeltMulti0Shape - Begin: Wipe In - Style: Intensity Melt - End: Wipe Out
[Color: StabColorArg]
Interactive Blast: Random Blasts - Default Level (Uses Style Option 2 for Editing): 1000 ms
Interactive Blast control requires blast.wav files in font. When Blast is triggered blast.wav will play, to deflect blast (blst.wav and visual effect) swing within 1000ms of blaster sound ending. Random number of blasts from 1 to multiple possible. Only one style per preset can contain.
Blast Effect (Randomly Selected): Blast Wave (Random), Blast Ripple Fade, Blast Wave (Medium), Responsive Blast Wave (Random), Responsive Blast Ripple Fade, Full Blade Blast Fade [Color: BlastColorArg]
Clash Effect: Real Clash V1 [Color: ClashColorArg]
Rain Effect: Rain Spark [Color: EmitterColorArg]
Battery Level: % Blade (Green to Red)
Battery Monitor: Passive Battery Monitor (Retraction)
*/
    StylePtr<Layers<ColorSelect<IntArg<STYLE_OPTION_ARG,0>,TrInstant,Layers<StaticFire<BrownNoiseFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,RandomPerLEDFlicker<Mix<Int<6000>,Black,RotateColorsX<Int<32000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,300>,Mix<Int<10772>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,6,10,1000,2>,AlphaL<AudioFlickerL<RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,SwingSpeed<400>>>,Layers<StripesX<Sin<Int<12>,Int<3000>,Int<7000>>,Scale<SwingSpeed<100>,Int<75>,Int<125>>,StripesX<Sin<Int<10>,Int<1000>,Int<3000>>,Scale<SwingSpeed<100>,Int<75>,Int<100>>,Pulsing<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<1265>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,1200>,Mix<SwingSpeed<200>,Mix<Int<16000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Pulsing<Mix<Int<6425>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,StripesX<Sin<Int<10>,Int<2000>,Int<3000>>,Sin<Int<10>,Int<75>,Int<100>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<12000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,2000>,Pulsing<Mix<Int<16448>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<642>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,3000>>,AlphaL<StaticFire<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<256>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,1,10,2000,2>,Int<10000>>,AlphaL<Stripes<2500,-3000,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<5654>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Pulsing<Mix<Int<2322>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black,800>>,SwingSpeed<375>>>,Layers<Mix<SmoothStep<Scale<SwingSpeed<400>,Int<6000>,Int<24000>>,Int<10000>>,Mix<Sin<Int<30>>,StaticFire<BrownNoiseFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<8167>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,300>,Mix<Int<4032>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,6,10,1000,2>,StaticFire<BrownNoiseFlicker<RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>,Mix<Int<8167>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>>,300>,Mix<Int<4032>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>,0,6,10,1000,2>>,HumpFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,40>>,AlphaL<AlphaL<AudioFlickerL<RotateColorsX<Int<800>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,SwingSpeed<350>>,SmoothStep<Scale<SwingSpeed<450>,Int<29000>,Int<9500>>,Int<16000>>>>,Layers<Mix<Sin<Int<3>>,AudioFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Stripes<5000,-90,Mix<Int<21200>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<16384>,Black,RotateColorsX<Int<30000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<12632>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>,AudioFlicker<RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Stripes<5000,-90,Mix<Int<21672>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<26736>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<26736>,Black,RotateColorsX<Int<28000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<21000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>>,AlphaL<Stripes<1000,-2000,RandomPerLEDFlicker<RotateColorsX<Int<31600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>,Black,RotateColorsX<Int<31600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>,SwingSpeed<525>>>,Layers<Stripes<15000,-300,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Pulsing<Mix<Int<3855>,Mix<Int<21845>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,White>,Mix<Int<23130>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,800>,Mix<Int<23130>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,AlphaL<RotateColorsX<Int<28600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Scale<IsLessThan<SwingSpeed<300>,Int<13600>>,Scale<SwingSpeed<300>,Int<-19300>,Int<32768>>,Int<0>>>>,Layers<StripesX<Int<3500>,Int<1200>,Mix<Sin<Int<20>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<25746>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Sin<Int<23>>,Mix<Int<19504>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RotateColorsX<Int<32000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Sin<Int<16>>,Mix<Int<3167>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,White>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Sin<Int<18>>,Mix<Int<11000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<22000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>,AlphaL<Stripes<1000,2000,RandomPerLEDFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Black>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Black>,SwingSpeed<500>>>>,TransitionEffectL<TrSelect<IntArg<IGNITION_POWER_UP_ARG,0>,TrConcat<TrJoin<TrDelayX<IgnitionTime<300>>,TrInstant>,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<300>>,TrInstant>,Remap<CenterDistF<>,Stripes<5000,-2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrInstant,AudioFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrFade<1200>>,TrConcat<TrInstant,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<1200>>,TrConcat<TrInstant,HumpFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,40>,TrFade<1200>>>,EFFECT_IGNITION>,TransitionEffectL<TrSelect<IntArg<RETRACTION_COOL_DOWN_ARG,0>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>>,EFFECT_RETRACTION>,SparkleL<RgbArg<EMITTER_COLOR_ARG,Rgb<255,255,255>>>,TransitionEffectL<TrRandom<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectRandomF<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>,Int<6000>>>,TrCenterWipeX<Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>,AlphaL<Remap<CenterDistF<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>,Stripes<1600,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Bump<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>,Int<32000>>>,TrJoin<TrSmoothFade<50>,TrCenterWipeX<Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<200>,Int<200>,Int<400>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<BladeAngle<>,Int<28000>,Int<8000>>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Int<3000>,Int<29000>>,Int<6000>>>,TrCenterWipeX<Int<100>,Scale<BladeAngle<>,Int<3000>,Int<29000>>>,AlphaL<Remap<CenterDistF<Scale<BladeAngle<>,Int<3000>,Int<29000>>>,Stripes<1600,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Bump<Scale<BladeAngle<>,Int<3000>,Int<29000>>,Int<32000>>>,TrJoin<TrSmoothFade<50>,TrCenterWipeX<Int<100>,Scale<BladeAngle<>,Int<3000>,Int<29000>>>>>,TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,TrFade<300>>>,EFFECT_BLAST>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<12000>,Int<60000>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrWaveX<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Int<100>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>,EFFECT_CLASH>>,LockupTrL<TransitionEffect<AlphaL<AlphaMixL<Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>,AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,BrownNoiseFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>,300>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>>,AlphaL<AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<20000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,TrExtend<5000,TrInstant>,TrFade<5000>,EFFECT_LOCKUP_BEGIN>,TrConcat<TrJoin<TrDelay<50>,TrInstant>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<20000>,Int<60000>>>>>,TrFade<300>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,SaberBase::LOCKUP_NORMAL,Int<1>>,ResponsiveLightningBlockL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrConcat<TrExtend<200,TrInstant>,AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Int<10000>,Int<21000>>,Int<10000>>>,TrFade<200>>,TrConcat<TrInstant,RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,Int<1>>,LockupTrL<AlphaL<TransitionEffect<RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>>,BrownNoiseFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>,Int<300>>,TrExtend<4000,TrInstant>,TrFade<4000>,EFFECT_DRAG_BEGIN>,SmoothStep<Scale<TwistAngle<>,IntArg<DRAG_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrWipeIn<200>,TrWipe<200>,SaberBase::LOCKUP_DRAG,Int<1>>,LockupTrL<AlphaL<Stripes<2000,4000,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,Mix<Sin<Int<50>>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,Mix<Int<4096>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrConcat<TrExtend<4000,TrWipeIn<200>>,AlphaL<HumpFlicker<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,RotateColorsX<Int<3000>,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,100>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrFade<4000>>,TrWipe<200>,SaberBase::LOCKUP_MELT,Int<1>>,TransitionEffectL<TrConcat<TrDelay<100>,AlphaL<White,Int<0>>,TrDoEffect<TrInstant,EFFECT_GAME_CHOICE>>,EFFECT_INTERACTIVE_BLAST>,TransitionEffectL<TrConcat<TrExtendX<Sum<WavLen<EFFECT_INTERACTIVE_BLAST>,IntArg<STYLE_OPTION2_ARG,1000>>,TrInstant>,TransitionPulseL<TrDoEffect<TrInstant,EFFECT_BLAST>,ThresholdPulseF<SwingSpeed<300>,Int<16000>>>,TrConcat<TrDelay<150>,TrRandom<TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>,TrInstant,TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>,TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>>>>,EFFECT_GAME_CHOICE>,InOutTrL<TrSelect<IntArg<IGNITION_OPTION_ARG,0>,TrWipeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,Red,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,DarkOrange,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,White,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>>,TrConcat<TrWipeInX<Mult<IgnitionTime<300>,Int<6553>>>,RandomBlink<30000,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Black>,TrJoin<TrDelayX<Mult<IgnitionTime<300>,Int<19660>>>,TrWipeInX<Mult<IgnitionTime<230>,Int<6553>>>>,Mix<SmoothStep<Scale<SlowNoise<Int<30000>>,IntArg<EMITTER_SIZE_ARG,1000>,Sum<Int<5000>,IntArg<EMITTER_SIZE_ARG,1000>>>,Int<-3000>>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrWipeX<Mult<IgnitionTime<300>,Int<19660>>>>,TrWipeInX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrJoin<TrDelayX<Mult<IgnitionTime<300>,Int<16384>>>,TrWipeX<Mult<IgnitionTime<300>,Int<16384>>>>,Mix<SmoothStep<NoisySoundLevel,Int<-1>>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrWipeX<Mult<IgnitionTime<300>,Int<16384>>>>>,TrSelect<IntArg<RETRACTION_OPTION_ARG,0>,TrWipeInX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeInSparkTipX<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,White,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,DarkOrange,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,Red,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,TrJoin<TrWipeInX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrSmoothFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,TrColorCycleX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,Layers<Black,TransitionEffectL<TrConcat<TrDoEffectAlways<TrInstant,EFFECT_TRANSITION_SOUND,0>,Layers<TransitionPulseL<TrDoEffectAlways<TrInstant,EFFECT_FAST_ON>,EffectPulseF<EFFECT_OFF_CLASH>>,AlphaL<BrownNoiseFlickerL<RgbArg<PREON_COLOR_ARG,Rgb<255,255,255>>,Int<100>>,SmoothStep<Scale<NoisySoundLevel,Int<1000>,Int<8000>>,Int<-3000>>>>,TrDelayX<WavLen<EFFECT_TRANSITION_SOUND>>>,EFFECT_INTERACTIVE_PREON>>>,TransitionEffectL<TrSelect<IntArg<OFF_OPTION_ARG,0>,TrConcat<TrJoin<TrDelayX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>,TrCenterWipeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>>,Remap<CenterDistF<>,Stripes<2000,-1500,Black,Rgb<100,100,150>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>,Remap<CenterDistF<>,Stripes<1000,-500,Black,Rgb<100,100,150>,Black>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>>,TrConcat<TrInstant,AlphaL<White,Int<0>>,TrJoin<TrDelay<1000>,TrInstant>,AlphaL<RgbArg<POSTOFF_COLOR_ARG,Rgb<255,255,255>>,SmoothStep<IntArg<EMITTER_SIZE_ARG,2000>,Int<-2000>>>,TrSmoothFadeX<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>>>,TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<POSTOFF_COLOR_ARG,Rgb<255,255,255>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,2000>,Sum<IntArg<PREON_SIZE_ARG,2000>,Int<3000>>>,Int<-4000>>>,TrDelayX<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>>>,TrConcat<TrInstant,AlphaL<White,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-4000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>,AlphaL<Orange,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-4000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>,AlphaL<Red,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-2000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>>>,EFFECT_POSTOFF>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrWipe<1000>>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<BatteryLevel,Int<-10>>>,TrWipeIn<1000>>,EFFECT_BATTERY_LEVEL>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrInstant>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<IntArg<EMITTER_SIZE_ARG,2000>,Int<-4000>>>,TrFade<300>>,EFFECT_RETRACTION>>>(),

/* copyright Fett263 Greyscale (Primary Blade) OS7 Style
https://www.fett263.com/fett263-proffieOS7-style-library.html#Greyscale
OS7.14 v2.242p
This Style Contains 21600 Unique Combinations
Style Options:
Default (0): Crispity (Unstable Blade - AudioFlicker Swing)
1: Mercenary (Smoke Blade with Ripple Swing)
2: Apocalypse (Swing Speed - Split Blade)
3: CODA (Rolling Pulse with Unstable Swing)
4: Masterless (Rotoscope with Color Swing)
5: Decay (Inverted Rolling Pulse with Ripple Swing)

Base Color: BaseColorArg (0)

--Effects Included--
Interactive Preon: Faulty Core [Color: PreonColorArg]
Interactive Preon Control = active Preon (auto times to sound), Clash to ignite. Requires/uses tr00.wav (glitchy ignition)
Note: Allow at least 30 seconds after initial boot for motion/clash detection to stabilize.
Ignition Effect Options: Default (0): Standard Ignition, 1: SparkTip Ignition, 2: Metal Forge (Heat Up), 3: Lightning Strike, 4: Wipe In, 5: Glitch On [Color: IgnitionColorArg]
PowerUp Effect Options: Default (0): Power Flash, 1: Power Burst Center Out, 2: Power Surge (Stable), 3: Power Surge (Unstable V1), 4: Power Surge (Unstable V2) [Color: IgnitionColorArg]
Retraction Effect Options: Default (0): Standard Retraction, 1: SparkTip Retraction, 2: Metal Forge (Cool Down), 3: Wipe In + Fade, 4: Cycle Down, 5: Run Up [Color: RetractionColorArg]
CoolDown Effect Options: Default (0): Unstable Cool Down Reverse, 1: Unstable Cool Down Forward, 2: Power Burst Forward, 3: Power Burst Reverse, 4: Power Flash [Color: RetractionColorArg]
PostOff Effect Options: Default (0): Exit Hyperspace, 1: Emitter Glow (Emitter Size), 2: Emitter Spark (Preon Size), 3: Emitter Cool Off (Preon Size) [Color: PostOffColorArg]
Lockup Effect:
0: mainLockMulti0Shape - Begin: Real Clash - Style: Intensity AudioFlicker - End: Full Blade Absorb
[Color: LockupColorArg]
Lightning Block Effect:
0: mainLBMulti0Shape - Begin: Responsive Impact - Style: Strobing AudioFlicker - End: Full Blade Absorb
[Color: LBColorArg]
Drag Effect:
0: mainDragMulti0Shape - Begin: Wipe In - Style: Intensity Sparking Drag - End: Wipe Out
[Color: DragColorArg]
Melt Effect:
0: mainMeltMulti0Shape - Begin: Wipe In - Style: Intensity Melt - End: Wipe Out
[Color: StabColorArg]
Interactive Blast: Random Blasts - Default Level (Uses Style Option 2 for Editing): 1000 ms
Interactive Blast control requires blast.wav files in font. When Blast is triggered blast.wav will play, to deflect blast (blst.wav and visual effect) swing within 1000ms of blaster sound ending. Random number of blasts from 1 to multiple possible. Only one style per preset can contain.
Blast Effect (Randomly Selected): Blast Wave (Random), Blast Ripple Fade, Blast Wave (Medium), Responsive Blast Wave (Random), Responsive Blast Ripple Fade, Full Blade Blast Fade [Color: BlastColorArg]
Clash Effect: Real Clash V1 [Color: ClashColorArg]
Rain Effect: Rain Spark [Color: EmitterColorArg]
Battery Level: % Blade (Green to Red)
Battery Monitor: Passive Battery Monitor (Retraction)
*/
    StylePtr<Layers<ColorSelect<IntArg<STYLE_OPTION_ARG,0>,TrInstant,Layers<StaticFire<BrownNoiseFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,RandomPerLEDFlicker<Mix<Int<6000>,Black,RotateColorsX<Int<32000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,300>,Mix<Int<10772>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,6,10,1000,2>,AlphaL<AudioFlickerL<RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,SwingSpeed<400>>>,Layers<StripesX<Sin<Int<12>,Int<3000>,Int<7000>>,Scale<SwingSpeed<100>,Int<75>,Int<125>>,StripesX<Sin<Int<10>,Int<1000>,Int<3000>>,Scale<SwingSpeed<100>,Int<75>,Int<100>>,Pulsing<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<1265>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,1200>,Mix<SwingSpeed<200>,Mix<Int<16000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Pulsing<Mix<Int<6425>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,StripesX<Sin<Int<10>,Int<2000>,Int<3000>>,Sin<Int<10>,Int<75>,Int<100>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<12000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,2000>,Pulsing<Mix<Int<16448>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<642>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,3000>>,AlphaL<StaticFire<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<256>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,1,10,2000,2>,Int<10000>>,AlphaL<Stripes<2500,-3000,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<5654>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Pulsing<Mix<Int<2322>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black,800>>,SwingSpeed<375>>>,Layers<Mix<SmoothStep<Scale<SwingSpeed<400>,Int<6000>,Int<24000>>,Int<10000>>,Mix<Sin<Int<30>>,StaticFire<BrownNoiseFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<8167>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,300>,Mix<Int<4032>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,6,10,1000,2>,StaticFire<BrownNoiseFlicker<RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>,Mix<Int<8167>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>>,300>,Mix<Int<4032>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>,0,6,10,1000,2>>,HumpFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,40>>,AlphaL<AlphaL<AudioFlickerL<RotateColorsX<Int<800>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,SwingSpeed<350>>,SmoothStep<Scale<SwingSpeed<450>,Int<29000>,Int<9500>>,Int<16000>>>>,Layers<Mix<Sin<Int<3>>,AudioFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Stripes<5000,-90,Mix<Int<21200>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<16384>,Black,RotateColorsX<Int<30000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<12632>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>,AudioFlicker<RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Stripes<5000,-90,Mix<Int<21672>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<26736>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<26736>,Black,RotateColorsX<Int<28000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<21000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>>,AlphaL<Stripes<1000,-2000,RandomPerLEDFlicker<RotateColorsX<Int<31600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>,Black,RotateColorsX<Int<31600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>,SwingSpeed<525>>>,Layers<Stripes<15000,-300,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Pulsing<Mix<Int<3855>,Mix<Int<21845>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,White>,Mix<Int<23130>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,800>,Mix<Int<23130>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,AlphaL<RotateColorsX<Int<28600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Scale<IsLessThan<SwingSpeed<300>,Int<13600>>,Scale<SwingSpeed<300>,Int<-19300>,Int<32768>>,Int<0>>>>,Layers<StripesX<Int<3500>,Int<1200>,Mix<Sin<Int<20>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<25746>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Sin<Int<23>>,Mix<Int<19504>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RotateColorsX<Int<32000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Sin<Int<16>>,Mix<Int<3167>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,White>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Sin<Int<18>>,Mix<Int<11000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<22000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>,AlphaL<Stripes<1000,2000,RandomPerLEDFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Black>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Black>,SwingSpeed<500>>>>,TransitionEffectL<TrSelect<IntArg<IGNITION_POWER_UP_ARG,0>,TrConcat<TrJoin<TrDelayX<IgnitionTime<300>>,TrInstant>,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<300>>,TrInstant>,Remap<CenterDistF<>,Stripes<5000,-2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrInstant,AudioFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrFade<1200>>,TrConcat<TrInstant,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<1200>>,TrConcat<TrInstant,HumpFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,40>,TrFade<1200>>>,EFFECT_IGNITION>,TransitionEffectL<TrSelect<IntArg<RETRACTION_COOL_DOWN_ARG,0>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>>,EFFECT_RETRACTION>,SparkleL<RgbArg<EMITTER_COLOR_ARG,Rgb<255,255,255>>>,TransitionEffectL<TrRandom<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectRandomF<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>,Int<6000>>>,TrCenterWipeX<Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>,AlphaL<Remap<CenterDistF<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>,Stripes<1600,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Bump<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>,Int<32000>>>,TrJoin<TrSmoothFade<50>,TrCenterWipeX<Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<200>,Int<200>,Int<400>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<BladeAngle<>,Int<28000>,Int<8000>>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Int<3000>,Int<29000>>,Int<6000>>>,TrCenterWipeX<Int<100>,Scale<BladeAngle<>,Int<3000>,Int<29000>>>,AlphaL<Remap<CenterDistF<Scale<BladeAngle<>,Int<3000>,Int<29000>>>,Stripes<1600,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Bump<Scale<BladeAngle<>,Int<3000>,Int<29000>>,Int<32000>>>,TrJoin<TrSmoothFade<50>,TrCenterWipeX<Int<100>,Scale<BladeAngle<>,Int<3000>,Int<29000>>>>>,TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,TrFade<300>>>,EFFECT_BLAST>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<12000>,Int<60000>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrWaveX<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Int<100>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>,EFFECT_CLASH>>,LockupTrL<TransitionEffect<AlphaL<AlphaMixL<Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>,AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,BrownNoiseFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>,300>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>>,AlphaL<AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<20000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,TrExtend<5000,TrInstant>,TrFade<5000>,EFFECT_LOCKUP_BEGIN>,TrConcat<TrJoin<TrDelay<50>,TrInstant>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<20000>,Int<60000>>>>>,TrFade<300>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,SaberBase::LOCKUP_NORMAL,Int<1>>,ResponsiveLightningBlockL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrConcat<TrExtend<200,TrInstant>,AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Int<10000>,Int<21000>>,Int<10000>>>,TrFade<200>>,TrConcat<TrInstant,RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,Int<1>>,LockupTrL<AlphaL<TransitionEffect<RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>>,BrownNoiseFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>,Int<300>>,TrExtend<4000,TrInstant>,TrFade<4000>,EFFECT_DRAG_BEGIN>,SmoothStep<Scale<TwistAngle<>,IntArg<DRAG_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrWipeIn<200>,TrWipe<200>,SaberBase::LOCKUP_DRAG,Int<1>>,LockupTrL<AlphaL<Stripes<2000,4000,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,Mix<Sin<Int<50>>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,Mix<Int<4096>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrConcat<TrExtend<4000,TrWipeIn<200>>,AlphaL<HumpFlicker<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,RotateColorsX<Int<3000>,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,100>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrFade<4000>>,TrWipe<200>,SaberBase::LOCKUP_MELT,Int<1>>,TransitionEffectL<TrConcat<TrDelay<100>,AlphaL<White,Int<0>>,TrDoEffect<TrInstant,EFFECT_GAME_CHOICE>>,EFFECT_INTERACTIVE_BLAST>,TransitionEffectL<TrConcat<TrExtendX<Sum<WavLen<EFFECT_INTERACTIVE_BLAST>,IntArg<STYLE_OPTION2_ARG,1000>>,TrInstant>,TransitionPulseL<TrDoEffect<TrInstant,EFFECT_BLAST>,ThresholdPulseF<SwingSpeed<300>,Int<16000>>>,TrConcat<TrDelay<150>,TrRandom<TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>,TrInstant,TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>,TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>>>>,EFFECT_GAME_CHOICE>,InOutTrL<TrSelect<IntArg<IGNITION_OPTION_ARG,0>,TrWipeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,Red,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,DarkOrange,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,White,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>>,TrConcat<TrWipeInX<Mult<IgnitionTime<300>,Int<6553>>>,RandomBlink<30000,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Black>,TrJoin<TrDelayX<Mult<IgnitionTime<300>,Int<19660>>>,TrWipeInX<Mult<IgnitionTime<230>,Int<6553>>>>,Mix<SmoothStep<Scale<SlowNoise<Int<30000>>,IntArg<EMITTER_SIZE_ARG,1000>,Sum<Int<5000>,IntArg<EMITTER_SIZE_ARG,1000>>>,Int<-3000>>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrWipeX<Mult<IgnitionTime<300>,Int<19660>>>>,TrWipeInX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrJoin<TrDelayX<Mult<IgnitionTime<300>,Int<16384>>>,TrWipeX<Mult<IgnitionTime<300>,Int<16384>>>>,Mix<SmoothStep<NoisySoundLevel,Int<-1>>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrWipeX<Mult<IgnitionTime<300>,Int<16384>>>>>,TrSelect<IntArg<RETRACTION_OPTION_ARG,0>,TrWipeInX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeInSparkTipX<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,White,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,DarkOrange,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,Red,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,TrJoin<TrWipeInX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrSmoothFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,TrColorCycleX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,Layers<Black,TransitionEffectL<TrConcat<TrDoEffectAlways<TrInstant,EFFECT_TRANSITION_SOUND,0>,Layers<TransitionPulseL<TrDoEffectAlways<TrInstant,EFFECT_FAST_ON>,EffectPulseF<EFFECT_OFF_CLASH>>,AlphaL<BrownNoiseFlickerL<RgbArg<PREON_COLOR_ARG,Rgb<255,255,255>>,Int<100>>,SmoothStep<Scale<NoisySoundLevel,Int<1000>,Int<8000>>,Int<-3000>>>>,TrDelayX<WavLen<EFFECT_TRANSITION_SOUND>>>,EFFECT_INTERACTIVE_PREON>>>,TransitionEffectL<TrSelect<IntArg<OFF_OPTION_ARG,0>,TrConcat<TrJoin<TrDelayX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>,TrCenterWipeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>>,Remap<CenterDistF<>,Stripes<2000,-1500,Black,Rgb<100,100,150>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>,Remap<CenterDistF<>,Stripes<1000,-500,Black,Rgb<100,100,150>,Black>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>>,TrConcat<TrInstant,AlphaL<White,Int<0>>,TrJoin<TrDelay<1000>,TrInstant>,AlphaL<RgbArg<POSTOFF_COLOR_ARG,Rgb<255,255,255>>,SmoothStep<IntArg<EMITTER_SIZE_ARG,2000>,Int<-2000>>>,TrSmoothFadeX<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>>>,TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<POSTOFF_COLOR_ARG,Rgb<255,255,255>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,2000>,Sum<IntArg<PREON_SIZE_ARG,2000>,Int<3000>>>,Int<-4000>>>,TrDelayX<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>>>,TrConcat<TrInstant,AlphaL<White,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-4000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>,AlphaL<Orange,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-4000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>,AlphaL<Red,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-2000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>>>,EFFECT_POSTOFF>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrWipe<1000>>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<BatteryLevel,Int<-10>>>,TrWipeIn<1000>>,EFFECT_BATTERY_LEVEL>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrInstant>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<IntArg<EMITTER_SIZE_ARG,2000>,Int<-4000>>>,TrFade<300>>,EFFECT_RETRACTION>>>(),

/* copyright Fett263 Greyscale (Primary Blade) OS7 Style
https://www.fett263.com/fett263-proffieOS7-style-library.html#Greyscale
OS7.14 v2.242p
This Style Contains 21600 Unique Combinations
Style Options:
Default (0): Crispity (Unstable Blade - AudioFlicker Swing)
1: Mercenary (Smoke Blade with Ripple Swing)
2: Apocalypse (Swing Speed - Split Blade)
3: CODA (Rolling Pulse with Unstable Swing)
4: Masterless (Rotoscope with Color Swing)
5: Decay (Inverted Rolling Pulse with Ripple Swing)

Base Color: BaseColorArg (0)

--Effects Included--
Interactive Preon: Faulty Core [Color: PreonColorArg]
Interactive Preon Control = active Preon (auto times to sound), Clash to ignite. Requires/uses tr00.wav (glitchy ignition)
Note: Allow at least 30 seconds after initial boot for motion/clash detection to stabilize.
Ignition Effect Options: Default (0): Standard Ignition, 1: SparkTip Ignition, 2: Metal Forge (Heat Up), 3: Lightning Strike, 4: Wipe In, 5: Glitch On [Color: IgnitionColorArg]
PowerUp Effect Options: Default (0): Power Flash, 1: Power Burst Center Out, 2: Power Surge (Stable), 3: Power Surge (Unstable V1), 4: Power Surge (Unstable V2) [Color: IgnitionColorArg]
Retraction Effect Options: Default (0): Standard Retraction, 1: SparkTip Retraction, 2: Metal Forge (Cool Down), 3: Wipe In + Fade, 4: Cycle Down, 5: Run Up [Color: RetractionColorArg]
CoolDown Effect Options: Default (0): Unstable Cool Down Reverse, 1: Unstable Cool Down Forward, 2: Power Burst Forward, 3: Power Burst Reverse, 4: Power Flash [Color: RetractionColorArg]
PostOff Effect Options: Default (0): Exit Hyperspace, 1: Emitter Glow (Emitter Size), 2: Emitter Spark (Preon Size), 3: Emitter Cool Off (Preon Size) [Color: PostOffColorArg]
Lockup Effect:
0: mainLockMulti0Shape - Begin: Real Clash - Style: Intensity AudioFlicker - End: Full Blade Absorb
[Color: LockupColorArg]
Lightning Block Effect:
0: mainLBMulti0Shape - Begin: Responsive Impact - Style: Strobing AudioFlicker - End: Full Blade Absorb
[Color: LBColorArg]
Drag Effect:
0: mainDragMulti0Shape - Begin: Wipe In - Style: Intensity Sparking Drag - End: Wipe Out
[Color: DragColorArg]
Melt Effect:
0: mainMeltMulti0Shape - Begin: Wipe In - Style: Intensity Melt - End: Wipe Out
[Color: StabColorArg]
Interactive Blast: Random Blasts - Default Level (Uses Style Option 2 for Editing): 1000 ms
Interactive Blast control requires blast.wav files in font. When Blast is triggered blast.wav will play, to deflect blast (blst.wav and visual effect) swing within 1000ms of blaster sound ending. Random number of blasts from 1 to multiple possible. Only one style per preset can contain.
Blast Effect (Randomly Selected): Blast Wave (Random), Blast Ripple Fade, Blast Wave (Medium), Responsive Blast Wave (Random), Responsive Blast Ripple Fade, Full Blade Blast Fade [Color: BlastColorArg]
Clash Effect: Real Clash V1 [Color: ClashColorArg]
Rain Effect: Rain Spark [Color: EmitterColorArg]
Battery Level: % Blade (Green to Red)
Battery Monitor: Passive Battery Monitor (Retraction)
*/
    StylePtr<Layers<ColorSelect<IntArg<STYLE_OPTION_ARG,0>,TrInstant,Layers<StaticFire<BrownNoiseFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,RandomPerLEDFlicker<Mix<Int<6000>,Black,RotateColorsX<Int<32000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,300>,Mix<Int<10772>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,6,10,1000,2>,AlphaL<AudioFlickerL<RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,SwingSpeed<400>>>,Layers<StripesX<Sin<Int<12>,Int<3000>,Int<7000>>,Scale<SwingSpeed<100>,Int<75>,Int<125>>,StripesX<Sin<Int<10>,Int<1000>,Int<3000>>,Scale<SwingSpeed<100>,Int<75>,Int<100>>,Pulsing<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<1265>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,1200>,Mix<SwingSpeed<200>,Mix<Int<16000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Pulsing<Mix<Int<6425>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,StripesX<Sin<Int<10>,Int<2000>,Int<3000>>,Sin<Int<10>,Int<75>,Int<100>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<12000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,2000>,Pulsing<Mix<Int<16448>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<642>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,3000>>,AlphaL<StaticFire<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<256>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,1,10,2000,2>,Int<10000>>,AlphaL<Stripes<2500,-3000,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<5654>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Pulsing<Mix<Int<2322>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black,800>>,SwingSpeed<375>>>,Layers<Mix<SmoothStep<Scale<SwingSpeed<400>,Int<6000>,Int<24000>>,Int<10000>>,Mix<Sin<Int<30>>,StaticFire<BrownNoiseFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<8167>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,300>,Mix<Int<4032>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,0,6,10,1000,2>,StaticFire<BrownNoiseFlicker<RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>,Mix<Int<8167>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>>,300>,Mix<Int<4032>,Black,RgbArg<ALT_COLOR_ARG,Rgb<0,255,0>>>,0,6,10,1000,2>>,HumpFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,40>>,AlphaL<AlphaL<AudioFlickerL<RotateColorsX<Int<800>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,SwingSpeed<350>>,SmoothStep<Scale<SwingSpeed<450>,Int<29000>,Int<9500>>,Int<16000>>>>,Layers<Mix<Sin<Int<3>>,AudioFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Stripes<5000,-90,Mix<Int<21200>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<16384>,Black,RotateColorsX<Int<30000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<12632>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>,AudioFlicker<RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Stripes<5000,-90,Mix<Int<21672>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<26736>,Black,RotateColorsX<Int<31000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<26736>,Black,RotateColorsX<Int<28000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Int<21000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>>,AlphaL<Stripes<1000,-2000,RandomPerLEDFlicker<RotateColorsX<Int<31600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>,Black,RotateColorsX<Int<31600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Black>,SwingSpeed<525>>>,Layers<Stripes<15000,-300,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Pulsing<Mix<Int<3855>,Mix<Int<21845>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,White>,Mix<Int<23130>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,800>,Mix<Int<23130>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,AlphaL<RotateColorsX<Int<28600>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Scale<IsLessThan<SwingSpeed<300>,Int<13600>>,Scale<SwingSpeed<300>,Int<-19300>,Int<32768>>,Int<0>>>>,Layers<StripesX<Int<3500>,Int<1200>,Mix<Sin<Int<20>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<25746>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Sin<Int<23>>,Mix<Int<19504>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RotateColorsX<Int<32000>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>,Mix<Sin<Int<16>>,Mix<Int<3167>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,White>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Sin<Int<18>>,Mix<Int<11000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,Mix<Int<22000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>,AlphaL<Stripes<1000,2000,RandomPerLEDFlicker<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Black>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Black>,SwingSpeed<500>>>>,TransitionEffectL<TrSelect<IntArg<IGNITION_POWER_UP_ARG,0>,TrConcat<TrJoin<TrDelayX<IgnitionTime<300>>,TrInstant>,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<300>>,TrInstant>,Remap<CenterDistF<>,Stripes<5000,-2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrInstant,AudioFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrFade<1200>>,TrConcat<TrInstant,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<1200>>,TrConcat<TrInstant,HumpFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,40>,TrFade<1200>>>,EFFECT_IGNITION>,TransitionEffectL<TrSelect<IntArg<RETRACTION_COOL_DOWN_ARG,0>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>>,EFFECT_RETRACTION>,SparkleL<RgbArg<EMITTER_COLOR_ARG,Rgb<255,255,255>>>,TransitionEffectL<TrRandom<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectRandomF<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>,Int<6000>>>,TrCenterWipeX<Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>,AlphaL<Remap<CenterDistF<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>,Stripes<1600,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Bump<Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>,Int<32000>>>,TrJoin<TrSmoothFade<50>,TrCenterWipeX<Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<3000>,Int<29000>>>>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<200>,Int<200>,Int<400>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<BladeAngle<>,Int<28000>,Int<8000>>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Int<3000>,Int<29000>>,Int<6000>>>,TrCenterWipeX<Int<100>,Scale<BladeAngle<>,Int<3000>,Int<29000>>>,AlphaL<Remap<CenterDistF<Scale<BladeAngle<>,Int<3000>,Int<29000>>>,Stripes<1600,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Bump<Scale<BladeAngle<>,Int<3000>,Int<29000>>,Int<32000>>>,TrJoin<TrSmoothFade<50>,TrCenterWipeX<Int<100>,Scale<BladeAngle<>,Int<3000>,Int<29000>>>>>,TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,TrFade<300>>>,EFFECT_BLAST>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<12000>,Int<60000>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrWaveX<RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Int<100>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>,EFFECT_CLASH>>,LockupTrL<TransitionEffect<AlphaL<AlphaMixL<Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>,AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,BrownNoiseFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<12000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>,300>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<22000>>>>,AlphaL<AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<20000>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,TrExtend<5000,TrInstant>,TrFade<5000>,EFFECT_LOCKUP_BEGIN>,TrConcat<TrJoin<TrDelay<50>,TrInstant>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<20000>,Int<60000>>>>>,TrFade<300>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,SaberBase::LOCKUP_NORMAL,Int<1>>,ResponsiveLightningBlockL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrConcat<TrExtend<200,TrInstant>,AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Bump<Scale<BladeAngle<>,Int<10000>,Int<21000>>,Int<10000>>>,TrFade<200>>,TrConcat<TrInstant,RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,TrFade<400>>,Int<1>>,LockupTrL<AlphaL<TransitionEffect<RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>>,BrownNoiseFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>,Int<300>>,TrExtend<4000,TrInstant>,TrFade<4000>,EFFECT_DRAG_BEGIN>,SmoothStep<Scale<TwistAngle<>,IntArg<DRAG_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrWipeIn<200>,TrWipe<200>,SaberBase::LOCKUP_DRAG,Int<1>>,LockupTrL<AlphaL<Stripes<2000,4000,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,Mix<Sin<Int<50>>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,Mix<Int<4096>,Black,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrConcat<TrExtend<4000,TrWipeIn<200>>,AlphaL<HumpFlicker<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>,RotateColorsX<Int<3000>,Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>>>>,100>,SmoothStep<Scale<TwistAngle<>,IntArg<MELT_SIZE_ARG,28000>,Int<30000>>,Int<3000>>>,TrFade<4000>>,TrWipe<200>,SaberBase::LOCKUP_MELT,Int<1>>,TransitionEffectL<TrConcat<TrDelay<100>,AlphaL<White,Int<0>>,TrDoEffect<TrInstant,EFFECT_GAME_CHOICE>>,EFFECT_INTERACTIVE_BLAST>,TransitionEffectL<TrConcat<TrExtendX<Sum<WavLen<EFFECT_INTERACTIVE_BLAST>,IntArg<STYLE_OPTION2_ARG,1000>>,TrInstant>,TransitionPulseL<TrDoEffect<TrInstant,EFFECT_BLAST>,ThresholdPulseF<SwingSpeed<300>,Int<16000>>>,TrConcat<TrDelay<150>,TrRandom<TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>,TrInstant,TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>,TrDoEffect<TrInstant,EFFECT_INTERACTIVE_BLAST>>>>,EFFECT_GAME_CHOICE>,InOutTrL<TrSelect<IntArg<IGNITION_OPTION_ARG,0>,TrWipeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,Red,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,DarkOrange,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,White,TrFadeX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>>,TrConcat<TrWipeInX<Mult<IgnitionTime<300>,Int<6553>>>,RandomBlink<30000,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Black>,TrJoin<TrDelayX<Mult<IgnitionTime<300>,Int<19660>>>,TrWipeInX<Mult<IgnitionTime<230>,Int<6553>>>>,Mix<SmoothStep<Scale<SlowNoise<Int<30000>>,IntArg<EMITTER_SIZE_ARG,1000>,Sum<Int<5000>,IntArg<EMITTER_SIZE_ARG,1000>>>,Int<-3000>>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrWipeX<Mult<IgnitionTime<300>,Int<19660>>>>,TrWipeInX<BendTimePowInvX<IgnitionTime<300>,Mult<IntArg<IGNITION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrJoin<TrDelayX<Mult<IgnitionTime<300>,Int<16384>>>,TrWipeX<Mult<IgnitionTime<300>,Int<16384>>>>,Mix<SmoothStep<NoisySoundLevel,Int<-1>>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrWipeX<Mult<IgnitionTime<300>,Int<16384>>>>>,TrSelect<IntArg<RETRACTION_OPTION_ARG,0>,TrWipeInX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeInSparkTipX<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrConcat<TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,White,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,DarkOrange,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,Red,TrFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,TrJoin<TrWipeInX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrSmoothFadeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,TrColorCycleX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>,TrWipeX<BendTimePowInvX<RetractionTime<0>,Mult<IntArg<RETRACTION_OPTION2_ARG,10992>,Int<98304>>>>>,Layers<Black,TransitionEffectL<TrConcat<TrDoEffectAlways<TrInstant,EFFECT_TRANSITION_SOUND,0>,Layers<TransitionPulseL<TrDoEffectAlways<TrInstant,EFFECT_FAST_ON>,EffectPulseF<EFFECT_OFF_CLASH>>,AlphaL<BrownNoiseFlickerL<RgbArg<PREON_COLOR_ARG,Rgb<255,255,255>>,Int<100>>,SmoothStep<Scale<NoisySoundLevel,Int<1000>,Int<8000>>,Int<-3000>>>>,TrDelayX<WavLen<EFFECT_TRANSITION_SOUND>>>,EFFECT_INTERACTIVE_PREON>>>,TransitionEffectL<TrSelect<IntArg<OFF_OPTION_ARG,0>,TrConcat<TrJoin<TrDelayX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>,TrCenterWipeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>>,Remap<CenterDistF<>,Stripes<2000,-1500,Black,Rgb<100,100,150>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>,Remap<CenterDistF<>,Stripes<1000,-500,Black,Rgb<100,100,150>,Black>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<8192>>>>,TrConcat<TrInstant,AlphaL<White,Int<0>>,TrJoin<TrDelay<1000>,TrInstant>,AlphaL<RgbArg<POSTOFF_COLOR_ARG,Rgb<255,255,255>>,SmoothStep<IntArg<EMITTER_SIZE_ARG,2000>,Int<-2000>>>,TrSmoothFadeX<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>>>,TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<POSTOFF_COLOR_ARG,Rgb<255,255,255>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,2000>,Sum<IntArg<PREON_SIZE_ARG,2000>,Int<3000>>>,Int<-4000>>>,TrDelayX<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>>>,TrConcat<TrInstant,AlphaL<White,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-4000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>,AlphaL<Orange,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-4000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>,AlphaL<Red,SmoothStep<IntArg<PREON_SIZE_ARG,2000>,Int<-2000>>>,TrFadeX<Mult<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>,Int<10923>>>>>,EFFECT_POSTOFF>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrWipe<1000>>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<BatteryLevel,Int<-10>>>,TrWipeIn<1000>>,EFFECT_BATTERY_LEVEL>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrInstant>,AlphaL<Mix<BatteryLevel,Red,Green>,SmoothStep<IntArg<EMITTER_SIZE_ARG,2000>,Int<-4000>>>,TrFade<300>>,EFFECT_RETRACTION>>>(),
    "ancient/n -tech"},

   { "angry-monkey;common", "tracks/track1.wav",
/* copyright Fett263 BlankBlade (Primary Blade) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#BlankBlade
OS6.5 v2.2
Single Style
Base Style: Blank Blade

--Effects Included--
Ignition Effect: Lightning Strike
Retraction Effect: Run Up
Lockup Effect: Intensity Lockup V1
LightningBlock Effect: Responsive Lightning Block
Drag Effect: Intensity Sparking Drag
Melt Effect: Intensity Melt
Blast Effect: Responsive Blast Wave (Large)
Clash Effect: Random Clash with Wave
Swing Effect: Interactive Fireball (Force Toggle)
Emitter Effect: Unstable Flare
*/
    StylePtr<Layers<Black,AlphaL<RandomPerLEDFlickerL<RgbArg<EMITTER_COLOR_ARG,Rgb<255,68,0>>>,SmoothStep<Scale<NoisySoundLevel,IntArg<EMITTER_SIZE_ARG,2000>,Sum<IntArg<EMITTER_SIZE_ARG,2000>,Int<6000>>>,Int<-6000>>>,ColorSelect<IncrementF<EffectPulseF<EFFECT_FORCE>,Int<32000>,Int<2>,Int<1>>,TrSmoothFade<500>,AlphaL<RgbArg<BASE_COLOR_ARG,Rgb<255,68,0>>,Int<0>>,AlphaL<AlphaMixL<SmoothStep<IncrementWithReset<Scale<IsGreaterThan<HoldPeakF<Ifon<SwingSpeed<400>,Int<0>>,Int<150>,Int<32000>>,Int<18000>>,Int<0>,ThresholdPulseF<StrobeF<Scale<HoldPeakF<Ifon<SwingAcceleration<>,Int<0>>,Int<150>,Int<32000>>,Int<20>,Int<200>>,Int<1>>,Int<32000>>>,ThresholdPulseF<IsLessThan<HoldPeakF<Ifon<SwingSpeed<400>,Int<0>>,Int<150>,Int<32000>>,Int<8000>>,Int<32000>>,Int<42000>,Int<1500>>,Scale<HoldPeakF<Ifon<SwingSpeed<400>,Int<0>>,Int<150>,Int<32000>>,Int<3000>,Int<10000>>>,HumpFlicker<RotateColorsX<Int<1400>,RgbArg<SWING_COLOR_ARG,Rgb<255,0,0>>>,RotateColorsX<Int<3200>,RgbArg<SWING_COLOR_ARG,Rgb<255,0,0>>>,20>,HumpFlicker<RotateColorsX<Int<1000>,RgbArg<SWING_COLOR_ARG,Rgb<255,0,0>>>,RotateColorsX<Int<400>,RgbArg<SWING_COLOR_ARG,Rgb<255,0,0>>>,60>,RandomFlicker<Mix<Int<16384>,Black,RgbArg<SWING_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<SWING_COLOR_ARG,Rgb<255,0,0>>>>,LinearSectionF<IncrementWithReset<Scale<IsGreaterThan<HoldPeakF<Ifon<SwingSpeed<400>,Int<0>>,Int<150>,Int<32000>>,Int<18000>>,Int<0>,ThresholdPulseF<StrobeF<Scale<HoldPeakF<Ifon<SwingAcceleration<>,Int<0>>,Int<150>,Int<32000>>,Int<20>,Int<200>>,Int<1>>,Int<32000>>>,ThresholdPulseF<IsLessThan<HoldPeakF<Ifon<SwingSpeed<400>,Int<0>>,Int<150>,Int<32000>>,Int<8000>>,Int<32000>>,Int<42000>,Int<1500>>,Scale<HoldPeakF<Ifon<SwingSpeed<400>,Int<0>>,Int<150>,Int<32000>>,Int<3000>,Int<10000>>>>>,MultiTransitionEffectL<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,187,108>>,Int<200>,Int<100>,Int<400>,Scale<BladeAngle<>,Int<28000>,Int<8000>>>,EFFECT_BLAST>,TransitionEffectL<TrWaveX<RgbArg<CLASH_COLOR_ARG,Rgb<255,187,108>>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Int<100>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Scale<ClashImpactF<>,Int<28000>,Int<8000>>>,EFFECT_CLASH>,LockupTrL<AlphaMixL<Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>,BrownNoiseFlickerL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>,Int<200>>,StripesX<Int<1800>,Scale<NoisySoundLevel,Int<-3500>,Int<-5000>>,Mix<Int<6425>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>,Mix<Int<12850>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>>>>,TrConcat<TrExtend<50,TrInstant>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<20000>,Int<60000>>>>>,TrExtend<3000,TrFade<300>>,AlphaL<AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>,Mix<Int<10280>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Int<13000>>>,TrFade<3000>>,TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>,Int<0>>,TrSelect<Scale<IsLessThan<ClashImpactF<>,Int<20000>>,Int<1>,Int<0>>,TrWaveX<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>,Scale<ClashImpactF<>,Int<50>,Int<400>>,Int<100>,Scale<ClashImpactF<>,Int<500>,Int<300>>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>,TrSparkX<Remap<CenterDistF<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>,Stripes<1200,-3600,Mix<Int<6425>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>,Mix<Int<12850>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,187,108>>>>>,Int<30>,Scale<Sum<ClashImpactF<>,SwingSpeed<600>>,Int<100>,Int<400>>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,187,108>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,187,108>>,Blue>,50,1>,TrConcat<TrInstant,AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,187,108>>,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,187,108>>,Int<16000>>,30>,TrSmoothFade<600>>>,LockupTrL<AlphaL<RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,187,108>>>,SmoothStep<IntArg<DRAG_SIZE_ARG,26000>,Int<3000>>>,TrConcat<TrExtend<4000,TrWipeIn<200>>,AlphaL<BrownNoiseFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,187,108>>,Int<300>>,SmoothStep<IntArg<DRAG_SIZE_ARG,26000>,Int<3000>>>,TrFade<4000>>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Remap<Scale<RampF,Int<65536>,Int<0>>,StaticFire<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>,Mix<TwistAngle<>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>,RotateColorsX<Int<3000>,Mix<Int<12000>,Black,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>>,0,3,5,3000,10>>,SmoothStep<IntArg<MELT_SIZE_ARG,26000>,Int<4000>>>,TrConcat<TrWipeIn<100>,AlphaL<RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,SmoothStep<IntArg<MELT_SIZE_ARG,26000>,Int<4000>>>,TrExtend<4000,TrFade<300>>,AlphaL<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>,SmoothStep<IntArg<MELT_SIZE_ARG,26000>,Int<4000>>>,TrFade<4000>>,TrWipe<200>,SaberBase::LOCKUP_MELT>,InOutTrL<TrConcat<TrWipeInX<Mult<IgnitionTime<300>,Int<6553>>>,RandomBlink<30000,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Black>,TrExtendX<Mult<IgnitionTime<300>,Int<19660>>,TrWipeInX<Mult<IgnitionTime<230>,Int<6553>>>>,Mix<SmoothStep<Scale<SlowNoise<Int<30000>>,IntArg<EMITTER_SIZE_ARG,1000>,Sum<Int<5000>,IntArg<EMITTER_SIZE_ARG,1000>>>,Int<-3000>>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,TrWipeX<Mult<IgnitionTime<300>,Int<19660>>>>,TrWipeX<RetractionTime<0>>,Black>>>(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(), "angry/nmonkey"},

   { "apocalypse;common", "tracks/track1.wav",
    StylePtr<Layers<
    Mix<SmoothStep<Scale<SwingSpeed<400>,Int<6000>,Int<24000>>,Int<10000>>,Mix<Sin<Int<30>>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,Red>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<128,0,0>>,RotateColorsX<Variation,Rgb<60,0,0>>>,300>,RotateColorsX<Variation,Rgb<30,0,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,OrangeRed>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<128,25,0>>,RotateColorsX<Variation,Rgb<60,15,0>>>,300>,RotateColorsX<Variation,Rgb<30,2,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>>,HumpFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<125,0,0>>,40>>,
      //Swing responsive humpflicker/rotating red/orange unstable base, unstable takes over the blade the harder you swing
      //HumpFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>,50>,
      //Alternate plain humpflicker
    AlphaL<AlphaL<AudioFlickerL<RotateColorsX<Variation,Rgb16<65535,8729,0>>>,SwingSpeed<350>>,SmoothStep<Scale<SwingSpeed<450>,Int<29000>,Int<9500>>,Int<16000>>>,
      //Responsive edge audioflicker swing - starts at the tip and takes over the blade the harder you swing
    LockupTrL<Layers<
    AlphaL<AudioFlickerL<Rgb<255,150,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,
    AlphaL<Moccasin,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<500>>,TrConcat<TrInstant,White,TrFade<600>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,OrangeRed>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<128,25,0>>,RotateColorsX<Variation,Rgb<60,15,0>>>,300>,RotateColorsX<Variation,Rgb<30,2,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>,TrFade<50>,RotateColorsX<Variation,Rgb16<65535,8729,0>>,TrFade<525>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,OrangeRed>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<128,25,0>>,RotateColorsX<Variation,Rgb<60,15,0>>>,300>,RotateColorsX<Variation,Rgb<30,2,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>,TrFade<50>,RotateColorsX<Variation,Rgb16<35913,7294,0>>,TrFade<250>,StyleFire<BrownNoiseFlicker<RotateColorsX<Variation,OrangeRed>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<128,25,0>>,RotateColorsX<Variation,Rgb<60,15,0>>>,300>,RotateColorsX<Variation,Rgb<30,2,0>>,0,6,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>,FireConfig<10,1000,2>>,TrFade<100>,RotateColorsX<Variation,Rgb16<20393,1818,0>>,TrBoing<950,3>>,SaberBase::LOCKUP_NORMAL>,
      //Responsive lockup with unstable cooldown
      //AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrJoinR<TrWipe<100>,TrWipeIn<100>>,White,TrFade<3000>>,SaberBase::LOCKUP_NORMAL>,
      //Alternate normal endlock effect
    ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,
      //Responsive lightning block
    ResponsiveStabL<RotateColorsX<Variation,Orange>>,
      //Responsive stab
    EffectSequence<EFFECT_BLAST,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,LocalizedClashL<White,80,30,EFFECT_BLAST>,ResponsiveBlastWaveL<White,Scale<SwingSpeed<400>,Int<500>,Int<200>>,Scale<SwingSpeed<400>,Int<100>,Int<400>>>,BlastL<White,200,200>,ResponsiveBlastFadeL<White,Scale<SwingSpeed<400>,Int<6000>,Int<12000>>,Scale<SwingSpeed<400>,Int<400>,Int<100>>>,ResponsiveBlastL<White,Scale<SwingSpeed<400>,Int<400>,Int<100>>,Scale<SwingSpeed<400>,Int<200>,Int<100>>,Scale<SwingSpeed<400>,Int<400>,Int<200>>>>,
      //Multi-blast, blaster reflect cycles through different responsive effects
      //ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,
      //Alternate responsive blast
    ResponsiveClashL<TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
      //Responsive Clash
      //ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
      //Alternate white clash
    TransitionEffectL<TrConcat<TrInstant,Stripes<3000,-3500,RotateColorsX<Variation,Orange>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<70,25,5>>,Black>,BrownNoiseFlicker<RotateColorsX<Variation,OrangeRed>,RotateColorsX<Variation,Rgb<75,20,5>>,200>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<155,25,0>>,RotateColorsX<Variation,Rgb<65,15,0>>>>,TrFade<2500>,Stripes<3000,-2250,RotateColorsX<Variation,DarkOrange>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<195,15,0>>,RotateColorsX<Variation,Rgb<50,15,0>>>,BrownNoiseFlicker<RotateColorsX<Variation,OrangeRed>,RotateColorsX<Variation,Rgb<85,15,0>>,200>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<155,25,0>>,RotateColorsX<Variation,Rgb<95,15,0>>>>,TrFade<1000>,Stripes<3000,-1500,RotateColorsX<Variation,Rgb16<65535,8729,0>>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<195,10,0>>,RotateColorsX<Variation,Rgb<55,5,0>>>,BrownNoiseFlicker<RotateColorsX<Variation,OrangeRed>,RotateColorsX<Variation,Rgb<185,10,0>>,200>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<255,13,0>>,RotateColorsX<Variation,Rgb<105,3,0>>>>,TrFade<2500>>,EFFECT_IGNITION>,
      //Unstable ignition
    TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<RotateColorsX<Variation,Rgb<255,75,0>>,40>,TrFade<500>>,EFFECT_RETRACTION>,
      //Humpflicker retraction
    LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,
      //Drag
    LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,
      //Responsive melt
    EffectSequence<EFFECT_POWERSAVE,AlphaL<Black,Int<8192>>,AlphaL<Black,Int<16384>>,AlphaL<Black,Int<24576>>,AlphaL<Black,Int<0>>>,
      //Power save, if using fett263's prop file hold Aux and click PWR while ON (pointing up) to dim blade in 25% increments.
    InOutTrL<TrWipeSparkTip<White,175,250>,TrColorCycle<500>>,
      //Spark tip ignition, cycle down retraction
    TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<White,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,Int<500>,Int<5500>>,Int<-4000>>>,TrFade<1100>>,EFFECT_RETRACTION>,
      //White flicker retraction effect
    TransitionEffectL<TrConcat<TrInstant,AlphaL<White,Bump<Int<0>,Int<10000>>>,TrFade<1600>,AlphaL<RotateColorsX<Variation,Orange>,Bump<Int<0>,Int<8000>>>,TrFade<1400>,AlphaL<RotateColorsX<Variation,Red>,Bump<Int<0>,Int<6000>>>,TrFade<1000>>,EFFECT_RETRACTION>,
      //Emitter cool off retraction effect
      //TransitionEffectL<TrConcat<TrDelay<1500>,Black,TrFade<1000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_BOOT>,
      //TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_NEWFONT>,
      //Optional/alternate passive battery monitor, on boot (1st line) or font change (2nd line) you will get a visual indicator at the emitter of your current battery level. This also works without a blade if you have a lit emitter or blade plug. Green is Full, Red is Low (the color will blend from Green to Red as the battery is depleted), the indicator will fade out after 3000 ms and not display again until powered down and back up or fonts change.
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrDelay<2000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrFade<1000>>,EFFECT_BATTERY_LEVEL>,
      //On demand battery level, if using fett263's prop file Hold AUX and click PWR while OFF, the battery level is represented by the location on the blade; tip = full, hilt = low and color; green = full, yellow = half, red = low
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<Trigger<EFFECT_PREON,Int<3000>,Int<2000>,Int<1000>>,BrownNoiseFlicker<Black,RotateColorsX<Variation,Red>,100>,RandomPerLEDFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb16<14386,0,0>>>,BrownNoiseFlicker<Mix<NoisySoundLevel,RotateColorsX<Variation,Red>,RotateColorsX<Int<4000>,RotateColorsX<Variation,Red>>>,DarkOrange,50>>,SmoothStep<Scale<NoisySoundLevel,Int<-1000>,Int<25000>>,Int<-4000>>>,TrDelay<6500>>,EFFECT_PREON>,
      //Noise responsive preon
    TransitionEffectL<TrConcat<TrDelay<3000>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Red>,Int<115>,Int<400>,Int<250>,Int<0>>>,TrDelay<1000>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Red>,Int<215>,Int<300>,Int<395>,Int<0>>>,TrDelay<1500>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Red>,Int<345>,Int<200>,Int<500>,Int<0>>>,TrDelay<1500>,AlphaL<RotateColorsX<Variation,Red>,Bump<Int<0>,Int<6000>>>,TrBoing<500,2>>,EFFECT_PREON>,
      //Charge up, wave out preon
    TransitionEffectL<TrConcat<TrFade<1500>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Red>,10>,Bump<Int<0>,Int<4000>>>,TrFade<2000>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Orange>,15>,Bump<Int<0>,Int<5000>>>,TrFade<2500>,AlphaL<HumpFlickerL<White,20>,Bump<Int<0>,Int<6000>>>,TrBoing<500,2>>,EFFECT_PREON>
      //Emitter heat up preon
    >>(),
    StyleFirePtr<RED, YELLOW, 1>(),
    StyleFirePtr<RED, YELLOW, 2>(),
    StyleFirePtr<RED, YELLOW, 3>(), "apocalypse"},

   { "arcane;common", "tracks/track1.wav",
      //Theory2Button.h "Decieved"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<NavajoWhite,Rgb<255,225,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<1060>,Black>>>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StylePtr<Layers<Layers<Blue,RandomL<Black>>,InOutHelperL<InOutFuncX<Int<300>,Int<800>>,Pulsing<Red,Black,2000>>>>(),
    "arcane"},

   { "ashely;common", "tracks/track1.wav",
      //Theory2Button.h "Chosen_One"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Blue>,RotateColorsX<Variation,Rgb<0,0,128>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<NavajoWhite,Rgb<255,225,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StyleFirePtr<BLUE, CYAN, 1>(),
    StyleFirePtr<BLUE, CYAN, 2>(),
    StyleFirePtr<BLUE, CYAN, 3>(), "ashely"},

   { "assassin;common", "tracks/track1.wav",
    StylePtr<Layers<
    HumpFlicker<RotateColorsX<Variation,Green>,RotateColorsX<Variation,Rgb<0,128,0>>,50>,
      //Green humpflicker
    AlphaL<Stripes<2500,-2750,RotateColorsX<Variation,Green>,RotateColorsX<Variation,Rgb<25,60,0>>,Pulsing<RotateColorsX<Variation,Rgb<0,30,0>>,Black,800>>,SwingSpeed<375>>,
      //Swing effect, rippling green
    LockupTrL<Layers<
    AlphaL<AudioFlickerL<Rgb<255,240,80>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,
    AlphaL<LemonChiffon,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,
      //Responsive lockup
    ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,
      //Responsive lightning block
    AlphaL<RotateColorsX<Variation,Rgb16<21301,65535,0>>,SmoothStep<Scale<SlowNoise<Int<2500>>,Int<1000>,Int<3000>>,Int<-4000>>>,
      //Sparking emitter flare
    ResponsiveStabL<Red>,
      //Responsive stab
    EffectSequence<EFFECT_BLAST,TransitionEffectL<TrConcat<TrInstant,AlphaL<White,BlastF<200,200>>,TrFade<300>>,EFFECT_BLAST>,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,ResponsiveBlastWaveL<White,Scale<SwingSpeed<400>,Int<500>,Int<200>>,Scale<SwingSpeed<400>,Int<100>,Int<400>>>,ResponsiveBlastFadeL<White,Scale<SwingSpeed<400>,Int<6000>,Int<12000>>,Scale<SwingSpeed<400>,Int<400>,Int<100>>>,ResponsiveBlastL<White,Scale<SwingSpeed<400>,Int<400>,Int<100>>,Scale<SwingSpeed<400>,Int<200>,Int<100>>,Scale<SwingSpeed<400>,Int<400>,Int<200>>>>,
      //Multi-blast, blaster reflect cycles through different responsive effects
    ResponsiveClashL<TransitionEffect<Rgb<255,240,80>,LemonChiffon,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
      //Responsive clash
    TransitionEffectL<TrConcat<TrInstant,Stripes<3000,-3500,RotateColorsX<Variation,Rgb16<38402,65535,3934>>,RandomPerLEDFlicker<Rgb<60,60,60>,Black>,BrownNoiseFlicker<RotateColorsX<Variation,Rgb16<38402,65535,3934>>,Rgb<30,30,30>,200>,RandomPerLEDFlicker<Rgb<80,80,80>,Rgb<30,30,30>>>,TrFade<500>>,EFFECT_IGNITION>,
      //Unstable ignition
    TransitionEffectL<TrConcat<TrInstant,AudioFlickerL<RotateColorsX<Variation,Rgb16<54757,65535,0>>>,TrFade<1000>>,EFFECT_RETRACTION>,
      //Bright retraction
    LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,
      //Drag
    LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,
      //Responsive melt
    EffectSequence<EFFECT_POWERSAVE,AlphaL<Black,Int<8192>>,AlphaL<Black,Int<16384>>,AlphaL<Black,Int<24576>>,AlphaL<Black,Int<0>>>,
      //Power save, if using fett263's prop file hold Aux and click PWR while ON (pointing up) to dim blade in 25% increments.
    InOutTrL<TrWipeSparkTip<White,250>,TrWipeInSparkTip<White,656>>,
      //Spark tip ignition and retraction
    //TransitionEffectL<TrConcat<TrDelay<1500>,Black,TrFade<1000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_BOOT>,
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_NEWFONT>,
      //Optional/alternate passive battery monitor, on boot (1st line) or font change (2nd line) you will get a visual indicator at the emitter of your current battery level. This also works without a blade if you have a lit emitter or blade plug. Green is Full, Red is Low (the color will blend from Green to Red as the battery is depleted), the indicator will fade out after 3000 ms and not display again until powered down and back up or fonts change.
    TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrDelay<2000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrFade<1000>>,EFFECT_BATTERY_LEVEL>
      //On demand battery level, if using fett263's prop file Hold AUX and click PWR while OFF, the battery level is represented by the location on the blade; tip = full, hilt = low and color; green = full, yellow = half, red = low
    >>(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(), "assassin"},

   { "banished-prince;common", "tracks/track1.wav",
      //Theory2Button.h "Dark_Lord"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,240,80>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<LemonChiffon,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,180,50>,LemonChiffon,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<LemonChiffon,Rgb<255,180,50>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,240,80>,LemonChiffon,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,240,80>,LemonChiffon,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,1000>,TrWipeIn<1060>,Black>>>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(), "banished/nprince"},

   { "battle1;common", "tracks/track1.wav",
      //Theory2Button.h "Battle1"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Green>,RotateColorsX<Variation,Rgb<0,128,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,150,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<Moccasin,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<Moccasin,Rgb<255,150,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(), "battle1"},

   { "battle2;common", "tracks/track1.wav",
      //Theory2Button.h "Battle2"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Rgb<180,130,0>>,RotateColorsX<Variation,Rgb<90,65,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,150,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<Moccasin,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<Moccasin,Rgb<255,150,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(), "battle2"},

   { "battle3;common", "tracks/track1.wav",
      //Theory2Button.h "Battle3"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Rgb<95,0,210>>,RotateColorsX<Variation,Rgb<48,0,105>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,150,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<Moccasin,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<Moccasin,Rgb<255,150,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,150,0>,Moccasin,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(), "battle3"},

   { "bode-akuna;common", "tracks/track1.wav",
/* copyright Fett263 ShimmerBlade (Crystal Chamber) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#ShimmerBlade
OS6.7 v4.021
This Style Contains 38880 Unique Combinations
Base Style: Interactive Shimmer Blade

Off Behavior Options: Default (0): Off, 1: AudioFlicker (Two Color), 2: Luke ROTJ (Green Arrow), 3: Luke ROTJ (Red Arrow), 4: Kyber Flow Up, 5: Kyber Flow Down

Base Color: Rgb<255,0,0> (0)

--Effects Included--
Preon Effect Options: Default (0): Full Blade Heat Up, 1: Sparking (Base Color), 2: Overload (Base Color), 3: Rey TROS Spark, 4: Erratic (Base Color)
Ignition Effect Options: Default (0): Instant, 1: SparkTip Ignition, 2: Gravity Ignition, 3: Stack, 4: Assemble, 5: Wipe In + Fade
PowerUp Effect Options: Default (0): Power Burst Forward, 1: Unstable Power Up Reverse, 2: Unstable Power Up Forward, 3: Power Surge (Unstable V2), 4: Power Burst Reverse, 5: Power Surge (Unstable V1)
Retraction Effect Options: Default (0): Instant, 1: Standard Retraction, 2: Fade Out, 3: Metal Forge (Cool Down), 4: Run Up + Fade, 5: Unstack
CoolDown Effect Options: Default (0): Power Burst Reverse, 1: Power Burst Forward, 2: Unstable Cool Down Reverse, 3: Power Flash, 4: Unstable Cool Down Forward, 5: Disable
Lockup Effect: Lockup Ripple Up
LightningBlock Effect: Lightning After Effect
Blast Effect (Randomly Selected): Blast Wave Up (Sound Based), Blast Ripple Fade Up, Blast Ripple Down, Blast Wave Up (Random), Blast Wave Down (Random), Full Blade Blast Fade
Clash Effect: Clash Ripple (Full Blade)
Rain Effect: Rain Spark
Battery Level: Full Blade (Green to Red)
*/
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
//    StylePtr<Layers<Mix<HoldPeakF<SwingSpeed<200>,Int<300>,Scale<SwingSpeed<200>,Int<8000>,Int<24000>>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RandomFlicker<Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,StripesX<Int<16000>,Scale<HoldPeakF<SwingSpeed<200>,Scale<SwingSpeed<200>,Int<1000>,Int<4000>>,Scale<SwingSpeed<200>,Int<4000>,Int<8000>>>,Int<-100>,Int<-3000>>,Mix<Int<24576>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<8192>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>>,TransitionEffectL<TrSelect<IntArg<IGNITION_POWER_UP_ARG,0>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrInstant,HumpFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,40>,TrFade<1200>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrInstant,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<1200>>>,EFFECT_IGNITION>,TransitionEffectL<TrSelect<IntArg<RETRACTION_COOL_DOWN_ARG,0>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrInstant>,EFFECT_RETRACTION>,SparkleL<White>,TransitionEffectL<TrRandom<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<WavLen<>,Int<100>,Int<400>>,Int<100>,Scale<WavLen<>,Int<100>,Int<400>>,Int<0>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrWaveX<Remap<CenterDistF<EffectPosition<EFFECT_BLAST>>,Stripes<1500,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Int<160>,Int<100>,Int<300>,Int<0>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrSparkX<Remap<CenterDistF<EffectPosition<EFFECT_BLAST>>,Stripes<2000,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Int<100>,Int<300>,Int<32768>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<0>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<32768>>,TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,TrFade<300>>>,EFFECT_BLAST>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,Remap<CenterDistF<EffectPosition<EFFECT_CLASH>>,Stripes<2000,-2000,RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,SmoothStep<ClashImpactF<>,Int<-4000>>>,TrFadeX<Scale<ClashImpactF<>,Int<100>,Int<300>>>>,EFFECT_LOCKUP_BEGIN>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrSparkX<Stripes<2000,-2000,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Int<100>,Int<300>,Int<0>>>,EFFECT_LOCKUP_END>,LockupTrL<AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrInstant,TrConcat<TrInstant,Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrFade<1000>>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,InOutTrL<TrSelect<IntArg<IGNITION_OPTION_ARG,0>,TrInstant,TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,IgnitionTime<0>>,TrSelect<Scale<IsLessThan<BladeAngle<>,Int<18384>>,Scale<IsGreaterThan<SwingAcceleration<>,Int<16384>>,Int<0>,Int<2>>,Int<1>>,TrWipeInX<Scale<BladeAngle<>,Int<1000>,Int<100>>>,TrWipeX<Scale<BladeAngle<>,Int<100>,Int<1000>>>,TrWipe<100>>,TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>>,TrConcat<TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>>,TrJoinR<TrWipeInX<IgnitionTime<0>>,TrSmoothFadeX<IgnitionTime<0>>>>,TrSelect<IntArg<RETRACTION_OPTION_ARG,0>,TrInstant,TrWipeInX<RetractionTime<0>>,TrFadeX<RetractionTime<0>>,TrConcat<TrFadeX<RetractionTime<0>>,White,TrFadeX<RetractionTime<0>>,DarkOrange,TrFadeX<RetractionTime<0>>,Red,TrFadeX<RetractionTime<0>>>,TrJoin<TrWipeX<RetractionTime<0>>,TrSmoothFadeX<RetractionTime<0>>>,TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8192>>>>>,ColorSelect<IntArg<OFF_OPTION_ARG,0>,TrInstant,Black,AudioFlicker<RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,RgbArg<ALT_COLOR_ARG,Rgb<128,0,0>>>,TransitionLoop<RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,TrConcat<TrBoing<3000,9>,Black,TrDelay<2000>>>,TransitionLoop<Black,TrConcat<TrDelay<3000>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,TrBoing<2000,5>>>,Stripes<5000,-2500,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,Stripes<5000,2500,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>>>,TransitionEffectL<TrSelect<IntArg<PREON_OPTION_ARG,0>,TrConcat<TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,Red,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,Orange,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,White,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>>,TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,32768>,Sum<IntArg<PREON_SIZE_ARG,32768>,Int<4000>>>,Int<-2000>>>,TrDelayX<WavLen<EFFECT_PREON>>>,TrConcat<TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,10>,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-4000>>>,TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,15>,SmoothStep<Sum<Int<2000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,20>,SmoothStep<Sum<Int<4000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrBoingX<Mult<Int<8192>,WavLen<EFFECT_PREON>>,3>>,TrConcat<TrJoin<TrDelayX<Int<100>>,TrInstant>,AlphaL<Green,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-2000>>>,TrWipe<100>,AlphaL<DodgerBlue,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-2000>>>,TrDelayX<Sum<WavLen<EFFECT_PREON>,Int<200>>>>,TrConcat<TrBoingX<Mult<Int<10922>,WavLen<EFFECT_PREON>>,5>,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>>,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-4000>>>,TrBoingX<Mult<Int<10922>,WavLen<EFFECT_PREON>>,3>,Black,TrBoingX<Mult<Int<7260>,WavLen<EFFECT_PREON>>,3>,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<200>>,SmoothStep<Sum<Int<4000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrBoingX<Mult<Int<3664>,WavLen<EFFECT_PREON>>,3>>>,EFFECT_PREON>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrInstant>,Mix<BatteryLevel,Red,Green>,TrFade<300>>,EFFECT_BATTERY_LEVEL>>>(),
/* copyright Fett263 ShimmerBlade (Crystal Chamber) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#ShimmerBlade
OS6.7 v4.021
This Style Contains 38880 Unique Combinations
Base Style: Interactive Shimmer Blade

Off Behavior Options: Default (0): Off, 1: AudioFlicker (Two Color), 2: Luke ROTJ (Green Arrow), 3: Luke ROTJ (Red Arrow), 4: Kyber Flow Up, 5: Kyber Flow Down

Base Color: Rgb<255,0,0> (0)

--Effects Included--
Preon Effect Options: Default (0): Full Blade Heat Up, 1: Sparking (Base Color), 2: Overload (Base Color), 3: Rey TROS Spark, 4: Erratic (Base Color)
Ignition Effect Options: Default (0): Instant, 1: SparkTip Ignition, 2: Gravity Ignition, 3: Stack, 4: Assemble, 5: Wipe In + Fade
PowerUp Effect Options: Default (0): Power Burst Forward, 1: Unstable Power Up Reverse, 2: Unstable Power Up Forward, 3: Power Surge (Unstable V2), 4: Power Burst Reverse, 5: Power Surge (Unstable V1)
Retraction Effect Options: Default (0): Instant, 1: Standard Retraction, 2: Fade Out, 3: Metal Forge (Cool Down), 4: Run Up + Fade, 5: Unstack
CoolDown Effect Options: Default (0): Power Burst Reverse, 1: Power Burst Forward, 2: Unstable Cool Down Reverse, 3: Power Flash, 4: Unstable Cool Down Forward, 5: Disable
Lockup Effect: Lockup Ripple Up
LightningBlock Effect: Lightning After Effect
Blast Effect (Randomly Selected): Blast Wave Up (Sound Based), Blast Ripple Fade Up, Blast Ripple Down, Blast Wave Up (Random), Blast Wave Down (Random), Full Blade Blast Fade
Clash Effect: Clash Ripple (Full Blade)
Rain Effect: Rain Spark
Battery Level: Full Blade (Green to Red)
*/
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),

//    StylePtr<Layers<Mix<HoldPeakF<SwingSpeed<200>,Int<300>,Scale<SwingSpeed<200>,Int<8000>,Int<24000>>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RandomFlicker<Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,StripesX<Int<16000>,Scale<HoldPeakF<SwingSpeed<200>,Scale<SwingSpeed<200>,Int<1000>,Int<4000>>,Scale<SwingSpeed<200>,Int<4000>,Int<8000>>>,Int<-100>,Int<-3000>>,Mix<Int<24576>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<8192>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>>,TransitionEffectL<TrSelect<IntArg<IGNITION_POWER_UP_ARG,0>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrInstant,HumpFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,40>,TrFade<1200>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrInstant,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<1200>>>,EFFECT_IGNITION>,TransitionEffectL<TrSelect<IntArg<RETRACTION_COOL_DOWN_ARG,0>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrInstant>,EFFECT_RETRACTION>,SparkleL<White>,TransitionEffectL<TrRandom<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<WavLen<>,Int<100>,Int<400>>,Int<100>,Scale<WavLen<>,Int<100>,Int<400>>,Int<0>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrWaveX<Remap<CenterDistF<EffectPosition<EFFECT_BLAST>>,Stripes<1500,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Int<160>,Int<100>,Int<300>,Int<0>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrSparkX<Remap<CenterDistF<EffectPosition<EFFECT_BLAST>>,Stripes<2000,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Int<100>,Int<300>,Int<32768>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<0>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<32768>>,TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,TrFade<300>>>,EFFECT_BLAST>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,Remap<CenterDistF<EffectPosition<EFFECT_CLASH>>,Stripes<2000,-2000,RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,SmoothStep<ClashImpactF<>,Int<-4000>>>,TrFadeX<Scale<ClashImpactF<>,Int<100>,Int<300>>>>,EFFECT_LOCKUP_BEGIN>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrSparkX<Stripes<2000,-2000,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Int<100>,Int<300>,Int<0>>>,EFFECT_LOCKUP_END>,LockupTrL<AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrInstant,TrConcat<TrInstant,Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrFade<1000>>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,InOutTrL<TrSelect<IntArg<IGNITION_OPTION_ARG,0>,TrInstant,TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,IgnitionTime<0>>,TrSelect<Scale<IsLessThan<BladeAngle<>,Int<18384>>,Scale<IsGreaterThan<SwingAcceleration<>,Int<16384>>,Int<0>,Int<2>>,Int<1>>,TrWipeInX<Scale<BladeAngle<>,Int<1000>,Int<100>>>,TrWipeX<Scale<BladeAngle<>,Int<100>,Int<1000>>>,TrWipe<100>>,TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>>,TrConcat<TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>>,TrJoinR<TrWipeInX<IgnitionTime<0>>,TrSmoothFadeX<IgnitionTime<0>>>>,TrSelect<IntArg<RETRACTION_OPTION_ARG,0>,TrInstant,TrWipeInX<RetractionTime<0>>,TrFadeX<RetractionTime<0>>,TrConcat<TrFadeX<RetractionTime<0>>,White,TrFadeX<RetractionTime<0>>,DarkOrange,TrFadeX<RetractionTime<0>>,Red,TrFadeX<RetractionTime<0>>>,TrJoin<TrWipeX<RetractionTime<0>>,TrSmoothFadeX<RetractionTime<0>>>,TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8192>>>>>,ColorSelect<IntArg<OFF_OPTION_ARG,0>,TrInstant,Black,AudioFlicker<RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,RgbArg<ALT_COLOR_ARG,Rgb<128,0,0>>>,TransitionLoop<RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,TrConcat<TrBoing<3000,9>,Black,TrDelay<2000>>>,TransitionLoop<Black,TrConcat<TrDelay<3000>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,TrBoing<2000,5>>>,Stripes<5000,-2500,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,Stripes<5000,2500,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>>>,TransitionEffectL<TrSelect<IntArg<PREON_OPTION_ARG,0>,TrConcat<TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,Red,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,Orange,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,White,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>>,TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,32768>,Sum<IntArg<PREON_SIZE_ARG,32768>,Int<4000>>>,Int<-2000>>>,TrDelayX<WavLen<EFFECT_PREON>>>,TrConcat<TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,10>,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-4000>>>,TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,15>,SmoothStep<Sum<Int<2000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,20>,SmoothStep<Sum<Int<4000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrBoingX<Mult<Int<8192>,WavLen<EFFECT_PREON>>,3>>,TrConcat<TrJoin<TrDelayX<Int<100>>,TrInstant>,AlphaL<Green,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-2000>>>,TrWipe<100>,AlphaL<DodgerBlue,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-2000>>>,TrDelayX<Sum<WavLen<EFFECT_PREON>,Int<200>>>>,TrConcat<TrBoingX<Mult<Int<10922>,WavLen<EFFECT_PREON>>,5>,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>>,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-4000>>>,TrBoingX<Mult<Int<10922>,WavLen<EFFECT_PREON>>,3>,Black,TrBoingX<Mult<Int<7260>,WavLen<EFFECT_PREON>>,3>,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<200>>,SmoothStep<Sum<Int<4000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrBoingX<Mult<Int<3664>,WavLen<EFFECT_PREON>>,3>>>,EFFECT_PREON>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrInstant>,Mix<BatteryLevel,Red,Green>,TrFade<300>>,EFFECT_BATTERY_LEVEL>>>(),
/* copyright Fett263 ShimmerBlade (Crystal Chamber) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#ShimmerBlade
OS6.7 v4.021
This Style Contains 38880 Unique Combinations
Base Style: Interactive Shimmer Blade

Off Behavior Options: Default (0): Off, 1: AudioFlicker (Two Color), 2: Luke ROTJ (Green Arrow), 3: Luke ROTJ (Red Arrow), 4: Kyber Flow Up, 5: Kyber Flow Down

Base Color: Rgb<255,0,0> (0)

--Effects Included--
Preon Effect Options: Default (0): Full Blade Heat Up, 1: Sparking (Base Color), 2: Overload (Base Color), 3: Rey TROS Spark, 4: Erratic (Base Color)
Ignition Effect Options: Default (0): Instant, 1: SparkTip Ignition, 2: Gravity Ignition, 3: Stack, 4: Assemble, 5: Wipe In + Fade
PowerUp Effect Options: Default (0): Power Burst Forward, 1: Unstable Power Up Reverse, 2: Unstable Power Up Forward, 3: Power Surge (Unstable V2), 4: Power Burst Reverse, 5: Power Surge (Unstable V1)
Retraction Effect Options: Default (0): Instant, 1: Standard Retraction, 2: Fade Out, 3: Metal Forge (Cool Down), 4: Run Up + Fade, 5: Unstack
CoolDown Effect Options: Default (0): Power Burst Reverse, 1: Power Burst Forward, 2: Unstable Cool Down Reverse, 3: Power Flash, 4: Unstable Cool Down Forward, 5: Disable
Lockup Effect: Lockup Ripple Up
LightningBlock Effect: Lightning After Effect
Blast Effect (Randomly Selected): Blast Wave Up (Sound Based), Blast Ripple Fade Up, Blast Ripple Down, Blast Wave Up (Random), Blast Wave Down (Random), Full Blade Blast Fade
Clash Effect: Clash Ripple (Full Blade)
Rain Effect: Rain Spark
Battery Level: Full Blade (Green to Red)
*/
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
//    StylePtr<Layers<Mix<HoldPeakF<SwingSpeed<200>,Int<300>,Scale<SwingSpeed<200>,Int<8000>,Int<24000>>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RandomFlicker<Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,StripesX<Int<16000>,Scale<HoldPeakF<SwingSpeed<200>,Scale<SwingSpeed<200>,Int<1000>,Int<4000>>,Scale<SwingSpeed<200>,Int<4000>,Int<8000>>>,Int<-100>,Int<-3000>>,Mix<Int<24576>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<8192>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>>,TransitionEffectL<TrSelect<IntArg<IGNITION_POWER_UP_ARG,0>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrInstant,HumpFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,40>,TrFade<1200>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrInstant,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<1200>>>,EFFECT_IGNITION>,TransitionEffectL<TrSelect<IntArg<RETRACTION_COOL_DOWN_ARG,0>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrInstant>,EFFECT_RETRACTION>,SparkleL<White>,TransitionEffectL<TrRandom<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<WavLen<>,Int<100>,Int<400>>,Int<100>,Scale<WavLen<>,Int<100>,Int<400>>,Int<0>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrWaveX<Remap<CenterDistF<EffectPosition<EFFECT_BLAST>>,Stripes<1500,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Int<160>,Int<100>,Int<300>,Int<0>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrSparkX<Remap<CenterDistF<EffectPosition<EFFECT_BLAST>>,Stripes<2000,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Int<100>,Int<300>,Int<32768>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<0>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<32768>>,TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,TrFade<300>>>,EFFECT_BLAST>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,Remap<CenterDistF<EffectPosition<EFFECT_CLASH>>,Stripes<2000,-2000,RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,SmoothStep<ClashImpactF<>,Int<-4000>>>,TrFadeX<Scale<ClashImpactF<>,Int<100>,Int<300>>>>,EFFECT_LOCKUP_BEGIN>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrSparkX<Stripes<2000,-2000,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Int<100>,Int<300>,Int<0>>>,EFFECT_LOCKUP_END>,LockupTrL<AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrInstant,TrConcat<TrInstant,Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrFade<1000>>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,InOutTrL<TrSelect<IntArg<IGNITION_OPTION_ARG,0>,TrInstant,TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,IgnitionTime<0>>,TrSelect<Scale<IsLessThan<BladeAngle<>,Int<18384>>,Scale<IsGreaterThan<SwingAcceleration<>,Int<16384>>,Int<0>,Int<2>>,Int<1>>,TrWipeInX<Scale<BladeAngle<>,Int<1000>,Int<100>>>,TrWipeX<Scale<BladeAngle<>,Int<100>,Int<1000>>>,TrWipe<100>>,TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>>,TrConcat<TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>>,TrJoinR<TrWipeInX<IgnitionTime<0>>,TrSmoothFadeX<IgnitionTime<0>>>>,TrSelect<IntArg<RETRACTION_OPTION_ARG,0>,TrInstant,TrWipeInX<RetractionTime<0>>,TrFadeX<RetractionTime<0>>,TrConcat<TrFadeX<RetractionTime<0>>,White,TrFadeX<RetractionTime<0>>,DarkOrange,TrFadeX<RetractionTime<0>>,Red,TrFadeX<RetractionTime<0>>>,TrJoin<TrWipeX<RetractionTime<0>>,TrSmoothFadeX<RetractionTime<0>>>,TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8192>>>>>,ColorSelect<IntArg<OFF_OPTION_ARG,0>,TrInstant,Black,AudioFlicker<RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,RgbArg<ALT_COLOR_ARG,Rgb<128,0,0>>>,TransitionLoop<RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,TrConcat<TrBoing<3000,9>,Black,TrDelay<2000>>>,TransitionLoop<Black,TrConcat<TrDelay<3000>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,TrBoing<2000,5>>>,Stripes<5000,-2500,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,Stripes<5000,2500,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>>>,TransitionEffectL<TrSelect<IntArg<PREON_OPTION_ARG,0>,TrConcat<TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,Red,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,Orange,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,White,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>>,TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,32768>,Sum<IntArg<PREON_SIZE_ARG,32768>,Int<4000>>>,Int<-2000>>>,TrDelayX<WavLen<EFFECT_PREON>>>,TrConcat<TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,10>,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-4000>>>,TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,15>,SmoothStep<Sum<Int<2000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,20>,SmoothStep<Sum<Int<4000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrBoingX<Mult<Int<8192>,WavLen<EFFECT_PREON>>,3>>,TrConcat<TrJoin<TrDelayX<Int<100>>,TrInstant>,AlphaL<Green,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-2000>>>,TrWipe<100>,AlphaL<DodgerBlue,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-2000>>>,TrDelayX<Sum<WavLen<EFFECT_PREON>,Int<200>>>>,TrConcat<TrBoingX<Mult<Int<10922>,WavLen<EFFECT_PREON>>,5>,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>>,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-4000>>>,TrBoingX<Mult<Int<10922>,WavLen<EFFECT_PREON>>,3>,Black,TrBoingX<Mult<Int<7260>,WavLen<EFFECT_PREON>>,3>,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<200>>,SmoothStep<Sum<Int<4000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrBoingX<Mult<Int<3664>,WavLen<EFFECT_PREON>>,3>>>,EFFECT_PREON>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrInstant>,Mix<BatteryLevel,Red,Green>,TrFade<300>>,EFFECT_BATTERY_LEVEL>>>(),
/* copyright Fett263 ShimmerBlade (Crystal Chamber) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#ShimmerBlade
OS6.7 v4.021
This Style Contains 38880 Unique Combinations
Base Style: Interactive Shimmer Blade

Off Behavior Options: Default (0): Off, 1: AudioFlicker (Two Color), 2: Luke ROTJ (Green Arrow), 3: Luke ROTJ (Red Arrow), 4: Kyber Flow Up, 5: Kyber Flow Down

Base Color: Rgb<255,0,0> (0)

--Effects Included--
Preon Effect Options: Default (0): Full Blade Heat Up, 1: Sparking (Base Color), 2: Overload (Base Color), 3: Rey TROS Spark, 4: Erratic (Base Color)
Ignition Effect Options: Default (0): Instant, 1: SparkTip Ignition, 2: Gravity Ignition, 3: Stack, 4: Assemble, 5: Wipe In + Fade
PowerUp Effect Options: Default (0): Power Burst Forward, 1: Unstable Power Up Reverse, 2: Unstable Power Up Forward, 3: Power Surge (Unstable V2), 4: Power Burst Reverse, 5: Power Surge (Unstable V1)
Retraction Effect Options: Default (0): Instant, 1: Standard Retraction, 2: Fade Out, 3: Metal Forge (Cool Down), 4: Run Up + Fade, 5: Unstack
CoolDown Effect Options: Default (0): Power Burst Reverse, 1: Power Burst Forward, 2: Unstable Cool Down Reverse, 3: Power Flash, 4: Unstable Cool Down Forward, 5: Disable
Lockup Effect: Lockup Ripple Up
LightningBlock Effect: Lightning After Effect
Blast Effect (Randomly Selected): Blast Wave Up (Sound Based), Blast Ripple Fade Up, Blast Ripple Down, Blast Wave Up (Random), Blast Wave Down (Random), Full Blade Blast Fade
Clash Effect: Clash Ripple (Full Blade)
Rain Effect: Rain Spark
Battery Level: Full Blade (Green to Red)
*/
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
//    StylePtr<Layers<Mix<HoldPeakF<SwingSpeed<200>,Int<300>,Scale<SwingSpeed<200>,Int<8000>,Int<24000>>>,Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RandomFlicker<Mix<Int<16384>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,StripesX<Int<16000>,Scale<HoldPeakF<SwingSpeed<200>,Scale<SwingSpeed<200>,Int<1000>,Int<4000>>,Scale<SwingSpeed<200>,Int<4000>,Int<8000>>>,Int<-100>,Int<-3000>>,Mix<Int<24576>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<8192>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>>>>>,TransitionEffectL<TrSelect<IntArg<IGNITION_POWER_UP_ARG,0>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrInstant,HumpFlickerL<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,40>,TrFade<1200>>,TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrInstant,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<1200>>>,EFFECT_IGNITION>,TransitionEffectL<TrSelect<IntArg<RETRACTION_COOL_DOWN_ARG,0>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<5000,-2500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,TrFade<1000>>,TrConcat<TrJoin<TrDelayX<RetractionTime<0>>,TrInstant>,Stripes<3000,-3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>>>>,TrFade<800>>,TrInstant>,EFFECT_RETRACTION>,SparkleL<White>,TransitionEffectL<TrRandom<TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<WavLen<>,Int<100>,Int<400>>,Int<100>,Scale<WavLen<>,Int<100>,Int<400>>,Int<0>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrWaveX<Remap<CenterDistF<EffectPosition<EFFECT_BLAST>>,Stripes<1500,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Int<160>,Int<100>,Int<300>,Int<0>>,TrConcat<TrInstant,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrSparkX<Remap<CenterDistF<EffectPosition<EFFECT_BLAST>>,Stripes<2000,-2000,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>>>>,Int<100>,Int<300>,Int<32768>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<0>>,TrWaveX<RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<32768>>,TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<255,255,255>>,TrFade<300>>>,EFFECT_BLAST>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,Remap<CenterDistF<EffectPosition<EFFECT_CLASH>>,Stripes<2000,-2000,RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<CLASH_COLOR_ARG,Rgb<255,255,255>>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,SmoothStep<ClashImpactF<>,Int<-4000>>>,TrFadeX<Scale<ClashImpactF<>,Int<100>,Int<300>>>>,EFFECT_LOCKUP_BEGIN>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Bump<Int<16384>,Int<6000>>>,TrFade<50>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrSparkX<Stripes<2000,-2000,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>,Mix<Int<2096>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<255,255,255>>>>,Int<100>,Int<300>,Int<0>>>,EFFECT_LOCKUP_END>,LockupTrL<AlphaL<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Int<0>>,TrInstant,TrConcat<TrInstant,Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrFade<1000>>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,InOutTrL<TrSelect<IntArg<IGNITION_OPTION_ARG,0>,TrInstant,TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,IgnitionTime<0>>,TrSelect<Scale<IsLessThan<BladeAngle<>,Int<18384>>,Scale<IsGreaterThan<SwingAcceleration<>,Int<16384>>,Int<0>,Int<2>>,Int<1>>,TrWipeInX<Scale<BladeAngle<>,Int<1000>,Int<100>>>,TrWipeX<Scale<BladeAngle<>,Int<100>,Int<1000>>>,TrWipe<100>>,TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrDelayX<Mult<IgnitionTime<0>,Int<8192>>>>,TrConcat<TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrSparkX<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>,Mult<IgnitionTime<0>,Int<6554>>,Int<32768>>>,TrJoinR<TrWipeInX<IgnitionTime<0>>,TrSmoothFadeX<IgnitionTime<0>>>>,TrSelect<IntArg<RETRACTION_OPTION_ARG,0>,TrInstant,TrWipeInX<RetractionTime<0>>,TrFadeX<RetractionTime<0>>,TrConcat<TrFadeX<RetractionTime<0>>,White,TrFadeX<RetractionTime<0>>,DarkOrange,TrFadeX<RetractionTime<0>>,Red,TrFadeX<RetractionTime<0>>>,TrJoin<TrWipeX<RetractionTime<0>>,TrSmoothFadeX<RetractionTime<0>>>,TrConcat<TrInstant,AlphaL<Black,SmoothStep<Int<26216>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<19662>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<13108>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8172>>>,AlphaL<Black,SmoothStep<Int<6554>,Int<0>>>,TrDelayX<Mult<RetractionTime<0>,Int<8192>>>>>,ColorSelect<IntArg<OFF_OPTION_ARG,0>,TrInstant,Black,AudioFlicker<RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,RgbArg<ALT_COLOR_ARG,Rgb<128,0,0>>>,TransitionLoop<RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,TrConcat<TrBoing<3000,9>,Black,TrDelay<2000>>>,TransitionLoop<Black,TrConcat<TrDelay<3000>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,TrBoing<2000,5>>>,Stripes<5000,-2500,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,Stripes<5000,2500,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>,Mix<Int<16384>,Black,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>,RgbArg<OFF_COLOR_ARG,Rgb<255,0,0>>>>>,TransitionEffectL<TrSelect<IntArg<PREON_OPTION_ARG,0>,TrConcat<TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,Red,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,Orange,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>,White,TrFadeX<Mult<WavLen<EFFECT_PREON>,Int<8192>>>>,TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,32768>,Sum<IntArg<PREON_SIZE_ARG,32768>,Int<4000>>>,Int<-2000>>>,TrDelayX<WavLen<EFFECT_PREON>>>,TrConcat<TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,10>,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-4000>>>,TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,15>,SmoothStep<Sum<Int<2000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrFadeX<Mult<Int<8192>,WavLen<EFFECT_PREON>>>,AlphaL<HumpFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,20>,SmoothStep<Sum<Int<4000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrBoingX<Mult<Int<8192>,WavLen<EFFECT_PREON>>,3>>,TrConcat<TrJoin<TrDelayX<Int<100>>,TrInstant>,AlphaL<Green,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-2000>>>,TrWipe<100>,AlphaL<DodgerBlue,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-2000>>>,TrDelayX<Sum<WavLen<EFFECT_PREON>,Int<200>>>>,TrConcat<TrBoingX<Mult<Int<10922>,WavLen<EFFECT_PREON>>,5>,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<100>>,SmoothStep<IntArg<PREON_SIZE_ARG,32768>,Int<-4000>>>,TrBoingX<Mult<Int<10922>,WavLen<EFFECT_PREON>>,3>,Black,TrBoingX<Mult<Int<7260>,WavLen<EFFECT_PREON>>,3>,AlphaL<BrownNoiseFlickerL<RgbArg<BASE_COLOR_ARG,Rgb<255,0,0>>,Int<200>>,SmoothStep<Sum<Int<4000>,IntArg<PREON_SIZE_ARG,32768>>,Int<-4000>>>,TrBoingX<Mult<Int<3664>,WavLen<EFFECT_PREON>>,3>>>,EFFECT_PREON>,TransitionEffectL<TrConcat<TrJoin<TrDelay<2000>,TrInstant>,Mix<BatteryLevel,Red,Green>,TrFade<300>>,EFFECT_BATTERY_LEVEL>>>(),
    "bode/nakuna" },

   { "c110p_chopper;common", "tracks/track1.wav",
      //Theory2Button.h "Negotiator"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Blue>,RotateColorsX<Variation,Rgb<0,0,128>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<NavajoWhite,Rgb<255,225,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(), "c110p/nchopper" },

   { "Cal-Kestis_BlueNormalized;common", "tracks/track1.wav",
      //Theory2Button.h "Survivor"
    StylePtr<Layers<Stripes<16000,-1000,RotateColorsX<Variation,Blue>,Pulsing<RotateColorsX<Variation,Rgb<0,0,90>>,RotateColorsX<Variation,Blue>,800>,RotateColorsX<Variation,Blue>>,TransitionEffectL<TrConcat<TrFade<600>,RandomFlicker<RotateColorsX<Variation,Blue>,RotateColorsX<Variation,Rgb<0,0,160>>>,TrDelay<30000>,RotateColorsX<Variation,Blue>,TrFade<800>>,EFFECT_FORCE>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
      // Marble style from Proffezzorn
    StylePtr<Mix<CircularSectionF<MarbleF<Int<-2000>,Int<40000>,Ifon<Int<827680>,Int<0>>,Int<1276800>>,ChangeSlowly<Ifon<Int<32768>,Int<3276>>,Int<2048>>>,Black,Mix<InOutFuncX<Int<2000>,Int<2000>>,Rgb<0,0,20>,Rgb<0,255,255>>>>(),
      // Marble style from Proffezzorn
    StylePtr<Mix<CircularSectionF<MarbleF<Int<-2000>,Int<40000>,Ifon<Int<827680>,Int<0>>,Int<1276800>>,ChangeSlowly<Ifon<Int<32768>,Int<3276>>,Int<2048>>>,Black,Mix<InOutFuncX<Int<2000>,Int<2000>>,Rgb<0,0,20>,Rgb<0,255,255>>>>(),
    StyleNormalPtr<CYAN, WHITE, 300, 800>(), "cal-kestis/n blue"},

   { "celestial-travels;common", "tracks/track1.wav",
      //Theory2Button.h "Grandmaster"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Green>,RotateColorsX<Variation,Rgb<0,128,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<NavajoWhite,Rgb<255,225,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(), "celestial/n travels"},

   { "centennial;common", "centennial/tracks/centennial.wav",
/* copyright Fett263 CustomBlade (Primary Blade) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#CustomBlade
OS6.7 v4.018
Single Style
Interactive Kinetic Swing
Default: Fire Blade Medium (Normal)
1: Fire Blade Fastest (Normal)

Base Color: Rgb<255,255,0> (0)
Build up kinetic energy with each swing to apply Style 2 in increasing levels based on inertia, once you've stopped moving the blade it will slowly dissipate and return to Style 1. (stop swinging for approx 5 seconds or clash to dissipate)

--Effects Included--
Ignition Effect: SparkTip Ignition
PowerUp Effect: Power Surge (Unstable V1)
Retraction Effect: SparkTip Retraction
CoolDown Effect: Unstable Cool Down Reverse
PostOff Effect: Emitter Spark (Emitter Size)
Lockup Effect: Intensity Lockup V1, Begin Effect: Real Clash, End Effect: Full Blade Absorb
LightningBlock Effect: Responsive Lightning Block
Drag Effect: Intensity Sparking Drag
Melt Effect: Intensity Melt
Blast Effect: Blast Wave (Random)
Clash Effect: Real Clash V1
Swing Effect: Interactive Ice Blade (Force Effect)
Emitter Effect: Emitter Flare

Swing Option 0- Interactive Ice Blade (Force Effect) Interactive Control: Force to freeze blade, clashes will break ice.
*/
    StylePtr<Layers<
      Mix<HoldPeakF<IncrementWithReset<ThresholdPulseF<SwingSpeed<400>,Int<24000>>,ThresholdPulseF<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_LOCKUP_BEGIN>,IncrementWithReset<ThresholdPulseF<BlinkingF<Int<1000>,Int<500>>,Int<32000>>,ThresholdPulseF<SwingSpeed<400>,Int<16000>>,Int<32768>,Int<8000>>>,Int<32000>>,Int<32768>,Scale<SwingAcceleration<>,Int<4000>,Int<8000>>>,Int<50>,Scale<IsLessThan<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_LOCKUP_BEGIN>>,Int<32000>>,Int<6000>,Int<32768>>>,StaticFire<RgbArg<BASE_COLOR_ARG,Yellow>,Mix<Int<10280>,Black,RgbArg<BASE_COLOR_ARG,Yellow>>,0,2,0,2000,3>,StaticFire<RgbArg<ALT_COLOR_ARG,Rgb<180,130,0>>,Mix<Int<10280>,Black,RgbArg<ALT_COLOR_ARG,Rgb<180,130,0>>>,0,5>>,
      AlphaL<RgbArg<EMITTER_COLOR_ARG,Rgb<118,0,194>>,SmoothStep<IntArg<EMITTER_SIZE_ARG,2000>,Int<-6000>>>,
      AlphaL<AudioFlickerL<RgbArg<SWING_COLOR_ARG,Rgb<118,0,194>>>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,
      ColorSelect<IncrementWithReset<EffectPulseF<EFFECT_FORCE>,ThresholdPulseF<IncrementWithReset<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_STAB>>,EffectPulseF<EFFECT_FORCE>,Int<32768>,Scale<ClashImpactF<>,Int<3000>,Int<14000>>>,Int<32600>>,Int<1>>,TrSmoothFadeX<Int<2000>>,AlphaL<RgbArg<BASE_COLOR_ARG,Yellow>,Int<0>>,RgbArg<BASE_COLOR_ARG,Yellow>>,
      ColorSelect<IncrementWithReset<EffectPulseF<EFFECT_FORCE>,ThresholdPulseF<IncrementWithReset<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_STAB>>,EffectPulseF<EFFECT_FORCE>,Int<32768>,Scale<ClashImpactF<>,Int<3000>,Int<14000>>>,Int<32600>>,Int<1>>,TrSelect<IncrementWithReset<EffectPulseF<EFFECT_FORCE>,Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_STAB>>,Int<1>>,TrSmoothFadeX<Int<3000>>,TrWipeSparkTipX<BrownNoiseFlicker<RgbArg<SWING_COLOR_ARG,Rgb<100,100,150>>,White,200>,WavLen<EFFECT_FORCE>>>,AlphaL<RgbArg<BASE_COLOR_ARG,Yellow>,Int<0>>,AlphaL<Stripes<22000,-20,RgbArg<SWING_COLOR_ARG,Rgb<100,100,150>>,Mix<Int<18000>,Black,RgbArg<SWING_COLOR_ARG,Rgb<100,100,150>>>>,SmoothStep<Sum<Int<33000>,IncrementWithReset<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_STAB>>,EffectPulseF<EFFECT_FORCE>,Int<33000>,Scale<Scale<ClashImpactF<>,Int<3000>,Int<14000>>,Int<-3000>,Int<-14000>>>>,Int<-1>>>>,
      TransitionEffectL<TrConcat<TrInstant,Stripes<3000,-3500,RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>>,Black>,BrownNoiseFlicker<RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>>,200>,RandomPerLEDFlicker<Mix<Int<16384>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>>,Mix<Int<7710>,Black,RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>>>>,TrFade<1200>>,EFFECT_IGNITION>,
      TransitionEffectL<TrConcat<TrJoin<TrDelayX<RetractionTime<>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Rgb<118,0,194>>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<118,0,194>>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Rgb<118,0,194>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<118,0,194>>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<118,0,194>>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Rgb<118,0,194>>>>>,TrFade<800>>,EFFECT_RETRACTION>,
      TransitionEffectL<TrWaveX<RgbArg<BLAST_COLOR_ARG,Cyan>,Scale<EffectRandomF<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,EFFECT_BLAST>,
      Mix<IsLessThan<ClashImpactF<>,Int<26000>>,TransitionEffectL<TrConcat<TrInstant,AlphaL<RgbArg<CLASH_COLOR_ARG,Rgb<118,0,194>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<12000>,Int<60000>>>>,TrFadeX<Scale<ClashImpactF<>,Int<200>,Int<400>>>>,EFFECT_CLASH>,TransitionEffectL<TrWaveX<RgbArg<CLASH_COLOR_ARG,Rgb<118,0,194>>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Int<100>,Scale<ClashImpactF<>,Int<100>,Int<400>>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>>,EFFECT_CLASH>>,
      LockupTrL<TransitionEffect<AlphaMixL<Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>,BrownNoiseFlickerL<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Int<200>>,StripesX<Int<1800>,Scale<NoisySoundLevel,Int<-3500>,Int<-5000>>,Mix<Int<6425>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Mix<Int<12850>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>>>>,AlphaL<AudioFlicker<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Mix<Int<10280>,Black,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Int<13000>>>,TrJoin<TrDelay<8000>,TrInstant>,TrFade<3000>,EFFECT_LOCKUP_BEGIN>,TrConcat<TrJoin<TrDelay<50>,TrInstant>,Mix<IsLessThan<ClashImpactF<>,Int<26000>>,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-10000>>>,Scale<ClashImpactF<>,Int<20000>,Int<60000>>>>>,TrFade<300>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,
      ResponsiveLightningBlockL<Strobe<RgbArg<LB_COLOR_ARG,White>,AudioFlicker<RgbArg<LB_COLOR_ARG,White>,Blue>,50,1>,TrConcat<TrInstant,AlphaL<RgbArg<LB_COLOR_ARG,White>,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<RgbArg<LB_COLOR_ARG,White>,Int<16000>>,30>,TrSmoothFade<600>>>,
      LockupTrL<AlphaL<RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,White>>,SmoothStep<IntArg<DRAG_SIZE_ARG,28000>,Int<3000>>>,TrConcat<TrJoin<TrDelay<4000>,TrWipeIn<200>>,AlphaL<BrownNoiseFlickerL<RgbArg<DRAG_COLOR_ARG,White>,Int<300>>,SmoothStep<IntArg<DRAG_SIZE_ARG,28000>,Int<3000>>>,TrFade<4000>>,TrFade<300>,SaberBase::LOCKUP_DRAG>,
      LockupTrL<AlphaL<Remap<Scale<RampF,Int<65536>,Int<0>>,StaticFire<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>,Mix<TwistAngle<>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>,RotateColorsX<Int<3000>,Mix<Int<12000>,Black,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>>,0,3,5,3000,10>>,SmoothStep<IntArg<MELT_SIZE_ARG,28000>,Int<4000>>>,TrConcat<TrWipeIn<100>,AlphaL<RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,SmoothStep<IntArg<MELT_SIZE_ARG,28000>,Int<4000>>>,TrJoin<TrDelay<4000>,TrFade<300>>,AlphaL<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>,SmoothStep<IntArg<MELT_SIZE_ARG,28000>,Int<4000>>>,TrFade<4000>>,TrWipe<200>,SaberBase::LOCKUP_MELT>,
      InOutTrL<TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>,IgnitionTime<>>,TrWipeInSparkTipX<RgbArg<RETRACTION_COLOR_ARG,Rgb<118,0,194>>,RetractionTime<>>>,
      TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<POSTOFF_COLOR_ARG,Rgb<118,0,194>>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<EMITTER_SIZE_ARG,2000>,Sum<IntArg<EMITTER_SIZE_ARG,2000>,Int<3000>>>,Int<-4000>>>,TrDelayX<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>>>,EFFECT_POSTOFF>>>(),

// pcb  
/* copyright Fett263 CustomBlade (Accent LED / PCB) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#CustomBlade
OS6.7 v4.018
Single Style
Interactive Kinetic Swing
Default: Fire Blade Medium (Normal)
1: Fire Blade Fastest (Normal)

Off Behavior: Fast Run Forward

Base Color: Rgb<255,255,0> (0)
Build up kinetic energy with each swing to apply Style 2 in increasing levels based on inertia, once you've stopped moving the blade it will slowly dissipate and return to Style 1. (stop swinging for approx 5 seconds or clash to dissipate)

--Effects Included--
Ignition Effect: Standard Ignition
PowerUp Effect: Power Flash
Retraction Effect: Run Up
Lockup Effect: Full Blade Lockup (Dissipate)
LightningBlock Effect: Full Blade Lightning
Blast Effect: Full Blade Blast Fade
Clash Effect: Flash on Clash (Full Blade)
Swing Effect: AudioFlicker Swing (Scaled Full Blade)
*/
    StylePtr<Layers<Mix<HoldPeakF<IncrementWithReset<ThresholdPulseF<SwingSpeed<400>,Int<24000>>,ThresholdPulseF<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_LOCKUP_BEGIN>,IncrementWithReset<ThresholdPulseF<BlinkingF<Int<1000>,Int<500>>,Int<32000>>,ThresholdPulseF<SwingSpeed<400>,Int<16000>>,Int<32768>,Int<8000>>>,Int<32000>>,Int<32768>,Scale<SwingAcceleration<>,Int<4000>,Int<8000>>>,Int<50>,Scale<IsLessThan<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_LOCKUP_BEGIN>>,Int<32000>>,Int<6000>,Int<32768>>>,StaticFire<RgbArg<BASE_COLOR_ARG,Rgb<255,255,0>>,Mix<Int<10280>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,255,0>>>,0,2,0,2000,3>,StaticFire<RgbArg<ALT_COLOR_ARG,Rgb<180,130,0>>,Mix<Int<10280>,Black,RgbArg<ALT_COLOR_ARG,Rgb<180,130,0>>>,0,5,0,2000,5>>,AlphaL<AudioFlickerL<RgbArg<SWING_COLOR_ARG,Rgb<118,0,194>>>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,TransitionEffectL<TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>,TrFade<1000>>,EFFECT_IGNITION>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<0,255,255>>,TrFade<300>>,EFFECT_BLAST>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<CLASH_COLOR_ARG,Rgb<118,0,194>>,TrFade<300>>,EFFECT_CLASH>,LockupTrL<AudioFlickerL<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,TrFade<400>>,TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Int<0>>,TrWaveX<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Int<300>,Int<100>,Int<400>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>>,SaberBase::LOCKUP_NORMAL>,LockupTrL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrInstant,TrFade<1000>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,InOutTrL<TrWipeX<IgnitionTime<0>>,TrWipeX<RetractionTime<0>>,TransitionLoop<Black,TrConcat<TrWipe<200>,RgbArg<OFF_COLOR_ARG,Rgb<255,255,0>>,TrWipe<200>>>>>>(),
    StylePtr<Layers<Mix<HoldPeakF<IncrementWithReset<ThresholdPulseF<SwingSpeed<400>,Int<24000>>,ThresholdPulseF<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_LOCKUP_BEGIN>,IncrementWithReset<ThresholdPulseF<BlinkingF<Int<1000>,Int<500>>,Int<32000>>,ThresholdPulseF<SwingSpeed<400>,Int<16000>>,Int<32768>,Int<8000>>>,Int<32000>>,Int<32768>,Scale<SwingAcceleration<>,Int<4000>,Int<8000>>>,Int<50>,Scale<IsLessThan<Sum<EffectPulseF<EFFECT_CLASH>,EffectPulseF<EFFECT_LOCKUP_BEGIN>>,Int<32000>>,Int<6000>,Int<32768>>>,StaticFire<RgbArg<BASE_COLOR_ARG,Rgb<255,255,0>>,Mix<Int<10280>,Black,RgbArg<BASE_COLOR_ARG,Rgb<255,255,0>>>,0,2,0,2000,3>,StaticFire<RgbArg<ALT_COLOR_ARG,Rgb<180,130,0>>,Mix<Int<10280>,Black,RgbArg<ALT_COLOR_ARG,Rgb<180,130,0>>>,0,5,0,2000,5>>,AlphaL<AudioFlickerL<RgbArg<SWING_COLOR_ARG,Rgb<118,0,194>>>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,TransitionEffectL<TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,RgbArg<IGNITION_COLOR_ARG,Rgb<118,0,194>>,TrFade<1000>>,EFFECT_IGNITION>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<0,255,255>>,TrFade<300>>,EFFECT_BLAST>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<CLASH_COLOR_ARG,Rgb<118,0,194>>,TrFade<300>>,EFFECT_CLASH>,LockupTrL<AudioFlickerL<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,TrFade<400>>,TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Int<0>>,TrWaveX<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Int<300>,Int<100>,Int<400>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>>,SaberBase::LOCKUP_NORMAL>,LockupTrL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrInstant,TrFade<1000>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,InOutTrL<TrWipeX<IgnitionTime<0>>,TrWipeX<RetractionTime<0>>,TransitionLoop<Black,TrConcat<TrWipe<200>,RgbArg<OFF_COLOR_ARG,Rgb<255,255,0>>,TrWipe<200>>>>>>(),
// cc 
/* copyright Fett263 (Accent LED / PCB) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#CustomBlade
OS6.7 v4.018
Single Style
On Behavior: Power Wave High
Off Behavior: Power Wave Slow

Base Color: Rgb<118,0,194> (0)

--Effects Included--
Ignition Effect: Instant
PowerUp Effect: Power Flash
Retraction Effect: Instant
Lockup Effect: Full Blade Lockup (Dissipate)
LightningBlock Effect: Full Blade Lightning
Blast Effect: Full Blade Blast Fade
Clash Effect: Flash on Clash (Full Blade)
*/
    StylePtr<Layers<Stripes<12000,-1800,RgbArg<BASE_COLOR_ARG,Rgb<118,0,194>>,Mix<Int<6000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<118,0,194>>>,RgbArg<BASE_COLOR_ARG,Rgb<118,0,194>>,Mix<Int<14000>,Black,RgbArg<BASE_COLOR_ARG,Rgb<118,0,194>>>>,TransitionEffectL<TrConcat<TrJoin<TrDelayX<IgnitionTime<0>>,TrInstant>,RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,0>>,TrFade<1000>>,EFFECT_IGNITION>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<BLAST_COLOR_ARG,Rgb<0,255,255>>,TrFade<300>>,EFFECT_BLAST>,TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<CLASH_COLOR_ARG,Rgb<118,0,194>>,TrFade<300>>,EFFECT_CLASH>,LockupTrL<AudioFlickerL<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,TrFade<400>>,TrConcat<TrInstant,AlphaL<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Int<0>>,TrWaveX<RgbArg<LOCKUP_COLOR_ARG,Rgb<118,0,194>>,Int<300>,Int<100>,Int<400>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>>,SaberBase::LOCKUP_NORMAL>,LockupTrL<Strobe<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,AudioFlicker<RgbArg<LB_COLOR_ARG,Rgb<255,255,255>>,Blue>,50,1>,TrInstant,TrFade<1000>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,InOutTrL<TrInstant,TrInstant,Stripes<16000,-400,RgbArg<OFF_COLOR_ARG,Rgb<118,0,194>>,Mix<Int<8000>,Black,RgbArg<OFF_COLOR_ARG,Rgb<118,0,194>>>,Mix<Int<16000>,Black,RgbArg<OFF_COLOR_ARG,Rgb<118,0,194>>>>>>>(),
    "centennial"},

   { "cere-junda;common", "tracks/track1.wav",
      //Theory2Button.h "Shadow_Hunter"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<NavajoWhite,Rgb<255,225,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StyleFirePtr<RED, YELLOW, 1>(),
    StyleFirePtr<RED, YELLOW, 2>(),
    StyleFirePtr<RED, YELLOW, 3>(), "cere/njunda"},

   { "coda;common", "tracks/track1.wav",
    StylePtr<Layers<
  //Rotates 3 times per minute between DodgerBlue and DeepSkyBlue with subtle Cyan/Blue audioflicker
  Mix<Sin<Int<3>>,AudioFlicker<RotateColorsX<Variation,DodgerBlue>,Stripes<5000,-90,RotateColorsX<Variation,Rgb<0,55,165>>,RotateColorsX<Variation,Rgb<0,85,115>>,RotateColorsX<Variation,Rgb<0,65,145>>,RotateColorsX<Variation,Rgb<0,30,185>>>>,AudioFlicker<RotateColorsX<Variation,Rgb<0,155,255>>,Stripes<5000,-90,RotateColorsX<Variation,Rgb<0,95,170>>,RotateColorsX<Variation,Rgb<0,115,215>>,RotateColorsX<Variation,Rgb<0,145,145>>,RotateColorsX<Variation,Rgb<0,65,225>>>>>,
  //Alternate DeepSkyBlue with very subtle audioflicker
  //AudioFlicker<RotateColorsX<Variation,DeepSkyBlue>,RotateColorsX<Variation,Rgb<0,95,195>>>,
  //Unstable swing
  AlphaL<BrownNoiseFlicker<RotateColorsX<Variation,DeepSkyBlue>,Black,300>,SwingSpeed<400>>,
  //Unstable ripple swing
  AlphaL<Stripes<1000,-2000,RandomPerLEDFlicker<RotateColorsX<Variation,DeepSkyBlue>,Black>,Black,RotateColorsX<Variation,DeepSkyBlue>,Black>,SwingSpeed<525>>,
  //Responsive lockup effect with screeching humpflicker endlock
  LockupTrL<Layers<
    AlphaL<AudioFlickerL<Rgb<255,240,80>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,
    AlphaL<LemonChiffon,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<875>>,SaberBase::LOCKUP_NORMAL>,
  //Alternate standard lockup
  //LockupTrL<Layers<
  //AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,
  //AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<4000>>,SaberBase::LOCKUP_NORMAL>,
  //Responsive lightning block
  ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,
  //Responsive stab
  ResponsiveStabL<RotateColorsX<Variation,Yellow>>,
  //Alternate responsive stab, no color change
  //ResponsiveStabL<Red>,
  //Multi-blast, blaster reflect cycles through different responsive effects
  EffectSequence<EFFECT_BLAST,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,LocalizedClashL<White,80,30,EFFECT_BLAST>,ResponsiveBlastWaveL<White,Scale<SwingSpeed<400>,Int<500>,Int<200>>,Scale<SwingSpeed<400>,Int<100>,Int<400>>>,BlastL<White,200,200>,ResponsiveBlastFadeL<White,Scale<SwingSpeed<400>,Int<6000>,Int<12000>>,Scale<SwingSpeed<400>,Int<400>,Int<100>>>,ResponsiveBlastL<White,Scale<SwingSpeed<400>,Int<400>,Int<100>>,Scale<SwingSpeed<400>,Int<200>,Int<100>>,Scale<SwingSpeed<400>,Int<400>,Int<200>>>>,
  //Alternate responsive blast
  //ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,
  //Responsive Clash
  ResponsiveClashL<TransitionEffect<Rgb<255,240,80>,LemonChiffon,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
  //Alternate white clash
  //ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
  //Stabilize ignition effect
  TransitionEffectL<TrConcat<TrInstant,Stripes<3000,-3500,RotateColorsX<Variation,Rgb<90,180,255>>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<0,26,60>>,Black>,BrownNoiseFlicker<RotateColorsX<Variation,Rgb<90,180,255>>,RotateColorsX<Variation,Rgb<0,26,60>>,200>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<0,42,128>>,RotateColorsX<Variation,Rgb<0,26,60>>>>,TrFade<400>,Stripes<3000,-3500,RotateColorsX<Variation,Rgb<90,180,255>>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<0,26,60>>,Black>,BrownNoiseFlicker<RotateColorsX<Variation,Rgb<90,180,255>>,RotateColorsX<Variation,Rgb<0,26,60>>,200>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<0,42,128>>,RotateColorsX<Variation,Rgb<0,26,60>>>>,TrFade<450>,HumpFlickerL<AlphaL<RotateColorsX<Variation,Rgb<90,180,255>>,Int<19000>>,25>,TrFade<2875>>,EFFECT_IGNITION>,
  //Slow brighten retraction effect
  TransitionEffectL<TrConcat<TrFade<1125>,RotateColorsX<Variation,Rgb<90,180,255>>,TrInstant>,EFFECT_RETRACTION>,
  //Drag
  LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,
  //Responsive melt
  LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,
  //Power save, if using fett263's prop file hold Aux and click PWR while ON (pointing up) to dim blade in 25% increments.
  EffectSequence<EFFECT_POWERSAVE,AlphaL<Black,Int<8192>>,AlphaL<Black,Int<16384>>,AlphaL<Black,Int<24576>>,AlphaL<Black,Int<0>>>,
  //Standard ignition/retraction
  InOutTrL<TrWipe<500>,TrWipeIn<1125>>,
  //Optional/alternate passive battery monitor, on boot (1st line) or font change (2nd line) you will get a visual indicator at the emitter of your current battery level. This also works without a blade if you have a lit emitter or blade plug. Green is Full, Red is Low (the color will blend from Green to Red as the battery is depleted), the indicator will fade out after 3000 ms and not display again until powered down and back up or fonts change.
  //TransitionEffectL<TrConcat<TrDelay<1500>,Black,TrFade<1000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_BOOT>,
  //TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_NEWFONT>,
  //On demand battery level, if using fett263's prop file Hold AUX and click PWR while OFF, the battery level is represented by the location on the blade; tip = full, hilt = low and color; green = full, yellow = half, red = low
  TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrDelay<2000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrFade<1000>>,EFFECT_BATTERY_LEVEL>,
  //Overload preon effect
  TransitionEffectL<TrConcat<TrFade<450>,AlphaL<HumpFlickerL<RotateColorsX<Variation,DeepSkyBlue>,10>,Bump<Int<0>,Int<3000>>>,TrFade<350>,AlphaL<HumpFlickerL<RotateColorsX<Variation,DeepSkyBlue>,15>,Bump<Int<0>,Int<5000>>>,TrFade<450>,AlphaL<HumpFlickerL<RotateColorsX<Variation,DeepSkyBlue>,20>,Bump<Int<0>,Int<7000>>>,TrFade<500>,AlphaL<HumpFlickerL<RotateColorsX<Variation,DeepSkyBlue>,25>,Bump<Int<0>,Int<10500>>>,TrBoing<150,1>>,EFFECT_PREON>
  >>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(), "coda"},

   { "crucible;common", "tracks/track1.wav",
      //Theory2Button.h "Emperor"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<NavajoWhite,Rgb<255,225,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StyleFirePtr<BLUE, CYAN, 1>(),
    StyleFirePtr<BLUE, CYAN, 2>(),
    StyleFirePtr<BLUE, CYAN, 3>(), "crucible"},

   { "DaganGeraLight;common", "tracks/track1.wav",
      //Theory2Button.h "Tragedy"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<NavajoWhite,Rgb<255,225,0>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,TransitionEffectL<TrConcat<TrInstant,Stripes<3000,-3500,White,RandomPerLEDFlicker<Rgb<60,60,60>,Black>,BrownNoiseFlicker<White,Rgb<30,30,30>,200>,RandomPerLEDFlicker<Rgb<80,80,80>,Rgb<30,30,30>>>,TrFade<800>>,EFFECT_IGNITION>,TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<White,40>,TrFade<1000>>,EFFECT_RETRACTION>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(), "dagangera/nlight"},

   { "DarthVader;common", "tracks/track1.wav",
      //Theory2Button.h "Prodigal_Son"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Green>,RotateColorsX<Variation,Rgb<0,128,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<Rgb<255,240,80>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<LemonChiffon,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,TransitionEffect<Rgb<255,180,50>,LemonChiffon,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,TrConcat<TrInstant,TransitionEffect<LemonChiffon,Rgb<255,180,50>,TrInstant,TrFade<200>,EFFECT_LOCKUP_BEGIN>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<TransitionEffect<Rgb<255,240,80>,LemonChiffon,TrInstant,TrFade<50>,EFFECT_BLAST>,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<TransitionEffect<Rgb<255,240,80>,LemonChiffon,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipeSparkTip<White,300>,TrWipeIn<500>,Black>>>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(), "darth/nvader"},

   { "DarkSouls;common", "tracks/track1.wav",
    StylePtr<Layers<Mix<BladeAngle<>,StyleFire<Gradient<RotateColorsX<Variation,Orange>,RotateColorsX<Variation,DarkOrange>,RotateColorsX<Variation,OrangeRed>,RotateColorsX<Variation,Red>>,RotateColorsX<Variation,Rgb<60,0,0>>,0,3,FireConfig<0,2000,5>,FireConfig<0,2000,5>,FireConfig<0,2000,5>,FireConfig<0,2000,5>>,StyleFire<Gradient<RotateColorsX<Variation,Orange>,RotateColorsX<Variation,DarkOrange>,RotateColorsX<Variation,OrangeRed>,RotateColorsX<Variation,Red>>,RotateColorsX<Variation,Rgb<60,0,0>>,0,6,FireConfig<0,2000,5>,FireConfig<0,2000,5>,FireConfig<0,2000,5>,FireConfig<0,2000,5>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<Yellow,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,ResponsiveClashL<TransitionEffect<Rgb<255,240,80>,LemonChiffon,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<10000>,Int<30000>>,Int<10000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipe<350>,TrWipeIn<1500>,Black>>>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(), "dark/nsouls"},

   { "DaganGeraDark;common", "tracks/track1.wav",
      //Theory2Button.h "Ronin"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipe<1000>,TrWipeIn<1400>,Black>>>(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(), "dagangera/ndark"},

   { "ronin;common", "tracks/track1.wav",
      //Theory2Button.h "Ronin"
    StylePtr<Layers<AudioFlicker<RotateColorsX<Variation,Red>,RotateColorsX<Variation,Rgb<128,0,0>>>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Orange,TrWipeIn<600>,TrWipe<600>>,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Rgb<255,200,0>,DarkOrange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrWipe<1000>,TrWipeIn<1400>,Black>>>(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(), "ronin"},

   { "deadlink;common", "tracks/track1.wav",
    StylePtr<Layers<
     HumpFlicker<RotateColorsX<Variation,Magenta>,RotateColorsX<Variation,Rgb<150,0,150>>,50>,
      //Magenta HumpFlicker
     AlphaL<Stripes<2500,-3000,RotateColorsX<Variation,DeepPink>,RotateColorsX<Variation,Rgb16<12482,0,18076>>,Pulsing<RotateColorsX<Variation,Rgb<10,0,26>>,Black,800>>,SwingSpeed<350>>,
      //Ripple swing effect
      //AlphaL<AudioFlickerL<Stripes<2500,-3000,RotateColorsX<Variation,DeepPink>,RotateColorsX<Variation,Rgb16<12482,0,18076>>,Pulsing<RotateColorsX<Variation,Rgb<10,0,26>>,Black,800>>>,SwingSpeed<300>>,
      //Alternate audioflicker ripple swing effect
     LockupTrL<Layers<
       AlphaL<AudioFlickerL<Rgb<255,225,0>>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,
       AlphaL<NavajoWhite,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,AlphaL<White,Int<0>>,TrWaveX<White,Int<300>,Int<100>,Int<400>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>>>,SaberBase::LOCKUP_NORMAL>,
      //Responsive lockup
     ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,
      //Responsive lightning block
     AlphaL<RotateColorsX<Variation,Rgb16<33124,0,65535>>,SmoothStep<Scale<SlowNoise<Int<2500>>,Int<1000>,Int<3500>>,Int<-4000>>>,
      //Sparking emitter flare
     ResponsiveStabL<Red>,
      //Responsive stab
     EffectSequence<EFFECT_BLAST,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,LocalizedClashL<White,80,30,EFFECT_BLAST>,ResponsiveBlastWaveL<White,Scale<SwingSpeed<400>,Int<500>,Int<200>>,Scale<SwingSpeed<400>,Int<100>,Int<400>>>,BlastL<White,200,200>,ResponsiveBlastFadeL<White,Scale<SwingSpeed<400>,Int<6000>,Int<12000>>,Scale<SwingSpeed<400>,Int<400>,Int<100>>>,ResponsiveBlastL<White,Scale<SwingSpeed<400>,Int<400>,Int<100>>,Scale<SwingSpeed<400>,Int<200>,Int<100>>,Scale<SwingSpeed<400>,Int<400>,Int<200>>>>,
      //Multi-blast, blaster reflect cycles through different responsive effects
     ResponsiveClashL<TransitionEffect<Rgb<255,225,0>,NavajoWhite,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
      //Responsive clash
     TransitionEffectL<TrConcat<TrDelay<875>,Stripes<3000,-3500,RotateColorsX<Variation,Rgb<160,0,255>>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<21,0,52>>,Black>,BrownNoiseFlicker<RotateColorsX<Variation,Rgb<160,0,255>>,RotateColorsX<Variation,Rgb<21,0,52>>,200>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<42,0,105>>,RotateColorsX<Variation,Rgb<21,0,52>>>>,TrFade<250>,HumpFlicker<RotateColorsX<Variation,Magenta>,RotateColorsX<Variation,Rgb<80,0,80>>,50>,TrFade<400>,Stripes<3000,-3500,RotateColorsX<Variation,DeepPink>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<21,0,52>>,Black>,BrownNoiseFlicker<RotateColorsX<Variation,Rgb<160,0,255>>,RotateColorsX<Variation,Rgb<21,0,52>>,200>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<42,0,105>>,RotateColorsX<Variation,Rgb<21,0,52>>>>,TrFade<1500>>,EFFECT_IGNITION>,
      //Unstable ignition effect
     TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<RotateColorsX<Variation,Rgb<180,60,255>>,40>,TrFade<2000>>,EFFECT_RETRACTION>,
      //Bright HumpFlicker retraction effect
     LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,
      //Drag
     LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,
      //Responsive melt
     EffectSequence<EFFECT_POWERSAVE,AlphaL<Black,Int<8192>>,AlphaL<Black,Int<16384>>,AlphaL<Black,Int<24576>>,AlphaL<Black,Int<0>>>,
      //Power save, if using fett263's prop file hold Aux and click PWR while ON (pointing up) to dim blade in 25% increments.
     InOutTrL<TrConcat<TrWipeIn<200>,RandomBlink<30000,RotateColorsX<Variation,Rgb16<65535,13655,65535>>>,TrWipeIn<200>,Mix<SmoothStep<Scale<SlowNoise<Int<30000>>,Int<1000>,Int<6000>>,Int<-3000>>,Black,RotateColorsX<Variation,Rgb16<65535,13655,65535>>>,TrDelay<400>,Mix<SmoothStep<Int<4000>,Int<-3000>>,Black,White>,TrWipe<175>>,TrColorCycle<2000>>,
      //Lightning strike ignition, cycle down retraction
      //TransitionEffectL<TrConcat<TrDelay<1500>,Black,TrFade<1000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_BOOT>,
      //TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_NEWFONT>,
      //Optional/alternate passive battery monitor, on boot (1st line) or font change (2nd line) you will get a visual indicator at the emitter of your current battery level. This also works without a blade if you have a lit emitter or blade plug. Green is Full, Red is Low (the color will blend from Green to Red as the battery is depleted), the indicator will fade out after 3000 ms and not display again until powered down and back up or fonts change.
     TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrDelay<2000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrFade<1000>>,EFFECT_BATTERY_LEVEL>
      //On demand battery level, if using fett263's prop file Hold AUX and click PWR while OFF, the battery level is represented by the location on the blade; tip = full, hilt = low and color; green = full, yellow = half, red = low
     >>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(), "deadlink"},

    {"decay;common", "tracks/track1.wav",
    StylePtr<Layers<
     StripesX<Int<3500>,Int<1200>,Mix<Sin<Int<20>>,RotateColorsX<Variation,Rgb<95,0,210>>,RotateColorsX<Variation,Rgb<75,0,165>>>,Mix<Sin<Int<23>>,RotateColorsX<Variation,Rgb<52,0,125>>,RotateColorsX<Variation,Rgb<84,0,210>>>,Mix<Sin<Int<16>>,RotateColorsX<Variation,Rgb<115,15,220>>,RotateColorsX<Variation,Rgb<95,0,210>>>,Mix<Sin<Int<18>>,RotateColorsX<Variation,Rgb<26,0,42>>,RotateColorsX<Variation,Rgb<60,0,132>>>>,
      //Bright purple absorb effect
      //StripesX<Int<3500>,Int<1200>,Mix<Sin<Int<20>>,RotateColorsX<Variation,Rgb<95,0,210>>,RotateColorsX<Variation,Rgb<75,0,165>>>,Mix<Sin<Int<23>>,RotateColorsX<Variation,Rgb<52,0,125>>,RotateColorsX<Variation,Rgb<84,0,210>>>,Mix<Sin<Int<16>>,RotateColorsX<Variation,Rgb<115,0,220>>,RotateColorsX<Variation,Rgb<95,0,210>>>,Mix<Sin<Int<18>>,RotateColorsX<Variation,Rgb<26,0,42>>,RotateColorsX<Variation,Rgb<60,0,132>>>>,
      //Alternate darker purple absorb effect, color change friendly (for reds and such)
     AlphaL<BrownNoiseFlicker<RotateColorsX<Variation,Rgb<95,0,210>>,Black,300>,SwingSpeed<400>>,
      //Unstable swing
     AlphaL<Stripes<1000,2000,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb<95,0,210>>,Black>,Black,RotateColorsX<Variation,Rgb<95,0,210>>,Black>,SwingSpeed<500>>,
      //Ripple down swing
     AlphaL<RotateColorsX<Variation,Rgb<160,60,255>>,Scale<IsLessThan<SwingSpeed<600>,Int<13600>>,Scale<SwingSpeed<600>,Int<-19300>,Int<32768>>,Int<0>>>,
      //Bright hard swings
     LockupTrL<Layers<
      AlphaL<AudioFlickerL<Azure>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,
      AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,AlphaL<White,Int<0>>,TrWaveX<White,Int<300>,Int<100>,Int<400>,Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>>,StripesX<Int<3500>,Int<1200>,Mix<Sin<Int<20>>,RotateColorsX<Variation,Rgb<95,0,210>>,RotateColorsX<Variation,Rgb<75,0,165>>>,Mix<Sin<Int<23>>,RotateColorsX<Variation,Rgb<52,0,125>>,RotateColorsX<Variation,Rgb<84,0,210>>>,Mix<Sin<Int<16>>,RotateColorsX<Variation,Rgb<115,15,220>>,RotateColorsX<Variation,Rgb<95,0,210>>>,Mix<Sin<Int<18>>,RotateColorsX<Variation,Rgb<26,0,42>>,RotateColorsX<Variation,Rgb<60,0,132>>>>,TrFade<1225>,RotateColorsX<Variation,Rgb<160,60,255>>,TrFade<250>>,SaberBase::LOCKUP_NORMAL>,
      //Responsive lockup with reset
     ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,
      //Responsive lightning block
     AlphaL<RotateColorsX<Variation,Rgb<160,60,255>>,SmoothStep<Scale<SlowNoise<Int<1750>>,Int<1500>,Int<4500>>,Int<-6000>>>,
      //Sparking emitter flare
      //AlphaL<RotateColorsX<Variation,Rgb16<45025,0,65535>>,SmoothStep<Scale<SlowNoise<Int<1750>>,Int<1500>,Int<4500>>,Int<-6000>>>,
      //Alternate darker sparking emitter flare, color change friendly (for reds and such)
     ResponsiveStabL<Red>,
      //Responsive stab
     EffectSequence<EFFECT_BLAST,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>,Int<400>>,LocalizedClashL<White,80,30,EFFECT_BLAST>,ResponsiveBlastWaveL<White,Scale<SwingSpeed<400>,Int<500>,Int<200>>,Scale<SwingSpeed<400>,Int<100>,Int<400>>>,BlastL<White,200,200>,ResponsiveBlastFadeL<White,Scale<SwingSpeed<400>,Int<6000>,Int<12000>>,Scale<SwingSpeed<400>,Int<400>,Int<100>>>,ResponsiveBlastL<White,Scale<SwingSpeed<400>,Int<400>,Int<100>>,Scale<SwingSpeed<400>,Int<200>,Int<100>>,Scale<SwingSpeed<400>,Int<400>,Int<200>>>>,
      //Multi-blast, blaster reflect cycles through different responsive effects
     ResponsiveClashL<TransitionEffect<Azure,White,TrInstant,TrFade<100>,EFFECT_CLASH>,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,
      //Responsive clash
     TransitionEffectL<TrConcat<TrInstant,Stripes<3000,-3500,RotateColorsX<Variation,Rgb<160,60,255>>,RandomPerLEDFlicker<Rgb<60,60,60>,Black>,BrownNoiseFlicker<RotateColorsX<Variation,Rgb<175,80,255>>,Rgb<30,30,30>,200>,RandomPerLEDFlicker<Rgb<80,80,80>,Rgb<30,30,30>>>,TrFade<1650>>,EFFECT_IGNITION>,
      //Bright unstable ignition
     TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<RotateColorsX<Variation,Rgb<160,60,255>>,40>,TrFade<1200>>,EFFECT_RETRACTION>,
      //Bright HumpFlicker retraction
     LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,
      //Drag
     LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,
      //Responsive melt
     EffectSequence<EFFECT_POWERSAVE,AlphaL<Black,Int<8192>>,AlphaL<Black,Int<16384>>,AlphaL<Black,Int<24576>>,AlphaL<Black,Int<0>>>,
      //Power save, if using fett263's prop file hold Aux and click PWR while ON (pointing up) to dim blade in 25% increments.
     InOutTrL<TrWipeInSparkTip<White,200>,TrWipeInSparkTip<White,1125>>,
      //Spark tip in ignition and retraction
      //InOutTrL<TrWipeSparkTip<White,200>,TrWipeInSparkTip<White,1125>>,
      //Alternate spark tip ignition and retraction
      //TransitionEffectL<TrConcat<TrDelay<1500>,Black,TrFade<1000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_BOOT>,
      //TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<Int<0>,Int<6000>>>,TrFade<3000>>,EFFECT_NEWFONT>,
      //Optional/alternate passive battery monitor, on boot (1st line) or font change (2nd line) you will get a visual indicator at the emitter of your current battery level. This also works without a blade if you have a lit emitter or blade plug. Green is Full, Red is Low (the color will blend from Green to Red as the battery is depleted), the indicator will fade out after 3000 ms and not display again until powered down and back up or fonts change.
     TransitionEffectL<TrConcat<TrInstant,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrDelay<2000>,AlphaL<Mix<BatteryLevel,Red,Green>,Bump<BatteryLevel,Int<10000>>>,TrFade<1000>>,EFFECT_BATTERY_LEVEL>,
      //On demand battery level, if using fett263's prop file Hold AUX and click PWR while OFF, the battery level is represented by the location on the blade; tip = full, hilt = low and color; green = full, yellow = half, red = low
     TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,40>,TrWipe<150>,HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,40>,TrBoing<350,2>>,EFFECT_PREON>,
     TransitionEffectL<TrConcat<TrInstant,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,30>,Bump<Int<0>,Int<5000>>>,TrFade<625>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,30>,Bump<Int<0>,Int<9000>>>,TrFade<625>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,40>,Bump<Int<0>,Int<13000>>>,TrFade<500>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,69>,Bump<Int<0>,Int<18000>>>,TrFade<750>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,69>,Bump<Int<0>,Int<23000>>>,TrFade<750>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,30>,Bump<Int<0>,Int<7000>>>,TrFade<500>,AlphaL<HumpFlickerL<RotateColorsX<Variation,Rgb<95,0,210>>,50>,Bump<Int<0>,Int<19000>>>,TrBoing<1950,9>>,EFFECT_PREON>,
     TransitionEffectL<TrConcat<TrInstant,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<500>,Int<200>,Int<400>,Int<32768>>>,TrDelay<1250>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<300>,Int<300>,Int<300>,Int<32768>>>,TrDelay<1000>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<300>,Int<315>,Int<215>,Int<32768>>>,TrDelay<1000>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<115>,Int<375>,Int<115>,Int<32768>>>,TrDelay<1250>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<300>,Int<300>,Int<300>,Int<32768>>>,TrDelay<1500>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<100>,Int<400>,Int<100>,Int<32768>>>,TrDelay<1750>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<300>,Int<300>,Int<300>,Int<32768>>>,TrDelay<2000>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<300>,Int<315>,Int<215>,Int<32768>>>,TrDelay<450>,TransitionLoopL<TrWaveX<RotateColorsX<Variation,Rgb<95,0,210>>,Int<100>,Int<400>,Int<100>,Int<32768>>>,TrDelay<1450>,AlphaL<RotateColorsX<Variation,Rgb<95,0,210>>,Bump<Int<0>,Int<6000>>>,TrBoing<1450,5>>,EFFECT_PREON>,
     TransitionEffectL<TrConcat<TrDelay<4350>,AlphaL<Mix<Trigger<EFFECT_PREON,Int<3000>,Int<5000>,Int<3000>>,BrownNoiseFlicker<Black,RotateColorsX<Variation,Rgb16<33124,0,65535>>,100>,RandomPerLEDFlicker<RotateColorsX<Variation,Rgb16<56306,0,65535>>,RotateColorsX<Variation,Rgb16<21919,0,22863>>>,BrownNoiseFlicker<Mix<NoisySoundLevel,RotateColorsX<Variation,Rgb16<33124,0,65535>>,RotateColorsX<Int<2750>,RotateColorsX<Variation,Rgb16<33124,0,65535>>>>,RotateColorsX<Variation,Rgb16<42753,14386,65535>>,50>>,SmoothStep<Scale<NoisySoundLevel,Int<-5000>,Int<42500>>,Int<-4000>>>,TrDelay<7750>>,EFFECT_PREON>
      //Life force drain preon
     >>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(), "decay"},

   {"LiquidStatic;common", "tracks/track1.wav",
    // === Main Blade: ===
    /* copyright Fett263 SmokeBlade (Primary Blade) OS6 Style
https://fett263.com/fett263-proffieOS6-style-library.html#SmokeBlade
OS6.7 v4.014
Single Style
Base Style: Smoke Blade

Base Color: Rgb<0,0,255> (0)

--Effects Included--
Preon Effect: Sparking (PreOn Color)
Ignition Effect: SparkTip Ignition
PowerUp Effect: Power Surge (Unstable V2)
Retraction Effect: SparkTip Retraction
CoolDown Effect: Unstable Cool Down Reverse
PostOff Effect: Emitter Spark (Preon Size)
Lockup Effect: Responsive Lockup, Begin Effect: Real Clash, End Effect: Full Blade Absorb
LightningBlock Effect: Original Lightning Block
Drag Effect: Intensity Sparking Drag
Melt Effect: Intensity Melt
Stab Effect: Normal Stab
Blast Effect: Blast Wave (Random)
Clash Effect: Flash on Clash (Full Blade)
Emitter Effect: Emitter Flare
*/
    StylePtr<Layers<
      StripesX<Sin<Int<12>,Int<3000>,Int<7000>>,Scale<SwingSpeed<100>,Int<75>,Int<125>>,StripesX<Sin<Int<10>,Int<1000>,Int<3000>>,Scale<SwingSpeed<100>,Int<75>,Int<100>>,Pulsing<RgbArg<BASE_COLOR_ARG,Blue>,Mix<Int<2570>,Black,RgbArg<BASE_COLOR_ARG,Blue>>,1200>,Mix<SwingSpeed<200>,Mix<Int<16000>,Black,RgbArg<BASE_COLOR_ARG,Blue>>,Black>>,Mix<Int<7710>,Black,RgbArg<BASE_COLOR_ARG,Blue>>,Pulsing<Mix<Int<6425>,Black,RgbArg<BASE_COLOR_ARG,Blue>>,StripesX<Sin<Int<10>,Int<2000>,Int<3000>>,Sin<Int<10>,Int<75>,Int<100>>,RgbArg<BASE_COLOR_ARG,Blue>,Mix<Int<12000>,Black,RgbArg<BASE_COLOR_ARG,Blue>>>,2000>,Pulsing<Mix<Int<16448>,Black,RgbArg<BASE_COLOR_ARG,Blue>>,Mix<Int<642>,Black,RgbArg<BASE_COLOR_ARG,Blue>>,3000>>,
      AlphaL<StaticFire<RgbArg<BASE_COLOR_ARG,Blue>,Mix<Int<256>,Black,RgbArg<BASE_COLOR_ARG,Blue>>,0,1,10,2000,2>,Int<10000>>,
      AlphaL<RgbArg<EMITTER_COLOR_ARG,LightCyan>,SmoothStep<IntArg<EMITTER_SIZE_ARG,2000>,Int<-6000>>>,
      TransitionEffectL<TrConcat<TrInstant,HumpFlickerL<RgbArg<IGNITION_COLOR_ARG,White>,40>,TrFade<1200>>,EFFECT_IGNITION>,
      TransitionEffectL<TrConcat<TrJoin<TrDelayX<RetractionTime<2100>>,TrInstant>,Stripes<3000,3500,RgbArg<RETRACTION_COLOR_ARG,Blue>,RandomPerLEDFlicker<Mix<Int<7710>,Black,RgbArg<RETRACTION_COLOR_ARG,Blue>>,Black>,BrownNoiseFlicker<RgbArg<RETRACTION_COLOR_ARG,Blue>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Blue>>,200>,RandomPerLEDFlicker<Mix<Int<3137>,Black,RgbArg<RETRACTION_COLOR_ARG,Blue>>,Mix<Int<3855>,Black,RgbArg<RETRACTION_COLOR_ARG,Blue>>>>,TrFade<800>>,EFFECT_RETRACTION>,
      TransitionEffectL<TrConcat<TrJoin<TrDelayX<WavLen<>>,TrWipeIn<200>>,AlphaL<RgbArg<STAB_COLOR_ARG,Red>,SmoothStep<IntArg<MELT_SIZE_ARG,28000>,Int<2000>>>,TrWipe<200>>,EFFECT_STAB>,
      MultiTransitionEffectL<TrWaveX<RgbArg<BLAST_COLOR_ARG,Aquamarine>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Int<100>,Scale<EffectPosition<EFFECT_BLAST>,Int<100>,Int<400>>,Scale<EffectPosition<EFFECT_BLAST>,Int<28000>,Int<8000>>>,EFFECT_BLAST>,
      TransitionEffectL<TrConcat<TrJoin<TrDelay<30>,TrInstant>,RgbArg<CLASH_COLOR_ARG,DeepSkyBlue>,TrFade<300>>,EFFECT_CLASH>,
      LockupTrL<AlphaMixL<Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<-12000>>,Sum<IntArg<LOCKUP_POSITION_ARG,16000>,Int<10000>>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AudioFlickerL<RgbArg<LOCKUP_COLOR_ARG,Cyan>>,BrownNoiseFlickerL<RgbArg<LOCKUP_COLOR_ARG,Cyan>,Int<200>>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Cyan>,TrFade<400>>,TrConcat<TrInstant,RgbArg<LOCKUP_COLOR_ARG,Cyan>,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,
      LockupTrL<AlphaL<RgbArg<LB_COLOR_ARG,Cyan>,LayerFunctions<Bump<Scale<SlowNoise<Int<2000>>,Int<3000>,Int<16000>>,Scale<BrownNoiseF<Int<10>>,Int<14000>,Int<8000>>>,Bump<Scale<SlowNoise<Int<2300>>,Int<26000>,Int<8000>>,Scale<NoisySoundLevel,Int<5000>,Int<10000>>>,Bump<Scale<SlowNoise<Int<2300>>,Int<20000>,Int<30000>>,Scale<IsLessThan<SlowNoise<Int<1500>>,Int<8000>>,Scale<NoisySoundLevel,Int<5000>,Int<0>>,Int<0>>>>>,TrConcat<TrInstant,AlphaL<RgbArg<LB_COLOR_ARG,Cyan>,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<RgbArg<LB_COLOR_ARG,Cyan>,Int<16000>>,30>,TrSmoothFade<600>>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,
      LockupTrL<AlphaL<RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,LightCyan>>,SmoothStep<IntArg<DRAG_SIZE_ARG,28000>,Int<3000>>>,TrConcat<TrJoin<TrDelay<4000>,TrWipeIn<200>>,AlphaL<BrownNoiseFlickerL<RgbArg<DRAG_COLOR_ARG,LightCyan>,Int<300>>,SmoothStep<IntArg<DRAG_SIZE_ARG,28000>,Int<3000>>>,TrFade<4000>>,TrFade<300>,SaberBase::LOCKUP_DRAG>,
      LockupTrL<AlphaL<Remap<Scale<RampF,Int<65536>,Int<0>>,StaticFire<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>,Mix<TwistAngle<>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>,RotateColorsX<Int<3000>,Mix<Int<12000>,Black,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>>,0,3,5,3000,10>>,SmoothStep<IntArg<MELT_SIZE_ARG,28000>,Int<4000>>>,TrConcat<TrWipeIn<100>,AlphaL<RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,SmoothStep<IntArg<MELT_SIZE_ARG,28000>,Int<4000>>>,TrJoin<TrDelay<4000>,TrFade<300>>,AlphaL<Mix<TwistAngle<>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>,RotateColorsX<Int<3000>,RgbArg<STAB_COLOR_ARG,Rgb<255,24,0>>>>,SmoothStep<IntArg<MELT_SIZE_ARG,28000>,Int<4000>>>,TrFade<4000>>,TrWipe<200>,SaberBase::LOCKUP_MELT>,
      InOutTrL<TrWipeSparkTipX<RgbArg<IGNITION_COLOR_ARG,White>,IgnitionTime<>>,TrWipeInSparkTipX<RgbArg<RETRACTION_COLOR_ARG,Blue>,RetractionTime<>>>,
      TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<PREON_COLOR_ARG,White>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,2000>,Sum<IntArg<PREON_SIZE_ARG,2000>,Int<4000>>>,Int<-2000>>>,TrDelayX<WavLen<EFFECT_PREON>>>,EFFECT_PREON>,
      TransitionEffectL<TrConcat<TrInstant,AlphaL<BrownNoiseFlickerL<RgbArg<POSTOFF_COLOR_ARG,White>,Int<30>>,SmoothStep<Scale<SlowNoise<Int<2000>>,IntArg<PREON_SIZE_ARG,2000>,Sum<IntArg<PREON_SIZE_ARG,2000>,Int<3000>>>,Int<-4000>>>,TrDelayX<Scale<IsLessThan<WavLen<EFFECT_POSTOFF>,Int<200>>,WavLen<EFFECT_POSTOFF>,Int<4000>>>>,EFFECT_POSTOFF>>>(),
    // === NPXL inner ring: ===
    StylePtr<ColorCycle<BLACK, 1, 0,BLUE, 99,1200, 4000>> (), //"Tron"
    // === NPXL outer ring: ===
    StylePtr<ColorCycle<OrangeRed, 1, 1, EasyBlade<Rainbow, WHITE>, 100, 1200, 10000> >(), //"Rainbow Tron"
    // === Crystal Chamber: ===
    StylePtr<Layers<Layers<Green,RandomL<Black>>,InOutHelperL<InOutFuncX<Int<300>,Int<800>>,Pulsing<Blue,Black,2000>>>>(),
    "liquid/nstatic"},

    { "slave1.5.2;common", "tracks/track1.wav",
      //Theory2Button.h "Kaboom"
     StylePtr<Layers<Layers<Mix<SmoothStep<Int<16384>,Int<4000>>,Stripes<10000,200,Rgb<0,20,90>,Rgb<0,50,240>>,Stripes<10000,-200,Rgb<0,20,90>,Rgb<0,50,240>>>,TransitionEffectL<TrConcat<TrInstant,White,TrFade<600>>,EFFECT_IGNITION>>,LockupTrL<Layers<AlphaL<AudioFlickerL<White>,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Scale<SwingSpeed<100>,Int<14000>,Int<18000>>>>,AlphaL<White,Bump<Scale<BladeAngle<>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>>,Int<10000>>>>,TrConcat<TrInstant,White,TrFade<400>>,TrConcat<TrInstant,White,TrFade<400>>,SaberBase::LOCKUP_NORMAL>,ResponsiveLightningBlockL<Strobe<White,AudioFlicker<White,Blue>,50,1>,TrConcat<TrInstant,AlphaL<White,Bump<Int<12000>,Int<18000>>>,TrFade<200>>,TrConcat<TrInstant,HumpFlickerL<AlphaL<White,Int<16000>>,30>,TrSmoothFade<600>>>,ResponsiveStabL<Red>,ResponsiveBlastL<White,Int<400>,Scale<SwingSpeed<200>,Int<100>,Int<400>>>,ResponsiveClashL<White,TrInstant,TrFade<400>,Scale<BladeAngle<0,16000>,Int<4000>,Int<26000>>,Int<6000>,Int<20000>>,LockupTrL<AlphaL<BrownNoiseFlickerL<White,Int<300>>,SmoothStep<Int<30000>,Int<5000>>>,TrWipeIn<400>,TrFade<300>,SaberBase::LOCKUP_DRAG>,LockupTrL<AlphaL<Mix<TwistAngle<>,Red,Orange>,SmoothStep<Int<28000>,Int<5000>>>,TrWipeIn<600>,TrFade<300>,SaberBase::LOCKUP_MELT>,InOutTrL<TrJoinR<TrWipe<300>,TrWipeIn<300>>,TrJoin<TrWipe<5000>,TrWipeIn<5000>>>,TransitionEffectL<TrConcat<TrInstant,AlphaL<Pulsing<Rgb<0,50,240>,Rgb<0,50,240>,400>,Bump<Scale<Trigger<EFFECT_PREON,Int<3000>,Int<1500>,Int<1500>>,Int<0>,Int<16384>>,Int<8000>>>,TrDelay<3000>,Mix<Bump<Int<16384>,Int<8000>>,Black,Rgb<0,50,240>>,TrJoin<TrWipe<1500>,TrWipeIn<1500>>,Mix<Bump<Int<16384>,Int<8000>>,Black,Rgb<0,50,240>>,TrDelay<160>>,EFFECT_PREON>>>(),
     StylePtr<InOutSparkTip<EASYBLADE(BLUE, MAGENTA), 300, 800> >(),
     StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, BLUE), 300, 800> >(),
     StylePtr<Layers<RandomFlicker<RotateColorsX<Variation,DeepSkyBlue>,RotateColorsX<Variation,Rgb<0,20,128>>> ,LockupTrL<BrownNoiseFlickerL<White,Int<200>>,TrConcat<TrInstant,White,TrFade<300>>,TrFade<300>,SaberBase::LOCKUP_NORMAL>,LockupTrL<BrownNoiseFlickerL<White,Int<200>>,TrConcat<TrInstant,White,TrFade<300>>,TrFade<300>,SaberBase::LOCKUP_LIGHTNING_BLOCK>,BlastL<Moccasin>,SimpleClashL<Moccasin>,InOutTrL<TrInstant,TrFade<300>,Pulsing<RotateColorsX<Variation,DeepSkyBlue>,RotateColorsX<Variation,Rgb<0,4,10>>,3000>>>>(),
     "slave1"},

/* === EMPTY TEMPLATE ===
   {";common", "tracks/track1.wav",
    // === Main Blade: ===
    ,
    // === NPXL inner ring: ===
    ,
    // === NPXL outer ring: ===
    ,
    // === Crystal Chamber: ===
    ,
    ""},

   { ";common", "tracks/track1.wav",
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 0>(), "" },

   { ";common", "tracks/track1.wav",
    StyleNormalPtr<CYAN, WHITE, 300, 800>(),
      // Marble style from Proffezzorn
    StylePtr<Mix<CircularSectionF<MarbleF<Int<-2000>,Int<40000>,Ifon<Int<827680>,Int<0>>,Int<1276800>>,ChangeSlowly<Ifon<Int<32768>,Int<3276>>,Int<2048>>>,Black,Mix<InOutFuncX<Int<2000>,Int<2000>>,Rgb<0,0,20>,Rgb<0,255,255>>>>(),
      // Marble style from Proffezzorn
    StylePtr<Mix<CircularSectionF<MarbleF<Int<-2000>,Int<40000>,Ifon<Int<827680>,Int<0>>,Int<1276800>>,ChangeSlowly<Ifon<Int<32768>,Int<3276>>,Int<2048>>>,Black,Mix<InOutFuncX<Int<2000>,Int<2000>>,Rgb<0,0,20>,Rgb<0,255,255>>>>(),
    StyleNormalPtr<CYAN, WHITE, 300, 800>(), ""},

   { ";common", "tracks/track1.wav",
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(BLUE, WHITE), 300, 800> >(), ""},

   { ";common", "tracks/track1.wav",
    StyleFirePtr<RED, YELLOW, 0>(),
    StyleFirePtr<RED, YELLOW, 1>(),
    StyleFirePtr<RED, YELLOW, 2>(),
    StyleFirePtr<RED, YELLOW, 3>(), ""},

   { ";common", "tracks/track1.wav",
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(),
    StyleNormalPtr<RED, WHITE, 300, 800>(), ""},

   { ";common", "tracks/track1.wav",
    StyleFirePtr<BLUE, CYAN, 0>(),
    StyleFirePtr<BLUE, CYAN, 1>(),
    StyleFirePtr<BLUE, CYAN, 2>(),
    StyleFirePtr<BLUE, CYAN, 3>(), ""},

   { ";common", "tracks/track1.wav",
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(),
    StylePtr<InOutHelper<EASYBLADE(OnSpark<GREEN>, WHITE), 300, 800> >(), ""},

   { ";common", "tracks/track1.wav",
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(),
    StyleNormalPtr<WHITE, RED, 300, 800, RED>(), ""},

   { ";common", "tracks/track1.wav",
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(),
    StyleNormalPtr<AudioFlicker<YELLOW, WHITE>, BLUE, 300, 800>(), ""},

   { ";common", "tracks/track1.wav",
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(),
    StylePtr<InOutSparkTip<EASYBLADE(MAGENTA, WHITE), 300, 800> >(), ""},

   { ";common", "tracks/track1.wav",
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(),
    StyleNormalPtr<Gradient<RED, BLUE>, Gradient<CYAN, YELLOW>, 300, 800>(), ""},
*/

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

// === Battery Level / Keep as last preset ===
   { "SmthJedi;common", "tracks/track1.wav",
    StylePtr<InOutHelperX<Gradient<Red,Orange,Yellow,Green,Green,Green,Green>, BatteryLevel>>(),
    &style_charging,
    StylePtr<InOutHelperX<Gradient<Red,Orange,Yellow,Green,Green,Green,Green>, BatteryLevel>>(),
    StyleNormalPtr<BLACK, BLACK, 300, 800>(), "battery\nlevel"},

};

BladeConfig blades[] = {
 { 0,
   // === Main Blade: ===
    WS281XBladePtr<144, bladePin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >(),
   // === NPXL Connector (1, 3, 5, 7, 9, 11, 13, 15 are "inner ring") ===
    SubBladeWithStride(0, 15, 2, WS281XBladePtr<16, blade2Pin, Color8::GRB, PowerPINS<bladePowerPin2, bladePowerPin3> >()),
   // === NPXL Connector (2, 4, 6, 8, 10, 12, 14, 16 are "outer ring") ===
    SubBladeWithStride(1, 15, 2, NULL),
   // === Crystal Chamber: ===
    WS281XBladePtr<1, blade3Pin, Color8::GRB, PowerPINS<bladePowerPin1> >(),
    CONFIGARRAY(presets) },
};

//RFID_Command RFID_Commands[] = {
//  { 0x0000000C04ULL,    "change_preset", "0" },
//  { 0x09003A8CDCULL,    "change_preset", "1" },
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

/*
#ifndef CONFIG_STYLES
using BatteryLevelStyle = InOutHelperX<Gradient<Red,Orange,Yellow,Green,Green,Green,Green>, BatteryLevel>; //"error: 'InOutHelperX' does not name a type" and does not compile
//more stuff can come here
#endif // CONFIG_STYLES
*/

#ifdef CONFIG_BOTTOM
    DisplayHelper<128, uint32_t,             //OLED additional features: "Bullet Counts" - Code needed to activate the display.
    BaseLayerOp<StandardDisplayController>,  // https://github.com/profezzorn/ProffieOSDocs/blob/main/display/bullet-counts.md
    ClearRectangleOp<10, 80, 8, 24>,         //
    WriteBulletCountOp<10, 20, 5> >          // https://github.com/profezzorn/ProffieOSDocs/blob/main/display/images-and-animations.md
    display_controller;
    SSD1306Template<128, uint32_t> display(&display_controller);

// == Color Display ==
/*
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
                                             //Proffieboard Experimental V4.1.0 (at the time of writing)
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
*/
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
#ifdef CONFIG_BOTTOM
    DisplayHelper<128, uint32_t,             //OLED additional features: "Bullet Counts" - Code needed to activate the display.
    BaseLayerOp<StandardDisplayController>,  // https://github.com/profezzorn/ProffieOSDocs/blob/main/display/bullet-counts.md
    ClearRectangleOp<10, 80, 8, 24>,         //
    WriteBulletCountOp<10, 20, 5> >          // https://github.com/profezzorn/ProffieOSDocs/blob/main/display/images-and-animations.md
    display_controller;
    //IfImageOp<OP>     //I don't know what this means ???: "This executes OP if the base layer is showing an image, but not otherwise. 
                        //The idea is that you could have a bullet count that draws over images, but not messages and battery monitors."
    //IfImageOp<OP>     // <-- What do I need instead of <OP> ???
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
*/