// ===================================== STAB ==================================

// Stab color Style (Normal)
using Stab_Color_Normal = AlphaL<
	STABCOLOR,
	SmoothStep<
		MELT_SIZE,
		Int<2000>
	>
>;

// Stab Color Style 2 (Audioflicker)
using Stab_Color_AudioFlicker = AlphaL<
	AudioFlickerL<STABCOLOR>,
	SmoothStep<
		MELT_SIZE,
		Int<2000>
	>
>;

// Stab Color Style 3 (Sparking)
using Stab_Color_Style3 = AlphaL<
	RandomPerLEDFlickerL<STABCOLOR>,
	SmoothStep<
		MELT_SIZE,
		Int<2000>
	>
>;

// Stab Start
using Stab_Start = TrJoin<
	TrDelayX<WavLen<EFFECT_STAB>>,
	TrWipeIn<200>
>;

// Stab End
using Stab_End = TrConcat <
	TrInstant, 
	TrWipe<200>
>;