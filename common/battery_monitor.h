#ifndef COMMON_BATTERY_MONITOR_H
#define COMMON_BATTERY_MONITOR_H


#include "analog_read.h"

#ifndef OSx
  // ProffieOS Battery Monitor
  // =========================
  #ifndef NO_BATTERY_MONITOR
  class BatteryMonitor : Looper, CommandParser, StateMachine {
  public:
  BatteryMonitor() : reader_(batteryLevelPin,
            INPUT
  #if VERSION_MAJOR == 5 || VERSION_MAJOR == 6
                              , 10e-6
  #endif
    ) {}
    const char* name() override { return "BatteryMonitor"; }
    float battery() const {
      return last_voltage_;
    }
    void SetLoad(bool on) {
      loaded_ = on;
    }
    bool low() const { return low_count_ > 1000; }
    float battery_percent() {
      // Energy is roughly proportional to voltage squared.
      float v = battery();
      float min_v = 2.85;
      float max_v = 4.1;
      return 100.0 * clamp((v * v - min_v * min_v) / (max_v * max_v - min_v * min_v), 0, 1);
  //    return 100.0 * (v - min_v) / (max_v - min_v);
    }
    void SetPinHigh(bool go_high) {
      #ifndef ULTRA_PROFFIE
        if (go_high) {
          pinMode(batteryLevelPin, OUTPUT);
          digitalWrite(batteryLevelPin, HIGH);
        } 
        else {
          #if VERSION_MAJOR >= 2
            pinMode(batteryLevelPin, INPUT);
          #else
            pinMode(batteryLevelPin, INPUT_PULLDOWN);
          #endif
          // delay reading voltage for a bit to let it settle.
          last_voltage_read_time_ = micros();
        }
      #endif
    }
  protected:
    void Setup() override {
      last_voltage_ = battery_now();
      SetPinHigh(false);
    }
    void Loop() override {
      if (monitor.ShouldPrint(Monitoring::MonitorBattery) ||
          millis() - last_print_millis_ > 20000) {
        STDOUT.print("Battery voltage: ");
        STDOUT.println(battery());
        last_print_millis_ = millis();
      }

      STATE_MACHINE_BEGIN();
      last_voltage_read_time_ = micros();
      while (true) {
        while (micros() - last_voltage_read_time_ < 1000) YIELD();
        while (!reader_.Start()) YIELD();
        while (!reader_.Done()) YIELD();
        float v = battery_now();
        uint32_t now = micros();
        // float mul = powf(0.05, (now - last_voltage_read_time_) / 1000000.0);
        float mul = expf(logf(0.05) * (now - last_voltage_read_time_) / 1000000.0);
        last_voltage_read_time_ = now;
        last_voltage_ = last_voltage_ * mul + v * (1 - mul);
        if (IsLow()) {
    low_count_++;
        } else {
    low_count_ = 0;
        }
      }
      STATE_MACHINE_END();
    }

    bool IsLow() {
  #if VERSION_MAJOR >= 4 && !defined(ULTRA_PROFFIE)
      if (USBD_Connected()) return false;
  #endif
      // Battery isn't low if it's not connected at all.
      if (battery() < 0.5) return false;
      
      return battery() < (loaded_ ? 2.6 : 3.0);
    }

    bool Parse(const char* cmd, const char* arg) override {
      if (!strcmp(cmd, "battery_voltage")) {
        STDOUT.println(battery());
        return true;
      }
      if (!strcmp(cmd, "batt") || !strcmp(cmd, "battery")) {
        STDOUT.print("Battery voltage: ");
        float v = battery();
        STDOUT.println(v);
  #ifdef ENABLE_AUDIO
        talkie.SayDigit((int)floorf(v));
        talkie.Say(spPOINT);
        talkie.SayDigit(((int)floorf(v * 10)) % 10);
        talkie.SayDigit(((int)floorf(v * 100)) % 10);
        talkie.Say(spVOLTS);
  #endif
        return true;
      }
  #if 0
      if (!strcmp(cmd, "bstate")) {
        STDOUT.print("Next state: ");
        STDOUT.println(reader_.state_machine_.next_state_);
        STDOUT.print("ADC SMP: ");
        STDOUT.println(reader_.adc_smp_);
        STDOUT.print("ADC state: ");
        STDOUT.println(stm32l4_adc.state);
        return true;
      }
  #endif
      return false;
    }
    void Help() override {
      #if defined(COMMANDS_HELP) || !defined(OSx)
      STDOUT.println(" batt[ery[_voltage]] - show battery voltage");
      #endif
    }
  private:
    
 #ifndef ULTRA_PROFFIE
    float battery_now() {
          // This is the volts on the battery monitor pin.
          float volts = 3.3 * reader_.Value() / 1023.0;
      #if VERSION_MAJOR == 5 || VERSION_MAJOR == 6
          return volts * 2.0;
      #else
      #ifdef V2
          float pulldown = 220000;  // External pulldown
          float pullup = 2000000;   // External pullup
      #else
          float pulldown = 33000;  // Internal pulldown is 33kOhm
          float pullup = BATTERY_PULLUP_OHMS;  // External pullup
      #endif
          return volts * (1.0 + pullup / pulldown);
      #endif
    }
    #else // ULTRA_PROFFIE
    float battery_now() {
        // This is the volts on the battery monitor pin.
        static float volts;
        volts = 3.0 * reader_.Value() / 1023.0;
          return volts * 3.0;
      }
    #endif // ULTRA_PROFFIE

    bool loaded_ = false;
    float last_voltage_ = 0.0;
    uint32_t last_voltage_read_time_ = 0;
    uint32_t last_print_millis_;
    uint32_t low_count_ = 0;
    AnalogReader reader_;
  };

  #else  // NO_BATTERY_MONITOR

  class BatteryMonitor {
  public:
    float battery() const { return 3.7f; }
    void SetLoad(bool on) {}
    bool low() const { return false; }
    float battery_percent() { return 100.0f;  }
    void SetPinHigh(bool go_high) {}
  };

  #endif  // NO_BATTERY_MONITOR

