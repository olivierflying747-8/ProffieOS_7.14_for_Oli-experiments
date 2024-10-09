// ================================ SWING EFFECTS ===========================

// AudioFlicker Swing
using Swing_AudioFlicker = AlphaL<
	AudioFlickerL<SWINGCOLOR>,
	SWING_SPEED_LESS_THAN<SWING_SPEED_DEFAULT>
>;

// Sparkle Swing
using Swing_Sparkle = AlphaL<
	SparkleL<SWINGCOLOR>,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<0>, Int<32768>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
>;

// Pulsing Swing
using Swing_Pulsing = AlphaL<
	PulsingL<
		SWINGCOLOR,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<1000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
	>,
	SWING_SPEED_LESS_THAN<SWING_SPEED_DEFAULT>
>;

// Fire Swing
using Swing_Fire = AlphaL<
	StripesX<
		//Int<2800>,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2800>, Int<1800>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<-3000>,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-2000>, Int<-3000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

		SWINGCOLOR,
		COLOR_MIX<Int<2096>, SWINGCOLOR>,
		COLOR_MIX_P<50, SWINGCOLOR>
	>,
	SWING_SPEED_LESS_THAN<SWING_SPEED_DEFAULT>
>;

//Unstable swing
using Swing_Unstable = AlphaL<
	BrownNoiseFlickerL<
		RotateColorsX<Variation, SWINGCOLOR>, //DeepSkyBlue
		//Black, 
		Int<300>
	>, 
	SwingSpeed<SWING_SPEED_DEFAULT>
>;

//Unstable swing ripple
using Swing_UnstableRippple = AlphaL<
	StripesX<
		//Int<1000>, 
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<1000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<-2000>, 
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-1000>, Int<-2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

		RandomPerLEDFlicker<
			RotateColorsX<Variation, SWINGCOLOR>, //DeepSkyBlue
			Black
		>, 
		Black, 
		RotateColorsX<Variation, SWINGCOLOR>, //DeepSkyBlue
		Black
	>, 
	SwingSpeed<SWING_SPEED_DEFAULT>
>;

//Fett263 Bright hard swing effect
using Swing_FettHard = AlphaL<
	RotateColorsX<Variation, COLOR_MIX_P<75, SWINGCOLOR, White>>, //LemonChiffon //255, 244, 157 // MIX ALT_COLOR_ARG, WHITE, 75% White
	SWING_SPEED_LESS_THAN<675, 750, Int<13600>, Int<-17300>>
>;

//Fett263 bright hard swing ripple
using Swing_FettRipple = AlphaL<
	StripesX<
		//Int<2500>,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2500>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<-3000>,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-2000>, Int<-3000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

		RotateColorsX<Variation, SWINGCOLOR>,
		RotateColorsX<
			Variation,
			COLOR_MIX<Int<6425>, SWINGCOLOR> //Rgb<44,42,0> // SWING_COLOR_ARG / 5.1
		>,
		PulsingX<
			RotateColorsX<
				Variation,
				COLOR_MIX_P<8, SWINGCOLOR> //Rgb<22,20,0> // SWING_COLOR_ARG / 12.75
			>,
			Black,
			//800
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<800>, Int<400>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
		>
	>,
	SwingSpeed<SWING_SPEED_DEFAULT>
>;

// Bright Swing Responsive Edge
using Swing_Bright_Edge = AlphaL<
	AlphaL<
		SWINGCOLOR,
		SWING_SPEED_LESS_THAN<SWING_SPEED_DEFAULT>
	>,
	SmoothStep<
		Scale<
			SWING_SPEED_LESS_THAN<SWING_SPEED_DEFAULT>,
			Int<28000>,
			Int<14000>
		>,
		Int<16000>
	>
>;

// Pixilate Swing
using Swing_Pixilate = AlphaL<
	RandomBlinkL<
		Int<10000>,
		SWINGCOLOR
	>,
	SWING_SPEED_LESS_THAN<SWING_SPEED_DEFAULT>
>;

