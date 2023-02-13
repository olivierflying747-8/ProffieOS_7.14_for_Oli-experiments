#ifndef XPROBE_H
#define XPROBE_H

/********************************************************************
 * CPU PROBES - measures run time, call frequency and cpu usage     *
 *  (C) Marius RANGU @ RSX Engineering. Licensed under GNU GPL.     *
 *  fileversion: v1.0 @ 2022/02                                     *
 ********************************************************************
 *  - enabled by #define X_PROBECPU                                *
 *  - overwrites ScopedCycleCounter and LoopCounter                 *
 *  - adds xProbe and xRange                                        *
 ********************************************************************/


#include <limits>
#include "xUtils.h"

typedef xRange<int32_t,7> xCCRange;      // Cycle counter range: 32bits, EMA order = 7;


enum DoWhatToProbe {
    print_frequency,
    print_duration,
    print_cpu_usage,
    reset_probe
};

/** -----------------------------------------------------------
 * CPU Probe: destination for ScopedCycleCounter
 * Holds statistics for duration of runs and time between runs
 */
class xProbe {
private:
    // Print a graphic bar showing val/maxval, filled with:
    // - char1 from start to val/max
    // - char0 until barsize characters total
    static void _print_bar(uint8_t barsize, char char1, char char0, float val, float maxval)
    {   uint8_t numch;    
        if (val<0) val=0;                                   // keep it positive!
        if (val>maxval) val=maxval;                         // keep ratio below 1

        numch = (uint8_t) ((float)barsize * val / maxval);  // number of char1 in the bar
        barsize-= numch;                                    // number of char0 in the bar
        while(numch--)
            STDOUT.print(char1);                            // print the full part of the bar
        while(barsize--)
            STDOUT.print(char0);                            // print the empty part of the bar        
    }

public:
    uint32_t micros;        // microsecond counter when probed task was last called. 
                            // micros() runs on SysTick wich is independent of CCYCNT, so we can keep track of real time
#ifdef X_PROBECPU
    xCCRange period;        // microseconds between successive runs (based on SysTick)
    xCCRange duration;      // duration of last run, in machine cycles (based on CCYCNT)
    xCCRange cpu100;        // 100 * cpu_usage[%] (holding 2 decimals in the integer). cpu_usage[%] = 100 * run time / run period
                            // We keep this in a distinct range because we want the min and max of cpu_usage decoupled of period's and duration's min and max
#endif // X_PROBECPU
    
    xProbe() {   micros = 0;  }    // make sure it initializes empty; xRange constructors already called...
    
    // reset stream and  microsecond counter 
    void Reset() {
        micros = 0; 
    #ifdef X_PROBECPU
        period.Reset();
        duration.Reset();
        cpu100.Reset();
    #endif // X_PROBECPU
    }

    // Print various reports at STDOUT (no CR/LF!)
    void Print(DoWhatToProbe whattoprint) {
        #ifdef X_PROBECPU
            float f;
            switch (whattoprint)
            {
                case print_frequency:       // call frequency report
                    f = 1000000.0f / (float)period.avg;   // average frequency, in [Hz]. Period comes in [us]
                    // STDOUT.print("Freq [Hz]:");
                    _print_bar(20,'*','_',f, 5000.0f);                          // bargraph, max = 5kHz
                    STDOUT.print ("avg:"); STDOUT.print(f); STDOUT.print(" ");
                    STDOUT.print ("min:"); STDOUT.print(1000000.0f / (float)period.max); STDOUT.print(" ");
                    STDOUT.print ("max:"); STDOUT.print(1000000.0f / (float)period.min); STDOUT.print(" ");
                    STDOUT.print ("now:"); STDOUT.print(1000000.0f / (float)period.val); 
                return;
                case print_duration:        // run time report
                    f = (float)duration.avg / (float)(_SYSTEM_CORE_CLOCK_/1000000);   // average time, in [us]. Duration comes in [mc]
                    // STDOUT.print("Time [us]:");  
                    _print_bar(20,'*','_',f, 500.0f);                                       // bargraph, max = 500 us                                   
                    STDOUT.print ("avg:"); STDOUT.print(f); STDOUT.print(" ");
                    STDOUT.print ("min:"); STDOUT.print((float)duration.min / (float)(_SYSTEM_CORE_CLOCK_/1000000)); STDOUT.print(" ");
                    STDOUT.print ("max:"); STDOUT.print((float)duration.max / (float)(_SYSTEM_CORE_CLOCK_/1000000)); STDOUT.print(" ");
                    STDOUT.print ("now:"); STDOUT.print((float)duration.val / (float)(_SYSTEM_CORE_CLOCK_/1000000));     
                return;
                case print_cpu_usage:       // cpu usage report
                    f = (float)cpu100.avg / 100.0f;   // average CPU usage, in [%]. cpu100 comes as 100 * cpu[%]
                    // STDOUT.print("CPU   [%]:");
                    _print_bar(20,'*','_',f, 20.0f);                             // bargraph, max = 20%
                    STDOUT.print ("avg:"); STDOUT.print(f); STDOUT.print(" ");
                    STDOUT.print ("min:"); STDOUT.print((float)cpu100.min / 100.0f); STDOUT.print(" ");
                    STDOUT.print ("max:"); STDOUT.print((float)cpu100.max / 100.0f); STDOUT.print(" ");
                    STDOUT.print ("now:"); STDOUT.print((float)cpu100.val / 100.0f); 
                return;
            }
        #endif // X_PROBECPU         
    }
    
};



