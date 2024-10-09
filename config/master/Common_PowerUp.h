// ===================== POWER UP STYLES =======================

// Flash
using Powerup_Flash = TrConcat<
	TRANSITION_DELAY<IGNITION_TIME, IGNITION_DELAY>,
	IGNITIONCOLOR,
	TrFadeX<POWERUP_TIME>
>;

// Surge
using Powerup_Surge = TrConcat<
	TRANSITION_DELAY<IGNITION_TIME, IGNITION_DELAY>,
	AudioFlickerL<IGNITIONCOLOR>,
	TrFadeX<POWERUP_TIME>
>;

// Emitter Flash Fade
using Powerup_Flash_Fade = TrConcat<
	TRANSITION_DELAY<IGNITION_TIME, IGNITION_DELAY>,
	AlphaL<
		AudioFlicker<
			IGNITIONCOLOR, //Blue,
			COLOR_MIX_P<50,	IGNITIONCOLOR> //SteelBlue
		>,
		Bump<
			Int<0>,
			EMITTER_SIZE //Int<8000>
		>
	>,
	TrFadeX<POWERUP_TIME>
>;

// Power Burst Emitter
using Powerup_Burst_Emitter = TrConcat<
	TRANSITION_DELAY<IGNITION_TIME, IGNITION_DELAY>,
	AlphaL<
		StripesX<
			//Int<5000>, 
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<5000>, Int<2500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			//Int<-2500>, 
			BLADE_ANGLE_SCLAE<Int<-2500>, Int<-1500>, Int<500>, Int<4000>>,

			IGNITIONCOLOR,
			COLOR_MIX<Int<7710>, IGNITIONCOLOR>, 
			COLOR_MIX<Int<3855>, IGNITIONCOLOR>
		>,
		Bump<
			Int<0>,
			EMITTER_SIZE
		>
	>,
	TrFadeX<POWERUP_TIME>
>;

// Power Burst Forward
using Powerup_Burst_Forward = TrConcat<
	TRANSITION_DELAY<IGNITION_TIME, IGNITION_DELAY>,
	StripesX<
		//Int<5000>, 
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<5000>, Int<2500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<-2500>, 
		BLADE_ANGLE_SCLAE<Int<-2500>, Int<-1500>, Int<500>, Int<4000>>,

		IGNITIONCOLOR, 
		COLOR_MIX<Int<7710>, IGNITIONCOLOR>, 
		COLOR_MIX<Int<3855>, IGNITIONCOLOR>
	>,
	TrFadeX<POWERUP_TIME>
>;

// Unstable Powerup Forward
using Powerup_Unstable_Forward = TrConcat<
	TRANSITION_DELAY<IGNITION_TIME, IGNITION_DELAY>,
	StripesX<
		//Int<3000>, 
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<-3500>, 
		BLADE_ANGLE_SCLAE<Int<-3500>, Int<-2000>, Int<500>, Int<4000>>,

		IGNITIONCOLOR, 
		RandomPerLEDFlicker<
			COLOR_MIX<Int<7710>, IGNITIONCOLOR>, 
			Black
		>, 
		BrownNoiseFlicker<
			IGNITIONCOLOR, 
			COLOR_MIX<Int<3855>, IGNITIONCOLOR>,
			200
		>, 
		RandomPerLEDFlicker<
			COLOR_MIX<Int<3137>, IGNITIONCOLOR>,
			COLOR_MIX<Int<3855>, IGNITIONCOLOR>
		>
	>, 
	TrFadeX<POWERUP_TIME>
>;

// Unstable Powerup Bright Forward
using Powerup_Unstable_Bright_Forward = TrConcat<
	TRANSITION_DELAY<IGNITION_TIME, IGNITION_DELAY>,
	StripesX<
		//Int<3000>,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<-3500>,
		BLADE_ANGLE_SCLAE<Int<-3500>, Int<-2000>, Int<500>, Int<4000>>,

		RotateColorsX<Variation, IGNITIONCOLOR>, //Rgb<100,100,150> //IGNITION_COLOR_ARG
		RandomPerLEDFlicker<
			RotateColorsX<Variation, COLOR_MIX_P<50, IGNITIONCOLOR>>, //Rgb<60,60,80> //IGNITION_COLOR_ARG / 2
			Black
		>,
		BrownNoiseFlicker<
			RotateColorsX<Variation, COLOR_MIX_P<25, IGNITIONCOLOR, White>>, //Rgb<110,115,140>  //IGNITION_COLOR_ARG + 25% white?
			RotateColorsX<Variation, COLOR_MIX_P<50, IGNITIONCOLOR>>, //Rgb<60,60,80> // IGNITION_COLOR_ARG / 2
			200
		>,
		RandomPerLEDFlicker<
			RotateColorsX<Variation, Rgb<127,127,127>>,  // White flicker
			RotateColorsX<Variation, COLOR_MIX_P<50, IGNITIONCOLOR>> //Rgb<60,60,80> // IGNITION_COLOR_ARG / 2
		>
	>,
	TrFadeX<
		Percentage<POWERUP_TIME, 65>
	>
>;

// Stabalize
using Powerup_Stabalize = TrConcat<
	TRANSITION_DELAY<IGNITION_TIME, IGNITION_DELAY>,
	Ignition_Flicker_Stripes,
	TrFadeX<Percentage<IGNITION_TIME, 133>>, //400>
	Ignition_Flicker_Stripes,
	TrFadeX<Percentage<IGNITION_TIME, 150>>, //450>
	HumpFlickerL<
		AlphaL<
			RotateColorsX<Variation, IGNITIONCOLOR>, //Rgb<90,180,255> // IGNITION_COLOR_ARG
			Int<19000>
		>,
		25
	>,
	TrFadeX<Percentage<POWERUP_TIME, 300>> //2875>
>;