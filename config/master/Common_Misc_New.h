// ================================ COMMON CODE ===========================

// DEFAULT SwingSpeed<> threshold used
const int SWING_SPEED_DEFAULT = 400;

// EDIT MODE Argument Defaults
using LOCKUP_POSITION = IntArg<LOCKUP_POSITION_ARG, 16000>;
using EMITTER_SIZE = IntArg<EMITTER_SIZE_ARG, 10000>;
using DRAG_SIZE = IntArg<DRAG_SIZE_ARG, 28000>;
using MELT_SIZE = IntArg<MELT_SIZE_ARG, 28000>;
using PREON_SIZE = IntArg<PREON_SIZE_ARG, 4000>;
using IGNITION_OPTION2 = IntArg<IGNITION_OPTION2_ARG, 10992>;
using RETRACTION_OPTION2 = IntArg<RETRACTION_OPTION2_ARG, 10992>;
using IGNITION_DELAY = IntArg<IGNITION_DELAY_ARG, 0>;
using RETRACTION_DELAY = IntArg<RETRACTION_DELAY_ARG, 0>;

// Default Ignition time = WavLen().
using IGNITION_TIME = IgnitionTime<300>; //0
using RETRACTION_TIME = RetractionTime<0>;
using POWERUP_TIME = WavLen<EFFECT_IGNITION>;
using COOLDOWN_TIME = WavLen<EFFECT_RETRACTION>;

// Simple Percentage
template<int PERCENT>
using PERCENTAGE_S = Percentage<Int<32768>, PERCENT>;

// Transition Delay function
template<class DELAY1, class DELAY2>
using TRANSITION_DELAY = TrJoin<
	TrDelayX<DELAY1>,
	TrDelayX<DELAY2>,
	TrInstant
>;

// Bend Time function
template<class TIME, class ARG>
using BEND_TIME = BendTimePowInvX<
	TIME,
	Mult<
		ARG,
		Int<98304>
	>
>;

// Blade Angle Scale
template<class MIN = Int<-50>, class MAX = Int<-2000>, class HOLD_TIME = Int<0>, class HOLD_SPEED = Int<0>, int MIN_BLADE = 0, int MAX_BLADE = 32768>
using BLADE_ANGLE_SCLAE = Scale<
	HoldPeakF<
		BladeAngle<MIN_BLADE, MAX_BLADE>,
		HOLD_TIME, // HOLD_TIME_MS
		HOLD_SPEED // TRANSITION SPEED
	>,
	MIN,
	MAX
>;

// Swing Speed Scale with HoldPeak. HoldPeak defaults to 0 so it doesn't hold.
template<int SPEED = SWING_SPEED_DEFAULT, class MIN = Int<-50>, class MAX = Int<-2000>, class HOLD_TIME_MIN = Int<0>, class HOLD_TIME_MAX = Int<0>, class HOLD_SPEED_MIN = Int<0>, class HOLD_SPEED_MAX = Int<0>>
using SWING_SPEED_SCLAE = Scale<
	HoldPeakF<
		SwingSpeed<SPEED>,
		//SwingAcceleration<250>,
		//TwistAcceleration<250>,
		//TwistAngle<>,
		//BladeAngle<>
		//ClashImpactF<>

		//HOLD_TIME
		Scale<
			SwingSpeed<SPEED>,
			HOLD_TIME_MIN,
			HOLD_TIME_MAX
		>,
		//HOLD_SPEED
		Scale<
			SwingSpeed<SPEED>,
			HOLD_SPEED_MIN,
			HOLD_SPEED_MAX
		>
	>,
	MIN,
	MAX
>;

// Swing Speed Scale (LessThan)
template<int COMPARE_SPEED = SWING_SPEED_DEFAULT, int SCALE_SPEED = COMPARE_SPEED, class THRESHOLD = Int<13600>, class MIN = Int<-19300>, class MAX = Int<32768>>
using SWING_SPEED_LESS_THAN = Scale<
	IsLessThan<
		SwingSpeed<COMPARE_SPEED>,
		THRESHOLD
	>,
	Scale<
		SwingSpeed<SCALE_SPEED>,
		MIN,
		MAX
	>,
	Int<0>
>;

