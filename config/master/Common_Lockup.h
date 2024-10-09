// ================================ LOCKUP COLORS ================================

// Lockup Color used in intensity/responsive style
using Lockup_Color_Intensity_ColorMix = AlphaMixL<
	// Mix method
	Bump<
		LOCKUPPOSITIONSCALE,
		Scale<
			SwingSpeed<100>, 
			Int<14000>, 
			Int<18000>
		>
	>, 
	// Color A
	BrownNoiseFlickerL<
		LOCKUPCOLOR, 
		Int<200>
	>, 
	// Color B
	StripesX<
		Int<1800>, 
		Scale<
			NoisySoundLevel, 
			Int<-3500>, 
			Int<-5000>
		>, 
		COLOR_MIX<Int<6425>, LOCKUPCOLOR>, 
		LOCKUPCOLOR, 
		COLOR_MIX<Int<12850>, LOCKUPCOLOR>
	>
>;
// Lockup Intensity/Responsive
using Lockup_Color_Intensity = TransitionEffect<
	Lockup_Color_Intensity_ColorMix,
	AlphaL<
		AudioFlicker<
			LOCKUPCOLOR,
			COLOR_MIX<Int<10280>, LOCKUPCOLOR>
		>,
		Bump<
			LOCKUPPOSITIONSCALE,
			Int<13000>
		>
	>,
	TrJoin<
		TrDelay<8000>,
		TrInstant
	>,
	TrFade<3000>,
	EFFECT_LOCKUP_BEGIN
>;

// Lockup Localized Flicker
using Lockup_Color_Localized_Flicker = Layers<
	AlphaL<
		AudioFlickerL<LOCKUPCOLOR>,
		Bump<
			LOCKUPPOSITIONSCALE,
			Scale<
				SwingSpeed<100>,
				Int<14000>,
				Int<18000>
			>
		>
	>,
	AlphaL<
		LOCKUPCOLOR,
		Bump<
			LOCKUPPOSITIONSCALE,
			Int<10000>
		>
	>
>;

// Original Moving Lockup Style
using Lockup_Color_Cylon = AlphaMixL<
	Bump<
		Sin<
			Int<12>,
			Sum<
				LOCKUP_POSITION,
				Int<-8000>
			>,
			Sum<
				LOCKUP_POSITION,
				Int<8000>
			>
		>,
		Scale<
			SwingSpeed<100>,
			Int<14000>,
			Int<18000>
		>
	>,
	AudioFlickerL<
		LOCKUPCOLOR
	>,
	BrownNoiseFlickerL<
		LOCKUPCOLOR,
		Int<200>
	>
>;

// Dual Lockup Style
using Lockup_Color_Dual = TransitionEffect<
	Layers<
		// Color Hump 1
		AlphaMixL<
			//Mix Method
			Bump<
				// Position (Move up/down with blade, min/max at middle)
				Scale<
					BladeAngle<>,
					Scale<
						BladeAngle<0,16000>,
						Sum<
							IntArg<LOCKUP_POSITION_ARG, 16000>,
							Int<-12000>
						>,
						Sum<
							IntArg<LOCKUP_POSITION_ARG, 16000>,
							Int<10000>
						>
					>,
					Sum<
						IntArg<LOCKUP_POSITION_ARG, 16000>,
						Int<-10000>
					>
				>,
				// Size
				Scale<
					TwistAngle<>, //SwingSpeed<100>,
					Int<14000>,
					Int<18000>
				>
			>,
			// Color A
			BrownNoiseFlickerL<
				RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>,
				Int<200>
			>,
			// Color B
			StripesX<
				Int<1800>,
				Scale<
					NoisySoundLevel,
					Int<-3500>,
					Int<-5000>
				>,
				Mix<
					Int<6425>,
					Black,
					RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>
				>,
				RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>,
				Mix<
					Int<12850>,
					Black,
					RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>
				>
			>
		>,
	// Color Hump 2
		AlphaMixL<
			//Mix Method
			Bump<
				// Position
				Scale<
					InvertF<BladeAngle<>>,
					Scale<
						InvertF<BladeAngle<16000, 32000>>,
						Sum<
							IntArg<LOCKUP_POSITION_ARG, 16000>,
							Int<12000>
						>,
						Sum<
							IntArg<LOCKUP_POSITION_ARG, 16000>,
							Int<-10000>
						>
					>,
					Sum<
						IntArg<LOCKUP_POSITION_ARG, 16000>,
						Int<10000>
					>
				>,
				// Size
				Scale<
					TwistAngle<>, //SwingSpeed<100>,
					Int<14000>,
					Int<18000>
				>
			>,
			// Color A
			BrownNoiseFlickerL<
				RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>,
				Int<200>
			>,
			// Color B
			StripesX<
				Int<1800>,
				Scale<
					NoisySoundLevel,
					Int<-3500>,
					Int<-5000>
				>,
				Mix<
					Int<6425>,
					Black,
					RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>
				>,
				RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>,
				Mix<
					Int<12850>,
					Black,
					RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>
				>
			>
		>
	>,
	// Effect Color
	AlphaL<
		AudioFlicker<
			RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>,
			Mix<
				Int<10280>,
				Black,
				RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>
			>
		>,
		Bump<
			Scale<
				BladeAngle<>,
				Scale<
					BladeAngle<0,16000>,
					Sum<
						IntArg<LOCKUP_POSITION_ARG,16000>,
						Int<-12000>
					>,
					Sum<
						IntArg<LOCKUP_POSITION_ARG,16000>,
						Int<10000>
					>
				>,
				Sum<
					IntArg<LOCKUP_POSITION_ARG,16000>,
					Int<-10000>
				>
			>,
			Int<13000>
		>
	>,
	// Transition 1
	TrJoin<
		TrDelay<8000>,
		TrInstant
	>,
	// Transition 2
	TrFade<3000>,
	EFFECT_LOCKUP_BEGIN
