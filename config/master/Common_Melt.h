// ===================================== MELT ==================================

// Responsive Melt
using Melt_Color_Responsive = AlphaL<
	Mix<
		TwistAngle<>,
		STABCOLOR,
		RotateColorsX<
			Int<3000>,
			STABCOLOR
		>
	>,
	SmoothStep<
		MELT_SIZE,
		Int<4000>
	>
>;

// Intenisty Melt (Fire)
using Melt_Color_Intensity = AlphaL<
	Remap<
		Scale<
			RampF, 
			Int<65536>, 
			Int<0>
		>, 
		StaticFire<
			Mix<
				TwistAngle<>, 
				STABCOLOR, //OrangeRed, 
				DarkOrange
			>, 
			Mix<
				TwistAngle<>, 
				STABCOLOR, //OrangeRed, 
				Orange
			>, 
			0, 
			3, 
			5, 
			3000, 
			10
		>
	>, 
	SmoothStep<
		MELT_SIZE, 
		Int<4000>
	>
>;

// Melt Start
using Melt_Start = TrConcat<
	TrWipeIn<100>,
	AlphaL<
		STABCOLOR,
		SmoothStep<
			MELT_SIZE,
			Int<4000>
		>
	>,
	TrFade<300>
>;

// Melt Intensity Start
using Melt_Start_Intensity = TrConcat<
	TrWipeIn<100>, 
	AlphaL<
		STABCOLOR, //Red
		SmoothStep<
			MELT_SIZE, 
			Int<4000>
		>
	>, 
	TrExtend<
		4000, 
		TrFade<300>
	>, 
	AlphaL<
		Mix<
			TwistAngle<>, 
			STABCOLOR,  //Red
			Orange
		>, 
		SmoothStep<
			MELT_SIZE, 
			Int<4000>
		>
	>, 
	TrFade<4000>
>;

// Melt End
using Melt_End = TrConcat <
	TrInstant,
	TrWipe<200>
>;