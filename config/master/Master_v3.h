// Include common "using" layer styles from another file
#include "Common_Colors.h" // Color / color blend defines
#include "Common_Misc.h" // Misc common code and effects
#include "Common_Blade.h" // Blade effects, for STYLE_OPTION_ARG
#include "Common_Blade2.h" // Blade effects, for STYLE_OPTION2_ARG
#include "Common_Swing.h" // Swing effects for SWING_OPTION_ARG
#include "Common_Blast.h" // Blaster effects
#include "Common_Lockup.h" // Lockup effects
#include "Common_Clash.h" // Clash effects
#include "Common_Stab.h" // Stab effects
#include "Common_Drag.h" // Drag effects
#include "Common_Melt.h" // Melt effects
#include "Common_Lightning.h" // Lightning Block effects
#include "Common_PreOn.h" // PreOn effects for PREON_OPTION_ARG
#include "Common_Ignition.h" // Effects for IGNITION_OPTION_ARG
#include "Common_Retraction.h" // effects for RETRACTION_OPTION_ARG
#include "Common_PowerUp.h" // Effects for IGNITION_POWER_UP_ARG
#include "Common_PowerDown.h" // Effects for RETRACTION_COOL_DOWN_ARG
#include "Common_PostOff.h" // Effects for OFF_OPTION_ARG (They should really add a POSTOFF_OPTION_ARG...)
#include "Common_Specials.h" // Special Effects (for use one each for EFFECT_USER1 - EFFECT_USER8)

