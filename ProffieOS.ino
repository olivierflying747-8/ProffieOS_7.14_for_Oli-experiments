/*
 ProffieOS: Control software for lightsabers and other props.
 http://fredrik.hubbe.net/lightsaber/teensy_saber.html
 Copyright (c) 2016-2019 Fredrik Hubinette
 Additional copyright holders listed inline below.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



// ProffieOSx Fork by RSX Engineering. Licensed under GPL v3 as above.
// *******************************************************************
// #define OSx    // This compilation switch activates the OSx alterations of ProffieOS. 
                  // Normally controlled by Arduino's board menu, under 'Operating Sytem'.
                  // ProffieOSx requires the board package 'UltraProffie Line'; to install it, add
                  // https://ultraproffie.com/package_ultraproffie_index.json in Board Manager.
#define CONFIG_FILE "config/osx_config.h"



/*-----------------------------------------------------------------*\
|  You can have multiple configuration files, and specify which one |
|  to use here by removing the two slashes at the beginning.        |
|  **NOTE** Only ONE line should be left uncommented at a time!     |
|  Add the slashes to any that you are not using.                   |
\*-----------------------------------------------------------------*/
// #define CONFIG_FILE "config/YOUR_CONFIG_FILE_NAME_HERE.h"
// #define CONFIG_FILE "config/default_v3_config.h"
// #define CONFIG_FILE "config/crossguard_config.h"
// #define CONFIG_FILE "config/graflex_v1_config.h"
// #define CONFIG_FILE "config/prop_shield_fastled_v1_config.h"
// #define CONFIG_FILE "config/owk_v2_config.h"
// #define CONFIG_FILE "config/test_bench_config.h"
// #define CONFIG_FILE "config/toy_saber_config.h"
// #define CONFIG_FILE "config/proffieboard_v1_test_bench_config.h"
// #define CONFIG_FILE "config/td_proffieboard_config.h"
// #define CONFIG_FILE "config/proffieboard_v1_graflex.h"
// #define CONFIG_FILE "config/teensy_audio_shield_micom.h"
// #define CONFIG_FILE "config/proffieboard_v2_ob4.h"
// #define CONFIG_FILE "config/testconfig.h"
// #endif

#ifdef CONFIG_FILE_TEST
#undef CONFIG_FILE
#define CONFIG_FILE CONFIG_FILE_TEST
#endif

#ifndef CONFIG_FILE
#error Please set CONFIG_FILE as shown above.
#endif

#ifndef ULTRA_PROFFIE

  #ifdef OSx
    // #define OLDINSTALL
    // #define OLDPROFILE
  #endif

  #define CONFIG_TOP
  #include CONFIG_FILE
  #undef CONFIG_TOP
#else
  #ifdef OSx
    // #define OLDINSTALL
    // #define OLDPROFILE
  #endif
  #define CONFIG_TOP
  #include "config/board_config.h"
  #undef CONFIG_TOP
#endif

#ifdef SAVE_STATE
#define SAVE_VOLUME
#define SAVE_PRESET
#define SAVE_COLOR_CHANGE
#define SAVE_DYNAMIC_DIMMING
#endif

#ifdef ENABLE_ALL_EDIT_OPTIONS
#define DYNAMIC_BLADE_LENGTH
#define DYNAMIC_BLADE_DIMMING
#define DYNAMIC_CLASH_THRESHOLD
#define SAVE_VOLUME
#define SAVE_BLADE_DIMMING
#define SAVE_CLASH_THRESHOLD
#define SAVE_COLOR_CHANGE
#endif

// #define ENABLE_DEBUG


//
// OVERVIEW
//
// Here explain some general code concepts to make it easier
// to understand the code below.
//
// Most things start with the ProbBase class. Depending on the
// configuration, this class is extended by the Saber class,
// the Detonator class, or some other class. The extended class
// is instantiated as "prop", and is responsible for handling
// button clicks, clashes, swings and other events. These events
// are then send to all registered SaberBase classes.
///
// Generally speaking, there are usually two registered SaberBase
// classes listening for events. One for sound and one for
// the blade. Sound and blade effects are generally executed
// separately by separate clases.
//
// Blades are generally handled by one of the child-classes of
// BladeBase. These classes know how many LEDs the current
// blade has, and how to set those LEDs to a given color, but
// they don't actually decide what the blade should look like.
// Instead they just call the current BladeStyle class and
// asks it to set the colors. The BladeStyle classes don't
// need to know what kind of blade is attached, although
// some combinations of BladeBases and BladeStyles just don't
// make any sense.
//
// Sounds are also abstracted. It starts with scanning a directory
// on the SD card for files that match known patterns of file names.
// The Effect class is responsible for keeping track of all numbered
// files that for a particular filename prefix.
//
// Once the directory has been scanned, we'll decide how to play
// sounds. In the past, there was one class for handling NEC style
// fonts and another for handling Plecter style fonts. However,
// both of those have now been merged into the HybridFont class
// which can do both. It is also capable of doing some mix and matching,
// so you can use a plecter style hum together with a NEC style
// swing if you so desire. The HybridFont class inherit from
// SaberBase and listen on on/off/clash/etc. events, just like
// BladeBase classes do.
//
// HybridFont tells the audio subsystem
// to trigger and mix sounds as aproperiate. The sound subsystem
// starts with an DMA channel which feeds data to a digital-to-analog
// converter. Once the data buffer is half-gone, and interrupt is
// triggered in the DAC class, which tries to fill it up by
// reading data from a int16_t AudioStream. Generally, that data
// stream is hooked up to the AudioDynamicMixer class. This
// class is responsible for taking multiple audio inputs,
// summing them up and then adjusting the volume to minimize
// clipping.

// TODO LIST:
//   stab detect/effect
//
// Audio work items:
//   select clash from force
//   stab effect
// Blade stuff
//    better clash
// Allow several blades to share power pins.

// If defined, DAC vref will be 3 volts, resulting in louder sound. (teensy only)
#define LOUD

// You can get better SD card performance by
// activating the  USE_TEENSY3_OPTIMIZED_CODE define
// in SD.h in the teensy library, however, my sd card
// did not work with that define.

#if !defined(ULTRA_PROFFIE) && defined(PROFFIEBOARD_VERSION)
  #include "common/crc.h"
#endif

#include <Arduino.h>

#ifdef TEENSYDUINO
#include <DMAChannel.h>
#include <usb_dev.h>

#ifndef USE_TEENSY4
#include <kinetis.h>
#endif

#include <i2c_t3.h>
#include <SD.h>
#include <SPI.h>

#define INPUT_ANALOG INPUT
#else

// This is a hack to let me access the internal stuff..
#define private public
#include <Wire.h>
#undef private

#include <FS.h>
#define digitalWriteFast digitalWrite
#include <stm32l4_wiring_private.h>
#include <stm32l4xx.h>
#include <armv7m.h>
#include <stm32l4_gpio.h>
#include <stm32l4_sai.h>
#include <stm32l4_dma.h>
#include <stm32l4_system.h>
#include <arm_math.h>
#include <STM32.h>
#define DMAChannel stm32l4_dma_t
#define DMAMEM
#define NVIC_SET_PRIORITY(X,Y) NVIC_SetPriority((X), (IRQn_Type)(Y))

#endif

#include <math.h>
#include <malloc.h>

#ifdef ENABLE_SERIALFLASH

// This is a hack to let me access the internal stuff..
#define private public
#define protected public

#include <SerialFlash.h>

#undef private
#undef protected
#endif

#ifdef ENABLE_SNOOZE
#define startup_early_hook DISABLE_startup_early_hook
#include <Snooze.h>
#undef startup_early_hook

SnoozeTimer snooze_timer;
SnoozeDigital snooze_digital;
SnoozeTouch snooze_touch;
SnoozeBlock snooze_config(snooze_touch, snooze_digital, snooze_timer);
#endif

#ifdef OSx
  const char version[] = "v6.7x" OSX_SUBVERSION;
#else // nOSx
  const char version[] = "v6.7";
#endif // OSx
const char install_time[] = __DATE__ " " __TIME__;

#include "common/common.h"
#include "common/state_machine.h"
#include "common/monitoring.h"
#include "common/stdout.h"

Monitoring monitor;
DEFINE_COMMON_STDOUT_GLOBALS;

void PrintQuotedValue(const char *name, const char* str) {
  STDOUT.print(name);
  STDOUT.write('=');
  if (str) {
    while (*str) {
      switch (*str) {
        case '\n':
          STDOUT.print("\\n");
          break;
        case '\t':
          STDOUT.print("\\t");
          break;
        case '\\':
          STDOUT.write('\\');
        default:
          STDOUT.write(*str);
      }
      ++str;
    }
  }
  #ifndef OSx
    STDOUT.write('\n');
  #else // OSx
    STDOUT.println("");
  #endif
}

#ifdef ENABLE_DEBUG

// This class is really useful for finding crashes
// basically, the pin you give it will be held high
// while this function is running. After that it will
// be set to low. If a crash occurs in this function
// it will stay high.
class ScopedPinTracer {
public:
  explicit ScopedPinTracer(int pin) : pin_(pin) {
    pinMode(pin_, OUTPUT);
    digitalWriteFast(pin, HIGH);
  }
  ~ScopedPinTracer() {
    digitalWriteFast(pin_, LOW);
  }
private:
  int pin_;
};

class ScopedTracer3 {
public:
  explicit ScopedTracer3(int code) {
    pinMode(bladePowerPin1, OUTPUT);
    pinMode(bladePowerPin2, OUTPUT);
    pinMode(bladePowerPin3, OUTPUT);
    digitalWriteFast(bladePowerPin1, !!(code & 1));
    digitalWriteFast(bladePowerPin2, !!(code & 2));
    digitalWriteFast(bladePowerPin3, !!(code & 4));
  }
  ~ScopedTracer3() {
    digitalWriteFast(bladePowerPin1, LOW);
    digitalWriteFast(bladePowerPin2, LOW);
    digitalWriteFast(bladePowerPin3, LOW);
  }
};

