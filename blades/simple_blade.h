#ifndef BLADES_SIMPLE_BLADE_H
#define BLADES_SIMPLE_BLADE_H

#include "abstract_blade.h"

#include "../styles/styles.h"


template<int PIN, class LED>
class PWMPin : public PWMPinInterface {
public:
  void Activate() override {
    static_assert(PIN >= 0, "PIN is negative?");
    LSanalogWriteSetup(PIN);
    LSanalogWrite(PIN, 0);  // make it black
  }
  void Deactivate() override {
    LSanalogWriteTeardown(PIN);
  }
  void set(const Color16& c) override {
    // STDOUT.print("[PWMPin.set()]: set pin "); STDOUT.print(PIN); STDOUT.print(" to color: "); 
    // STDOUT.print(c.r); STDOUT.print(", "); STDOUT.print(c.g); STDOUT.print(", "); STDOUT.println(c.b);
    LSanalogWrite(PIN, led_.PWM(c));
  }
  void set_overdrive(const Color16& c) override {
    LSanalogWrite(PIN, led_.PWM_overdrive(c));
  }

  Color8 getColor8() const { return led_.getColor8(); }

  DriveLogic<LED> led_;
};

template<class LED>
class PWMPin<-1, LED> : PWMPinInterface {
public:
  void Activate() override {}
  void Deactivate() override {}
  void set(const Color16& c) override {}
  void set_overdrive(const Color16& c) override {}
};

template<int PIN>
class PWMPin<PIN, NoLED> : PWMPinInterface {
public:
  void Activate() override {}
  void Deactivate() override {}
  void set(const Color16& c) override {}
  void set_overdrive(const Color16& c) override {}
  Color8 getColor8() const { return Color8(0,0,0); }
};

template<>
class PWMPin<-1, NoLED> : PWMPinInterface {
public:
  void Activate() override {}
  void Deactivate() override {}
  void set(const Color16& c) override {}
  void set_overdrive(const Color16& c) override {}
  Color8 getColor8() const { return Color8(0,0,0); }
};
template<class ... LEDS>
class MultiChannelLED {};

template<>
class MultiChannelLED<> : public PWMPinInterface {
public:
  void Activate() override {}
  void Deactivate() override {}
  void set(const Color16& c) override {}
  void set_overdrive(const Color16& c) override {}
  Color8 getColor8() const { return Color8(0,0,0); }
};

template<class LED, class... LEDS>
class MultiChannelLED<LED, LEDS...> : public PWMPinInterface {
public:
  void Activate() override {
    led_.Activate();
    rest_.Activate();
  }
  void Deactivate() override {
    led_.Deactivate();
    rest_.Deactivate();
  }
  void set(const Color16& c) override {
    led_.set(c);
    rest_.set(c);
  }
  void set_overdrive(const Color16& c) override {
    led_.set_overdrive(c);
    rest_.set_overdrive(c);
  }
  Color8 getColor8() const {
    return led_.getColor8() | rest_.getColor8();
  }
private:
  LED led_;
  MultiChannelLED<LEDS...> rest_;
};

template<class... LEDS>
class LEDArrayHelper {};

template<>
class LEDArrayHelper<> {
public:
  static const size_t size = 0;
  void InitArray(PWMPinInterface** pos) {}
  void Activate() {}
  void Deactivate() {}
};

template<class LED, class... LEDS>
class LEDArrayHelper<LED, LEDS...> {
public:
  static const size_t size = LEDArrayHelper<LEDS...>::size + 1;
  void InitArray(PWMPinInterface** pos) {
    *pos = &led_;
    rest_.InitArray(pos + 1);
  }
  void Activate() {
    led_.Activate();
    rest_.Activate();
  }
  void Deactivate() {
    led_.Deactivate();
    rest_.Deactivate();
  }
  Color8 getColor8() const {
    return led_.getColor8();
  }
private:
  LED led_;
  LEDArrayHelper<LEDS...> rest_;
};


// Simple blade, LED string or LED star with optional flash on clash.
// Note that this class does nothing when first constructed. It only starts
// interacting with pins and timers after Activate() is called.
// #ifndef OSx
  #if !defined(OSx) || defined(OLDINSTALL)


template<class ... LEDS>
class Simple_Blade : public AbstractBlade, CommandParser, Looper {
public:
  Simple_Blade() :
    AbstractBlade(),
    CommandParser(NOLINK),
    Looper(NOLINK) {
    led_structs_.InitArray(leds_);
  }

#else // OSx installs LEDs at runtime

class Simple_Blade : public AbstractBlade, CommandParser, Looper {
public:
  Simple_Blade() : AbstractBlade(), CommandParser(NOLINK), Looper(NOLINK) {
      nLEDs = 0;
      for (uint8_t i=0; i<ALED_MAXCH; i++)
        leds[i] = 0;
    }

