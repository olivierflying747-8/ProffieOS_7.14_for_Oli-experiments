// ===================== IGNITION STYLES =======================

// Standard
using Ignition_Standard = TrWipeX<
	BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
>;

// Dual Mode Wipe (up = fast)
using Ignition_DualMode = TrWipeX<
	BEND_TIME<
		Scale<
			IsLessThan<
				BladeAngle<>, 
				PERCENTAGE_S<50> //Int<16384>
			>, 
			Mult<
				IGNITION_TIME, 
				PERCENTAGE_S<50> //Int<16384>
			>, 
			IGNITION_TIME
		>,
		IGNITION_OPTION2
	>
>;

// Spark Tip
using Ignition_SparkTip = TrWipeSparkTipX<
	IGNITIONCOLOR,
	BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
>;

// Center Wipe
using Ignition_CenterWipe = TrCenterWipeInX<
	BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>,
	PERCENTAGE_S<50> //Int<16384>
>;

// Wipe In (Reverse)
using Ignition_WipeIn = TrWipeInX<
	BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
>;

// Color Cycle
using Ignition_ColorCycle = TrColorCycleX<
	BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>, //Percentage<IGNITION_TIME, 1000>, //3000,
	3000,
	0
>;

// Fade On
using Ignition_Fade_On = TrFadeX<
	BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
>;

// Glitch On
using Ignition_Glitch_On = TrConcat<
	TrJoin<
		TrDelayX<
			BEND_TIME<
				Mult<
					IGNITION_TIME,
					PERCENTAGE_S<50> //Int<16384>
				>,
				IGNITION_OPTION2
			>
		>,
		TrWipeX<
			BEND_TIME<
				Mult<
					IGNITION_TIME,
					PERCENTAGE_S<50> //Int<16384>
				>,
				IGNITION_OPTION2
			>
		>
	>,
	COLOR_MIX<
		SmoothStep<
			NoisySoundLevel,
			Int<-1>
		>,
		IGNITIONCOLOR
	>,
	TrWipeX<
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				PERCENTAGE_S<50> //Int<16384>
			>,
			IGNITION_OPTION2
		>
	>
>;

// Ignition Gravity
using Ignition_Gravity = TrSelect<
	Scale<
		IsLessThan<
			BladeAngle<>,
			Int<18384>
		>,
		Scale<
			IsGreaterThan<
				SwingAcceleration<>,
				PERCENTAGE_S<50> //Int<16384>
			>,
			Int<0>,
			Int<2>
		>,
		Int<1>
	>,
	TrWipeInX<
		BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
	>,
	TrWipeX<
		BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
	>,
	TrWipe<100>
>;

// Lighting Strike
using Ignition_LightningStrike = TrConcat<
	TrWipeInX<
		BEND_TIME<
			Percentage<IGNITION_TIME, 66>,
			IGNITION_OPTION2
		>
	>, //200>
	RandomBlinkX<
//		BEND_TIME<
			Percentage<IGNITION_TIME, 10000>, //30000,
//			IGNITION_OPTION2
//		>,
		RotateColorsX<Variation, IGNITIONCOLOR>
	>,
	TrWipeInX<
		BEND_TIME<
			Percentage<IGNITION_TIME, 66>,
			IGNITION_OPTION2
		>
	>, //200>,
	COLOR_MIX<
		SmoothStep<
			Scale<
				SlowNoise<Int<30000>>,
				Int<1000>,
				Int<6000>
			>,
			Int<-3000>
		>,
		RotateColorsX<Variation, IGNITIONCOLOR>
	>,
	TrDelayX<
		BEND_TIME<
			Percentage<IGNITION_TIME, 130>,
			IGNITION_OPTION2
		>
	>, //400>,
	COLOR_MIX<
		SmoothStep<
			Int<4000>,
			Int<-3000>
		>,
		White
	>,
	TrWipeSparkTipX<
		IGNITIONCOLOR,
		BEND_TIME<
			Percentage<IGNITION_TIME, 58>,
			IGNITION_OPTION2
		>
	> //175>
>;

// Metal Forge Heatup
using Ignition_Metal_Forge_Heatup = TrConcat<
	TrFadeX<
		BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
	>,
	Red,
	TrFadeX<
		BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
	>,
	DarkOrange,
	TrFadeX<
		BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
	>,
	White,
	TrFadeX<
		BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
	>
>;

// Flash On
using Ignition_Flash = TrConcat<
	TrWipeX<BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>>,
	StrobeL<IGNITIONCOLOR, Int<100>, IGNITION_TIME>,
	TrFadeX<BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>>
>;

// Interactive Stack (5 Swings)
using Ignition_Stack_Interactive = TrConcat<
	TrJoin<
		TrDelay<30000>,
		TrInstant
	>,
	AlphaL<
		Black,
		SmoothStep<
			IncrementWithReset<
				ThresholdPulseF<
					SwingSpeed<400>,
					Int<18000>
				>,
				EffectPulseF<EFFECT_IGNITION>,
				Int<33000>,
				Int<6600>
			>,
			Int<0>
		>
	>,
	TrWipeX<
		BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
	>
>;

// TODO: Incorperate BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
// Assemble
using Ignition_Assemble = TrConcat<
	TrSparkX<
		IGNITIONCOLOR,
		Int<100>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<6554> //20%
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	AlphaL<
		Black,
		SmoothStep<
			Int<6554>,
			Int<0>
		>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<100>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<6554>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	AlphaL<
		Black,
		SmoothStep<
			Int<13108>,
			Int<0>
		>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<100>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<6554>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	AlphaL<
		Black,
		SmoothStep<
			Int<19662>,
			Int<0>
		>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<100>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<6554>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	AlphaL<
		Black,
		SmoothStep<
			Int<26216>,
			Int<0>
		>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<100>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<6554>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>
>;

// Photon Ignition
using Ignition_Photon = TrConcat<
	TrSparkX<
		IGNITIONCOLOR,
		Int<200>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<4096>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	Black,
	TrSparkX<
		IGNITIONCOLOR,
		Int<200>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<4096>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<200>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<4096>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<200>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<4096>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<200>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<4096>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<200>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<4096>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<200>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<4096>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	TrSparkX<
		IGNITIONCOLOR,
		Int<200>,
		BEND_TIME<
			Mult<
				IGNITION_TIME,
				Int<4096>
			>,
			IGNITION_OPTION2
		>,
		Int<32768>
	>,
	// Now wipe
	TrWipeSparkTipX<
		IGNITIONCOLOR,
		BEND_TIME<IGNITION_TIME, IGNITION_OPTION2>
	>
>;