#endif

#ifdef OSx 
  #include "common/xProbe.h"   // LoopCounter and ScopedCycleCounter redefined here
  // #include "common/xInterpolator.h"
  #include "common/profiling.h"
  xProbe audio_dma_interrupt_cycles;
  xProbe pixel_dma_interrupt_cycles;
  xProbe motion_interrupt_cycles;
  xProbe wav_interrupt_cycles;
#else // nOSx
#include "common/scoped_cycle_counter.h"
#include "common/profiling.h"

uint64_t audio_dma_interrupt_cycles = 0;
uint64_t pixel_dma_interrupt_cycles = 0;
uint64_t motion_interrupt_cycles = 0;
uint64_t wav_interrupt_cycles = 0;
uint64_t loop_cycles = 0;

#include "common/loop_counter.h"
#endif // OSx

#define NELEM(X) (sizeof(X)/sizeof((X)[0]))

#ifdef DOSFS_CONFIG_STARTUP_DELAY
#define PROFFIEOS_SD_STARTUP_DELAY DOSFS_CONFIG_STARTUP_DELAY
#else
#define PROFFIEOS_SD_STARTUP_DELAY 1000
#endif

#ifndef CONFIG_STARTUP_DELAY
#define CONFIG_STARTUP_DELAY 0
#endif

#if PROFFIEOS_SD_STARTUP_DELAY > CONFIG_STARTUP_DELAY
#define PROFFIEOS_STARTUP_DELAY PROFFIEOS_SD_STARTUP_DELAY
#else
#define PROFFIEOS_STARTUP_DELAY CONFIG_STARTUP_DELAY
#endif

#include "common/linked_list.h"
#include "common/looper.h"
#include "common/command_parser.h"
#include "common/monitor_helper.h"

CommandParser* parsers = NULL;
MonitorHelper monitor_helper;

#include "common/vec3.h"
#include "common/quat.h"
#include "common/ref.h"
#include "common/events.h"
#include "common/saber_base.h"
#include "common/saber_base_passthrough.h"
SaberBase* saberbases = NULL;
SaberBase::LockupType SaberBase::lockup_ = SaberBase::LOCKUP_NONE;
SaberBase::ColorChangeMode SaberBase::color_change_mode_ =
  SaberBase::COLOR_CHANGE_MODE_NONE;
bool SaberBase::on_ = false;
uint32_t SaberBase::last_motion_request_ = 0;
uint32_t SaberBase::current_variation_ = 0;
float SaberBase::sound_length = 0.0;
int SaberBase::sound_number = -1;
float SaberBase::clash_strength_ = 0.0;
#ifdef OSx
  bool SaberBase::monoFont = true;  
  uint8_t Sensitivity::master = 128;


#endif

#ifdef DYNAMIC_BLADE_DIMMING
int SaberBase::dimming_ = 16384;
#endif


#include "common/box_filter.h"

// Returns the decimals of a number, ie 12.2134 -> 0.2134
float fract(float x) { return x - floorf(x); }

// clamp(x, a, b) makes sure that x is between a and b.
float clamp(float x, float a, float b) {
  if (x < a) return a;
  if (x > b) return b;
  return x;
}
float Fmod(float a, float b) {
  return a - floorf(a / b) * b;
}

int32_t clampi32(int32_t x, int32_t a, int32_t b) {
  if (x < a) return a;
  if (x > b) return b;
  return x;
}
int16_t clamptoi16(int32_t x) {
  return clampi32(x, -32768, 32767);
}
int32_t clamptoi24(int32_t x) {
  return clampi32(x, -8388608, 8388607);
}

#include "common/sin_table.h"

void EnableBooster();
void EnableAmplifier();
bool AmplifierIsActive();
void MountSDCard();
const char* GetSaveDir();

#ifdef ULTRA_PROFFIE
void SilentEnableBooster(bool on);
void SilentEnableAmplifier(bool on);
#endif 

#include "common/lsfs.h"
#include "common/strfun.h"


// Double-zero terminated array of search paths.
// No trailing slashes!
char current_directory[128];
const char* next_current_directory(const char* dir) {
  dir += strlen(dir);
  dir ++;
  if (!*dir) return NULL;
  return dir;
}

#include "sound/sound.h"
#include "common/battery_monitor.h"
#include "common/xBatteryCharger.h"
#include "common/color.h"
#include "common/range.h"
#include "common/fuse.h"
#include "blades/blade_base.h"
#include "blades/blade_wrapper.h"

class MicroEventTime {
  void SetToNow() { micros_ = micros(); millis_ = millis(); }
  uint32_t millis_since() { return millis() - millis_; }
  uint32_t micros_since() {
    if (millis_since() > (0xFFFF0000UL / 1000)) return 0xFFFFFFFFUL;
    return micros() - micros_;
  }
private:
  uint32_t millis_;
  uint32_t micros_;
};

template<class T, class U>
struct is_same_type { static const bool value = false; };

template<class T>
struct is_same_type<T, T> { static const bool value = true; };

// This really ought to be a typedef, but it causes problems I don't understand.
#define StyleAllocator class StyleFactory*

#include "styles/rgb.h"
#include "styles/rgb_arg.h"
#include "styles/charging.h"
#include "styles/fire.h"
#include "styles/sparkle.h"
#include "styles/gradient.h"
#include "styles/random_flicker.h"
#include "styles/random_per_led_flicker.h"
#include "styles/audio_flicker.h"
#include "styles/brown_noise_flicker.h"
#include "styles/hump_flicker.h"
#include "styles/rainbow.h"
#include "styles/color_cycle.h"
#include "styles/cylon.h"
#include "styles/ignition_delay.h"
#include "styles/retraction_delay.h"
#include "styles/pulsing.h"
#include "styles/blinking.h"
#include "styles/on_spark.h"
#include "styles/rgb_cycle.h"
#include "styles/clash.h"
#include "styles/lockup.h"  // Also does "drag"
#include "styles/blast.h"
#include "styles/strobe.h"
#include "styles/inout_helper.h"
#include "styles/inout_sparktip.h"
#include "styles/colors.h"
#include "styles/mix.h"
#include "styles/style_ptr.h"
#include "styles/file.h"
#include "styles/stripes.h"
#include "styles/random_blink.h"
#include "styles/sequence.h"
#include "styles/byteorder.h"
#include "styles/rotate_color.h"
#include "styles/colorchange.h"
#include "styles/transition_effect.h"
#include "styles/transition_loop.h"
#include "styles/effect_sequence.h"
#include "styles/color_select.h"
#include "styles/remap.h"
#include "styles/edit_mode.h"

// functions
#include "functions/ifon.h"
#include "functions/change_slowly.h"
#include "functions/int.h"
#include "functions/int_arg.h"
#include "functions/int_select.h"
#include "functions/sin.h"
#include "functions/scale.h"
#include "functions/battery_level.h"
#include "functions/trigger.h"
#include "functions/bump.h"
#include "functions/smoothstep.h"
#include "functions/swing_speed.h"
#include "functions/sound_level.h"
#include "functions/blade_angle.h"
#include "functions/variation.h"
#include "functions/twist_angle.h"
#include "functions/layer_functions.h"
#include "functions/islessthan.h"
#include "functions/circular_section.h"
#include "functions/marble.h"
#include "functions/slice.h"
#include "functions/mult.h"
#include "functions/wavlen.h"
#include "functions/wavnum.h"
#include "functions/effect_position.h"
#include "functions/time_since_effect.h"
#include "functions/sum.h"
#include "functions/ramp.h"
#include "functions/center_dist.h"
#include "functions/linear_section.h"
#include "functions/hold_peak.h"
#include "functions/clash_impact.h"
#include "functions/effect_increment.h"
#include "functions/increment.h"

// transitions
#include "transitions/fade.h"
#include "transitions/join.h"
#include "transitions/concat.h"
#include "transitions/instant.h"
#include "transitions/delay.h"
#include "transitions/wipe.h"
#include "transitions/join.h"
#include "transitions/boing.h"
#include "transitions/random.h"
#include "transitions/colorcycle.h"
#include "transitions/wave.h"
#include "transitions/select.h"
#include "transitions/extend.h"
#include "transitions/center_wipe.h"
#include "transitions/sequence.h"

#include "styles/legacy_styles.h"
//responsive styles
#include "styles/responsive_styles.h"
#include "styles/pov.h"

class NoLED;

#include "blades/power_pin.h"
#include "blades/drive_logic.h"
#include "blades/pwm_pin.h"

#ifdef OSx  // added only on Osx , error  on compiling on normal OS battery_monitor.voltageLSB not found
            // TODO ask if x files (analog , cod reader are only for OSx ) - YES!
#include "blades/xAnalogLED.h"
#endif

#include "blades/ws2811_blade.h"
#include "blades/fastled_blade.h"
#include "blades/simple_blade.h"
#include "blades/saviblade.h"
#include "blades/sub_blade.h"
#include "blades/dim_blade.h"
#include "blades/leds.h"
#include "blades/blade_id.h"
#if defined(OSx) && !defined(OLDPROFILE)
  #include "common/xPreset.h"
  #include "common/xProfile.h"   
#endif
#include "common/preset.h"
#include "common/blade_config.h"
#include "common/current_preset.h"
#include "common/status_led.h"
#include "styles/style_parser.h"
#include "styles/length_finder.h"
#include "styles/show_color.h"
#include "styles/blade_shortener.h"

#ifndef OSx
  BladeConfig* current_config = nullptr;
#else // OSx
  extern BladeConfig blades[];
  BladeConfig* current_config = blades;

// Get a address of a blade. bladeNo starts at 1 !!!
inline class BladeBase* BladeAddress(uint8_t bladeNo) {
    switch (bladeNo) {
        #if NUM_BLADES >= 1
            case 1: return current_config->blade1;
        #endif
         #if NUM_BLADES >= 2
            case 2: return current_config->blade2;
        #endif
        #if NUM_BLADES >= 3
            case 3: return current_config->blade3;
        #endif
        #if NUM_BLADES >= 4
            case 4: return current_config->blade4;
        #endif
        #if NUM_BLADES >= 5
            case 5: return current_config->blade5;
        #endif
        #if NUM_BLADES >= 6
            case 6: return current_config->blade6;
        #endif                                   
        default: return 0;
    }
}

