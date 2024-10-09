// ====================================== DRAG ==================================

// Drag Color Style (Intensity Sparking Drag)
using Drag_Color_Sparking = AlphaL<
	RandomPerLEDFlickerL<DRAGCOLOR>, 
	SmoothStep<
		DRAG_SIZE, 
		Int<3000>
	>
>;

// Drag Color Style (Intensity Fire Drag)
using Drag_Color_Fire = AlphaL<
	Stripes<
		2000,
		4000,
		DRAGCOLOR,
		COLOR_MIX<
			Sin<Int<50>>,
			DRAGCOLOR
		>,
		COLOR_MIX_P<12, DRAGCOLOR>
	>,
	SmoothStep<
		DRAG_SIZE,
		Int<3000>
	>
>;

// Drag Start Sparking
using Drag_Start_Sparking = TrConcat<
	TrJoin<
		TrDelay<4000>,
		TrWipeIn<200>
	>,
	AlphaL<
		BrownNoiseFlickerL<
			DRAGCOLOR, 
			Int<300>
		>, 
		SmoothStep<
			DRAG_SIZE, 
			Int<3000>
		>
	>, 
	TrFade<4000>
>;

// Drag Start 2 (Fire)
using Drag_Start_Fire = TrConcat<
	TrJoin<
		TrDelay<4000>,
		TrWipeIn<200>
	>,
	AlphaL<
		Stripes<
			2000,
			3000,
			DRAGCOLOR,
			COLOR_MIX<
				Sin<Int<30>>,
				DRAGCOLOR
			>,
			COLOR_MIX_P<25, DRAGCOLOR>
		>,
		SmoothStep<
			DRAG_SIZE,
			Int<3000>
		>
	>,
	TrFade<4000>
>;

// Drag End
using Drag_End = TrConcat<
	TrInstant,
	TrFade<300>
>;