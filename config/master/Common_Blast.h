// ================================ BLAST EFFECTS ===========================

// Blast Fade
template<class POS = BLASTPOS_SCALE<>, class SIZE = BLASTFADE_SIZE<>>
using Blast_Fade = TrConcat<
	TrInstant,
	AlphaMixL<
		Bump<
			POS,
			SIZE
		>,
		BLASTCOLOR,
		COLOR_MIX<Int<16384>, BLASTCOLOR>
	>,
	TrFade<300>
>;

// Blast Wave
template<class FADEOUT = BLASTWAVE_SCALE<>, class SIZE = BLASTWAVE_SCALE<SlowNoise<Int<3000>>>, class TIME = BLASTWAVE_SCALE<>, class POS = BLASTPOS_SCALE<>>
using Blast_Wave = TrWaveX<
	BLASTCOLOR,
	FADEOUT,
	SIZE,
	TIME,
	POS
>;

// Blast Ripple Fade
template<class POS = BLASTRIPPLE_POS<>, class SIZE1 = Int<6000>, class SIZE2 = Int<32000>>
using Blast_Ripple_Fade = TrConcat<
	TrInstant,
	AlphaL<
		BLASTCOLOR,
		Bump<
			POS,
			SIZE1
		>
	>,
	TrCenterWipeX<
		Int<100>,
		POS
	>,
	AlphaL<
		Remap<
			CenterDistF<POS>,
			Stripes<
				1600,
				-2000,
				BLASTCOLOR,
				COLOR_MIX<Int<2096>, BLASTCOLOR>
			>
		>,
		Bump<
			POS,
			SIZE2
		>
	>,
	TrJoin<
		TrSmoothFade<50>,
		TrCenterWipeX<
			Int<100>,
			POS
		>
	>
>;

// Blaster mode shot
using Blast_Blaster_Shot = TrWaveX<
	BLASTCOLOR,
	Scale<
		WavLen<>,
		Int<100>,
		Int<400>
	>,
	Int<100>,
	Scale<
		WavLen<>,
		Int<100>,
		Int<400>
	>,
	Int<0>
>;

// ================================ BLAST CONTROLLERS ===========================

// Interactive Blast
template<BladeEffectType EFFECTTYPE, class TIMEOUT = Int<1000>>
using Blast_Interactive_Control = Layers<
	TransitionEffectL<
		TrSelect<
			EffectIncrementF<
				EFFECTTYPE,
				Int<2>
			>,
			TrConcat<
				TrDelay<100>,
				TRANSPARENT,
				TrDoEffect<
					TrInstant,
					EFFECT_GAME_CHOICE
				>
			>,
			TrInstant
		>,
		EFFECT_INTERACTIVE_BLAST
	>,
	// Interactive Blast Random
	TransitionEffectL<
		TrSelect<
			EffectIncrementF<
				EFFECTTYPE,
				Int<2>
			>,
			TrConcat<
				TrExtendX<
					Sum<
						WavLen<EFFECT_INTERACTIVE_BLAST>,
						TIMEOUT
					>,
					TrInstant
				>,
				TransitionPulseL<
					TrDoEffect<
						TrInstant,
						EFFECT_BLAST
					>,
					ThresholdPulseF<
						SwingSpeed<300>,
						Int<16000>
					>
				>,
				TrConcat<
					TrDelay<150>,
					TrRandom<
						TrInstant,
						TrDoEffect<
							TrInstant,
							EFFECT_INTERACTIVE_BLAST
						>,
						TrDoEffect<
							TrInstant,
							EFFECT_INTERACTIVE_BLAST
						>,
						TrDoEffect<
							TrInstant,
							EFFECT_INTERACTIVE_BLAST
						>
					>
				>
			>,
			TrInstant
		>,
		EFFECT_GAME_CHOICE
	>
>;