// Lightning Swing
using Swing_Lightning = AlphaL<
	BrownNoiseFlickerL<
		StripesX<
			//Int<2600>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2600>, Int<2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			Scale<
				IncrementWithReset<
					ThresholdPulseF<
						StrobeF<
							Int<6>,
							Int<1>
						>,
						Int<32000>
					>,
					ThresholdPulseF<
						ThresholdPulseF<
							IsLessThan<
								HoldPeakF<
									Ifon<
										SwingSpeed<SWING_SPEED_DEFAULT>,
										Int<0>
									>,
									Int<150>,
									Int<32000>
								>,
								Int<8000>
							>,
							Int<32000>
						>
					>,
					Int<30000>,
					Int<3000>
				>,
				Int<-1200>,
				Int<-4000>
			>,
			SWINGCOLOR,
			COLOR_MIX_P<50, SWINGCOLOR>,
			COLOR_MIX_P<50, SWINGCOLOR, White>
		>,
		Int<50>
	>,
	SmoothStep<
		IncrementWithReset<
			Scale<
				IsGreaterThan<
					HoldPeakF<
						Ifon<
							SwingSpeed<SWING_SPEED_DEFAULT>,
							Int<0>
						>,
						Int<150>,
						Int<32000>
					>,
					Int<18000>
				>,
				Int<0>,
				ThresholdPulseF<
					StrobeF<
						Scale<
							HoldPeakF<
								Ifon<
									SwingAcceleration<>,
									Int<0>
								>,
								Int<150>,
								Int<32000>
							>,
							Int<20>,
							Int<200>
						>,
						Int<1>
					>,
					Int<32000>
				>
			>,
			ThresholdPulseF<
				IsLessThan<
					HoldPeakF<
						Ifon<
							SwingSpeed<SWING_SPEED_DEFAULT>,
							Int<0>
						>,
						Int<150>,
						Int<32000>
					>,
					Int<8000>
				>,
				Int<32000>
			>,
			Int<42000>,
			Int<1500>
		>,
		Int<-8000>
	>
>;

// Static Electricty Swing
using Swing_Static_Electricity = ColorSelect<
	IncrementWithReset<
		ThresholdPulseF<
			SwingSpeed<SWING_SPEED_DEFAULT>,
			Int<18000>
		>,
		Sum<
			EffectPulseF<EFFECT_CLASH>,
			EffectPulseF<EFFECT_LOCKUP_BEGIN>
		>,
		Int<1>
	>,
	TrSelect<
		IncrementWithReset<
			ThresholdPulseF<
				SwingSpeed<SWING_SPEED_DEFAULT>,
				Int<18000>
			>,
			Sum<
				EffectPulseF<EFFECT_CLASH>,
				EffectPulseF<EFFECT_LOCKUP_BEGIN>
			>,
			Int<1>
		>,
		TrConcat<
			TrInstant,
			COLOR_MIX_P<50, BASECOLOR, White>,
			TrSmoothFade<500>
		>,
		TrSmoothFade<600>
	>,
	// Base Style
	TRANSPARENT,
	/*
	AudioFlicker<
		BASECOLOR,
		COLOR_MIX<Int<18000>, BASECOLOR>
	>,*/
	// Swing Static
	Layers<
		// Stripes
		StripesX<
			Int<6000>,
			Scale<
				IncrementWithReset<
					ThresholdPulseF<
						SwingSpeed<SWING_SPEED_DEFAULT>,
						Int<18000>
					>,
					Sum<
						EffectPulseF<EFFECT_CLASH>,
						EffectPulseF<EFFECT_LOCKUP_BEGIN>
					>,
					Int<32000>,
					Int<2000>
				>,
				Int<-100>,
				Int<-3000>
			>,
			COLOR_MIX<Int<9000>, BASECOLOR>,
			BASECOLOR,
			COLOR_MIX<Int<18000>, BASECOLOR>
		>,
		// Flicker
		AlphaL<
			RandomPerLEDFlickerL<Black>,
			IncrementWithReset<
				ThresholdPulseF<
					SwingSpeed<SWING_SPEED_DEFAULT>,
					Int<18000>
				>,
				Sum<
					EffectPulseF<EFFECT_CLASH>,
					EffectPulseF<EFFECT_LOCKUP_BEGIN>
				>,
				Int<30000>,
				Int<4000>
			>
		>
	>
>;