#endif // OSx

class BladeBase* GetPrimaryBlade() {
#if NUM_BLADES == 0
  return nullptr;
#else  
  return current_config->blade1;
#endif  
}
const char* GetSaveDir() {
  if (!current_config) return "";
  if (!current_config->save_dir) return "";
  return current_config->save_dir;
}


#ifndef OSx // sorry, no ascii chat between machines...
ArgParserInterface* CurrentArgParser;
#endif

#define CONFIG_PRESETS
#include CONFIG_FILE
#undef CONFIG_PRESETS

#define CONFIG_PROP
#include CONFIG_FILE
#undef CONFIG_PROP

#ifndef OSx // ULTRA_PROFFIE
  #ifndef PROP_TYPE
  #include "props/saber.h"
  // #include "props/ultrasaber.h"  
  #endif
#else 
  #ifndef PROP_TYPE
    #ifdef PF_PROP_ULTRASABERS
      #include "props/ultrasaber.h"  
    #elif defined(PF_PROP_SABER)
      #include "props/saber.h"
    #elif defined(PF_PROP_SABER_SHTOK)
      #include "props/saber_shtok_buttons.h"
    #elif defined(PF_PROP_SABER_SA22C)
      #include "props/saber_sa22c_buttons.h"
    #elif defined(PF_PROP_SABER_FETT)
      #include "props/saber_fett263_buttons.h"
    #elif defined(PF_PROP_SABER_BC)
      #include "props/saber_BC_buttons.h"
    #elif defined(PF_PROP_DETON)
      #include "props/detonator.h"
    #elif defined(PF_PROP_BLASTER)
      #include "props/blaster.h"
    #elif defined(PF_PROP_AUDIOFX)
      #include "props/audiofx.h"
    #endif

  #endif
#endif

PROP_TYPE prop;




#if 0
#include "scripts/test_motion_timeout.h"
#warning MOTION TEST SCRIPT ACTIVE
MotionTimeoutScript script;
#endif

#if 0
#include "scripts/v3_test_script.h"
#warning !!! V3 TEST SCRIPT ACTIVE !!!
V3TestScript script;
#endif

#if 0
#include "scripts/proffieboard_test_script.h"
#warning !!! PROFFIEBOARD TEST SCRIPT ACTIVE !!!
V4TestScript script;
Blinker1 blinker1;
Blinker2 blinker2;
CapTest captest;
#endif

#include "buttons/floating_button.h"
#include "buttons/latching_button.h"
#include "buttons/button.h"
#ifdef TEENSYDUINO
#include "buttons/touchbutton.h"
#else
#include "buttons/stm32l4_touchbutton.h"
#endif
#include "buttons/rotary.h"
#include "buttons/pots.h"

#include "ir/ir.h"
#include "ir/receiver.h"
#include "ir/blaster.h"
#include "ir/print.h"
#include "ir/nec.h"
#include "ir/rc6.h"
#include "ir/stm32_ir.h"

#ifndef TEENSYDUINO

uint32_t startup_AHB1ENR;
uint32_t startup_AHB2ENR;
uint32_t startup_AHB3ENR;
uint32_t startup_APB1ENR1;
uint32_t startup_APB1ENR2;
uint32_t startup_APB2ENR;
uint32_t startup_MODER[4];

#endif



#ifndef ULTRA_PROFFIE
#define CONFIG_BUTTONS
#include CONFIG_FILE
#undef CONFIG_BUTTONS
#else
  #define CONFIG_BUTTONS
  #include "config/board_config.h"
  #undef CONFIG_BUTTONS
#endif

#if defined(OSx) && !defined(OLDINSTALL)
  #include "common/xInstall.h"   // after all invocations of CONFIG_FILE
#endif

// #if defined(OSx) && !defined(OLDPROFILE)
//   #include "common/xProfile.h"   
// #endif  



#ifdef BLADE_DETECT_PIN
LatchingButtonTemplate<FloatingButtonBase<BLADE_DETECT_PIN>>
    BladeDetect(BUTTON_BLADE_DETECT, BLADE_DETECT_PIN, "blade_detect");
#endif

#include "common/sd_test.h"

#ifdef ULTRA_PROFFIE
  #include "common/xProdSerial.h"
#endif

#ifdef OSX_ENABLE_MTP
  #include "common/serial.h"
#endif 



class I2CDevice;

#ifdef OSx
  int	rand (void) { return millis(); }    // cheaper and randomer, since nothing is in sync
  // Need those to report RAM usage
  extern "C" char *sbrk(int i);
  extern uint32_t __StackLimit;
  extern uint32_t __StackTop;
  extern uint32_t __HeapLimit;
  extern uint32_t __HeapBase;
  extern uint32_t __data_start__;
  extern uint32_t __data_end__;
  extern uint32_t __bss_start__;
  extern uint32_t __bss_end__;  
#endif

class Commands : public CommandParser {
 public:
  enum PinType {
    PinTypeFloating,
    PinTypePulldown,
    PinTypeCap,
    PinTypeOther,
  };