  // Assign an xAnalogLED object to the blade. Order of LEDs is determined by the order of AssignLED() calls
  bool AssignLED(xAnalogLED* newLed) {  // __attribute__((optimize("Og"))) {      
      if (nLEDs == ALED_MAXCH ) return false;   // all possible LEDs are already assigned
      if (leds[nLEDs]) return false;      // LED already assigned (should not happen!)
      leds[nLEDs++] = newLed;
      // STDOUT.print("[SimpleBlade.AssignLED]: Assign LED with "); STDOUT.print(newLed->nCh); STDOUT.print(" channels as #"); STDOUT.print(nLEDs); STDOUT.println(":");
      // for (uint8_t i=0; i<newLed->nCh; i++) {
      //   STDOUT.print(" * Channel #"); STDOUT.print(i); STDOUT.print(": "); newLed->channels[i]->Raport(); STDOUT.println("");
      // }
      return true;
  }

#endif


  
  const char* name() override { return "Simple_Blade"; }

  void Activate() override {
    #ifndef OSx
      STDOUT.println("Simple Blade");
    #else // OSx
      #ifdef DIAGNOSE_BLADES
        STDOUT.print("Activating analog blade with ");
        STDOUT.print(nLEDs);
        if (nLEDs>1)
          STDOUT.println(" leds.");
        else 
          STDOUT.println(" leds");
      #endif // DIAGNOSE_BLADES
    #endif // OSx
    Power(true);
    CommandParser::Link();
    Looper::Link();
    AbstractBlade::Activate();
  }

  void Deactivate() override {
    Power(false);
    AbstractBlade::Deactivate();
    Looper::Unlink();
    CommandParser::Unlink();
  }

// #ifndef OSx
  #if !defined(OSx) || defined(OLDINSTALL)

  void Power(bool on) {
    if (power_ != on) {
      if (on) {
	led_structs_.Activate();
      } else {
	led_structs_.Deactivate();
      }
      power_ = on;
    }
  }

  // BladeBase implementation
  int num_leds() const override {
    return LEDArrayHelper<LEDS...>::size;
  }

  Color8::Byteorder get_byteorder() const override {
    Color8 color = led_structs_.getColor8();
    if (color.r && color.g && color.b) {
      return Color8::RGB;
    }
    return Color8::NONE;
  }
  bool is_on() const override {
    return on_;
  }
  void set(int led, Color16 c) override {
    leds_[led]->set(c);
    // STDOUT.print("[SimpleBlade.Set]: Set LED "); STDOUT.print(led); STDOUT.print(" to color ");
    // STDOUT.print(c.r); STDOUT.print(", "); STDOUT.print(c.g); STDOUT.print(", "); STDOUT.print(c.b); STDOUT.println(".");
  }

  void set_overdrive(int led, Color16 c) override {
    leds_[led]->set_overdrive(c);
  }

  #else // OSx
  void Power(bool on) {
    if (power_ != on && nLEDs) {
      if (on) for (uint8_t i=0; i<nLEDs; i++)
          leds[i]->Activate();
      else for (uint8_t i=0; i<nLEDs; i++)
          leds[i]->Deactivate();
      power_ = on;
    }
  }

  // BladeBase implementation
  int num_leds() const override {
    return nLEDs;   // some styles expect number of distinct LED modules, not number of analog LEDs !!!
  }

  Color8::Byteorder get_byteorder() const override {
      return Color8::RGB;
  }

  bool is_on() const override {
    return on_;
  }
  void set(int led, Color16 c) override { // __attribute__((optimize("Og"))) {
    uint32_t hexRGB = c.r << 8;   // 8-bit R
    hexRGB &= 0xFF0000;
    hexRGB += c.g;              // 8-bit G
    hexRGB &= 0xFFFF00;
    hexRGB += (c.b >> 8);      // 8-bit B
    // STDOUT.print("[SimpleBlade.set()]: set led "); STDOUT.print(led); STDOUT.print(" to color16 ");  
    // STDOUT.print(c.r); STDOUT.print(", "); STDOUT.print(c.g); STDOUT.print(", "); STDOUT.println(c.b); // STDOUT.print(" = ");  STDOUT.println(hexRGB); 
    
    leds[led]->Set(hexRGB);


  }

  void set_overdrive(int led, Color16 c) override {
    // leds_[led]->set_overdrive(c);
    set(led, c);
  }

  #endif