>;

// DUNE Shield Lockup
using Lockup_Color_Shield =	AlphaL<
	StripesX<
		Int<16000>,
		Int<12000>,
		Rgb<128,0,0>,
		Red,
		Rgb<90,0,0>
	>,
	Bump<
		LOCKUPPOSITIONSCALE,
		Int<50000>
	>
>;

// Lockup Full Blade Flicker
using Lockup_Color_Full_Flicker = AudioFlickerL<LOCKUPCOLOR>;

// ================================ LOCKUP START TRANSITIONS ================================

// Localized Clash
using Lockup_Start_Localized = TrConcat<
	TrJoin<
		TrDelay<50>,
		TrInstant
	>, 
	LOCKUPCLASHCOLOR,
	TrExtend<
		3000, 
		TrFade<300>
	>, 
	AlphaL<
		AudioFlicker<
			LOCKUPCOLOR, 
			COLOR_MIX<Int<10280>, LOCKUPCOLOR>
		>, 
		Bump<
			LOCKUPPOSITIONSCALE,
			Int<13000>
		>
	>, 
	TrFade<3000>
>;

// Real Clash V1
using Lockup_Start_RealClash = TrConcat<
	TrJoin<
		TrDelay<50>,
		TrInstant
	>,
	Mix<
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
	>,
	TrFade<300>
>;

// Full Blade Flash
using Lockup_Start_Full_Flash = TrConcat<
	TrJoin<
		TrDelay<50>,
		TrInstant
	>,
	LOCKUPCLASHCOLOR,
	TrFade<300>
>;

// Localized Flash
using Lockup_Start_Localized_Flash = TrConcat<
	TrInstant,
	AlphaL<
		LOCKUPCOLOR,
		Bump<
			LOCKUPPOSITIONSCALE,
			Int<10000>
		>
	>,
	TrFade<300>
>;

// Lockup Start Shield
using Lockup_Start_Shield = TrConcat<
	TrJoin<
		TrDelayX<
			Scale<
				ClashImpactF<>,
				Int<2000>,
				Int<100>
			>
		>,
		TrCenterWipeX<
			Int<150>,
			LOCKUPPOSITIONSCALE
		>
	>,
	AlphaL<
		StripesX<
			Int<16000>,
			Scale<
				ClashImpactF<>,
				Int<3000>,
				Int<10000>
			>,
			Mix<
				IsGreaterThan<
					ClashImpactF<>,
					Int<23000>
				>,
				Rgb<0,20,128>,
				Rgb<128,0,0>
			>,
			Mix<
				IsGreaterThan<
					ClashImpactF<>,
					Int<23000>
				>,
				DodgerBlue,
				Red
			>,
			Mix<
				IsGreaterThan<
					ClashImpactF<>,
					Int<23000>
				>,
				Rgb<0,10,80>,
				Rgb<90,0,0>
			>
		>,
		Bump<
			LOCKUPPOSITIONSCALE,
			Scale<
				ClashImpactF<>,
				Int<20000>,
				Int<50000>
			>
		>
	>,
	TrFadeX<
		Scale<
			ClashImpactF<>,
			Int<600>,
			Int<100>
		>
	>