BatteryMonitor battery_monitor;

#else // OSx
  // ProffieOSx Battery Monitor
  #define BATMIN_LOADED     3.1   // Minimum battery voltage (1%), when loaded
  #define BATMAX_LOADED     4.15   // Maximum battery voltage (100%), when loaded
  #define BATMIN_UNLOADED   3.3   // Minimum battery voltage (1%), when unloaded  
  #define BATMAX_UNLOADED   4.2   // Maximum battery voltage (100%), when unloaded
  // #define CALIBRATED_VOLTAGE_LSB 0.00875912 // Calibrated voltageLSB - if defined it is used instead of .voltageLSB()

  // RESINDEX determines the voltage resolution. This is relevant for Analog LEDs, which regulate output based on current voltage. To increase processing speed we'll keep voltage in integer until a float
  // Lower resolution will increase measurement accuracy AND processing time
  /*  RESINDEX    ProffieBoard LSB    ProffieLite LSB
        0             1.6 mV                1.1 mV
        1             3.2 mV                2.2 mV
        2             6.4 mV                4.4 mV
        3            12.9 mV                8.8 mV
        4            25.8 mV               17.6 mV
        5            51.6 mV               35.2 mV
  */

  template <uint8_t LSBINDEX=0>
  class BatteryMonitor : Looper, CommandParser, StateMachine {
  private:
      bool loaded_ = false;
      uint16_t low_count_ = 0;
      AnalogReader readerVbat_;
      #ifdef ULTRA_PROFFIE
        AnalogReader readerVRef_;
      #endif
      float calibratedLSB = 0;
  public:
      xRange<int32_t,7> iVoltage; // integer voltage -> gets converted to volts (float) only when requested - via battery(). EMA filter runs on this integer


      #ifdef ULTRA_PROFFIE // Proffie Lite: read voltage by VBAT and internal reference
        BatteryMonitor() : Looper(1000), readerVbat_(batteryLevelPin, INPUT , 10e-6),  readerVRef_(batteryRefPin, INPUT , 10e-6) {}  
      #else // Proffie Board: read voltage by pin
        BatteryMonitor() : Looper(1000), readerVbat_(batteryLevelPin, INPUT , 10e-6) {}  
      # endif // ULTRA_PROFFIE

      const char* name() override { return "BatteryMonitor"; }

      // Voltage LSB - defined below in specializations, only for the allowed values of LSBINDEX
      // This is also the voltage change threshold for LED refresh, so lower LSB means more calculations
      float voltageLSB() { return 0; }

    // Get battery voltage as integer ( = multiple of voltageLSB )
    int32_t iBattery() {
      return iVoltage.avg >> LSBINDEX + 7;
    }

      // Get battery voltage as float ( = volts)
      float battery() { // __attribute__((optimize("Og"))) {
        #ifdef CALIBRATED_VOLTAGE_LSB
          return CALIBRATED_VOLTAGE_LSB * (float)iBattery();  // 1. Use FLASH calibrated LSB, if available
        #else
          if (calibratedLSB) return calibratedLSB * (float)iBattery();  // 2. Use RAM calibrated LSB, if available
          return voltageLSB() * (float)iBattery();    // 3. Use calculated (un-calibrated) LSB
        #endif
      }


      void SetLoad(bool on) {
        loaded_ = on;
        // STDOUT.print("Battery load = "); STDOUT.println(on);
      }

      bool low() const { return low_count_ > 1000; }

      float battery_percent() {
        // Energy is roughly proportional to voltage squared.
        float v = battery();  // battery voltage
        float p; // battery percentage  
        if (loaded_)  p = 100.0 * clamp((v * v - BATMIN_LOADED*BATMIN_LOADED) / (BATMAX_LOADED*BATMAX_LOADED - BATMIN_LOADED*BATMIN_LOADED), 0.01, 1);    
        else p = 100.0 * clamp((v * v - BATMIN_UNLOADED*BATMIN_UNLOADED) / (BATMAX_UNLOADED*BATMAX_UNLOADED - BATMIN_UNLOADED*BATMIN_UNLOADED), 0.01, 1);  
        return p;  
      }

      void Print() {
         if (battery() < 0.5) STDOUT.print("not connected");
         else { 
            float percent = battery_percent();
            if (percent<5) STDOUT.print("empty");
            else { 
              STDOUT.print((uint8_t)battery_percent()); 
              STDOUT.print("%"); 
            }
         }
      }

      void SetPinHigh(bool go_high) {
      #ifndef ULTRA_PROFFIE
        if (go_high) {
          pinMode(batteryLevelPin, OUTPUT);
          digitalWrite(batteryLevelPin, HIGH);
        } 
        else
          pinMode(batteryLevelPin, INPUT);
        // delay reading voltage for a bit to let it settle.
        // last_voltage_read_time_ = micros();        
      #endif
    }

    // protected:
    public:

      void Setup() override {
        // last_voltage_ = battery_now();
        //last_voltage_ = STM32.getVBAT();
        //SetPinHigh(false);
      }

      void Loop() override  {
        if (monitor.ShouldPrint(Monitoring::MonitorBattery)) {
          STDOUT.print("Battery voltage: ");
          STDOUT.println(battery());
          // last_print_millis_ = millis();
        }

      #ifdef ULTRA_PROFFIE // Proffie Lite: read voltage by VBAT and internal reference
        STATE_MACHINE_BEGIN();
        // last_voltage_read_time_ = micros();
        while (true) {
          // while (micros() - last_voltage_read_time_ < 1000) YIELD();
          while (!readerVRef_.Start()) YIELD();
          while (!readerVRef_.Done()) YIELD();
          while (!readerVbat_.Start()) YIELD();
          while (!readerVbat_.Done()) YIELD();

          int32_t intVolt;   // integer voltage 
          intVolt = *((uint16_t*)0x1fff75aa);  // calibration value , Datasheet 3.15.1
          intVolt *= readerVbat_.Value();  
          // intVolt <<= 4;       
          intVolt <<= 8;    // scale with 2^8  before filtering, to minimize rounding errors      
          intVolt /= readerVRef_.Value();  // Voltage [V] = ADC_reading/4095 * 3 {volts} * 3 {resistors_ratio}
          // intVolt >>= LSBINDEX+1;             
          iVoltage.Add (intVolt);
      
      #else // Proffie Board: read voltage at pin
       STATE_MACHINE_BEGIN();
        while (true) {
          while (!readerVbat_.Start()) YIELD();
          while (!readerVbat_.Done()) YIELD(); 
          int32_t intVolt = readerVbat_.Value();   // integer voltage 
          intVolt <<= 7;   // scale with 2^7 before filtering, to minimize rounding errors
          iVoltage.Add (intVolt);
      
      # endif // ULTRA_PROFFIE


      if (IsLow()) {
        if (low_count_ < 10000) // don't overrun!
          low_count_++;
      }
      else low_count_ = 0;
          
      }
      STATE_MACHINE_END();
    }

      bool IsLow() {
        #if VERSION_MAJOR >= 4 && !defined(ULTRA_PROFFIE)
          if (USBD_Connected()) return false;
        #endif
        if (battery() < 0.5) return false;        // Battery isn't low if it's not connected at all.
        return battery() < (loaded_ ? BATMIN_LOADED : BATMIN_UNLOADED);
      }

      bool Parse(const char* cmd, const char* arg) override {
        // if (!strcmp(cmd, "battery_voltage")) {
        //   STDOUT.println(battery());
        //   return true;
        // }
      
        if (!strcmp(cmd, "battery")) {
          STDOUT.print(battery()); STDOUT.print("V = ");
          Print(); STDOUT.println("");
          return true;
        }

  #ifdef ENABLE_DEVELOPER_COMMANDS
      if (!strcmp(cmd, "battery_calibration")) {          
          uint16_t milliVolts = atoi(arg);
          if (milliVolts < 3500 || milliVolts > 4000) {
            STDOUT.println ("FAILED - Calibrate between 3500 [mV] and 4000 [mV]. Reverted to factory calibration");
            calibratedLSB = 0;
            return true;
          }
          float vLSB = 1000 * milliVolts;    // known voltage / ADC reading = LSB
          vLSB /= iBattery();
          calibratedLSB = vLSB/1000000;
          STDOUT.print("Set CALIBRATED_VOLTAGE_LSB to "); STDOUT.print(vLSB); STDOUT.println(" E-6 today.");
          return true;
        }
  #endif // ENABLE_DEVELOPER_COMMANDS


        return false;
      }

      void Help() override {
        #if defined(COMMANDS_HELP) || !defined(OSx)
        STDOUT.println(" battery - show battery percent");
        STDOUT.println(" battery_voltage - show battery voltage");
        STDOUT.println(" battery_calibration <milliVolts> - calibrate battery monitor");
        #endif
      }

   
  };

// Constants to calculate voltage [V] from integer voltage
#ifdef ULTRA_PROFFIE
  template<>  // voltage LSB for LSBINDEX = 0
  float BatteryMonitor<0>::voltageLSB() { return 0.001098901; } // 1.1 mV

  template<> // voltage LSB for LSBINDEX = 1
  float BatteryMonitor<1>::voltageLSB() { return 0.002197802; } // 2.2 mV

  template<> // voltage LSB for LSBINDEX = 2
  float BatteryMonitor<2>::voltageLSB() { return 0.004395604; } // 4.4 mV

  template<> // voltage LSB for LSBINDEX = 3
  float BatteryMonitor<3>::voltageLSB() { return 0.008791209; } // 8.8 mV

  template<> // voltage LSB for LSBINDEX = 4
  float BatteryMonitor<4>::voltageLSB() { return 0.017582418; } // 17.6 mV

  template<> // voltage LSB for LSBINDEX = 5
  float BatteryMonitor<5>::voltageLSB() { return 0.035164835; } // 35.2 mV

  // BatteryMonitor<3> battery_monitor;  // iVoltage LSB = 8.8mV 
  BatteryMonitor<1> battery_monitor;  // iVoltage LSB = 8.8mV 


#else // ULTRA_PROFFIE
  template<>  // voltage LSB for LSBINDEX = 0
  float BatteryMonitor<0>::voltageLSB() { return 0.001611722; } // 1.6 mV

  template<> // voltage LSB for LSBINDEX = 1
  float BatteryMonitor<1>::voltageLSB() { return 0.003223443; } // 3.2 mV

  template<> // voltage LSB for LSBINDEX = 2
  float BatteryMonitor<2>::voltageLSB() { return 0.006446886; } // 6.4 mV

  template<> // voltage LSB for LSBINDEX = 3
  float BatteryMonitor<3>::voltageLSB() { return 0.012893773; } // 12.9 mV

  template<> // voltage LSB for LSBINDEX = 4
  float BatteryMonitor<4>::voltageLSB() { return 0.025787546; } // 25.8 mV

  template<> // voltage LSB for LSBINDEX = 5
  float BatteryMonitor<5>::voltageLSB() { return 0.051575092; } // 51.6 mV

  BatteryMonitor<2> battery_monitor;  // iVoltage LSB = 6.4mV 

#endif // ULTRA_PROFFIE



#endif // OSx





#endif // COMMON_BATTERY_MONITOR_H

