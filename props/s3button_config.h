// Sabertrio Proffie Preconfiguration
// DEFAULT 2 SWITCH CONTROLS (ACTIVATION and AUXILIARY)
//
// Ignite Blade					- Press & release ACTIVATION SWITCH while blade is OFF.
//                              - Twist while blade is OFF.
// 							NOTE: If no blade or blade plug is detected, the 'no blade' sound effect will play.
// Volume Menu 				    - Press AUXILIARY SWITCH + ACTIVATION SWITCH while blade is OFF.
// Volume Up                    - Press AUXILIART SWITCH while in Volume Menu.
// Volume Down                  - Press ACTIVATION SWITCH while in Volume Menu
//                          NOTE: Press & hold ACTIVATION SWITCH or AUXILIARY SWITCH to exit Volume Menu.
// Retract Blade 			    - Press & hold the ACTIVATION SWITCH for while blade is ON.
//                              - Twist while blade is ON.
// Blaster Block Effect			- Press & release AUXILIARY SWITCH while blade is ON.
// Flash on Clash				- Strike blade while blade is ON.
// Blade Lockup Effect 			- Press & hold AUXILIARY SWITCH and strike blade while blade is ON.
// Blade Tip Drag Effect		- Press & hold AUXILIARY SWITCH and stab down and strike blade while ON.
// Wall Melt Effect  			- Press & hold AUXILIARY SWITCH while thrust stab forward and strike blade while blade is ON.
// Force Effect 				- Press & hold AUXILIARY SWITCH while blade is ON.
// Kyber Dial 					- Press & hold AUXILIARY SWITCH & press ACTIVATION SWITCH while blade is ON to enter blade color change mode.
//          				THEN: Twist rotate saber to change blade color.
//          				NOTE: Press & release ACTIVATION SWITCH or AUXILIARY SWITCH to select color.
// Force Lightning Parry Effect - Double press & hold ACTIVATION SWITCH when blade is on. 
// Cycle to Next Sound Font		- Press & hold AUXILIARY SWITCH while blade is OFF.
//							NOTE: Only works when blade / blade plug is present.
// Cycle to Previous Sound Font - Press & hold ACTIVATION SWITCH while blade is OFF.
//							NOTE: Only works when blade / blade plug is present.
// Battery Level Meter			- Press & Release AUXILIARY SWITCH while blade is OFF.
//							NOTE: Battery level meter will automatically turn off after 4 seconds.
// Track Player                 - Press & hold ACTIVATION SWITCH & press AUXILIARY SWITCH.
//                          NOTE: Only works when a track is defined in the s3config.h file for the blade style.

#ifndef PROPS_SABER_SABERTRIO_BUTTONS_H
#define PROPS_SABER_SABERTRIO_BUTTONS_H

#include "prop_base.h"
#include "../sound/hybrid_font.h"

#undef PROP_TYPE
#define PROP_TYPE SaberSabertrioButtons

#ifdef S3_TWIST_ON
#define TWIST_GESTURE
#endif
#ifdef S3_TWIST_OFF
#define TWIST_GESTURE
#endif

EFFECT(battery);  // for EFFECT_BATTERY_LEVEL
EFFECT(vmbegin);  // for Begin Volume Menu
EFFECT(vmend);    // for End Volume Menu
EFFECT(volup);    // for increse volume
EFFECT(voldown);  // for decrease volume
EFFECT(volmin);   // for minimum volume reached
EFFECT(volmax);   // for maximum volume reached
#include "../sound/sound_library.h"

// The Saber class is for the implementation of the basic states and actions of the saber.
class SaberSabertrioButtons : public PropBase {
public:
SaberSabertrioButtons() : PropBase() {}
  const char* name() override { return "SaberSabertrioButtons"; }

  void Loop() override 
  {
    PropBase::Loop();
    DetectTwist();
    DetectSwing();
  }
  
  // SA22C Volume Menu
  void VolumeUp() 
  {
    if (dynamic_mixer.get_volume() < VOLUME) 
    {
      dynamic_mixer.set_volume(std::min<int>(VOLUME + VOLUME * 0.1,
      dynamic_mixer.get_volume() + VOLUME * 0.10));
      hybrid_font.PlayCommon(&SFX_volup);
    } 
    
    else
    {
      hybrid_font.PlayCommon(&SFX_volmax);
    }
  }

  void VolumeDown() 
  {
    if (dynamic_mixer.get_volume() > (0.10 * VOLUME)) 
    {
      dynamic_mixer.set_volume(std::max<int>(VOLUME * 0.1,
      dynamic_mixer.get_volume() - VOLUME * 0.10));
      hybrid_font.PlayCommon(&SFX_voldown);
    } 
    
    else 
    {
      hybrid_font.PlayCommon(&SFX_volmin);
    }
  }