>;

// ================================ LOCKUP END TRANSITIONS ================================

// Lockup End
using Lockup_End_Intensity = TrConcat<
	TrInstant, 
	TRANSPARENT, 
	// Selected based on Impact Force
	TrSelect<
		Scale<
			IsLessThan<
				ClashImpactF<>, 
				Int<20000>
			>, 
			Int<1>, 
			Int<0>
		>, 
		// Wave
		TrWaveX<
			LOCKUPCOLOR, 
			Scale<
				ClashImpactF<>, 
				Int<50>, 
				Int<400>
			>, 
			Int<100>, 
			Scale<
				ClashImpactF<>, 
				Int<500>, 
				Int<300>
			>, 
			LOCKUPPOSITIONSCALE
		>, 
		// Ripple
		TrSparkX<
			Remap<
				CenterDistF<LOCKUPPOSITIONSCALE>,
				StripesX<
					Int<1200>, 
					Int<-3600>, 
					COLOR_MIX<Int<6425>, LOCKUPCOLOR>, 
					LOCKUPCOLOR, 
					COLOR_MIX<Int<12850>, LOCKUPCOLOR>
				>
			>, 
			Int<30>, 
			Scale<
				Sum<
					ClashImpactF<>, 
					SwingSpeed<600>
				>, 
				Int<100>, 
				Int<400>
			>, 
			LOCKUPPOSITIONSCALE
		>
	>
>;

/* // Merged into the above.
// Effect B: Wave (Dissipate)
using Lockup_End_Wave = TrConcat<
	TrInstant,
	TRANSPARENT,
	TrWaveX<
		LOCKUPCOLOR,
		Int<300>,
		Int<100>,
		Int<400>,
		LOCKUPPOSITIONSWING
	>
>;
// Effect C: Ripple
using Lockup_End_Ripple = TrSparkX<
	Remap<
		CenterDistF<LOCKUPPOSITIONSCALE>,
		Stripes<
			1200,
			-3600,
			COLOR_MIX<Int<6425>, LOCKUPCOLOR>,
			LOCKUPCOLOR,
			COLOR_MIX<Int<12850>, LOCKUPCOLOR>
		>
	>,
	Int<30>,
	Scale<
		Sum<
			ClashImpactF<>,
			SwingSpeed<600>
		>,
		Int<50>,
		Int<200>
	>,
	LOCKUPPOSITIONSCALE
>;
*/

// Power Burst
using Lockup_End_Power_Burst = TrConcat<
	TrCenterWipeX<
		Int<150>,
		LOCKUPPOSITIONSCALE
	>,
	LOCKUPCOLOR,
	TrJoin<
		TrCenterWipeX<
			Int<150>,
			LOCKUPPOSITIONSCALE
		>,
		TrSmoothFade<150>
	>
>;

// Localized Absorb
using Lockup_End_Localized_Absorb = TrConcat<
	TrInstant,
	AlphaL<
		LOCKUPCOLOR,
		Bump<
			LOCKUPPOSITIONSCALE,
			Int<13000>
		>
	>,
	TrFade<400>
>;

// Full Blade Absorb
using Lockup_End_Full_Absorb = TrConcat<
	TrInstant,
	LOCKUPCOLOR,
	TrFade<400>
>;

// Lockup End Shield
using Lockup_End_Shield = TrFade<400>;


// Lockup Start Random
using Lockup_Start_Random = TrRandom< //TrSequence<
	// Real Clash v1
	Lockup_Start_RealClash,
	// Localized Flicker
	Lockup_Start_Localized,
	// Localized Flash/Fade
	Lockup_Start_Localized_Flash,
	// Full blade Flash/Fade
	Lockup_Start_Full_Flash
>;

// Lockup End Random
using Lockup_End_Random = TrRandom< //TrSequence<
	// Real Clash Intensity
	Lockup_End_Intensity,
	// Power Burst Wave release
	Lockup_End_Power_Burst,
	// Localized Absorb Flash
	Lockup_End_Localized_Absorb,
	// Full blade flash
	Lockup_End_Full_Absorb
>;