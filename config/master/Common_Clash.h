// ================================ CLASH ================================

// Real Clash V1 Light Impact
using Clash_RealV1_Base = TransitionEffectL<
	TrConcat<
		TrInstant, 
		AlphaL<
			CLASHCOLOR, 
			Bump<
				LOCKUPPOSITIONSCALE, 
				Scale<
					ClashImpactF<>, 
					Int<12000>, 
					Int<60000>
				>
			>
		>, 
		TrFadeX<
			Scale<
				ClashImpactF<>, 
				Int<200>, 
				Int<400>
			>
		>
	>, 
	EFFECT_CLASH
>;
// Clash Update flash
using Clash_Wave_Internal = TrWaveX<
	CLASHCOLOR,
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
>;
// Real Clash V1 Heavy Impact
using Clash_RealV1_Wave = TransitionEffectL<
	Clash_Wave_Internal,
	EFFECT_CLASH
>;

// Clash Random Position
using Clash_Random = TransitionEffectL<
	TrConcat<
		TrInstant,
		AlphaMixL<
			Bump<
				EffectPosition<EFFECT_CLASH>,
				Scale<
					ClashImpactF<>,
					Int<9000>,
					Int<12000>
				>
			>,
			CLASHCOLOR,
			COLOR_MIX_P<50, CLASHCOLOR>
		>,
		TrFade<300>
	>,
	EFFECT_CLASH
>;

// Responsive Ripple
using Clash_Responsive_Ripple = TransitionEffectL<
	TrConcat<
		TrInstant,
		AlphaL<
			CLASHCOLOR,
			Bump<
				LOCKUPPOSITIONSCALE,
				Int<6000>
			>
		>,
		TrCenterWipeX<
			Int<100>,
			LOCKUPPOSITIONSCALE
		>,
		AlphaL<
			Remap<
				CenterDistF<
					LOCKUPPOSITIONSCALE
				>,
				Stripes<
					1400,
					-2000,
					CLASHCOLOR,
					COLOR_MIX<Int<2096>, CLASHCOLOR>
				>
			>,
			Bump<
				LOCKUPPOSITIONSCALE,
				Int<38000>
			>
		>,
		TrJoin<
			TrSmoothFade<50>,
			TrCenterWipeX<
				Int<100>,
				LOCKUPPOSITIONSCALE
			>
		>
	>,
	EFFECT_CLASH
>;

// Clash DUNE Shield
using Clash_Dune_Shield = TransitionEffectL<
	TrConcat<
		TrJoin<
			TrDelayX<
				Scale<
					ClashImpactF<>,
					Int<100>,
					Int<600>
				>
			>,
			TrCenterWipeX<
				Int<150>,
				LOCKUPPOSITIONSCALE
			>
		>,
		AlphaL<
			Remap<
				CenterDistF<
					LOCKUPPOSITIONSCALE
				>,
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
				Int<200>,
				Int<600>
			>
		>
	>,
	EFFECT_CLASH
>;

// TODO: Implement in a Crystal Style
// Real Clash V3 (For side blades/crystals?)
using Clash_RealV3 = AlphaL<
	TransitionEffectL<
		// Lockup Effect
		TrSelect<
			Scale<
				ClashImpactF<>,
				Int<0>,
				Int<4>
			>,
			TrConcat<
				TrInstant,
				AlphaL<
					CLASHCOLOR,
					Bump<
						LOCKUPPOSITIONSCALE,
						Scale<
							ClashImpactF<>,
							Int<8000>,
							Int<12000>
						>
					>
				>,
				TrFadeX<
					Scale<
						ClashImpactF<>,
						Int<200>,
						Int<600>
					>
				>
			>,
			Clash_Wave_Internal,
			TrSparkX<
				Remap<
					CenterDistF<
						LOCKUPPOSITIONSCALE
					>,
					Stripes<
						1500,
						-3000,
						CLASHCOLOR,
						COLOR_MIX_P<50, CLASHCOLOR>
					>
				>,
				Int<100>,
				Scale<
					ClashImpactF<>,
					Int<100>,
					Int<400>
				>,
				LOCKUPPOSITIONSCALE
			>,
			TrConcat<
				TrInstant,
				CLASHCOLOR,
				TrFadeX<
					Scale<
						ClashImpactF<>,
						Int<200>,
						Int<400>
					>
				>
			>,
			TrConcat<
				TrInstant,
				CLASHCOLOR,
				TrFadeX<
					Scale<
						ClashImpactF<>,
						Int<300>,
						Int<500>
					>
				>
			>
		>,
		EFFECT_CLASH
	>,
	Scale<
		ClashImpactF<>,
		Int<24000>,
		Int<32768>
	>
>;

using Clash_Sequence = EffectSequence <
	EFFECT_CLASH,
	// Real Clash V1
	Mix<
		IsLessThan<
			ClashImpactF<>, 
			Int<26000>
		>,
		// Mix A
		Clash_RealV1_Base,
		// Mix B
		Clash_RealV1_Wave
	>,
	// Responsive Wave
	Clash_RealV1_Wave,
	// Responsive Ripple
	Clash_Responsive_Ripple,
	// Random Clash
	Clash_Random
>;