// Rainbow Swing
using Swing_Rainbow = AlphaL<
	StyleFire<
		StripesX<
			//Int<30000>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<30000>, Int<20000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-500>, Int<-1000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			BASECOLOR,
			RotateColorsX<Int<5461>,BASECOLOR>,
			RotateColorsX<Int<10922>,BASECOLOR>,
			RotateColorsX<Int<16384>,BASECOLOR>,
			RotateColorsX<Int<21845>,BASECOLOR>,
			RotateColorsX<Int<27306>,BASECOLOR>
		>,
		COLOR_MIX<
			P_50,
			StripesX<
				//Int<30000>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<30000>, Int<20000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-250>, Int<-500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
				BASECOLOR,
				RotateColorsX<Int<5461>,BASECOLOR>,
				RotateColorsX<Int<10922>,BASECOLOR>,
				RotateColorsX<Int<16384>,BASECOLOR>,
				RotateColorsX<Int<21845>,BASECOLOR>,
				RotateColorsX<Int<27306>,BASECOLOR>
			>
		>,
		0,
		4
	>,
	ChangeSlowly<
		Scale<
			IsGreaterThan<
				//SwingSpeed<SWING_SPEED_DEFAULT>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<0>, Int<32768>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
				Int<16384>
			>,
			Int<0>,
			Int<32768>
		>,
		Int<12228>
	>
>;

// Clash Responsive Charge Buildup
using Swing_Clash_BuildUp = Layers <
	AlphaL<
		Layers<
			// Stripes one way
			StripesX<
				//Int<6000>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<6000>, Int<4000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
				Scale<
					IncrementWithReset<
						EffectPulseF<EFFECT_CLASH>,
						EffectPulseF<EFFECT_LOCKUP_BEGIN>,
						Int<32768>,
						Int<4096> // 8 clashes to full strength.
					>,
					Int<-100>, // Min
					Int<-2000> // Max
				>,
				COLOR_MIX<Int<9000>, SWINGCOLOR>,
				SWINGCOLOR,
				COLOR_MIX<Int<18000>, SWINGCOLOR>
			>,
			// 50% Stripes other way
			AlphaL<
				StripesX<
					//Int<6000>,
					SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<6000>, Int<4000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
					Scale<
						IncrementWithReset<
							EffectPulseF<EFFECT_CLASH>,
							EffectPulseF<EFFECT_LOCKUP_BEGIN>,
							Int<32768>,
							Int<4096> // 8 clashes to full strength.
						>,
						Int<100>, // Min
						Int<2000> // Max
					>,
					COLOR_MIX<Int<9000>, SWINGCOLOR>,
					SWINGCOLOR,
					COLOR_MIX<Int<18000>, SWINGCOLOR>
				>,
				Int<16384>
			>,
			// Random LED Flicker
			AlphaL<
				RandomPerLEDFlickerL<Black>,
				IncrementWithReset<
					EffectPulseF<EFFECT_CLASH>,
					EffectPulseF<EFFECT_LOCKUP_BEGIN>,
					Int<16384>, //32768>,
					Int<2048> //4096> // 8 clashes to full strength.
				>
			>,
			// Sparks
			TrSparkX_Random<White, Int<0>>,
			TrSparkX_Random<White, Int<0>>,
			TrSparkX_Random<White, Int<0>>,
			TrSparkX_Random<White, Int<32768>>,
			TrSparkX_Random<White, Int<32768>>,
			TrSparkX_Random<White, Int<32768>>
		>,
		IncrementWithReset<
			EffectPulseF<EFFECT_CLASH>,
			EffectPulseF<EFFECT_LOCKUP_BEGIN>,
			Int<24576>,
			Int<3072> // 8 clashes to full?
		>
	>,

	// Lockup Effect Flash
	Remap<
		CenterDistF<>,
		TransitionEffectL<
			TrConcat<
				TrWipe<300>,
				AlphaL<
					LOCKUPCOLOR, //White,
					/*
					RandomBlinkL<
						Int<300>,
						White
					>,
					*/
					IncrementWithReset<
						EffectPulseF<EFFECT_CLASH>,
						EffectPulseF<EFFECT_LOCKUP_BEGIN>,
						Int<32768>,
						Int<4096> // 8 clashes to full strength.
					>
				>,
				TrFade<300>
			>,
			EFFECT_LOCKUP_BEGIN //EFFECT_BLAST
		>
	>
>;