/** -----------------------------------------------------------
 * Cycle counter: counts cycles during and between runs
 *  Overwrites scoped_cycle_counter.h
 */
class ScopedCycleCounter {
private: 
    uint32_t cycles_;               // cycle counter @ constructor call
    xProbe& dest_;                // destination probe

public:
    // Constructor calculates period and usage
    ScopedCycleCounter(xProbe& dest) : dest_(dest) {
        uint32_t microsNow = micros();      // we store micros() of last call even if CPU probes are disabled, we need this for the looper's scheduler
    #ifdef X_PROBECPU
        cycles_ = DWT->CYCCNT;              // store machine cycle counter   
        // PRINT_TIMESTAMP STDOUT.print("ScopedCycleCounter constructor. Calculating frequency. Store micros = "); STDOUT.println(microsNow);
        if (dest_.micros) { // If the destination probe is not initialized ignore this iteration, we don't have enough data for calculations
            dest_.period.Add(microsNow-dest_.micros);   // Update period range  
                                                        // micros() is also a free running counter just like CCYCNT, but it resets at 71 minutes so we don't really need to guard
            uint64_t temp = dest_.duration.val;         // cpu100 = 100 * cpu_usage[%]
            temp *= 10000;   // cpu_usage[%] = 100 * execution time / call period
            temp /= dest_.period.val;                   
            temp /= _SYSTEM_CORE_CLOCK_MHZ_;
            // if (temp>10000*_SYSTEM_CORE_CLOCK_MHZ_) temp=10000*_SYSTEM_CORE_CLOCK_MHZ_; // 
            dest_.cpu100.Add((uint32_t)temp);     // Update cpu usage
            // STDOUT.print(" Added period "); STDOUT.print((float)dest_.period.val*1000.0f); STDOUT.println("[ms]");
        }
        else {
            // PRINT_TIMESTAMP STDOUT.println("Frequency calculation not running on first entry"); 
        }
    #endif // X_PROBECPU    
        dest_.micros = microsNow;           // store  microsecond counter, even if CPU probes are disabled
    }

    // Destructor calculates duration 
    ~ScopedCycleCounter() {
    #ifdef X_PROBECPU
        // PRINT_TIMESTAMP STDOUT.println("ScopedCycleCounter destructor. Calculating duration. "); 
        uint64_t dCycles;                               // we need to add two uint32's here
        uint32_t cyclesNow = DWT->CYCCNT;               // it will change while running...
        
        // PRINT_TIMESTAMP STDOUT.print("cycles_since("); STDOUT.print(previous_CYCCNT); STDOUT.print(") = ");        
        if (cycles_ < cyclesNow)              // DWT->CYCCNT is a free running counter so it resets every 
            dCycles = cyclesNow - cycles_;    // 2^32 * cycletime (~53sec @ 80MHz). 
        else
            dCycles = (std::numeric_limits<uint32_t>::max() - cycles_) + cyclesNow;     // ... CYCCNT overrun

        dest_.duration.Add((uint32_t)dCycles);      // Update duration range.
        // STDOUT.print(" Added duration "); STDOUT.print(dest_.duration.val/80000.0f); STDOUT.println("[ms]");
        // PRINT_TIMESTAMP
        DWT->CYCCNT = cycles_;  // Restore CYCCNT to its state at the constructor call
                                // With this CCYCNT loses the sense of real time, but we need it to make the objects reentrant
        // STDOUT.print("Restore CYCCNT = "); STDOUT.println(cycles);
    #endif // X_PROBECPU
    }



};


/*---------------------------------------------------------------------------
 *  Delegates everything to xProbe (still here for backward compatibility)
 *  Overwrites loop_counter.h
 */
class LoopCounter {
public:
    void Print() {
    #ifdef X_PROBECPU 
        STDOUT.println(""); 
        cpu_probe_.Print(DoWhatToProbe::print_frequency); 
        cpu_probe_.Reset(); 
    #endif // X_PROBECPU
    }
    
    void Print(DoWhatToProbe whattoprint) {   
    #ifdef X_PROBECPU 
        cpu_probe_.Print(whattoprint);  
    #endif // X_PROBECPU
    }

    void Reset() {  cpu_probe_.Reset(); }
    inline void Update() {  ScopedCycleCounter cc(cpu_probe_);    }

private:
    xProbe cpu_probe_;
};