// Basic Center position based on blade angle.
using LOCKUPPOSITIONCENTER = Scale<
	BladeAngle<0, 16000>, 
	Sum<
		LOCKUP_POSITION, 
		Int<-12000>
	>, 
	Sum<
		LOCKUP_POSITION, 
		Int<10000>
	>
>;

// Blade Angle / Lockup Position.
using LOCKUPPOSITIONSCALE = Scale<
	BladeAngle<>, 
	LOCKUPPOSITIONCENTER,
	Sum<
		LOCKUP_POSITION, 
		Int<-10000>
	>
>;

// Blade Angle / Lockup Position Scale with SwingSpeed.
using LOCKUPPOSITIONSWING = Scale<
	BladeAngle<>,
	LOCKUPPOSITIONCENTER,
	Scale<
		SwingSpeed<100>,
		Int<14000>,
		Int<18000>
	>
>;

// Lockup Clash Impact Color
using LOCKUPCLASHCOLOR = Mix<
	IsLessThan<
		ClashImpactF<>, 
		Int<26000>
	>, 
	LOCKUPCOLOR, 
	AlphaL<
		LOCKUPCOLOR, 
		Bump<
			LOCKUPPOSITIONSCALE,
			Scale<
				ClashImpactF<>, 
				Int<20000>, 
				Int<60000>
			>
		>
	>
>;

// Random blast effect selector
using BLAST_SELECT_EFFECT = EffectRandomF<EFFECT_BLAST>;

// Blast Position Scale
using BLASTPOS_ANGLE = BladeAngle<>;
using BLASTPOS_RANDOM = EffectRandomF<EFFECT_BLAST>;

// Blast Position Scale
using BLASTPOS_SCALE = Scale<
    BLASTPOS_ANGLE,
	Int<28000>,
	Int<8000>
>;

// Blast Fade Size
using BLASTFADE_SIZE = Scale<
    BLASTPOS_RANDOM,
	Int<9000>,
	Int<15000>
>;

// Blast Wave Fadeout / Time
using BLASTWAVE_SCALE = Scale<
    BLASTPOS_ANGLE,
	Int<100>,
	Int<400>
>;

// Blast Ripple Position
using BLASTRIPPLE_POS = Scale<
    BLASTPOS_RANDOM,
	Int<3000>,
	Int<29000>
>;

// Lightning Block Position Function
using LIGHTNINGBLOCK_RESPONSIVE_POSITION = LayerFunctions<
	 Bump<
		Scale<
			SlowNoise<	
				Scale<
					BladeAngle<24000, 32768>,
					Int<2100>,
					Int<1000>
				>
			>,
			Scale<
				BladeAngle<24000, 32768>,
				Int<3000>,
				Int<10000>
			>,
			Int<16000>
		>,
		Scale<
			BrownNoiseF<Int<10>>,
			Scale<
				TwistAngle<>,
				Int<4000>,
				Int<10000>
			>,
			Scale<
				TwistAngle<>,
				Int<9000>,
				Int<14000>
			>
		>
	>,
	Bump<
		Scale<
			SlowNoise<Int<2200>>,
			Scale<
				BladeAngle<24000, 32768>,
				Int<26000>,
				Int<18000>
			>,
			Int<8000>
		>,
		Scale<
			NoisySoundLevel,
			Scale<
				TwistAngle<>,
				Int<6000>,
				Int<10000>
			>,
			Scale<
				TwistAngle<>,
				Int<10000>,
				Int<14000>
			>
		>
	>,
	Bump<
		Scale<
			SlowNoise<Int<2300>>,
			Scale<
				BladeAngle<24000, 32768>,
				Int<20000>,
				Int<16000>
			>,
			Scale<
				BladeAngle<24000, 32768>,
				Int<30000>,
				Int<24000>
			>
		>,
		Scale<
			IsLessThan<
				SlowNoise<Int<2000>>,
				Int<12000>
			>,
			Scale<
				NoisySoundLevel,
				Scale<
					TwistAngle<>,
					Int<9000>,
					Int<5000>
				>,
				Int<0>
			>,
			Int<0>
		>
	>
>;