//Interactive Power Build-up (Force Toggle)
using Swing_Interactive_Power_Buildup = ColorSelect<
	IncrementF<
		EffectPulseF<EFFECT_FORCE>,
		Int<32000>,
		Int<2>
	>,
	TrSmoothFade<500>,
	TRANSPARENT,
	AlphaL<
		StripesX<
			//Int<10000>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<10000>, Int<6000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			Scale<
				IncrementWithReset<
					ThresholdPulseF<
						Ifon<
							StrobeF<
								Int<12>,
								Int<1>
							>,
							Int<0>
						>,
						Int<32000>
					>,
					ThresholdPulseF<
						Sum<
							ThresholdPulseF<
								Ifon<
									InvertF<
										HoldPeakF<
											SwingSpeed<SWING_SPEED_DEFAULT>,
											Int<100>,
											Int<33000>
										>
									>,
									Int<0>
								>,
								Int<24000>
							>,
							EffectPulseF<EFFECT_FORCE>
						>,
						Int<32000>
					>,
					Int<10000>,
					Int<100>
				>,
				Int<-50>,
				Int<-8000>
			>,
			COLOR_MIX_P<31,  SWINGCOLOR>,
			COLOR_MIX_P<62, SWINGCOLOR>,
			SWINGCOLOR
		>,
		SmoothStep<
			Sum<
				IncrementWithReset<
					ThresholdPulseF<
						StrobeF<
							Int<10>,
							Int<1>
						>,
						Int<30000>
					>,
					ThresholdPulseF<
						Sum<
							ThresholdPulseF<
								Ifon<
									InvertF<
										HoldPeakF<
											SwingSpeed<SWING_SPEED_DEFAULT>,
											Int<100>,
											Int<38000>
										>
									>,
									Int<0>
								>,
								Int<16000>
							>,
							EffectPulseF<EFFECT_FORCE>
						>,
						Int<32000>
					>,
					Int<4000>,
					Int<100>
				>,
				IncrementWithReset<
					ThresholdPulseF<
						Ifon<
							HoldPeakF<
								SwingSpeed<SWING_SPEED_DEFAULT>,
								Int<100>,
								Int<33000>
							>,
							Int<0>
						>,
						Int<16000>
					>,
					ThresholdPulseF<
						Sum<
							ThresholdPulseF<
								Ifon<
									InvertF<
										HoldPeakF<
											SwingSpeed<SWING_SPEED_DEFAULT>,
											Int<100>,
											Int<38000>
										>
									>,
									Int<0>
								>,
								Int<16000>
							>,
							EffectPulseF<EFFECT_FORCE>
						>,
						Int<32000>
					>,
					Int<38000>,
					Int<38000>
				>
			>,
			Int<-2000>
		>
	>
>;

// Interactive Fireball Swing (Force Toggle)
using Swing_Interactive_Fireball = ColorSelect<
	IncrementF<
		EffectPulseF<EFFECT_FORCE>,
		Int<32000>,
		Int<2>,
		Int<1>
	>,
	TrSmoothFade<500>,
	TRANSPARENT,
	AlphaL<
		AlphaMixL<
			SmoothStep<
				IncrementWithReset<
					Scale<
						IsGreaterThan<
							HoldPeakF<
								Ifon<
									SwingSpeed<SWING_SPEED_DEFAULT>,
									Int<0>
								>,
								Int<150>,
								Int<32000>
							>,
							Int<18000>
						>,
						Int<0>,
						ThresholdPulseF<
							StrobeF<
								Scale<
									HoldPeakF<
										Ifon<	
											SwingAcceleration<>,
											Int<0>
										>,
										Int<150>,
										Int<32000>
									>,
									Int<40>,
									Int<400>
								>,
								Int<1>
							>,
							Int<32000>
						>
					>,
					ThresholdPulseF<
						IsLessThan<
							HoldPeakF<
								Ifon<
									SwingSpeed<SWING_SPEED_DEFAULT>,
									Int<0>
								>,
								Int<150>,
								Int<32000>
							>,
							Int<8000>
						>,
						Int<32000>
					>,
					Int<42000>,
					Int<1500>
				>,
				Scale<
					HoldPeakF<
						Ifon<
							SwingSpeed<SWING_SPEED_DEFAULT>,
							Int<0>
						>,
						Int<150>,
						Int<32000>
					>,
					Int<3000>,
					Int<10000>
				>
			>,
			HumpFlicker<
				RotateColorsX<Int<1400>, SWINGCOLOR>,
				RotateColorsX<Int<3200>, SWINGCOLOR>,
				20
			>,
			HumpFlicker<
				RotateColorsX<Int<1000>, SWINGCOLOR>,
				RotateColorsX<Int<400>, SWINGCOLOR>,
				60
			>,
			RandomFlicker<
				COLOR_MIX<Int<16384>, SWINGCOLOR>,
				SWINGCOLOR
			>
		>,
		LinearSectionF<
			IncrementWithReset<
				Scale<
					IsGreaterThan<
						HoldPeakF<
							Ifon<
								SwingSpeed<SWING_SPEED_DEFAULT>,
								Int<0>
							>,
							Int<150>,
							Int<32000>
						>,
						Int<18000>
					>,
					Int<0>,
					ThresholdPulseF<
						StrobeF<
							Scale<
								HoldPeakF<
									Ifon<
										SwingAcceleration<>,
										Int<0>
									>,
									Int<150>,
									Int<32000>
								>,
								Int<40>,
								Int<400>
							>,
							Int<1>
						>,
						Int<32000>
					>
				>,
				ThresholdPulseF<
					IsLessThan<
						HoldPeakF<
							Ifon<
								SwingSpeed<SWING_SPEED_DEFAULT>,
								Int<0>
							>,
							Int<150>,
							Int<32000>
						>,
						Int<8000>
					>,
					Int<32000>
				>,
				Int<42000>,
				Int<1500>
			>,
			Scale<
				HoldPeakF<
					Ifon<
						SwingSpeed<SWING_SPEED_DEFAULT>,
						Int<0>
					>,
					Int<150>,
					Int<32000>
				>,
				Int<3000>,
				Int<10000>
			>
		>
	>