  void allow_disable() override {
    if (!on_) Power(false);
  }
  virtual void SetStyle(BladeStyle* style) {
    Power(true);
    AbstractBlade::SetStyle(style);
  }
  #if defined(OSx) && !defined(OLDPROFILE)
      StyleHeart StylesAccepted() override { return StyleHeart::_4analog; }  
  #endif // OSx
  // SaberBase implementation
  void SB_IsOn(bool *on) override {
    if (on_ || power_) *on = true;
  }
  void SB_On() override {
    AbstractBlade::SB_On();
    // battery_monitor.SetLoad(true);
    on_ = true;
    Power(true);
  }
  void SB_Effect2(BladeEffectType type, float location) override {
    AbstractBlade::SB_Effect2(type, location);
    // battery_monitor.SetLoad(true);
    Power(true);
  }
  void SB_Off(OffType off_type) override {
    AbstractBlade::SB_Off(off_type);
    // battery_monitor.SetLoad(false);
    on_ = false;
    if (off_type == OFF_IDLE) {
      Power(false);
    }
  }

  bool Parse(const char* cmd, const char* arg) override {
    
    #if !defined(OSx) || ( defined(OSx) && defined(X_LIGHTTEST) )
      if (!strcmp(cmd, "ablade")) {
        if (!strcmp(arg, "on")) {
          SB_On();
          return true;
        }
        if (!strcmp(arg, "off")) {
          SB_Off(OFF_NORMAL);
          return true;
        }
      }
    #endif
  

// #if defined(OSx) && defined(X_LIGHTTEST)
  #if defined(OSx) && !defined(OLDINSTALL) && defined(X_LIGHTTEST)

    // parse "aled_pintest" on all analog led channels
    uint8_t ledcnt = nLEDs;
    uint8_t chcnt;
    while (ledcnt) {
        chcnt = leds[--ledcnt]->nCh;
        while (chcnt) 
          if (leds[ledcnt]->channels[--chcnt]->Parse(cmd, arg)) return true;      
    }

    // parse "aled_chtest" on first analog led
    if (nLEDs) 
      if (leds[0]->Parse(cmd, arg)) return true;  

#endif

    return false;

  }

  void Help() override {
#if defined(COMMANDS_HELP) || !defined(OSx)
    STDOUT.println(" ablade on/off - turn analog blade on/off");

  #if defined(OSx) && (defined X_LIGHTTEST)
    STDOUT.println(" aled_pintest <pin>, <brightness> - analog LED test: apply brightness [0, 65535] to LED pin [1, 6]");     
    STDOUT.println(" aled_chtest <channel>, <R>, <G>, <B> - analog LED test: apply RGB color [0, 255] to channel number [1, 4]");     
  #endif
 #endif

  }

protected:
  void Loop() override {
    if (!power_) return;
    // Make sure the booster is running so we don't get low voltage
    // and under-drive any FETs.
    EnableBooster();
    if (current_style_)
      current_style_->run(this);
  }

private:
  #if !defined(OSx) || defined(OLDINSTALL)
  PWMPinInterface* leds_[LEDArrayHelper<LEDS...>::size];
  LEDArrayHelper<LEDS...> led_structs_;
#else  // OSx
  uint8_t nLEDs;    // number of single or multi channel Analog LEDs
  xAnalogLED* leds[ALED_MAXCH];  // Pointers to Analog LEDs
#endif // OSx

  bool on_ = false;
  bool power_ = false;
};





// #ifndef OSx
  #if !defined(OSx) || defined(OLDINSTALL)

template<class LED1, class LED2, class LED3, class LED4,
          int pin1 = bladePowerPin1,
          int pin2 = bladePowerPin2,
          int pin3 = bladePowerPin3,
          int pin4 = bladePin>
class BladeBase *SimpleBladePtr() {
  static Simple_Blade<
    MultiChannelLED<
      PWMPin<pin1, LED1>,
      PWMPin<pin2, LED2>,
      PWMPin<pin3, LED3>,
      PWMPin<pin4, LED4>
    >
  > blade;
  return &blade;
}


  #if VERSION_MAJOR >= 2
  // Possibly one LED driver per channel...
  template<class LED, int CLASH_PIN = -1, class CLASH_LED = NoLED>
  class BladeBase *StringBladePtr() {
    static Simple_Blade<
      MultiChannelLED<PWMPin<bladePowerPin1, LED>,
                      PWMPin<CLASH_PIN, CLASH_LED> >,
      PWMPin<bladePowerPin2, LED>,
      PWMPin<bladePowerPin3, LED>,
      PWMPin<bladePowerPin4, LED>,
      PWMPin<bladePowerPin5, LED>,
      PWMPin<bladePowerPin6, LED>
    > blade;
    return &blade;
  }
  #endif

#endif // OSx

#endif