// Ignition Flicker Stripes, used in Stabalize Ignition.
using Ignition_Flicker_Stripes = StripesX<
	//Int<3000>,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
	//Int<-3500>,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-2500>, Int<-3500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
	RotateColorsX<Variation, IGNITIONCOLOR>, //Rgb<90,180,255> //IGNITION_COLOR_ARG
	RandomPerLEDFlicker<
		RotateColorsX<
			Variation,
			COLOR_MIX<Int<7710>, IGNITIONCOLOR> //Rgb<0,26,60> // IGNITION_COLOR_ARG / 4.25
		>,
		Black
	>,
	BrownNoiseFlicker<
		RotateColorsX<Variation, IGNITIONCOLOR>, //Rgb<90,180,255> //IGNITION_COLOR_ARG
		RotateColorsX<
			Variation,
			COLOR_MIX<Int<7710>, IGNITIONCOLOR> //Rgb<0,26,60> //IGNITION_COLOR_ARG / 4.25
		>,
		200
	>,
	RandomPerLEDFlicker<
		RotateColorsX<
			Variation,
			COLOR_MIX<Int<16384>, IGNITIONCOLOR> //Rgb<0,42,128> // IGNITION_COLOR_ARG / 2
		>,
		RotateColorsX<
			Variation,
			COLOR_MIX<Int<7710>, IGNITIONCOLOR> //Rgb<0,26,60> // IGNITION_COLOR_ARG / 4.25
		>
	>
>;


// Random Spark
template<class COLOR, class POSITION = Int<0>, class SPEED = Int<250>, class SPARK_SIZE_MIN = Int<200>, class SPARK_SIZE_MAX = Int<600>, class MIN_DELAY = Int<200>, class MAX_DELAY = Int<600>, class FADE_TIME = Int<100>, class BOING_TIME = Int<500>>
using TrSparkX_Random = TransitionLoopL<
	TrConcat<
		TrBoingX<BOING_TIME, 3>,
		TrConcat<
			TrFadeX<FADE_TIME>,
			TrSparkX<
				COLOR,
				Scale<
					NoisySoundLevel,
					SPARK_SIZE_MIN,
					SPARK_SIZE_MAX
				>,
				SPEED,
				POSITION
			>,
			TrFadeX<FADE_TIME>
		>,
		TrDelayX< // Random Timer
			Scale<
				RandomF,
				MIN_DELAY,
				MAX_DELAY
			>
		>
	>
>;

// ShowBatteryLevelHilt
using ShowBatteryLevelHilt = TrConcat<
	TrDelay<1500>,
	Black,
	TrFade<1000>,
	AlphaL<
		Mix<
			BatteryLevel,
			Red,
			Green
		>,
		Bump<
			Int<0>, //BatteryLevel
			EMITTER_SIZE //Int<12000>
		>
	>,
	TrFade<3000>
>;

// Battery Monitor on Boot
using BatteryLevelOnBoot = TransitionEffectL<
	ShowBatteryLevelHilt,
	EFFECT_BOOT
>;

// Battery level on font change
using BatteryLevelOnFontChange = TransitionEffectL<
	ShowBatteryLevelHilt,
	EFFECT_NEWFONT
>;

// Battery level
using BatteryLevelOnDemand = TransitionEffectL<
	ShowBatteryLevelHilt,
	EFFECT_BATTERY_LEVEL
>;

// Volume level
using VolumeLevelOnDemand = TransitionEffectL<
	TrConcat<
		TrExtend<
			2000,
			TrFade<100>
		>,
		AlphaL<
			White,
			Bump<
				VolumeLevel,
				Int<8000>
			>
		>,
		TrFade<300>
	>,
	EFFECT_VOLUME_LEVEL
>;

// Power Save (10% increments)
using Battery_Power_Save = EffectSequence<
	EFFECT_POWERSAVE,
	AlphaL<Black,Int<3277>>,
	AlphaL<Black,Int<6554>>,
	AlphaL<Black,Int<9831>>,
	AlphaL<Black,Int<13108>>,
	AlphaL<Black,Int<16385>>,
	AlphaL<Black,Int<19662>>,
	AlphaL<Black,Int<22939>>,
	AlphaL<Black,Int<26216>>,
	AlphaL<Black,Int<29493>>,
	AlphaL<Black,Int<0>>
>;