>;

// Interactive Flame Thrower (Force Toggle)
using Swing_Interactive_Flamethrower = ColorSelect<
	IncrementF<
		EffectPulseF<EFFECT_FORCE>,
		Int<32000>,
		Int<2>
	>,
	TrSmoothFade<500>,
	TRANSPARENT,
	AlphaL<
		StaticFire<
			StripesX<
				//Int<12000>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<12000>, Int<8000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
				//Int<-2000>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-1500>, Int<-2500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
				SWINGCOLOR,
				RotateColorsX<
					Int<200>,
					SWINGCOLOR
				>
			>,
			COLOR_MIX<Int<16384>, SWINGCOLOR>,
			0,
			3,
			2,
			2000,
			8
		>,
		SmoothStep<
			Scale<
				HoldPeakF<
					Ifon<
						Scale<
							IsGreaterThan<
								SwingSpeed<SWING_SPEED_DEFAULT>,
								Int<16000>
							>,
							Int<2000>,
							SwingSpeed<300>
						>,
						Int<0>
					>,
					Scale<
						SwingAcceleration<>,
						Int<100>,
						Int<600>
					>,
					Scale<
						SwingAcceleration<>,
						Int<10000>,
						Int<4000>
					>
				>,
				Int<1000>,
				Int<40000>
			>,
			Int<-4000>
		>
	>
>;

// Interactive Ice Blade
using Swing_Interactive_IceBlade = Layers<
	// Part 1
	ColorSelect<
		IncrementWithReset<
			EffectPulseF<EFFECT_FORCE>,
			ThresholdPulseF<
				IncrementWithReset<
					Sum<
						EffectPulseF<EFFECT_CLASH>,
						EffectPulseF<EFFECT_STAB>
					>,
					EffectPulseF<EFFECT_FORCE>,
					Int<32768>,
					Scale<
						ClashImpactF<>,
						Int<3000>,
						Int<14000>
					>
				>,
				Int<32600>
			>,
			Int<1>
		>,
		TrSmoothFadeX<
			Int<2000>
		>,
		TRANSPARENT,
		BASECOLOR
	>,
	// Part 2
	ColorSelect<
		IncrementWithReset<
			EffectPulseF<EFFECT_FORCE>,
			ThresholdPulseF<
				IncrementWithReset<
					Sum<
						EffectPulseF<EFFECT_CLASH>,
						EffectPulseF<EFFECT_STAB>
					>,
					EffectPulseF<EFFECT_FORCE>,
					Int<32768>,
					Scale<
						ClashImpactF<>,
						Int<3000>,
						Int<14000>
					>
				>,
				Int<32600>
			>,
			Int<1>
		>,
		TrSelect<
			IncrementWithReset<
				EffectPulseF<EFFECT_FORCE>,
				Sum<
					EffectPulseF<EFFECT_CLASH>,
					EffectPulseF<EFFECT_STAB>
				>,
				Int<1>
			>,
			TrSmoothFadeX<
				Int<3000>
			>,
			TrWipeSparkTipX<
				BrownNoiseFlicker<
					SWINGCOLOR,
					White,
					200
				>,
				WavLen<EFFECT_FORCE>
			>
		>,
		TRANSPARENT,
		AlphaL<
			StripesX<
				Int<22000>,
				Int<-20>,
				SWINGCOLOR,
				COLOR_MIX_P<55, SWINGCOLOR>
			>,
			SmoothStep<
				Sum<
					Int<33000>,
					IncrementWithReset<
						Sum<
							EffectPulseF<EFFECT_CLASH>,
							EffectPulseF<EFFECT_STAB>
						>,
						EffectPulseF<EFFECT_FORCE>,
						Int<33000>,
						Scale<
							Scale<
								ClashImpactF<>,
								Int<3000>,
								Int<14000>
							>,
							Int<-3000>,
							Int<-14000>
						>
					>
				>,
				Int<-1>
			>
		>
	>