/*

// Blast Wave Random
using Blast_Wave_Random = TrWaveX<
	BLASTCOLOR,
	Scale<
		EffectRandomF<EFFECT_BLAST>, 
		Int<100>, 
		Int<400>
	>, 
	Int<100>, 
	Scale<
		EffectRandomF<EFFECT_BLAST>, 
		Int<100>, 
		Int<400>
	>, 
	Scale<
		EffectRandomF<EFFECT_BLAST>, 
		Int<28000>, 
		Int<8000>
	>
>;

// Blast Wave (sound based)
using Blast_Wave_Sound = TrWaveX<
	BLASTCOLOR, 
	Scale<
		WavLen<EFFECT_BLAST>, 
		Int<100>, 
		Int<400>
	>, 
	Int<100>, 
	Scale<
		WavLen<EFFECT_BLAST>, 
		Int<100>, 
		Int<400>
	>, 
	Scale<
		EffectRandomF<EFFECT_BLAST>, 
		Int<28000>, 
		Int<8000>
	>
>;

// Blast Fade Random
using Blast_Fade_Random = TrConcat<
	TrInstant,
	AlphaMixL<
		Bump<
			EffectPosition<EFFECT_BLAST>,
			Scale<
				EffectPosition<EFFECT_BLAST>,
				Int<9000>,
				Int<12000>
			>
		>,
		BLASTCOLOR,
		COLOR_MIX<Int<16384>, BLASTCOLOR>
	>,
	TrFade<300>
>;

// Blade Fade (sound based)
using Blast_Fade_Sound = TrConcat<
	TrInstant, 
	AlphaMixL<
		Bump<
			EffectPosition<EFFECT_BLAST>,
			Scale<
				WavLen<EFFECT_BLAST>, 
				Int<9000>, 
				Int<12000>
			>
		>, 
		BLASTCOLOR, 
		COLOR_MIX_P<50, BLASTCOLOR>
	>, 
	TrFade<300>
>;

// Blast Ripple
using Blast_Ripple = TrConcat<
	TrInstant, 
	AlphaL<
		BLASTCOLOR, 
		Bump<
			PERCENTAGE_S<50>, //Int<16384>, 
			Int<6000>
		>
	>, 
	TrFade<50>, 
	AlphaL<
		BLASTCOLOR, 
		Int<0>
	>, 
	TrSparkX<
		Remap<
			CenterDistF<EffectPosition<EFFECT_BLAST>>,
			Stripes<
				2000, 
				-2000, 
				BLASTCOLOR, 
				COLOR_MIX<Int<2096>, BLASTCOLOR>
			>
		>, 
		Int<100>, 
		Int<300>, 
		EffectPosition<>
	>
>;

// Blast Ripple Fade
using Blast_Ripple_Fade = TrConcat<
	TrInstant, 
	AlphaL<
		BLASTCOLOR, 
		Bump<
			PERCENTAGE_S<50>, //Int<16384>, 
			Int<6000>
		>
	>, 
	TrFade<50>, 
	AlphaL<
		BLASTCOLOR, 
		Int<0>
	>, 
	TrWaveX<
		Remap<
			CenterDistF<EffectPosition<>>, 
			Stripes<
				1500, 
				-2000, 
				BLASTCOLOR,
				COLOR_MIX<Int<2096>, BLASTCOLOR>
			>
		>, 
		Int<160>, 
		Int<100>, 
		Int<300>, 
		EffectPosition<>
	>
>;

// Blast Responsive
using Blast_Responsive = TrConcat <
	TrInstant,
	ResponsiveBlastL<
		BLASTCOLOR,
		Int<400>,
		Scale<
			SwingSpeed<200>,
			Int<100>,
			Int<400>
		>,
		Int<400>
	>,
	TrFade<300>
>;

// Blast Responsive Swing
using Blast_Responsive_Swing = TrConcat <
	TrInstant,
	ResponsiveBlastL<
		BLASTCOLOR,
		Scale<
			SwingSpeed<400>,
			Int<400>,
			Int<100>
		>,
		Scale<
			SwingSpeed<400>,
			Int<200>,
			Int<100>
		>,
		Scale<
			SwingSpeed<400>,
			Int<400>,
			Int<200>
		>
	>,
	TrFade<300>
>;

// Blast Localized Clash
using Blast_LocalClash = TrConcat <
	TrInstant,
	LocalizedClashL<
		BLASTCOLOR,
		80,
		30,
		EFFECT_BLAST
	>,
	TrFade<300>
>;

// Blast Responsive Wave
using Blast_Responsive_Wave = TrConcat <
	TrInstant,
	ResponsiveBlastWaveL<
		BLASTCOLOR,
		Scale<
			SwingSpeed<400>,
			Int<500>,
			Int<200>
		>,
		Scale<
			SwingSpeed<400>,
			Int<100>,
			Int<400>
		>
	>,
	TrFade<300>
>;

// Blast L
using Blast_BlastL = TrConcat <
	TrInstant,
	BlastL<
		BLASTCOLOR,
		200,
		200
	>,
	TrFade<300>
>;

// Blast Responsive Fade
using Blast_Responsive_Fade_Swing = TrConcat <
	TrInstant,
	ResponsiveBlastFadeL<
		BLASTCOLOR,
		Scale<
			SwingSpeed<400>,
			Int<6000>,
			Int<12000>
		>,
		Scale<
			SwingSpeed<400>,
			Int<400>,
			Int<100>
		>
	>,
	TrFade<300>
>;

// TODO: Merge with above code and stuff

// Responsive Blast Effect Sequence
using ResponsiveEffectBlastStyle = EffectSequence<
	EFFECT_BLAST,
	ResponsiveBlastL<
		COLOR_MIX_P<50, BASECOLOR, BLASTCOLOR>,
		Int<400>,
		Scale<
			SwingSpeed<200>,
			Int<100>,
			Int<400>
		>,
		Int<400>
	>,
	LocalizedClashL<
		COLOR_MIX_P<50, BASECOLOR, BLASTCOLOR>,
		80,
		30,
		EFFECT_BLAST
	>,
	ResponsiveBlastWaveL<
		COLOR_MIX_P<50, BASECOLOR, BLASTCOLOR>,
		Scale<
			SwingSpeed<400>,
			Int<500>,
			Int<200>
		>,
		Scale<
			SwingSpeed<400>,
			Int<100>,
			Int<400>
		>
	>,
	BlastL<
		COLOR_MIX_P<50, BASECOLOR, BLASTCOLOR>,
		200,
		200
	>,
	ResponsiveBlastFadeL<
		COLOR_MIX_P<50, BASECOLOR, BLASTCOLOR>,
		Scale<
			SwingSpeed<400>,
			Int<6000>,
			Int<12000>
		>,
		Scale<
			SwingSpeed<400>,
			Int<400>,
			Int<100>
		>
	>,
	ResponsiveBlastL<
		COLOR_MIX_P<50, BASECOLOR, BLASTCOLOR>,
		Scale<
			SwingSpeed<400>,
			Int<400>,
			Int<100>
		>,
		Scale<
			SwingSpeed<400>,
			Int<200>,
			Int<100>
		>,
		Scale<
			SwingSpeed<400>,
			Int<400>,
			Int<200>
		>
	>
>;

// Single hook function
using Blast_MultiRandom = MultiTransitionEffectL<
	TrRandom<
		// Option 1: Blast Wave (Random)
		Blast_Wave_Random,
		// Option 3: Blast Wave (Sound Based)
		Blast_Wave_Sound,
		// Option 4: Blast Ripple
		Blast_Ripple,
		// Option 2: Blast Ripple Fade
		Blast_Ripple_Fade,
		// Option 5: Blast Fade (Sound Based)
		Blast_Fade_Sound,
		// Option 6, Responsive Blast
		Blast_Responsive,
		// Option 7: Localized clash
		Blast_LocalClash,
		// Option 8: Responsive Wave
		Blast_Responsive_Wave,
		// Option 9: BlastL
		Blast_BlastL,
		// Option 10: Responsive Blast Fade
		Blast_Responsive_Fade,
		// Option 11: Responsive Blast (Swing based)
		Blast_Responsive_Swing
	>, 
	EFFECT_BLAST
>;
*/