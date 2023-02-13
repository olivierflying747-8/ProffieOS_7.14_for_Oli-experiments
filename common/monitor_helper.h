#ifndef COMMON_MONITOR_HELPER
#define COMMON_MONITOR_HELPER

#include "looper.h"
#include "command_parser.h"

// Debug printout helper class
class MonitorHelper : Looper, CommandParser {
public:
  MonitorHelper() : Looper(), CommandParser() {}
  const char* name() override { return "MonitorHelper"; }
  
protected:
  void Loop() { monitor.Loop(); }
  bool Parse(const char *cmd, const char* arg) override {
//#ifndef DISABLE_DIAGNOSTIC_COMMANDS
#ifdef ENABLE_DEVELOPER_COMMANDS
    if (!strcmp(cmd, "monitor") || !strcmp(cmd, "mon")) {
      if (!strcmp(arg, "swings")) {
        monitor.Toggle(Monitoring::MonitorSwings);
        return true;
      }
      if (!strcmp(arg, "gyro")) {
        monitor.Toggle(Monitoring::MonitorGyro);
        return true;
      }
      if (!strcmp(arg, "samples")) {
        monitor.Toggle(Monitoring::MonitorSamples);
        return true;
      }
      if (!strcmp(arg, "touch")) {
        monitor.Toggle(Monitoring::MonitorTouch);
        return true;
      }
      if (!strcmp(arg, "battery")) {
        monitor.Toggle(Monitoring::MonitorBattery);
        return true;
      }
      if (!strcmp(arg, "pwm")) {
        monitor.Toggle(Monitoring::MonitorPWM);
        return true;
      }
      if (!strcmp(arg, "clash")) {
        monitor.Toggle(Monitoring::MonitorClash);
        return true;
      }
      if (!strcmp(arg, "temp")) {
        monitor.Toggle(Monitoring::MonitorTemp);
        return true;
      }
      if (!strcmp(arg, "strokes")) {
        monitor.Toggle(Monitoring::MonitorStrokes);
        return true;
      }
      if (!strcmp(arg, "serial")) {
        monitor.Toggle(Monitoring::MonitorSerial);
        return true;
      }
      if (!strcmp(arg, "fusion")) {
        monitor.Toggle(Monitoring::MonitorFusion);
        return true;
      }
      if (!strcmp(arg, "var") || !strcmp(arg, "variation")) {
        monitor.Toggle(Monitoring::MonitorVariation);
        return true;
      }
    }
#endif // ENABLE_DEVELOPER_COMMANDS

#if defined (ENABLE_DEVELOPER_COMMANDS) && defined(ENABLE_TRACING) 
  #ifndef OSx
    if (!strcmp(cmd, "dumptrace")) {
      for (size_t i = 0; i < NELEM(trace); i++) {
	STDOUT << (const char *)(trace[(trace_pos + i) & (NELEM(trace) - 1)]) << "\n";
      }
      return true;
    }
  #else // OSx
      if (!strcmp(cmd, "dumptrace")) {
        for (size_t i = 0; i < NELEM(trace); i++) 
          if (trace[i]) {
            STDOUT.print("  "); STDOUT.print(i+1); STDOUT.print(": ");
            STDOUT.println((char*)(trace[i]));
            trace[i]=0; 
          }
        STDOUT.print("trace_pos = "); STDOUT.println(trace_pos);
        trace_pos = 0;
        return true;
    }
  #endif // OSx

#endif // ENABLE_DEVELOPER_COMMANDS
    return false;
  }
  void Help() {
    #if defined(COMMANDS_HELP) || !defined(OSx)
    STDOUT.println(" mon[itor] swings/samples/touch/battery/pwm/clash/temp/serial/fusion - toggle monitoring");
    #endif
  }
};

#endif