/* Based on Fett263 Static/Flicker (Primary Blade) OS6 Style, heavily modified (Added more options)
https://fett263.s3.us-east-2.amazonaws.com/fett263-proffieOS6-style-library.html#Static/Flicker
OS6.5 v1.0
This Style Contains ???? (a lot) Unique Combinations
Style Options:
0: Static Color (Base Color)
1: Audio Flicker (Base Color, Alt Color)
2: Random Flicker (Base Color, Alt Color)
3: BrownNoise Flicker Blade (Base Color)
4: Pulsing (Base Color, Alt Color)
5: Stripes (Base Color)
6: Stripes SlowNoise (Base Color, Alt Color)
7: Stripes Unstable (Base Color)
8: Thunderstorm blade (Base Color, Alt Color)
9: Fett263 Smoke Blade style. (Base Color)
10: Glitchy / Broken blade. (Base Color)
11: DarkSaber (Base Color, Alt Color)
12: Electro Staff Blade (Base Color, Alt Color)
13: Ghost Buster Blade (Base Color, Alt Color, Alt Color 2)
14: Smash Blade (Custom Colors)
15: Fire Blade (Base Color)
16: Coda blade style w/ swing effects. (Base Color, Alt Color, Alt Color 2)
17: Fire Pulse Blade (Interactive, Base Color)
18: Static Electricty (Base Color)
19: Lava Lamp (Base Color)
20: Water Blade (Base Color)
21: Glowstick (Base Color, Alt Color)
22: Rotoscope (Base Color)
23: Omni Blade (All Colors)
24: Rainbow Stripes (All Colors)
25: Rainbow Fire (All Colors)

--Effects Included--
STYLE_OPTION2_ARG options: // Secondary Blade Effects while on
0: Disabled
1: Audio Flicker (Alt Color 2)
2: Random Flicker (Alt Color 2)
3: Blinking (Alt Color 2)
4: Pulsing (Alt Color 2)
5: BrownNoise Stripes (Alt Color 2)
6: HumpFlicker Random (Alt Color 2)
7: Waves (Alt Color, Alt Color 2)
8: Sparkles (Alt Color 2)
9: Fett263 FireBlade (Alt Color 2)
10: Fire (Alt Color, Alt Color 2)
11: Cylon (Alt Color 2)
12: Lightning flash (Alt Color 2)
13: Emitter Fade (Alt Color 2)
14: Blade Tip Flame (Alt Color 2)

STYLE_OPTION3_ARG options: // Tirtiary Blade Effects while on
0: Disabled
1: Audio Flicker (Alt Color 3)
2: Random Flicker (Alt Color 3)
3: Blinking (Alt Color 2)
4: Pulsing (Alt Color 3)
5: BrownNoise Stripes (Alt Color 3)
6: HumpFlicker Random (Alt Color 3)
7: Waves (Alt Color2, Alt Color 3)
8: Sparkles (Alt Color 3)
9: Fett263 FireBlade (Alt Color 3)
10: Fire (Alt Color 2, Alt Color 3)
11: Cylon (Alt Color 3)
12: Lightning Flash (Alt Color 3)
13: Emitter Flare (Emiter Color)
14: Emitter Breathing (Emitter Color)
15: Emitter Pulse (Emitter Color)
16: Emitter Fade (Alt Color 3)
17: Blade Spark (Interactive, Alt Color 3)

Ignition Effect Options (Ignition Color):
0: Instant
1: Standard Ignition
2: Dual Mode Wipe (Up = Fast)
3: SparkTip Ignition
4: Center Wipe
5: Wipe In
6: Fade On
7: Color Cycle
8: Glitch On
9: Gravity Ignition
10: Assemble
11: Lightning Strike
12: Photon
13: Flash
14: Interactive Assemble
15: Metal Forge Heatup

PowerUp Effect Options (Ignition Color):
0: Disabled
1: Glitch On (Power Flash)
2: Power Surge
3: Emitter Flash
4: Power Burst Emitter
5: Power Burst Forward
6: Unstable Power Up Forward
7: Unstable Bright
8: Stabalize

Retraction Effect Options (Retraction Color):
0: Instant
1: Standard Retraction
2: Dual Mode Wipe In (Up = Fast)
3: SparkTip Retraction
4: Center Wipe
5: Wipe Out
6: Fade Off
7: Color Cycle
8: Glitch Off
9: Gravity Retraction
10: Disassemble
11: Blink Off
12: Glowstick
13: Metal Forge Cooldown

CoolDown Effect Options (Retraction Color):
0: Disabled
1: Glitch Off (Flash)
2: Power Burst Reverse
3: Unstable Cool Down Reverse
4: Bright Humpflicker

Swing Effect Options (Swing Color):
0: Disabled
1: Audio Flicker
2: Sparkle
3: Pulsing
4: Fire
5: Ripple (Fett263's)
6: Unstable
7: Bright Edge (Responsive)
8: Pixilate
9: Lightning
10: Rainbow
11: Clash Buildup, Lockup Release
// Force Effects
12: Interactive Power Buildup (Force Toggle)
13: Interactive Fireball (Force Toggle)
14: Force Pulse
15: Force Flash
16: Force Aura
17: Force Flicker Swing
18: Force Heat
19: Interactive Flamethrower (Force Toggle)
20: Force Rage Unstable
21: Force Rage Lightning
22: Interactive Ice Blade
23: Static Electricty Swing

Preon Effect Options (PreOn Color): 
0: Disabled
1: Overload
2: Sparking
3: Emitter Warm up
4: Faulty Ignition
5: Faulty Fire Ignition
6: Erratic
7: Sparking Absorb
8: Force Drain
9: Glowstick
10: Seismic Charge
11: Blade Pre-Light up

PostOff Effect Options (PostOff Color):
0: Disabled
1: Emitter Cooldown
2: Emitter Spark
3: Emitter Glow

Special Abilities:
USER1: Lockup Selection: 0 = Normal, 1 = Clash/Lockup Shield Toggle (DUNE Shield), 2 = Dual Lockup (Two Independent Lockup Humps)			//Hold PWR + Turn Right (parallel or up) = Special Ability 1 (USER1)
USER2: Force Lightning Toggle (Replaces Lightning Block)																					//Hold PWR + Turn Left (parallel or up) = Special Ability 2 (USER2)
USER3: Fireflies																															//Hold PWR + Turn Right (pointing down) = Special Ability 3 (USER3)
USER4: Rain Toggle (Off Color)																												//Hold PWR + Turn Left (pointing down) = Special Ability 4 (USER4)
USER5: Blaster mode?																														//Hold PWR + Turn Right (parallel or up) = Special Ability 5 (USER5)
USER6:																																		//Hold PWR + Turn Left (parallel or up) = Special Ability 6 (USER6)
USER7: Next Phase?																															//Hold PWR + Turn Right (pointing down) = Special Ability 7 (USER7)
USER8: Previous Phase?																														//Hold PWR + Turn Left (pointing down) = Special Ability 8 (USER8)

Lockup Effects (Sequential): 
- Intensity Lockup
- Localized AudioFlicker
- Full Blade AudioFlicker
- Cylon (Oldschool) Lockup

Lockup Start Transitions (Random):
- Real Clash (Intensity)
- Localized Flicker
- Localized Flash/Fade
- Full blade Flash/Fade

Lockup End Transitions (Random):
- Real Clash (Intensity)
- Power Burst Wave
- Localized Absorb Flash
- Full Blade Flash

LightningBlock Effect: 
- Responsive Lightning Block

Drag Effect (Sequential):
- Intensity Sparking
- Fire Spark

Melt Effect (Sequential): 
- Responsive Melt
- Intensity Melt

Blast Effect (Randomly Selected) (Blast Color): 
- Responsive Blast Fade (Random), 
- Responsive Blast Wave (Random), 
- Responsive Blast Ripple Fade (Random)

Clash Effect (Sequential): 
- Real Clash V1
- Responsive Wave
- Responsive Ripple
- Random Clash

Battery Level: Hilt Location (Green to Red) on Boot/FontChange/BatteryLevel

Volume Level: Blade Light (White)

Power Save: 10% Increment
*/

