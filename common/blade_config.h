#ifndef COMMON_BLADE_CONFIG_H
#define COMMON_BLADE_CONFIG_H

class BladeBase;

struct BladeConfig {
  // Blade identifier resistor.
  int ohm;

  // Blade driver.
#define DEFINE_BLADES(N) BladeBase* blade##N;
  #ifndef OSx
  ONCEPERBLADE(DEFINE_BLADES);
  #else // OSx
    ONCEPERSUPPORTEDBLADE(DEFINE_BLADES);
  #endif

  #if !defined(OSx) || defined(OLDPROFILE)
    // Blade presets
    Preset* presets;
    size_t num_presets;
  #else // OSx
    vector<xPreset>* presets;
  #endif


  const char* save_dir;
};

extern BladeConfig* current_config;

struct RFID_Command {
  uint64_t id;
  const char* cmd;
  const char* arg;
};

#endif
