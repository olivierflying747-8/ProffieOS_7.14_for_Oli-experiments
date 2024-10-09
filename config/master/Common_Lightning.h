// ================================ LIGHTNING BLOCK ================================

// Lightning Block Color
using LB_Color_Style = Strobe<
	LBCOLOR, 
	AudioFlicker<
		LBCOLOR, 
		Mix<
			BladeAngle<>,
			LBCOLOR,
			Blue
		>
	>, 
	50, 
	1
>;

// TODO: Add more styles via TrRandom?
// LB Start
using LB_Start = TrConcat<
	TrInstant, 
	AlphaL<
		LBCOLOR, 
		Bump<
			Int<12000>, 
			Int<18000>
		>
	>, 
	TrFade<200>
>;

// TODO: Add more styles via TrRandom?
// LB End
using LB_End = TrConcat<
	TrInstant, 
	HumpFlickerL<
		AlphaL<
			LBCOLOR, 
			Int<16284>
		>, 
		30
	>, 
	TrSmoothFade<600>
>;


// Force Lightning
using Lockup_Force_Lightning = StripesX<
	Int<3000>,
	Int<-2000>,
	RandomBlinkX<
		Int<30000>,
		Strobe<
			COLOR_MIX_P<50, LBCOLOR, White>, //Rgb<125,125,225>>,
			White,
			50,
			1
		>,
		COLOR_MIX_P<33, LBCOLOR, White> //Rgb<75,75,150>
	>,
	RandomPerLEDFlicker<
		COLOR_MIX_P<20, LBCOLOR, White>, //Rgb<20,20,100>,
		COLOR_MIX_P<66, LBCOLOR, White> //Rgb<100,100,150>
	>
>;
using Lockup_Force_Lightning_StartEnd = TrWipe<200>;