  bool TestPin(int pin, PinType t) {
    int ret = 0;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(20);
    ret <<= 1;
    ret |= digitalRead(pin);

    digitalWrite(pin, HIGH);
    delayMicroseconds(20);
    ret <<= 1;
    ret |= digitalRead(pin);

    // Discharge time
    pinMode(pin, INPUT_PULLDOWN);
    uint32_t start = micros();
    uint32_t end;
    while (digitalRead(pin)) {
      end = micros();
      if (end - start > 32768) break; // 32 millis
    }
    ret <<= 16;
    ret |= (end - start);

    pinMode(pin, INPUT_PULLUP);
    delayMicroseconds(20);
    ret <<= 1;
    ret |= digitalRead(pin);
    pinMode(pin, INPUT);

    return ret;
  }
  bool Parse(const char* cmd, const char* e) override {
//#ifndef DISABLE_DIAGNOSTIC_COMMANDS
    if (!strcmp(cmd, "help")) {
      CommandParser::DoHelp();
      return true;
    }
//#endif

#if defined(ULTRA_PROFFIE) && defined(OSx)
  if(!strcmp(cmd, "board_info")) {
    STDOUT.println("board_info-START");
    STDOUT.println("HARDWARE:");
    PROFFIE_HDID.printHWSN(NULL);
    STDOUT.println("FIRMWARE:");
    STDOUT.print("ProffieOS "); STDOUT.println(version);
    STDOUT.print("Compiled: "); STDOUT.println(install_time);
    STDOUT.print("Build for: "); STDOUT.println(XSTR(HWVER));

    STDOUT.print("Prop: '"); STDOUT.print(prop.name()); STDOUT.println("'");
    STDOUT.print("Supported blades: "); STDOUT.println(NUM_BLADES);
    STDOUT.print("Diagnose: ");
    #ifdef PF_STATUS_REPORT_ON
      STDOUT.println("ON");
    #else
      STDOUT.println("OFF");
    #endif
    STDOUT.print("Developer mode: ");
    #ifdef ENABLE_DEVELOPER_MODE
      STDOUT.println("ON");
    #else
      STDOUT.println("OFF");
    #endif

    STDOUT.println("board_info-END");
    return true;
  }
#endif


    
#ifndef OSx 
  #ifndef DISABLE_DIAGNOSTIC_COMMANDS
    if (!strcmp(cmd, "renamePath") && e) {
      STDOUT.println("rename path");
      { 
        char *String = (char*)e;
        char pathFrom[128];
        char pathTo[128];
        char *token;
        for(uint8_t i=0; i<128;i++)
        {
            pathFrom[i] = 0;
            pathTo[i] = 0;
        }
        LOCK_SD(true);
        token = strtok(String, " ");
        uint8_t i = 0;
        while( token != NULL ) {
          if(!i) {
            sprintf(pathFrom, "%s", token);
            STDOUT.print("PATH FROM "); STDOUT.println(pathFrom);
            i++;
          } else {
            sprintf(pathTo, "%s", token);
            STDOUT.print("PATH TO "); STDOUT.println(pathTo);
            i++;
            break;
          }
          token = strtok(NULL, " ");
        }
        if(i == 2) {
          STDOUT.print("SUCCESS PArSiNG");
          STDOUT.print("Renaming ");
          STDOUT.print("from ");
          STDOUT.print(pathFrom);
          STDOUT.print(" to ");
          STDOUT.println(pathTo);
          if(LSFS::Exists(pathFrom)) {
            STDOUT.print("Renaming result = "); STDOUT.println(LSFS::RenamePath(pathFrom, pathTo));
          } else {
              STDOUT.print("Path not exist");
          }

        }
        LOCK_SD(false);

      }

      return true;
    }   
    #endif // DISABLE_DIAGNOSTIC_COMMANDS

    #if defined(ENABLE_SD) && defined(ENABLE_SERIALFLASH)
        if (!strcmp(cmd, "cache")) {
          LOCK_SD(true);
          File f = LSFS::Open(e);
          if (!f) {
            STDOUT.println("File not found.");
            return true;
          }
          int bytes = f.size();
          if (!SerialFlashChip::create(e, bytes)) {
            STDOUT.println("Not enough space on serial flash chip.");
            return true;
          }
          SerialFlashFile o = SerialFlashChip::open(e);
          while (bytes) {
            char tmp[256];
            int b = f.read(tmp, min(bytes, (int)NELEM(tmp)));
            o.write(tmp, b);
            bytes -= b;
          }
          LOCK_SD(false);
          STDOUT.println("Cached!");
          return true;
        }
    #endif
    
    #ifdef ENABLE_SERIALFLASH
        if (!strcmp(cmd, "ls")) {
          char tmp[128];
          SerialFlashChip::opendir();
          uint32_t size;
          while (SerialFlashChip::readdir(tmp, sizeof(tmp), size)) {
            STDOUT.print(tmp);
            STDOUT.print(" ");
            STDOUT.println(size);
          }
          STDOUT.println("Done listing files.");
          return true;
        }
        if (!strcmp(cmd, "rm")) {
          if (SerialFlashChip::remove(e)) {
            STDOUT.println("Removed.\n");
          } else {
            STDOUT.println("No such file.\n");
          }
          return true;
        }
        if (!strcmp(cmd, "format")) {
          STDOUT.print("Erasing ... ");
          SerialFlashChip::eraseAll();
          while (!SerialFlashChip::ready());
          STDOUT.println("Done");
          return true;
        }
    #endif // ENABLE_SERIALFLASH

    #ifdef ENABLE_SD
      #ifndef DISABLE_DIAGNOSTIC_COMMANDS
          if (!strcmp(cmd, "cat") && e) {
            LOCK_SD(true);
            File f = LSFS::Open(e);
            while (f.available()) {
              STDOUT.write(f.read());
            }
            f.close();
            LOCK_SD(false);
            return true;
          }
      #endif    // DISABLE_DIAGNOSTIC_COMMANDS

      #ifdef ENABLE_DEVELOPER_COMMANDS
          if (!strcmp(cmd, "readalot")) {
            uint8_t tmp[10];
            LOCK_SD(true);
            File f = LSFS::Open(e);
            for (int i = 0; i < 10000; i++) {
              f.seek(0);
              f.read(tmp, 10);
              f.seek(1000);
              f.read(tmp, 10);
            }
            f.close();
            LOCK_SD(false);
            STDOUT.println("Done");
            return true;
          }
      #endif // ENABLE_DEVELOPER_COMMANDS

      #ifndef DISABLE_DIAGNOSTIC_COMMANDS
          if (!strcmp(cmd, "sdtest")) {
            SDTestHelper sdtester;
            if (e && !strcmp(e, "all")) {
        sdtester.TestDir("");
            } else {
        sdtester.TestFont();
            }
            return true;
          }
      #endif

    #endif // ENABLE_SD

    #ifdef ENABLE_DEVELOPER_COMMANDS
        if (!strcmp(cmd, "high") && e) {
          pinMode(atoi(e), OUTPUT);
          digitalWrite(atoi(e), HIGH);
          STDOUT.println("Ok.");
          return true;
        }
    #endif // ENABLE_DEVELOPER_COMMANDS
    #ifdef ENABLE_DEVELOPER_COMMANDS
        if (!strcmp(cmd, "low") && e) {
          pinMode(atoi(e), OUTPUT);
          digitalWrite(atoi(e), LOW);
          STDOUT.println("Ok.");
          return true;
        }
    #endif // ENABLE_DEVELOPER_COMMANDS

    #if VERSION_MAJOR >= 4
        if (!strcmp(cmd, "booster")) {
          if (!strcmp(e, "on")) {
            digitalWrite(boosterPin, HIGH);
            STDOUT.println("Booster on.");
            return true;
          }
          if (!strcmp(e, "off")) {
            digitalWrite(boosterPin, LOW);
            STDOUT.println("Booster off.");
            return true;
          }
        }
    #endif

    #ifdef ENABLE_DEVELOPER_COMMANDS
        if (!strcmp(cmd, "sleep") && e) {
          delay(atoi(e));
          return true;
        }
    #endif

    #ifdef ENABLE_DEVELOPER_COMMANDS
        if (!strcmp(cmd, "twiddle")) {
          int pin = strtol(e, NULL, 0);
          STDOUT.print("twiddling ");
          STDOUT.println(pin);
          pinMode(pin, OUTPUT);
          for (int i = 0; i < 1000; i++) {
            digitalWrite(pin, HIGH);
            delay(10);
            digitalWrite(pin, LOW);
            delay(10);
          }
          STDOUT.println("done");
          return true;
        }
    #endif 

    #ifdef ENABLE_DEVELOPER_COMMANDS
        if (!strcmp(cmd, "twiddle2")) {
          int pin = strtol(e, NULL, 0);
          STDOUT.print("twiddling ");
          STDOUT.println(pin);
          pinMode(pin, OUTPUT);
          for (int i = 0; i < 1000; i++) {
            for (int i = 0; i < 500; i++) {
              digitalWrite(pin, HIGH);
              delayMicroseconds(1);
              digitalWrite(pin, LOW);
              delayMicroseconds(1);
            }
            delay(10);
          }
          STDOUT.println("done");
          return true;
        }
    #endif 

    #ifndef DISABLE_DIAGNOSTIC_COMMANDS
        if (!strcmp(cmd, "malloc")) {
            STDOUT.print("alloced: ");
            STDOUT.println(mallinfo().uordblks);
            STDOUT.print("Free: ");
            STDOUT.println(mallinfo().fordblks);
            return true;
        }
    #endif

    if (!strcmp(cmd, "make_default_console")) {
      default_output = stdout_output;
      return true;
    }
    #if 0
        // Not finished yet
        if (!strcmp(cmd, "selftest")) {
          struct PinDefs { int8_t pin; PinType type; };
          static PinDefs pin_defs[]  = {
            { bladePowerPin1, PinTypePulldown },
            { bladePowerPin2, PinTypePulldown },
            { bladePowerPin3, PinTypePulldown },
            { bladePowerPin4, PinTypePulldown },
            { bladePowerPin5, PinTypePulldown },
            { bladePowerPin6, PinTypePulldown },
            { bladePin,       PinTypeOther },
            { blade2Pin,      PinTypeFloating },
            { blade3Pin,      PinTypeFloating },
            { blade4Pin,      PinTypeFloating },
            { blade5Pin,      PinTypeFloating },
            { amplifierPin,   PinTypeFloating },
            { boosterPin,     PinTypeFloating },
            { powerButtonPin, PinTypeFloating },
            { auxPin,         PinTypeFloating },
            { aux2Pin,        PinTypeFloating },
            { rxPin,          PinTypeOther },
            { txPin,          PinTypeFloating },
          };
          for (size_t test_index = 0; test_index < NELEM(pin_defs); test_index++) {
            int pin = pin_defs[test_index].pin;
            for (size_t i = 0; i < NELEM(pin_defs); i++)
              pinMode(pin_defs[i].pin, INPUT);

            // test
            for (size_t i = 0; i < NELEM(pin_defs); i++) {
              pinMode(pin_defs[i].pin, OUTPUT);
              digitalWrite(pin_defs[i].pin, HIGH);
              // test
              digitalWrite(pin_defs[i].pin, LOW);
              // test
              pinMode(pin_defs[i].pin, INPUT);
            }
          }
        }
    #endif

    #ifndef DISABLE_DIAGNOSTIC_COMMANDS
        if (!strcmp(cmd, "top")) {
      #ifdef TEENSYDUINO
          if (!(ARM_DWT_CTRL & ARM_DWT_CTRL_CYCCNTENA)) {
            ARM_DEMCR |= ARM_DEMCR_TRCENA;
            ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
            STDOUT.println("Cycle counting enabled, top will work next time.");
            return true;
          }
      #else
          if (!(DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk)) {
            CoreDebug->DEMCR |= 1<<24; // DEMCR_TRCENA_Msk;
            DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
            STDOUT.println("Cycle counting enabled, top will work next time.");
            return true;
          }
      #endif

          // TODO: list cpu usage for various objects.
          float total_cycles =
            (float)(audio_dma_interrupt_cycles +
              pixel_dma_interrupt_cycles +
        motion_interrupt_cycles +
                    wav_interrupt_cycles +
        Looper::CountCycles() +
        CountProfileCycles());
          STDOUT.print("Audio DMA: ");
          STDOUT.print(audio_dma_interrupt_cycles * 100.0f / total_cycles);
          STDOUT.println("%");
          STDOUT.print("Wav reading: ");
          STDOUT.print(wav_interrupt_cycles * 100.0f / total_cycles);
          STDOUT.println("%");
          STDOUT.print("Pixel DMA: ");
          STDOUT.print(pixel_dma_interrupt_cycles * 100.0f / total_cycles);
          STDOUT.println("%");
          STDOUT.print("LOOP: ");
          STDOUT.print(loop_cycles * 100.0f / total_cycles);
          STDOUT.println("%");
          STDOUT.print("Motion: ");
          STDOUT.print(motion_interrupt_cycles * 100.0f / total_cycles);
          STDOUT.println("%");
          STDOUT.print("Global loops / second: ");
          global_loop_counter.Print();
          STDOUT.println("");
          STDOUT.print("High frequency loops / second: ");
          hf_loop_counter.Print();
          STDOUT.println("");
          SaberBase::DoTop(total_cycles);
          Looper::LoopTop(total_cycles);
          DumpProfileLocations(total_cycles);
          noInterrupts();
          audio_dma_interrupt_cycles = 0;
          pixel_dma_interrupt_cycles = 0;
          motion_interrupt_cycles = 0;
          wav_interrupt_cycles = 0;
          interrupts();
          return true;
        }
    #endif

    if (!strcmp(cmd, "version")) {
      STDOUT.println(version);
      STDOUT.print("Installed: ");
      STDOUT.println(install_time);
      return true;
    }

    #ifndef TEENSYDUINO

      if (!strcmp(cmd, "shutdown")) {
        STDOUT.println("Sleeping 10 seconds.\n");
        STM32.stop(100000);
        return true;
      }

      if (!strcmp(cmd, "RebootDFU")) {
        stm32l4_system_dfu();
        return true;
      }

      #ifdef ENABLE_DEVELOPER_COMMANDS
          if (!strcmp(cmd, "stm32info")) {
            STDOUT.print("VBAT: ");
            STDOUT.println(STM32.getVBAT());
            STDOUT.print("VREF: ");
            STDOUT.println(STM32.getVREF());
            STDOUT.print("TEMP: ");
            STDOUT.println(STM32.getTemperature());
            return true;
          }

          if (!strcmp(cmd, "CLK")) {
            if (e) {
              uint32_t c = atoi(e) * 1000000;
              stm32l4_system_sysclk_configure(c, c/2, c/2);
            }
            STDOUT.print("Clocks: hse=");
            STDOUT.print(stm32l4_system_hseclk());
            STDOUT.print(" lse=");
            STDOUT.print(stm32l4_system_lseclk());
            STDOUT.print(" sys=");
            STDOUT.print(stm32l4_system_sysclk());
            STDOUT.print(" f=");
            STDOUT.print(stm32l4_system_fclk());
            STDOUT.print(" h=");
            STDOUT.print(stm32l4_system_hclk());
            STDOUT.print(" p1=");
            STDOUT.print(stm32l4_system_pclk1());
            STDOUT.print(" p2=");
            STDOUT.print(stm32l4_system_pclk2());
            STDOUT.print(" sai=");
            STDOUT.println(stm32l4_system_saiclk());
            return true;
          }

        #ifdef HAVE_STM32L4_DMA_GET    
            if (!strcmp(cmd, "dmamap")) {
              for (int channel = 0; channel < 16; channel++) {
          stm32l4_dma_t *dma = stm32l4_dma_get(channel);
          if (dma) {
            STDOUT.print(" DMA");
            STDOUT.print( 1 +(channel / 8) );
            STDOUT.print("_CH");
            STDOUT.print( channel % 8 );
            STDOUT.print(" = ");
            STDOUT.println(dma->channel >> 4, HEX);
          }
              }
              return true;
            }
        #endif // HAVE_STM32L4_DMA_GET     

      #endif // ENABLE_DEVELOPER_COMMANDS

    #endif // TEENSYDUINO


#else // OSx  

  #ifdef ENABLE_DIAGNOSE_COMMANDS
    if (!strcmp(cmd, "cod") && e) {
        int8_t res;
        bool result;
        uint32_t readCRC, calcCRC;
        xCodReader codReaderObj;  
        result = codReaderObj.Open(e);
        if(result) 
        {
          calcCRC = codReaderObj.codInterpreter->GetFileCrC(&readCRC);
          STDOUT.print("CRC READ "); STDOUT.print(readCRC); STDOUT.print(" CRC CALC "); STDOUT.println(calcCRC);
          for(uint8_t i=1; i <= codReaderObj.headerNrEntries; i++ )
          {
              res = codReaderObj.GetEntry(i);
              if(res > 0)
              {   
                  if(res == COD_ENTYPE_TABLE) 
                  {   STDOUT.print("   "); STDOUT.print(codReaderObj.codProperties.table.ID); STDOUT.print(": table ");
                      STDOUT.print(codReaderObj.codProperties.table.Rows); STDOUT.print(" x "); STDOUT.print(codReaderObj.codProperties.table.Columns); 
                      STDOUT.print(" for handler "); STDOUT.println(codReaderObj.codProperties.table.Handler);
                      // STDOUT.print("==Entry TYPE=="); STDOUT.print(res); STDOUT.print(" "); STDOUT.println((char)res);
                      // STDOUT.print("Table ID = "); STDOUT.println(codReaderObj.codProperties.table.ID);
                      // STDOUT.print("Table SizeR  = "); STDOUT.println(codReaderObj.codProperties.table.Rows);
                      // STDOUT.print("Table SizeC = "); STDOUT.println(codReaderObj.codProperties.table.Columns); 
                      // STDOUT.print("Table dataType = "); STDOUT.println(codReaderObj.codProperties.table.DataType);
                      // STDOUT.print("Table Handler = "); STDOUT.println(codReaderObj.codProperties.table.Handler);

                  } else if(res == COD_ENTYPE_STRUCT) {
                      STDOUT.print("   "); STDOUT.print(codReaderObj.codProperties.structure.ID); STDOUT.print(": struct of ");
                      STDOUT.print(codReaderObj.codProperties.structure.Size); STDOUT.print(" bytes for handler  ");
                      STDOUT.println(codReaderObj.codProperties.structure.Handler);

                      // STDOUT.print("==Entry TYPE== "); STDOUT.print(res); STDOUT.print(" "); STDOUT.println((char)res);
                      // STDOUT.print("Struct ID = "); STDOUT.println(codReaderObj.codProperties.structure.ID);
                      // STDOUT.print("Struct Size = "); STDOUT.println(codReaderObj.codProperties.structure.Size);
                      // STDOUT.print("Struct Handler = "); STDOUT.println(codReaderObj.codProperties.structure.Handler);

                  } else {
                      STDOUT.print("==Entry TYPE=="); STDOUT.println(res);
                      STDOUT.print("Entry on nrCRT "); STDOUT.println(i);
                  }

              } 
              else if(res == 0 )
              {
                  STDOUT.print("Inconsistent number of entries, should be "); STDOUT.println(i);
              } else {
                  STDOUT.print("Error reading entry number "); STDOUT.println(i);
              }

          }
        }
        codReaderObj.Close();
        STDOUT.print("End of "); STDOUT.print(e); STDOUT.println(" --- ");

        return true;
      }
  #endif // ENABLE_DIAGNOSE_COMMANDS

  #if defined(X_POWER_MAN) && defined(ULTRA_PROFFIE)  && defined(ENABLE_DEVELOPER_MODE)
      // if(!strcmp(cmd, "goToSleep")) {
      //   xPowerManager::cpu_EnterSTOP0Mode(PWR_STOPENTRY_WFE);   // PWR_STOPENTRY_WFE PWR_STOPENTRY_WFI
      //   return true;
      // }

      if(!strcmp(cmd, "printRequestedTime")) {
        xPowerManager::PrintRequestedTime();   // PWR_STOPENTRY_WFE PWR_STOPENTRY_WFI
        return true;
      }
  #endif // X_POWER_MAN

  #if defined(X_PROBECPU) && defined(ENABLE_DEVELOPER_MODE)
      if (!strcmp(cmd, "malloc")) {
          struct mallinfo mi = mallinfo();
          STDOUT.print(" * Total non-mmapped bytes (arena): "); STDOUT.println(mi.arena);
          STDOUT.print(" * Number of free chunks (ordblks): "); STDOUT.println(mi.ordblks);
          STDOUT.print(" * Number of free fastbin blocks (smblks): "); STDOUT.println(mi.smblks);
          STDOUT.print(" * Number of mapped regions (hblks): "); STDOUT.println(mi.hblks);
          STDOUT.print(" * Bytes in mapped regions (hblkhd): "); STDOUT.println(mi.hblkhd);
          STDOUT.print(" * Max. total allocated space (usmblks): "); STDOUT.println(mi.usmblks);
          STDOUT.print(" * Free bytes held in fastbins (fsmblks): "); STDOUT.println(mi.fsmblks);
          STDOUT.print(" * Total allocated space (uordblks): "); STDOUT.println(mi.uordblks);
          STDOUT.print(" * Total free space (fordblks): "); STDOUT.println(mi.fordblks);
          STDOUT.print(" * Topmost releasable block (keepcost): "); STDOUT.println(mi.keepcost);
        return true;
      }
    
      if (!strcmp(cmd, "ram")) {
        char *heapend = (char*)sbrk(0);
        char * stack_ptr = (char*)__get_MSP();
        float percent, tmpPercent;

        STDOUT.print(" * Static RAM (data & bss): "); STDOUT.print((uint32_t)(&__HeapLimit) - (uint32_t)(&__data_start__) ); STDOUT.print(" bytes = "); 
        percent = 100.0f *  ( (uint32_t)(&__HeapLimit) - (uint32_t)(&__data_start__) ) / ( (uint32_t)(&__StackTop) - (uint32_t)(&__data_start__) );
        STDOUT.print(percent); STDOUT.println("%.");
        STDOUT.print(" * Dynamic RAM (heap): "); STDOUT.print((uint32_t)(heapend) - (uint32_t)(&__HeapLimit) ); STDOUT.print(" bytes = "); 
        tmpPercent = 100.0f *  ( (uint32_t)(heapend) - (uint32_t)(&__HeapLimit) ) / ( (uint32_t)(&__StackTop) - (uint32_t)(&__data_start__) );
        STDOUT.print(tmpPercent); STDOUT.println("%.");
        percent += tmpPercent;
        STDOUT.print(" * Temporary RAM (stack): "); STDOUT.print((uint32_t)(&__StackTop) - (uint32_t)(stack_ptr) ); STDOUT.print(" bytes = "); 
        tmpPercent = 100.0f *  ( (uint32_t)(&__StackTop) - (uint32_t)(stack_ptr) ) / ( (uint32_t)(&__StackTop) - (uint32_t)(&__data_start__) );
        STDOUT.print(tmpPercent); STDOUT.print("%. - Minimum is set to "); STDOUT.print(((uint32_t)(&__StackTop) - (uint32_t)(&__StackLimit) )); STDOUT.println(" bytes.");
        percent += tmpPercent;
        STDOUT.print("----- Total SRAM1 usage: "); STDOUT.print(percent); STDOUT.println("%.");
        return true;
      }

      if (!strcmp(cmd, "top")) {
        // 1. Enable cycle counter if it's not
        if (!(DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk)) {
          CoreDebug->DEMCR |= 1<<24; // DEMCR_TRCENA_Msk;
          DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
          STDOUT.println("Cycle counting enabled, top will work next time.");
          return true;
        }
        // 2. Report call frequencies
        STDOUT.println("");
        STDOUT.println("Call frequencies [Hz]:"); 
        audio_dma_interrupt_cycles.Print(DoWhatToProbe::print_frequency); STDOUT.println(" Audio DMA ISR");  // report frequency for ISRs
        wav_interrupt_cycles.Print(DoWhatToProbe::print_frequency); STDOUT.println(" WAV Reader ISR"); 
        pixel_dma_interrupt_cycles.Print(DoWhatToProbe::print_frequency); STDOUT.println(" Pixel ISR"); 
        motion_interrupt_cycles.Print(DoWhatToProbe::print_frequency); STDOUT.println(" Motion ISR"); 
        Looper::DoProbe(DoWhatToProbe::print_frequency);  // Call .Print() on all looper's probes                                                                                // report frequency for all loopers
        // 3. Report runtimes
        STDOUT.println("Execution times [us]:"); 
        audio_dma_interrupt_cycles.Print(DoWhatToProbe::print_duration); STDOUT.println(" Audio DMA ISR");  // report frequency for ISRs
        wav_interrupt_cycles.Print(DoWhatToProbe::print_duration); STDOUT.println(" WAV Reader ISR"); 
        pixel_dma_interrupt_cycles.Print(DoWhatToProbe::print_duration); STDOUT.println(" Pixel ISR"); 
        motion_interrupt_cycles.Print(DoWhatToProbe::print_duration); STDOUT.println(" Motion ISR"); 
        Looper::DoProbe(DoWhatToProbe::print_duration); 
        // 4. Report CPU usage
        STDOUT.println("CPU usage [%]:"); 
        audio_dma_interrupt_cycles.Print(DoWhatToProbe::print_cpu_usage); STDOUT.println(" Audio DMA ISR");  // report frequency for ISRs
        wav_interrupt_cycles.Print(DoWhatToProbe::print_cpu_usage); STDOUT.println(" WAV Reader ISR"); 
        pixel_dma_interrupt_cycles.Print(DoWhatToProbe::print_cpu_usage); STDOUT.println(" Pixel ISR"); 
        motion_interrupt_cycles.Print(DoWhatToProbe::print_cpu_usage); STDOUT.println(" Motion ISR"); 
        Looper::DoProbe(DoWhatToProbe::print_cpu_usage); 
        // 5. Report loop counters
        SaberBase::DoTop(0);  // original DoTop needed total cycles to make calculations, we send 0 to keep backward compatibility
        // 6. Reset probes
        noInterrupts();
        Looper::DoProbe(DoWhatToProbe::reset_probe); 
        audio_dma_interrupt_cycles.Reset();
        wav_interrupt_cycles.Reset();
        pixel_dma_interrupt_cycles.Reset();
        motion_interrupt_cycles.Reset();
        interrupts();
        STDOUT.println("-> CPU probes reset.");
        STDOUT.println("");
        return true;
      }

    if (!strcmp(cmd, "clk")) {
      if (e) {
        uint32_t c = atoi(e) * 1000000;
        stm32l4_system_sysclk_configure(c, c/2, c/2);
      }
      STDOUT.print("Clocks: hse=");
      STDOUT.print(stm32l4_system_hseclk());
      STDOUT.print(" lse=");
      STDOUT.print(stm32l4_system_lseclk());
      STDOUT.print(" sys=");
      STDOUT.print(stm32l4_system_sysclk());
      STDOUT.print(" f=");
      STDOUT.print(stm32l4_system_fclk());
      STDOUT.print(" h=");
      STDOUT.print(stm32l4_system_hclk());
      STDOUT.print(" p1=");
      STDOUT.print(stm32l4_system_pclk1());
      STDOUT.print(" p2=");
      STDOUT.print(stm32l4_system_pclk2());
      return true;
    }


    if (!strcmp(cmd, "dmamap")) {
      for (int channel = 0; channel < 16; channel++) {
        stm32l4_dma_t *dma = stm32l4_dma_get(channel);
        if (dma) {
          STDOUT.print(" DMA");
          STDOUT.print( 1 +(channel / 8) );
          STDOUT.print("_CH");
          STDOUT.print( channel % 8 );
          STDOUT.print(" = ");
          STDOUT.println(dma->channel >> 4, HEX);
        }
      }
      return true;
    }



  #endif // X_PROBECPU

  if (!strcmp(cmd, "alive")) {
    STDOUT.println("alive-START");
    if (prop.IsOn()) STDOUT.println("propstate: on");
    else STDOUT.println("propstate: off");
    STDOUT.print("battery: ");  battery_monitor.Print(); STDOUT.println("");
    STDOUT.println("alive-END");
    return true;
  }

  #ifdef X_BROADCAST // Enable binary streaming
    if (!strcmp(cmd, "broadcast")) {
        STDOUT.StartBroadcast();    // reset board to turn off, unless it gets stopped in code
    return true;
    }
  #endif // X_BROADCAST

#endif // OSx



#ifdef ENABLE_SD

  #ifdef ENABLE_DIAGNOSE_COMMANDS
      if (!strcmp(cmd, "dir")) {
        LOCK_SD(true);
        if (!e || LSFS::Exists(e)) {
          for (LSFS::Iterator dir(e ? e : ""); dir; ++dir) {
            STDOUT.print(dir.name());
            STDOUT.print(" ");
            STDOUT.println(dir.size());
          }
          STDOUT.println("Done listing files.");
        } else {
          STDOUT.println("No such directory.");
        }
        LOCK_SD(false);
        return true;
      }
  #endif 

  #ifdef ENABLE_DEVELOPER_COMMANDS
    if (!strcmp(cmd, "del") && e) {
      LOCK_SD(true);
      LSFS::Remove(e);
      LOCK_SD(false);
      return true;
    }
  #endif 

#endif  // ENABLE_SD


#ifdef ENABLE_AUDIO

  #ifdef ENABLE_DEVELOPER_COMMANDS
      if (!strcmp(cmd, "dumpwav")) {
        int16_t tmp[32];
        wav_players[0].Stop();
        wav_players[0].read(tmp, NELEM(tmp));
        wav_players[0].Play(e);
        for (int j = 0; j < 64; j++) {
          int k = wav_players[0].read(tmp, NELEM(tmp));
          for (int i = 0; i < k; i++) {
            STDOUT.print(tmp[i]);
            STDOUT.print(" ");
          }
          STDOUT.println("");
        }
        wav_players[0].Stop();
        return true;
      }
  #endif // ENABLE_DEVELOPER_COMMANDS

  #ifdef ENABLE_DEVELOPER_COMMANDS
      if (!strcmp(cmd, "dumpwavplayer")) {
        for (size_t i = 0; i < NELEM(wav_players); i++) {
          if (e && atoi(e) != i) continue;
          wav_players[i].dump();
        }
        return true;
      }



  #endif // ENABLE_DEVELOPER_COMMANDS

#endif // ENABLE_AUDIO


#ifdef ENABLE_DIAGNOSE_COMMANDS
  
  if (!strcmp(cmd, "effects")) {
      Effect::ShowAll();
      return true;
  }

#endif // ENABLE_DIAGNOSE_COMMANDS





#ifdef ENABLE_DEVELOPER_COMMANDS

    if (!strcmp(cmd, "dumpfusor")) {
      fusor.dump();
      return true;
    }

    #if defined(ENABLE_MOTION) || defined(ENABLE_SSD1306) || defined(INCLUDE_SSD1306)
        if (!strcmp(cmd, "i2cstate")) {
          extern void DumpI2CState();
          DumpI2CState();
          SaberBase::DumpMotionRequest();
          return true;
        }
    #endif

    if (!strcmp(cmd, "portstates")) {
      GPIO_TypeDef *GPIO;
      for (int i = 0; i < 4; i++) {
        switch (i) {
          case 0:
            GPIO = (GPIO_TypeDef *)GPIOA_BASE;
            STDOUT.print("PORTA: ");
            break;
          case 1:
            GPIO = (GPIO_TypeDef *)GPIOB_BASE;
            STDOUT.print("PORTB: ");
            break;
          case 2:
            GPIO = (GPIO_TypeDef *)GPIOC_BASE;
            STDOUT.print("PORTC: ");
            break;
          case 3:
            GPIO = (GPIO_TypeDef *)GPIOH_BASE;
            STDOUT.print("PORTH: ");
            break;
        }
        for (int j = 15; j >= 0; j--) {
          uint32_t now = (GPIO->MODER >> (j * 2)) & 3;
          uint32_t saved = (startup_MODER[i] >> (j * 2)) & 3;
          STDOUT.print((now == saved ? "ioga" : "IOGA")[now]);
          if (!(j & 3)) STDOUT.print(" ");
        }
        STDOUT.print("  ");
        for (int j = 15; j >= 0; j--) {
          uint32_t now = (GPIO->PUPDR >> (j * 2)) & 3;
          STDOUT.print("-ud?"[now]);
          if (!(j & 3)) STDOUT.print(" ");
        }
        STDOUT.print("  ");
        for (int j = 15; j >= 0; j--) {
          uint32_t now = ((GPIO->IDR >> j) & 1) | (((GPIO->ODR >> j) & 1) << 1);
          STDOUT.print("lhLH"[now]);
          if (!(j & 3)) STDOUT.print(" ");
        }
        STDOUT.print("  ");
        for (int j = 15; j >= 0; j--) {
	  int afr = 0xf & (GPIO->AFR[j >> 3] >> ((j & 7) * 4));
          STDOUT.print("0123456789ABCDEF"[afr]);
          if (!(j & 3)) STDOUT.print(" ");
        }
        STDOUT.println("");
      }
      return true;
    }

    if (!strcmp(cmd, "whatispowered")) {
      STDOUT.print("ON: ");
      #define PRINTIFON(REG, BIT) do {                                        \
              if (RCC->REG & RCC_##REG##_##BIT##EN) {                         \
                STDOUT.print(" " #BIT);                                       \
                if (!(startup_##REG & RCC_##REG##_##BIT##EN)) STDOUT.print("+"); \
              }                                                               \
            } while(0)

            PRINTIFON(AHB1ENR,FLASH);
            PRINTIFON(AHB1ENR,DMA1);
            PRINTIFON(AHB1ENR,DMA2);
            PRINTIFON(AHB2ENR,GPIOA);
            PRINTIFON(AHB2ENR,GPIOB);
      #ifdef GPIOC_BASE
            PRINTIFON(AHB2ENR,GPIOC);
      #endif      
      #ifdef GPIOD_BASE
            PRINTIFON(AHB2ENR,GPIOD);
      #endif      
      #ifdef GPIOE_BASE
            PRINTIFON(AHB2ENR,GPIOE);
      #endif
      #if defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(AHB2ENR,GPIOF);
            PRINTIFON(AHB2ENR,GPIOG);
      #endif
            PRINTIFON(AHB2ENR,GPIOH);
      #if defined(STM32L496xx)
            PRINTIFON(AHB2ENR,GPIOI);
      #endif
            PRINTIFON(AHB2ENR,ADC);
            PRINTIFON(APB1ENR1,DAC1);
      #if defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(AHB2ENR,OTGFS);
      #elif !defined(STM32L431xx)
            PRINTIFON(APB1ENR1,USBFS);
      #endif
            PRINTIFON(APB2ENR,USART1);
            PRINTIFON(APB1ENR1,USART2);
      #if defined(STM32L433xx) || defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(APB1ENR1,USART3);
      #endif
      #if defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(APB1ENR1,UART4);
            PRINTIFON(APB1ENR1,UART5);
      #endif
            PRINTIFON(APB1ENR2,LPUART1);
            PRINTIFON(APB1ENR1,I2C1);
      #if defined(STM32L433xx) || defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(APB1ENR1,I2C2);
      #endif
            PRINTIFON(APB1ENR1,I2C3);
      #if defined(STM32L496xx)
            PRINTIFON(APB1ENR2,I2C4);
      #endif
            PRINTIFON(APB2ENR,SPI1);
      #if defined(STM32L433xx) || defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(APB1ENR1,SPI2);
      #endif
            PRINTIFON(APB1ENR1,SPI3);
            PRINTIFON(APB1ENR1,CAN1);
      #if defined(STM32L496xx)
            PRINTIFON(APB1ENR1,CAN2);
      #endif
            PRINTIFON(AHB3ENR,QSPI);
      #if defined(STM32L433xx) || defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(APB2ENR,SDMMC1);
      #endif
            PRINTIFON(APB2ENR,SAI1);
      #if defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(APB2ENR,SAI2);
            PRINTIFON(APB2ENR,DFSDM1);
      #endif
            PRINTIFON(APB2ENR,TIM1);
            PRINTIFON(APB1ENR1,TIM2);
      #ifdef TIM3_BASE
            PRINTIFON(APB1ENR1,TIM3);
      #endif
      #ifdef TIM4_BASE
            PRINTIFON(APB1ENR1,TIM4);
      #endif
      #ifdef TIM5_BASE
            PRINTIFON(APB1ENR1,TIM5);
      #endif
            PRINTIFON(APB1ENR1,TIM6);
      #ifdef TIM7_BASE      
            PRINTIFON(APB1ENR1,TIM7);
      #endif
      #ifdef TIM8_BASE      
            PRINTIFON(APB2ENR,TIM8);
      #endif
            PRINTIFON(APB2ENR,TIM15);
            PRINTIFON(APB2ENR,TIM16);
      #if defined(STM32L476xx) || defined(STM32L496xx)
            PRINTIFON(APB2ENR,TIM17);
      #endif
            PRINTIFON(APB1ENR1,LPTIM1);
            PRINTIFON(APB1ENR2,LPTIM2);

            // Not sure what CPUs implement these
            PRINTIFON(AHB1ENR, CRC);
            PRINTIFON(AHB1ENR, TSC);
            PRINTIFON(AHB2ENR, RNG);
      #ifdef LCD_BASE
            PRINTIFON(APB1ENR1, LCD);
      #endif
            PRINTIFON(APB1ENR1, RTCAPB);
            PRINTIFON(APB1ENR1, WWDG);
            PRINTIFON(APB1ENR1, CRS);
            PRINTIFON(APB1ENR1, CAN1);
            PRINTIFON(APB1ENR1, PWR);
            PRINTIFON(APB1ENR1, OPAMP);
      #ifdef SWPMI1_BASE
            PRINTIFON(APB1ENR2, SWPMI1);
      #endif
            PRINTIFON(APB2ENR, SYSCFG);
            PRINTIFON(APB2ENR, FW);
      #if !defined(STM32L431xx)
            STDOUT.println("");
            STDOUT.print("VBUS: ");
            STDOUT.println(stm32l4_gpio_pin_read(GPIO_PIN_PB2));
            STDOUT.print("USBD connected: ");
            STDOUT.println(USBD_Connected());
      #endif
            return true;
    }

#endif //  ENABLE_DEVELOPER_COMMANDS

    if (!strcmp(cmd, "reset")) {
    #ifdef TEENSYDUINO
      SCB_AIRCR = 0x05FA0004;
    #else
      STM32.reset();
    #endif 
      STDOUT.println("Reset failed.");
      return true;
    }

    return false;
  }

  void Help() override {
#if defined(COMMANDS_HELP) || !defined(OSx)
    STDOUT.println(" version - show software version");
    STDOUT.println(" reset - restart software");
  #ifndef DISABLE_DIAGNOSTIC_COMMANDS    
    STDOUT.println(" effects - list current effects");
  #endif    
  #ifdef ENABLE_SERIALFLASH
    STDOUT.println("Serial Flash memory management:");
    STDOUT.println("   ls, rm <file>, format, play <file>, effects");
    STDOUT.println("To upload files: tar cf - files | uuencode x >/dev/ttyACM0");
  #endif
  #if defined(ENABLE_SD) && !defined(DISABLE_DIAGNOSTIC_COMMANDS)
    STDOUT.println(" dir [directory] - list files on SD card.");
    STDOUT.println(" sdtest - benchmark SD card");
  #endif
  #ifdef OSx
    #ifdef X_PROBECPU
      STDOUT.println(" top - report CPU usage and execution times");
    #endif
    #ifdef X_BROADCAST
      STDOUT.println(" broadcast on/off - enable/disable binary broadcasting");
    #endif
    #ifndef DISABLE_DIAGNOSTIC_COMMANDS
      STDOUT.println(" cod <filename> - list all entries in a .COD file");
    #endif
  #endif // OSx
#else // COMMANDS_HELP
  STDOUT.println("For help on ASCII commands, visit http://git.ultraproffie/ASCII_Commands.md");
#endif // COMMANDS_HELP
  }
};

StaticWrapper<Commands> commands;

#include "common/serial.h"


#if defined(ENABLE_MOTION) || defined(ENABLE_SSD1306) || defined(INCLUDE_SSD1306)
#include "common/i2cdevice.h"
I2CBus i2cbus;
#endif

#ifdef ENABLE_SSD1306
#include "display/ssd1306.h"

StandardDisplayController<128, uint32_t> display_controller;
SSD1306Template<128, uint32_t> display(&display_controller);
#endif

#ifdef INCLUDE_SSD1306
#include "display/ssd1306.h"
#endif


#ifdef ENABLE_MOTION

#include "motion/motion_util.h"
#include "motion/mpu6050.h"
#include "motion/lsm6ds3h.h"
#include "motion/fxos8700.h"
#include "motion/fxas21002.h"

// Define this to record clashes to sd card as CSV files
// #define CLASH_RECORDER

#include "scripts/clash_recorder.h"

#ifdef GYRO_CLASS
// Can also be gyro+accel.
StaticWrapper<GYRO_CLASS> gyroscope;
#endif

#ifdef ACCEL_CLASS
StaticWrapper<ACCEL_CLASS> accelerometer;
#endif

#endif   // ENABLE_MOTION

#include "sound/amplifier.h"
#include "common/sd_card.h"
#include "common/booster.h"


#if defined(ULTRA_PROFFIE) && defined(OSx)
bool PublishContent(const char* filename)
{

  FileReader myfileReader;
  bool result;
  LOCK_SD(true);
  result = myfileReader.Create(filename);
  if(result)
  { 
    char buffer[10];
    myfileReader.Write("board_info-START\n");
    myfileReader.Write("HARDWARE:\n");
    #ifdef ULTRA_PROFFIE
    PROFFIE_HDID.printHWSN(&myfileReader);
    #endif
    myfileReader.Write("FIRMWARE:\n");
    myfileReader.Write("ProffieOS "); myfileReader.Write(version); myfileReader.Write("\n");
    myfileReader.Write("Compiled: "); myfileReader.Write(install_time); myfileReader.Write("\n");
    myfileReader.Write("Build for: "); myfileReader.Write(XSTR(HWVER)); myfileReader.Write("\n");

    sprintf(buffer, "%d", NUM_BLADES);
    myfileReader.Write("Prop: '"); myfileReader.Write(prop.name()); myfileReader.Write("'\n");
    myfileReader.Write("Supported blades: "); myfileReader.Write(buffer); myfileReader.Write("\n");
    myfileReader.Write("Diagnose: ");   
    #ifdef PF_STATUS_REPORT_ON
      myfileReader.Write("ON\n");
    #else
      myfileReader.Write("OFF\n");
    #endif
    myfileReader.Write("Developer mode: ");
    #ifdef ENABLE_DEVELOPER_MODE
      myfileReader.Write("ON\n");
    #else
      myfileReader.Write("OFF\n");
    #endif
    myfileReader.Write("board_info-END\n");
    myfileReader.Write("\n");

    prop.list_styles(&myfileReader); myfileReader.Write("\n");
    prop.list_fonts(&myfileReader);  myfileReader.Write("\n");
    prop.list_tracks(&myfileReader); myfileReader.Write("\n");
    prop.list_presets(&myfileReader); myfileReader.Write("\n");
    prop.list_profile(&myfileReader); myfileReader.Write("\n");
    LOCK_SD(true);
    if (userProfile.preset) sprintf(buffer, "%d", presets[userProfile.preset-1].variation);
    else sprintf(buffer, "%d", 0);
    myfileReader.Write("get_color-START\n");
    myfileReader.Write(buffer);  myfileReader.Write("\n");
    myfileReader.Write("get_color-END\n");
    myfileReader.Close();
    LOCK_SD(false);
    return true;
  }
  LOCK_SD(false);
  return false;
  
}
#include "common/fwupdate.h"

bool BootInSafeMode()
{
  pinMode(auxPin, INPUT_PULLUP);
  delay(10); // wait a bit before start to read
  // uint32_t timeStamp, lastDebounce;
  // bool state = false;
  // int reading, btnState = 1, lastBtnState =1; 
  // timeStamp = millis();
  // lastDebounce = timeStamp;
  // while((millis() - timeStamp) < 100) {  // wait 50 ms to detect 
  //   reading = digitalRead(auxPin);
  //   if(reading != lastBtnState) lastDebounce = millis();
  //   if(millis() - lastDebounce > 40) 
  //   {
  //     if(reading != btnState) 
  //       btnState = reading;
  //   }
  //   lastBtnState = reading;
  // }
  // // STDOUT.print("PinState: "); STDOUT.println(digitalRead(auxPin));
  // if(btnState == 0) {
  if (digitalRead(auxPin) == LOW) {
    STDOUT.println("BOOTING IN SAFE MODE - NO SOUND AND LIGHTS! ");
    beeper.Beep(0.5, 1000);
    beeper.Beep(0.5, 2000);
    beeper.Beep(0.5, 5000);
    return true;
  }
   pinMode(auxPin, INPUT);
  return false;
}
#endif

void setup() {
#if VERSION_MAJOR >= 4
#define SAVE_RCC(X) startup_##X = RCC->X
  SAVE_RCC(AHB1ENR);
  SAVE_RCC(AHB2ENR);
  SAVE_RCC(AHB3ENR);
  SAVE_RCC(APB1ENR1);
  SAVE_RCC(APB1ENR2);
  SAVE_RCC(APB2ENR);
#define SAVE_MODER(PORT, X) startup_MODER[X] = ((GPIO_TypeDef *)GPIO##PORT##_BASE)->MODER
  SAVE_MODER(A, 0);
  SAVE_MODER(B, 1);
  SAVE_MODER(C, 2);
  SAVE_MODER(H, 3);

  // TODO enable/disable as needed
  pinMode(boosterPin, OUTPUT);
  digitalWrite(boosterPin, HIGH);
#endif


#ifdef OSX_ENABLE_MTP
Serial.begin(SERIAL_ASCII_BAUD);
#else 
Serial.begin(9600);
#endif

//  Serial.begin(921600);  // 921600
//  Serial.begin(9600);

#if defined(OSx) && !defined(ULTRA_PROFFIE) && defined(ENABLE_DEVELOPER_MODE)
  // #ifdef X_WAIT_FOR_SERIAL
    { // wait until we can use serial (up to 5 seconds if USB is not connected)
      uint32_t started_ = millis();
      while ( !Serial && (millis()-started_<5000) );   
    }
    if (Serial) { Serial.println(""); Serial.println(""); Serial.println(""); Serial.println("- serial port alive -"); }
  // #endif
#endif // OSx

#ifdef OSx
  #if defined(ULTRA_PROFFIE) 
    #if HWL_CONCAT(MQUOATE, HW_PREFIX, MQUOATE) == 'L'
      CheckFwUpdate();  // todo
    #endif 
  #endif
  if (Serial) { 
    Serial.println(""); Serial.println("");
    STDOUT.print(" - Welcome to ProffieOS ");
    STDOUT.print(version);  STDOUT.println(" -");
    STDOUT.print("Prop: '"); STDOUT.print(prop.name()); STDOUT.print("' supports ");
    STDOUT.print(NUM_BLADES);
    STDOUT.print(" blades. Diagnose is ");
    #ifdef PF_STATUS_REPORT_ON
      STDOUT.print("ON");
    #else
      STDOUT.print("OFF");
    #endif
    STDOUT.print(". Developer mode is ");
    #ifdef ENABLE_DEVELOPER_MODE
      STDOUT.print("ON");
    #else
      STDOUT.print("OFF");
    #endif
    STDOUT.println(".");
    STDOUT.println("");
    }
#endif // OSx

#if VERSION_MAJOR >= 4
  // TODO: Figure out if we need this.
  // Serial.blockOnOverrun(false);
#endif

  // Wait for all voltages to settle.
  // Accumulate some entrypy while we wait.
  uint32_t now = millis();

  while (millis() - now < PROFFIEOS_STARTUP_DELAY) {
#ifndef NO_BATTERY_MONITOR  
    srand((rand() * 917823) ^ LSAnalogRead(batteryLevelPin));
#endif

#ifdef BLADE_DETECT_PIN
    // Figure out if blade is connected or not.
    // Note that if PROFFIEOS_STARTUP_DELAY is smaller than
    // the settle time for BladeDetect, this won't work properly.
    BladeDetect.Warmup();
#endif
  }

  // 1. Init memory
#ifdef ENABLE_SERIALFLASH
  SerialFlashChip::begin(serialFlashSelectPin);
#endif
#ifdef ENABLE_SD
  bool sd_card_found = LSFS::Begin();
  if (!sd_card_found) {
    if (sdCardSelectPin >= 0 && sdCardSelectPin < 255) {
      #if (defined(OSx) && defined(DIAGNOSE_STORAGE)) || !defined(OSx)
      STDOUT.println("No "STORAGE_RES" found.");
      #endif
      pinMode(sdCardSelectPin, OUTPUT);
      digitalWrite(sdCardSelectPin, 0);
      delayMicroseconds(2);
      pinMode(sdCardSelectPin, INPUT);
      delayMicroseconds(2);
      if (digitalRead(sdCardSelectPin) != HIGH) {
        #if (defined(OSx) && defined(DIAGNOSE_STORAGE)) || !defined(OSx)
        STDOUT.println("SD select not pulled high!");
        #endif
      }
    }
#if VERSION_MAJOR >= 4
    stm32l4_gpio_pin_configure(GPIO_PIN_PA5,   (GPIO_PUPD_PULLUP | GPIO_OSPEED_HIGH | GPIO_MODE_INPUT));
    delayMicroseconds(10);
    if (!stm32l4_gpio_pin_read(GPIO_PIN_PA5)) {
      STDOUT.println("SCK won't go high!");
    }
    stm32l4_gpio_pin_configure(GPIO_PIN_PA5,   (GPIO_PUPD_PULLDOWN | GPIO_OSPEED_HIGH | GPIO_MODE_INPUT));
    delayMicroseconds(10);
    if (stm32l4_gpio_pin_read(GPIO_PIN_PA5)) {
      STDOUT.println("SCK won't go low!");
    }
#endif // VERSION_MAJOR
  } else {
    #if (defined(OSx) && defined(DIAGNOSE_STORAGE)) || !defined(OSx)
    STDOUT.println(STORAGE_RES" found.");
    #endif
  }
#endif // ENABLE_SD

#if !defined(ULTRA_PROFFIE) && defined(PROFFIEBOARD_VERSION)
  ProffieBoard_InitCRC();   // Ugly patch, we need to get all board packages under the same JSON to get rid of this...
#endif

  // 2. Install configuration
  #if defined(OSx) && !defined(OLDINSTALL)
      #if defined(ULTRA_PROFFIE)
      bool skip = BootInSafeMode();
      #else 
      bool skip = 0;
      #endif

      if(!skip)	
      {
        #ifdef DIAGNOSE_BOOT
          xInstall(INSTALL_FILE);
          STDOUT.println("");
        #else
          STDOUT.print("Running xInstall ... ");
          if (xInstall(INSTALL_FILE)) STDOUT.println("Success.");
          else STDOUT.println("FAILED!");
        #endif
      }
  #endif // OSx

  #if !defined(OSx) || defined(OLDPROFILE)
      Looper::DoSetup();
      // Time to identify the blade.
      prop.FindBlade();
  #else // OSx

      // 3. User Profile
      if(!skip) {
        #ifdef DIAGNOSE_BOOT
            SetUserProfile(PROFILE_FILE);
        #else // DIAGNOSE_BOOT
          STDOUT.print("Running xProfile ... ");
          if (SetUserProfile(PROFILE_FILE)) STDOUT.println("Success.");
          else STDOUT.println("FAILED!");
        #endif // DIAGNOSE_BOOT

        // 4. Publish content
        #if defined(BOARDTYPE_LITE)
          #ifdef DIAGNOSE_BOOT    
            STDOUT.print ("Publishing content in "); STDOUT.print(OFFLINE_FILE); STDOUT.print(" ........................ ");
            if (PublishContent(OFFLINE_FILE)) STDOUT.println("Success.");
            else STDOUT.println("FAILED!");
          #else
            STDOUT.print("Publishing content ... ");
            if (PublishContent(OFFLINE_FILE)) STDOUT.println("Success.");
            else STDOUT.println("FAILED!");
          #endif
        #endif // BOARDTYPE_LITE

        STDOUT.println("");
        prop.ActivateBlades();
        prop.SetPreset(userProfile.preset, false);
      }     
      
      

      // 5. Setup
      Looper::DoSetup();    
  #endif // OSx

  // 5. Signal boot
  SaberBase::DoBoot();
#if defined(ENABLE_SD) && defined(ENABLE_AUDIO)
  if (!sd_card_found) {
    talkie.Say(talkie_sd_card_15, 15);
    talkie.Say(talkie_not_found_15, 15);
  }
#endif // ENABLE_AUDIO && ENABLE_SD
  
}

#ifdef MTP_RX_ENDPOINT

void mtp_yield() { Looper::DoLoop(); }
void mtp_lock_storage(bool lock) {
  AudioStreamWork::LockSD(lock);
}

#include "mtp/mtpd.h"
MTPD mtpd;

#ifdef ENABLE_SD
#include "mtp/mtp_storage_sd.h"
MTPStorage_SD sd_storage(&mtpd);
#endif

#ifdef ENABLE_SERIALFLASH
#include "mtp/mtp_storage_serialflash.h"
MTPStorage_SerialFlash serialflash_storage(&mtpd);
#endif

#endif  // MTP_RX_ENDPOINT

#include "common/clock_control.h"

void loop() {
#ifdef MTP_RX_ENDPOINT
  mtpd.loop();
#endif
  Looper::DoLoop();
}

#define CONFIG_BOTTOM
#include CONFIG_FILE
#undef CONFIG_BOTTOM