using MasterStyle = Layers<

	ColorSelect<
		IntArg<STYLE_OPTION_ARG, 0>, 
		TrInstant, 

		/*
		BaseStyle_Static,

		BaseStyle_Survivor,

		// Option 12: Fire Blade with Swing Speed and Fire Tip (BASECOLOR)
		BaseStyle_FireTipBlade,
		// Option 13: blablabla
		BaseStyle_FireTipBase,
		*/

		// Option 0: Static Color (BASECOLOR)
		BaseStyle_Static,
		// Option 1: Audioflicker (BASECOLOR, ALTCOLOR)
		BaseStyle_AudioFilter,
		// Option 2: Random Flicker (BASECOLOR, ALTCOLOR)
		BaseStyle_RandomFlicker,
		// Option 3: BrownNoise (BASECOLOR)
		BaseStyle_BrownNoiseFlicker,
		// Option 4: Pulsing Blade (BASECOLOR, ALTCOLOR)
		BaseStyle_Pulsing,
		// Option 5: Stripes (BASECOLOR)
		BaseStyle_Stripes,
		// Option 6: Stripes SlowNoise (BASECOLOR, ALTCOLOR)
		BaseStyle_Stripes_2Color,
		// Option 7: Unstable Stripes (BASECOLOR)
		BaseStyle_Stripes_RandomPerLEDFlicker,
		// Option 8: Thunderstorm (BASECOLOR, ALTCOLOR)
		BaseStyle_ThunderstormBlade,
		// Option 9: Base Fett263 Smoke Blade style (BASECOLOR)
		BaseStyle_SmokeBlade,
		// Option 10: Flickery / Broken Blade (BASECOLOR)
		BaseStyle_FlickerBlade,
		// Option 11: Darksaber Blade (BASECOLOR, ALTCOLOR)
		BaseStyle_DarkSaber,
		// Option 12: ElectroStaff (BASECOLOR)
		BaseStyle_StaffBlade,
		// Option 13: Ghostbuster (BASECOLOR, ALTCOLOR, ALTCOLOR2)
		BaseStyle_GhostBusterBlade,
		// Option 14: Smash Blade (Special Colors)
		BaseStyle_SmashBlade,

		// Option 15: Fire blade (BASECOLOR)
		BaseStyle_FireBlade,
		// Option 16: Coda (BASECOLOR, ALTCOLOR, ALTCOLOR2)
		BaseStyle_CodaBlade,
		// Option 17: Fireblade Interactive Pulse (BASECOLOR)
		BaseStyle_FirePulseInteractive,
		// Option 18: Static Electricty (BASECOLOR)
		BaseStyle_StaticElectricity,
		// Option 19: Lava Lamp (BASECOLOR)
		BaseStyle_LavaLamp,
		// Option 20: Water Blade (BASECOLOR)
		BaseStyle_WaterBlade,
		// Option 21: Glowstick (BASECOLOR, ALTCOLOR)
		BaseStyle_Glowstick,
		// Option 22: Rotoroscope (BASECOLOR)
		BaseStyle_Rotoscope_Responsive,

		// Option 23: Omni Blade
		BaseStyle_Omni_Blade,
		// Option 24: Rainbow Stripes (All Colors)
		BaseStyle_Rainbow_Stripes,
		// Option 25: Rainbow Fire (All Colors)
		BaseStyle_Rainbow_Fire
	>,

	// Secondary blade Styles
	ColorSelect<
		IntArg<STYLE_OPTION2_ARG, 0>,
		TrInstant,
		// Option 0 Off
		TRANSPARENT,
		
		/*
		AltStyle_FireTEST<ALTCOLOR2>,
		AltStyle_Fire<ALTCOLOR, ALTCOLOR2>,
		*/

		// Option 1: AudiFlicker (ALTCOLOR2)
		AltStyle_AudioFilter<ALTCOLOR2>,
		// Option 2: RandomFlicker (ALTCOLOR2)
		AltStyle_RandomFlicker<ALTCOLOR2>,
		// Option 3: Blinking
		AltStyle_Blinking<ALTCOLOR2>,
		// Option 4: Pusling (ALTCOLOR2)
		AltStyle_Pulsing<ALTCOLOR2, SWING_SPEED_DEFAULT, Int<1200>, Int<600>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		// Option 5: BrownNoise Stripes (ALTCOLOR2)
		AltStyle_BrownNoise_Stripes<ALTCOLOR2>,
		// Option 6: HumpFlicker Random (ALTCOLOR2)
		AltStyle_HumpFlicker_Random<ALTCOLOR2>,
		// Option 7: Hump Waves (ALTCOLOR, ALTCOLOR2)
		AltStyle_HumpWave<ALTCOLOR, ALTCOLOR2>,
		// Option 8: Sparkles (ALTCOLOR2)
		AltStyle_Sparkle<ALTCOLOR2>,
		// Option 9: Underlying Fett263 Smoke Blade Fire layer (ALTCOLOR)
		AltStyle_SmokeBlade<ALTCOLOR2, 1>,
		// Option 10: Fire (ALTCOLOR, ALTCOLOR2)
		AltStyle_Fire<ALTCOLOR, ALTCOLOR2>,
		// Option 11: Cylon (ALTCOLOR2)
		AltStyle_Cylon<ALTCOLOR2, 5, 20>,
		// Option 12: Lightning flash (ALTCOLOR2)
		AltStyle_LightningFlash<ALTCOLOR2>,
		// Option 13: Emitter Fade
		AltStyle_Emitter_Fade<ALTCOLOR2>,
		// Option 14: Blade Tip Flame (ALTCOLOR2)
		AltStyle_Blade_Tip_Flame<ALTCOLOR2>

		// Option 4: Random LED Flicker (ALTCOLOR2)
		//AltStyle_RandomPerLEDFlicker<ALTCOLOR2>, // Looks too similar to BownNoise_Stripes.
		// Option 6: StripesX Slownoise (ALTCOLOR2 50%)
		//AltStyle_StripesX_SlowNoise<ALTCOLOR2>, // Stripes doesn't support Transparency.
	>,

	// Tirtiary blade Styles
	ColorSelect<
		IntArg<STYLE_OPTION3_ARG, 0>,
		TrInstant,
		// Option 0 Off
		TRANSPARENT,

		// Option 1: AudiFlicker (ALTCOLOR3)
		AltStyle_AudioFilter<ALTCOLOR3>,
		// Option 2: RandomFlicker (ALTCOLOR3)
		AltStyle_RandomFlicker<ALTCOLOR3>,
		// Option 3: Blinking
		AltStyle_Blinking<ALTCOLOR3, SWING_SPEED_DEFAULT, Int<500>, Int<800>, Int<1200>>,
		// Option 4: Pusling (ALTCOLOR3)
		AltStyle_Pulsing<ALTCOLOR3, SWING_SPEED_DEFAULT, Int<1400>, Int<2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		// Option 5: BrownNoise Stripes (ALTCOLOR3)
		AltStyle_BrownNoise_Stripes<ALTCOLOR3, SWING_SPEED_DEFAULT, Int<2500>, Int<3500>, Int<-1500>, Int<-2500>>,
		// Option 6: HumpFlicker Random (ALTCOLOR3)
		AltStyle_HumpFlicker_Random<ALTCOLOR3, 8, SWING_SPEED_DEFAULT, Int<512>, Int<4096>, Int<400>, Int<800>>,
		// Option 7: Hump Waves (ALTCOLOR3)
		AltStyle_HumpWave<ALTCOLOR2, ALTCOLOR3, SWING_SPEED_DEFAULT, Int<150>, Int<300>, Int<400>, Int<800>, Int<3000>, Int<7000>>,
		// Option 8: Sparkles (ALTCOLOR3)
		AltStyle_Sparkle<ALTCOLOR3>,
		// Option 9: Underlying Fett263 Smoke Blade Fire layer (ALTCOLOR3)
		AltStyle_SmokeBlade<ALTCOLOR3, 2>,
		// Option 10: Fire (ALTCOLOR2, ALTCOLOR3)
		AltStyle_Fire<ALTCOLOR2, ALTCOLOR3, 3>,
		// Option 11: Cylon (ALTCOLOR3)
		AltStyle_Cylon<ALTCOLOR3, 5, -20>,
		// Option 12: Lightning Flash (ALTCOLOR3)
		AltStyle_LightningFlash<ALTCOLOR3>,
		// Option 13: Emitter Flare (EMITTER COLOR)
		AltStyle_Emitter_Flare<EMITTERCOLOR>,
		// Option 14: Timed "breathing" emitter flare (EMITTER COLOR)
		AltStyle_Emitter_Breathe<EMITTERCOLOR>,
		// Option 15: Emitter Pulse (EMITTER COLOR)
		AltStyle_Emitter_Pulse<EMITTERCOLOR>,
		// Option 16: Emitter Fade
		AltStyle_Emitter_Fade<ALTCOLOR3>,
		// Option 17: Blade Angle Flare (ALTCOLOR3)
		AltStyle_Spark_BladeAngle<ALTCOLOR3>

		// Option 4: Random LED Flicker (ALTCOLOR3)
		//AltStyle_RandomPerLEDFlicker<ALTCOLOR3>, // Looks too similar to BrownNoise_Stripes
		// Option 6: StripesX Slownoise
		//AltStyle_StripesX_SlowNoise<ALTCOLOR3>, // Stripes doesn't support Transparency
	>,
	
	// Swing Options/Force Effect options
	ColorSelect<
		IntArg<SWING_OPTION_ARG, 0>, 
		TrInstant, 
		// Option 0: Disabled
		TRANSPARENT,

		// Option 1: AudioFlicker
		Swing_AudioFlicker,
		// Option 2: Sparkle
		Swing_Sparkle,
		// Option 3: Pusling
		Swing_Pulsing,
		// Option 4: Fire
		Swing_Fire,
		// Option 5: Fett263's Swing Effect
		Layers <
			//Fett263 Ripple swing effect
			Swing_FettRipple,

			//Fett263 Bright hard swing effect
			Swing_FettHard
		>,
		// Option 6: Unstable Swing
		Layers <
			//Unstable swing
			Swing_Unstable,
			//Unstable ripple swing
			Swing_UnstableRippple
		>,
		// Option 7: Bright Edge (Responsive)
		Swing_Bright_Edge,
		// Option 8: Pixilate
		Swing_Pixilate,
		// Option 9: Lightning
		Swing_Lightning,
		// Option 10: Rainbow
		Swing_Rainbow,
		// Option 10: Clash Buildup
		Swing_Clash_BuildUp,
		// Option 11: Interactive Power Buildup (Force Toggle)
		Swing_Interactive_Power_Buildup,
		// Option 12: Interactive Fireball (Force Toggle)
		Swing_Interactive_Fireball,
		// Option 13: Force Pulse
		Swing_Force_Pulse,
		// Option 14: Force Flash
		Swing_Force_Flash,
		// Option 15: Force Aura
		Swing_Force_Aura,
		// Option 16: Force Flicker Swing
		Swing_Force_Flicker,
		// Option 17: Force Heat
		Swing_Force_Heat,
		// Option 18: Interactive Flamethrower (Force Toggle)
		Swing_Interactive_Flamethrower,
		// Option 19: Force Rage Unstable
		Swing_Force_Rage_Unstable,
		// Option 20: Force Rage Lightning
		Swing_Force_Rage_Lightning,
		// Option 21: Interactive Ice Blade
		Swing_Interactive_IceBlade,
		// Option 22: Static Electricty Swing
		Swing_Static_Electricity
	>,

	// Powerup Effect
	TransitionEffectL<
		TrSelect<
			IntArg<IGNITION_POWER_UP_ARG, 0>,
			// Option 0: None
			TrInstant, 
			// Option 1: Power Flash
			Powerup_Flash,
			// Option 2: Power Surge (Stable)
			Powerup_Surge,
			// Option 3: Emitter Flash
			Powerup_Flash_Fade,
			// Option 4: Power Burst Emitter
			Powerup_Burst_Emitter,
			// Option 5: Power Burst Forward
			Powerup_Burst_Forward,
			// Option 6: Unstable Power Up Forward
			Powerup_Unstable_Forward,
			// Option 7: Fett263 Unstable bright ignition effect
			Powerup_Unstable_Bright_Forward,
			// Option 8: Stabilize ignition
			Powerup_Stabalize
		>,
		EFFECT_IGNITION
	>,

	// Cooldown effect
	TransitionEffectL<
		TrSelect<
			IntArg<RETRACTION_COOL_DOWN_ARG, 0>,
			// Option 0: None
			TrInstant, 
			// Option 1: Power Flash
			PowerDown_Flash,
			// Option 2: Unstable Cool Down Reverse
			PowerDown_Burst_Reverse,
			// Option 3: Power Burst Reverse
			PowerDown_Unstable_Reverse,
			// Option 4: Fett263 Bright Humpflicker retraction effect
			PowerDown_Bright_Hump
		>,
		EFFECT_RETRACTION
	>,

	// Special Abiltiies
	//EFFECT_USER1: Lockup Selection : 0 = Normal, 1 = Clash / Lockup Shield (DUNE Shield), 2 = Dual Lockup(Two Independent Lockup Humps)
	//EFFECT_USER2: Force Lightning Toggle(Replaces Lightning Block)
	Special_Rain<EFFECT_USER4, 0>,
	Special_Fireflies<EFFECT_USER3>, // Uses SPECIAL 8 for effect triggers
	Special_Phase_Next<EFFECT_USER7>,
	//Special_Phase_Previous<EFFECT_USER8>,
	
	// Multi blast effect
	MultiTransitionEffectL<
		TrSelect<
			// BLASTER Mode
			EffectIncrementF<
				EFFECT_USER5,
				Int<2>
			>,
			// Normal Blasts.
			TrRandom<
				// Blast Fade Random
				Blast_Fade<BLASTPOS_SCALE<>, BLASTFADE_SIZE<>>,

				// Blast Wave Random
				Blast_Wave<BLASTWAVE_SCALE<>, BLASTWAVE_SCALE<>, BLASTWAVE_SCALE<>, BLASTPOS_SCALE<>>,

				// Blast Ripple Fade
				Blast_Ripple_Fade<BLASTRIPPLE_POS<>, Int<6000>, Int<320000>>

			>,
			// Blaster mode
			Blast_Blaster_Shot
		>, 
		EFFECT_BLAST
	>, 
	
	// Clash effect
	EffectSequence<
		EFFECT_USER1,
		// Normal Clash
		Clash_Sequence,
		// DUNE Shield
		Clash_Dune_Shield,
		// Normal Clash
		Clash_Sequence
	>,

	/*
	// Bright flash ripple on CLASH_UPDATE? TEST ME!
	TransitionEffectL<
		TrConcat<
			TrInstant,
			TrWaveX<
				//CLASHCOLOR,
				Rgb<255, 0, 255>, // TEST ME
				Scale<
					ClashImpactF<>,
					Int<100>, 
					Int<400>
				>, 
				Int<100>, 
				Scale<
					ClashImpactF<>,
					Int<100>, 
					Int<400>
				>, 
				LOCKUPPOSITIONSCALE
			>
		>,
		EFFECT_CLASH_UPDATE
	>,
	*/

	// Lockup
	LockupTrL<
		EffectSequence<
			EFFECT_USER1,
			/*
		// Lockup Effect
		ColorSelect<
			EffectIncrementF<
				EFFECT_USER1,
				Int<3>
			>,
			TrInstant,
			*/
			// Dial Mode Lockup using USER1 Special Ability
			Lockup_Color_Dual,
			// Dune Shield Lockup
			Lockup_Color_Shield,
			// Normal Lockup, pick a random effect
			EffectSequence<
				EFFECT_LOCKUP_BEGIN,
				// Intensity Lockup
				Lockup_Color_Intensity,
				// Localized AudioFlicker
				Lockup_Color_Localized_Flicker,
				// Full Blade AudioFlicker
				Lockup_Color_Full_Flicker,
				// Original old Lockup, moves on it's own...
				Lockup_Color_Cylon
			>
		>,
		// EFFECT_LOCKUP_BEGIN
		TrSelect<
			// look for DUNE Shield using USER1 Special Ability
			EffectIncrementF<
				EFFECT_USER1,
				Int<3>
			>,
			// Normal Lockup, pick a random effect
			Lockup_Start_Random,
			// Dune Shield Lockup
			Lockup_Start_Shield,
			// Normal Lockup, pick a random effect
			Lockup_Start_Random
		>,
		// EFFECT_LOCKUP_END
		TrSelect<
			// look for DUNE Shield using USER1 Special Ability
			EffectIncrementF<
				EFFECT_USER1,
				Int<3>
			>,
			// Normal Lockup, pick a random effect
			Lockup_End_Random,
			// Dune Shield Lockup
			Lockup_End_Shield,
			// Normal Lockup, pick a random effect
			Lockup_End_Random
		>,
		SaberBase::LOCKUP_NORMAL
	>,
	
	// Lightning Block
	EffectSequence<
		EFFECT_USER2,
		// Force Lightning
		LockupTrL<
			Lockup_Force_Lightning,
			// Force Lightning Start
			Lockup_Force_Lightning_StartEnd,
			// Force Lightning End
			Lockup_Force_Lightning_StartEnd,
			SaberBase::LOCKUP_LIGHTNING_BLOCK
		>,
		// Normal Lightning Block
		LockupTrL<
			AlphaL<
				LB_Color_Style,
				// LB Positions
				LIGHTNINGBLOCK_RESPONSIVE_POSITION
			>,
			// Start Transition
			LB_Start,
			// End Transition
			LB_End,
			SaberBase::LOCKUP_LIGHTNING_BLOCK
		>
	>,
	/* // Old, kinda hard to do options in.
	ResponsiveLightningBlockL<
		LB_Color_Style,
		LB_Start,
		LB_End
	>
	*/
	
	// Drag
	LockupTrL<
		EffectSequence<
			EFFECT_DRAG_BEGIN,
			Drag_Color_Sparking,
			Drag_Color_Fire
		>,
		TrSequence<
			Drag_Start_Sparking,
			Drag_Start_Fire
		>,
		Drag_End, // EFFECT_DRAG_END
		SaberBase::LOCKUP_DRAG
	>,

	// Stab
	ResponsiveStabL<
		EffectSequence<
			EFFECT_STAB,
			Stab_Color_Normal,
			Stab_Color_AudioFlicker,
			Stab_Color_Style3
		>,
		Stab_Start,
		Stab_End,

		MELT_SIZE,
		Sum<
			MELT_SIZE,
			Int<2000>
		>	
	>,
	/* // Non Responsive Stab Effect
	TransitionEffectL<
		TrConcat<
			Stab_Start,
			EffectSequence<
				EFFECT_STAB,
				Stab_Color_Normal,
				Stab_Color_AudioFlicker,
				Stab_Color_Style3
			>,
			Stab_End,
		>,
		EFFECT_STAB
	>,
	*/
	
	// Melt
	LockupTrL<
		EffectSequence<
			EFFECT_LOCKUP_BEGIN,
			// Responsive Melt
			Melt_Color_Responsive, 
			// Intensity Melt
			Melt_Color_Intensity
		>,
		TrSequence<
			// Standard Start
			Melt_Start, 
			// Intensity Start
			Melt_Start_Intensity
		>,
		Melt_End, 
		SaberBase::LOCKUP_MELT
	>,
	
	// Interactive Blast, Random
	Blast_Interactive_Control<EFFECT_USER5, Int<1000>>,

	// In/Out
	InOutTrL<
		// Ignition Options
		TrSelect<
			IntArg<IGNITION_OPTION_ARG, 0>, 
			// Option 0: Instant, for letting the PreOn do the work
			TrInstant, 

			// Option 1: Standard
			Ignition_Standard,
			// Option 2: Dual Mode wip (up = fast)
			Ignition_DualMode,
			// Option 3: Spark Tip
			Ignition_SparkTip, 
			// Option 4: Center Wipe
			Ignition_CenterWipe,
			// Option 5: Wipe In
			Ignition_WipeIn,
			// Option 6: Fade On
			Ignition_Fade_On,
			// Option 7: Color Cycle
			Ignition_ColorCycle,
			// Option 8: Glitch On
			Ignition_Glitch_On,
			// Option 9: Gravity based
			Ignition_Gravity,
			// Option 10: Assemble (Stack)
			Ignition_Assemble,
			// Option 11: Lightning Strike
			Ignition_LightningStrike,
			// Option 12: Photon Ignition
			Ignition_Photon,
			// Option 13: Flash On
			Ignition_Flash,
			// Option 14: Assemble Interactive
			Ignition_Stack_Interactive,
			// Option 15: Metal Forge Heatup
			Ignition_Metal_Forge_Heatup
		>, 
		// Retraction Options
		TrSelect<
			IntArg<RETRACTION_OPTION_ARG, 0>, 
			// Option 0: Instant, for letting PostOff do the work
			TrInstant, 

			// Option 1: Standard
			Retraction_Standard,
			// Option 2: Dual Mode
			Retraction_DualMode,
			// Option 3: Spark tip.
			Retraction_SparkTip,
			// Option 4: Center Wipe
			Retraction_CenterWipe,
			// Option 5: Wipe Out
			Retraction_WipeOut,
			// Option 6: Fade off
			Retraction_Fade_Off,
			// Option 7, Color cycle
			Retraction_ColorCycle,
			// Option 8, Glitch off
			Retraction_Glitch_Off,
			// Option 9: Gravity based
			Retraction_Gravity,
			// Option 10: Disassemble
			Retraction_Disassemble,
			// Option 11: Blink off
			Retraction_Blink_Off,
			// Option 12: Glow stick
			Retraction_Glowstick,
			// Option 13: Metal Forge Cooldown
			Retraction_Metal_Forge_Cooldown
		>, 
		Black
	>,

	// Pre On
	TransitionEffectL<
		TrSelect<
			IntArg<PREON_OPTION_ARG, 0>, 
			// Option 0: None
			TrInstant,

			// Option 1: Overload
			PreOn_Overload,
			// Option 2: Sparking
			PreOn_Sparking,
			// Option 3: Emitter Warm up
			PreOn_Emitter_Warmup, //PreOn_Emitter_Heatup,
			// Option 4: Faulty Ignition
			PreOn_Faulty_Ignition, //PreOn_Faulty_Ignition_Volatile,
			// Option 5: Faulty Fire Ignition
			PreOn_Faulty_Ignition_Fire,
			// Option 6: Erratic
			PreOn_Erratic,
			// Option 7: Sparking Absorb
			PreOn_Sparking_Absorb,
			// Option 8: Force Drain
			PreOn_Force_Drain,
			// Option 9: Glowstick
			PreOn_Glowstick,
			// Optoin 10: Seismic Charge
			PreOn_Seismic_Charge,
			// Option 11: Dim Pre-Blade Extension
			PreOn_Dim_Blade
		>, 
		EFFECT_PREON
	>,

	// Post Off
	TransitionEffectL<
		TrSelect<
			IntArg<OFF_OPTION_ARG, 0>,
			// Option 0 // None
			TrInstant, 

			// Option 1: Emitter Cooldown
			PostOff_EmitterCoolOff,
			// Option 2: Emitter Spark
			PostOff_Emitter_Spark,
			// Option 3: Emitter Glow
			PostOff_Emitter_Glow
		>,
		EFFECT_POSTOFF
	>,

	// Special Ability Toggle effects
	//Special_ToggleFlash<EFFECT_USER1, Green>,
	//Special_ToggleFlash<EFFECT_USER2, Red>,
	//Special_ToggleFlash<EFFECT_USER3, Blue>,
	//Special_ToggleFlash<EFFECT_USER4, Yellow>,
	//Special_ToggleFlash<EFFECT_USER5, Green>,
	//Special_ToggleFlash<EFFECT_USER6, Red>,
	//Special_ToggleFlash<EFFECT_USER7, Blue>,
	//Special_ToggleFlash<EFFECT_USER8, Yellow>,
	Special_ToggleAudio<EFFECT_USER1, 1>,
	Special_ToggleAudio<EFFECT_USER2, 1>,
	Special_ToggleAudio<EFFECT_USER3, 1>,
	Special_ToggleAudio<EFFECT_USER4, 1>,
	Special_ToggleAudio<EFFECT_USER5, 1>,
	Special_ToggleAudio<EFFECT_USER6, 1>,
	Special_ToggleAudio<EFFECT_USER7, 1>,
	//Special_ToggleAudio<EFFECT_USER8>, // Used for Special 3 firefly effect
	
	// Battery Monitor on Boot
	BatteryLevelOnBoot,

	// Battery level on font change
	BatteryLevelOnFontChange,

	// Battery level
	BatteryLevelOnDemand,

	// Volume level
	VolumeLevelOnDemand,

	// Power Saver
	Battery_Power_Save
>;