>;

// Force Flash
using Swing_Force_Flash = TransitionEffectL<
	TrConcat<
		TrJoin<
			TrDelay<100>,
			TrFade<300>
		>,
		Pulsing<
			SWINGCOLOR,
			COLOR_MIX_P<50, SWINGCOLOR>,
			3000
		>,
		TrFade<300>
	>,
	EFFECT_FORCE
>;

// Force Pulse (Slow)
using Swing_Force_Pulse = TransitionEffectL<
	TrConcat<
		TrExtendX<
			Int<30000>, 
			TrFade<300>
		>, 
		PulsingX<
			SWINGCOLOR, 
			COLOR_MIX<P_50, SWINGCOLOR>, 
			//3000
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
		>, 
		TrFade<300>
	>, 
	EFFECT_FORCE
>;

// Force Aura
using Swing_Force_Aura = TransitionEffectL<
	TrConcat<
		TrJoin<
			TrDelay<30000>,
			TrFade<300>
		>,
		AudioFlickerL<SWINGCOLOR>,
		TrFade<300>
	>,
	EFFECT_FORCE
>;

// Force Boost AudioFlicker Swing
using Swing_Force_Flicker = TransitionEffectL<
	TrConcat<
		TrJoin<
			TrDelay<30000>,
			TrFade<300>
		>,
		AlphaL<
			AudioFlickerL<SWINGCOLOR>,
			Scale<
				IsLessThan<
					SwingSpeed<SWING_SPEED_DEFAULT>,
					Int<13600>
				>,
				Scale<
					SwingSpeed<SWING_SPEED_DEFAULT>,
					Int<-19300>,
					Int<32768>
				>,
				Int<0>
			>
		>,
		TrFade<300>
	>,
	EFFECT_FORCE
>;

// Force Rage Unstable
using Swing_Force_Rage_Unstable = TransitionEffectL<
	TrConcat<
		TrJoin<
			TrDelay<30000>,
			TrFade<300>
		>,
		StripesX<
			Int<3500>,
			Scale<
				SlowNoise<Int<3000>>,
				Int<-2500>,
				Int<-3500>
			>,
			SWINGCOLOR,
			COLOR_MIX<Int<10280>, SWINGCOLOR>,
			RandomPerLEDFlicker<
				COLOR_MIX<Int<2570>, SWINGCOLOR>,
				SWINGCOLOR
			>
		>,
		TrFade<300>
	>,
	EFFECT_FORCE
>;

// Force Rage Lightning
using Swing_Force_Rage_Lightning = TransitionEffectL<
	TrConcat<
		TrInstant,
		TransitionLoopL<
			TrConcat<
				TrJoin<
					TrDelayX<
						Scale<
							SlowNoise<Int<3000>>,
							Int<200>,
							Int<700>
						>
					>,
					TrWipe<200>
				>,
				RandomPerLEDFlickerL<SWINGCOLOR>,
				TrWipe<200>
			>
		>,
		TrFade<300>
	>,
	EFFECT_FORCE
>;

// Force Heating
using Swing_Force_Heat = EffectSequence<
	EFFECT_FORCE,
	// On
	AlphaL<
		Mix<
			SWING_SPEED_LESS_THAN<SWING_SPEED_DEFAULT>,
			Red,
			Orange,
			White
		>,
		Scale<
			SWING_SPEED_LESS_THAN<SWING_SPEED_DEFAULT>,
			Int<0>,
			Int<32768>
		>
	>,
	// Off
	TRANSPARENT
>;