void XProbe_test(void) {   

    

    // STDOUT.println(""); STDOUT.println("XProbe_test ------->"); STDOUT.println(""); 
    CoreDebug->DEMCR |= 1<<24; // DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;                    // Enable CYCCNT
    DWT->CYCCNT = 0;                                        // Reset CYCCNT
    
    // PRINT_TIMESTAMP STDOUT.println("Reset.");
    // xProbe testprobe, testprobe2, testprobe3;
    // testprobe.Print_Freq(); STDOUT.println("");
    // testprobe.Print_Time(); STDOUT.println("");
    // testprobe.Print_CPU();STDOUT.println("");

    // PRINT_TIMESTAMP STDOUT.println("Wait 100 ms."); 
    // delay(100); // wait 
    // {   PRINT_TIMESTAMP STDOUT.println("Run for 20 ms"); 
    //     ScopedCycleCounter_ testCC(testprobe); 
    //     delay(20); // run 
    // }
    // testprobe.Print_Freq(); STDOUT.println("");
    // testprobe.Print_Time(); STDOUT.println("");
    // testprobe.Print_CPU();STDOUT.println("");

    // PRINT_TIMESTAMP STDOUT.println("Wait 98 ms."); 
    // delay(98); // wait 
    // {   PRINT_TIMESTAMP STDOUT.println("Run for 12 ms"); 
    //     ScopedCycleCounter_ testCC(testprobe); 
    //     delay(12); // run 
    //     PRINT_TIMESTAMP STDOUT.println("Start ISR");
    //     { ScopedCycleCounter_ testCC2(testprobe2); 
    //         delay(10); // run ISR 
    //         PRINT_TIMESTAMP STDOUT.println("Stop ISR after 10ms");
    //     }
    //     testprobe2.Print_Freq(); STDOUT.println("");
    //     testprobe2.Print_Time(); STDOUT.println("");
    //     testprobe2.Print_CPU();STDOUT.println("");
    //     PRINT_TIMESTAMP STDOUT.println("Run for 18 ms"); 
    //     delay(18); // continue running
    // }
    // testprobe.Print_Freq(); STDOUT.println("");
    // testprobe.Print_Time(); STDOUT.println("");
    // testprobe.Print_CPU();STDOUT.println("");

    // PRINT_TIMESTAMP STDOUT.println("Wait 200 ms."); 
    // delay(200); // wait 
    // {   PRINT_TIMESTAMP STDOUT.println("Run for 10 ms"); 
    //     ScopedCycleCounter_ testCC(testprobe); 
    //     delay(25); // run 
    //     PRINT_TIMESTAMP STDOUT.println("   Start ISR1 for 5 ms");
    //     { ScopedCycleCounter_ testCC2(testprobe2); 
    //         delay(5); // run ISR 
    //         PRINT_TIMESTAMP STDOUT.println("      Start ISR2 for 40 ms");
    //         {   ScopedCycleCounter_ testCC3(testprobe3); 
    //             delay(40); // run ISR 
    //             PRINT_TIMESTAMP STDOUT.println("      Stop ISR2");
    //         }
    //         PRINT_TIMESTAMP STDOUT.println("   Stop ISR1");
    //     }
    //     testprobe2.Print_Freq(); STDOUT.println("");
    //     testprobe2.Print_Time(); STDOUT.println("");
    //     testprobe2.Print_CPU();STDOUT.println("");
    //     PRINT_TIMESTAMP STDOUT.println("Run for 30 ms"); 
    //     delay(45); // continue running
    // }
    // testprobe.Print_Freq(); STDOUT.println("");
    // testprobe.Print_Time(); STDOUT.println("");
    // testprobe.Print_CPU();STDOUT.println("");



    
    
    STDOUT.println(""); STDOUT.println("XProbe_test <-------"); STDOUT.println(""); 



    // xRange<uint16_t,7> testrange;
    // STDOUT.println("XProbe_test -->");
    // STDOUT.print("Created without initialization. Value = "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange += 100;
    // STDOUT.print("Added "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange += 110;
    // STDOUT.print("Added "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange += 120;
    // STDOUT.print("Added "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange += 115;
    // STDOUT.print("Added "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange += 105;
    // STDOUT.print("Added "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange += 95;
    // STDOUT.print("Added "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange += 50;
    // STDOUT.print("Added "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange += 121;
    // STDOUT.print("Added "); STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // testrange = 10;
    // STDOUT.print("Reset to 10. Value = ");  STDOUT.print(testrange.val); STDOUT.print(". Min = "); STDOUT.print(testrange.min); STDOUT.print(" Max = "); STDOUT.print(testrange.max); STDOUT.print(" Average = "); STDOUT.println(testrange.avg);
    // STDOUT.println("<-- XProbe_test");


}












#endif  //XPROBE_H