  bool Event2(enum BUTTON button, EVENT event, uint32_t modifiers) override 
  {
    switch (EVENTID(button, event, modifiers)) 
    {
      case EVENTID(BUTTON_POWER, EVENT_PRESSED, MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_PRESSED, MODE_ON):
        if (accel_.x < -0.15) 
        {
          pointing_down_ = true;
        } 

        else 
        {
          pointing_down_ = false;
        }
        return true;
	
  
  	// S3 - Saber ON & Volume Down
    case EVENTID(BUTTON_POWER, EVENT_CLICK_SHORT, MODE_OFF):
	case EVENTID(BUTTON_POWER, EVENT_CLICK_LONG, MODE_OFF):
	
		if (!mode_volume_) 
    {
			aux_on_ = false;
			On();
		} 
    else 
    {
      VolumeDown();
    }

		return true;
	
	// S3 - Battery Indicator & Volume Up
	case EVENTID(BUTTON_AUX, EVENT_CLICK_SHORT, MODE_OFF):
	case EVENTID(BUTTON_AUX, EVENT_CLICK_LONG, MODE_OFF):
		if (!mode_volume_) 
    {
			SaberBase::DoEffect(EFFECT_BATTERY_LEVEL, 0);
		} 
    else 
    {
			VolumeUp();
		}
		return true;

	//S3 - Enter Volume Menu
	case EVENTID(BUTTON_POWER, EVENT_CLICK_SHORT, MODE_OFF | BUTTON_AUX):
    if (!mode_volume_) 
    {
      mode_volume_ = true;
      if (SFX_vmbegin) 
      {
        hybrid_font.PlayCommon(&SFX_vmbegin);
      } 
      else 
      {
        beeper.Beep(0.5, 3000);
      }
    } 

	else {
      mode_volume_ = false;
      if (SFX_vmend) {
        hybrid_font.PlayCommon(&SFX_vmend);
      } else {
        beeper.Beep(0.5, 3000);
      }
    }
    return true;

#ifdef S3_TWIST_ON
  case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_OFF):
  if(!mode_volume_)
		{
			// Delay twist events to prevent false trigger from over twisting
			if (millis() - last_twist_ > 1000 && millis() - saber_off_time_ > 1000) 
			{
				On();
				last_twist_ = millis();
			}
			return true;
		}
    return false;
#endif

#ifdef S3_TWIST_OFF
// Delay twist events to prevent false trigger from over twisting
	case EVENTID(BUTTON_NONE, EVENT_TWIST, MODE_ON):
  if(!SaberBase::Lockup()) 
  {
  	if (SaberBase::GetColorChangeMode() == SaberBase::COLOR_CHANGE_MODE_NONE) 
	{
		if (millis() - last_twist_ > 1000)
		{
			Off();
			last_twist_= millis();
		}
	}
  }
	return true;
#endif

// S3 - Blade OFF
      case EVENTID(BUTTON_POWER, EVENT_HELD_MEDIUM, MODE_ON):
		if (SaberBase::GetColorChangeMode() == SaberBase::COLOR_CHANGE_MODE_NONE) 
			{
				Off();     
				return true;				
			}
			return false;
        
 
// S3 - Next Soundfont
      case EVENTID(BUTTON_AUX, EVENT_HELD_LONG, MODE_OFF):
		if(!mode_volume_)
		{
        next_preset();
		}
		else 
	{
		mode_volume_ = false;
		if (SFX_vmend) 
		{
			hybrid_font.PlayCommon(&SFX_vmend);
		}
		else 
		{
        beeper.Beep(0.5, 3000);
		}
		STDOUT.println("Exit Volume Menu");
    }
        return true;
		
// S3 - Previous Soundfont
      case EVENTID(BUTTON_POWER, EVENT_HELD_LONG, MODE_OFF):
	if(!mode_volume_)
	{
        previous_preset();
	}
	else 
	{
      mode_volume_ = false;
      if (SFX_vmend) 
      {
        hybrid_font.PlayCommon(&SFX_vmend);
      } 
      else 
      {
        beeper.Beep(0.5, 3000);
      }
      STDOUT.println("Exit Volume Menu");
    }
        return true;

// S3 - Start or Stop Track
  case EVENTID(BUTTON_AUX, EVENT_CLICK_SHORT, MODE_OFF | BUTTON_POWER):
  if(!mode_volume_)
  {
      StartOrStopTrack();
  }
    return true;
  
  case EVENTID(BUTTON_AUX, EVENT_CLICK_SHORT, MODE_ON | BUTTON_POWER):
    if (!mode_volume_)
    {
		StartOrStopTrack();
	}
    return true;

  case EVENTID(BUTTON_POWER, EVENT_PRESSED, MODE_OFF):
  case EVENTID(BUTTON_AUX, EVENT_PRESSED, MODE_OFF):
    SaberBase::RequestMotion();
    return true;


// S3 - Blaster Block
		case EVENTID(BUTTON_AUX, EVENT_CLICK_SHORT, MODE_ON):
        if (!SaberBase::Lockup()) 
		{
			if (SaberBase::GetColorChangeMode() == SaberBase::COLOR_CHANGE_MODE_NONE) 
			{
				DoBlast();
			}
		}
        
        return true;
		
		
		  
// S3 - Confirm selected blade color in color change mode, with power switch 		  
		case EVENTID(BUTTON_AUX, EVENT_HELD_LONG, MODE_ON):
		case EVENTID(BUTTON_POWER, EVENT_HELD_LONG, MODE_ON):
          if (SaberBase::GetColorChangeMode() != SaberBase::COLOR_CHANGE_MODE_NONE) 
          {			 
            ToggleColorChangeMode();          
		 			
		  }
		  return true;

				
// S3 - Lightning Block
      case EVENTID(BUTTON_POWER, EVENT_SECOND_HELD, MODE_ON):
	  if (SaberBase::GetColorChangeMode() == SaberBase::COLOR_CHANGE_MODE_NONE) 
	  {
        SaberBase::SetLockup(SaberBase::LOCKUP_LIGHTNING_BLOCK);
        SaberBase::DoBeginLockup();
		return true;
	  }
	  return false;

// S3 - Lockup & Drag
      case EVENTID(BUTTON_NONE, EVENT_CLASH, MODE_ON | BUTTON_AUX):

        if (!SaberBase::Lockup()) 
        {
          if (pointing_down_) 
          {
            SaberBase::SetLockup(SaberBase::LOCKUP_DRAG);
          } 
          else 
          {
            SaberBase::SetLockup(SaberBase::LOCKUP_NORMAL);
          }
          SaberBase::DoBeginLockup();
          return true;
        }
        return false;
		
// S3 - Melt Lockup
      case EVENTID(BUTTON_NONE, EVENT_STAB, MODE_ON | BUTTON_AUX):
        if (!SaberBase::Lockup()) 
        {
          SaberBase::SetLockup(SaberBase::LOCKUP_MELT);
          SaberBase::DoBeginLockup();
          return true;
        }
        return false;
		
// S3 - Toggle color change mode
	  case EVENTID(BUTTON_POWER, EVENT_CLICK_SHORT, MODE_ON | BUTTON_AUX):
	    ToggleColorChangeMode();
		return false;

// S3 - Force
      case EVENTID(BUTTON_AUX, EVENT_HELD_MEDIUM, MODE_ON):
		if (SaberBase::GetColorChangeMode() == SaberBase::COLOR_CHANGE_MODE_NONE) 
		{
			SaberBase::DoForce();
			return true;
		}
		return false;
	  		
#ifdef BLADE_DETECT_PIN
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_ON, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_ON, MODE_ANY_BUTTON | MODE_OFF):
        // Might need to do something cleaner, but let's try this for now.
        blade_detected_ = true;
        FindBladeAgain();
        SaberBase::DoBladeDetect(true);
        return true;

      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_OFF, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_BLADE_DETECT, EVENT_LATCH_OFF, MODE_ANY_BUTTON | MODE_OFF):
        // Might need to do something cleaner, but let's try this for now.
        blade_detected_ = false;
        FindBladeAgain();
        SaberBase::DoBladeDetect(false);
        return true;
#endif

// Events that needs to be handled regardless of what other buttons are pressed.
      case EVENTID(BUTTON_POWER, EVENT_RELEASED, MODE_ANY_BUTTON | MODE_ON):
      case EVENTID(BUTTON_AUX, EVENT_RELEASED, MODE_ANY_BUTTON | MODE_ON):
        if (SaberBase::Lockup()) 
        {
          SaberBase::DoEndLockup();
          SaberBase::SetLockup(SaberBase::LOCKUP_NONE);
          mode_volume_ = false;
          return true;
        }
    }
    return false;
  }
  
  void SB_Effect(EffectType effect, float location) override 
  {
    switch (effect) 
    {
        case EFFECT_BATTERY_LEVEL:
        if (SFX_battery) 
        {
          hybrid_font.PlayCommon(&SFX_battery);
        } 
        else 
        {
          beeper.Beep(0.5, 3000);
        }
        return;
      
     
    }
  }

private:
  bool aux_on_ = true;
  bool pointing_down_ = false;
  bool mode_volume_ = false;
  bool max_volume_reached = false;
  bool min_vol_reached_ = false;
  uint32_t last_twist_ = millis();
  uint32_t saber_off_time_ = millis();
};

#endif

	
		