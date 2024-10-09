// ===================== BASIC COLOR BLENDS ===================
// Base Color
using BASECOLOR = RgbArg<BASE_COLOR_ARG, Rgb<127, 0, 0>>;
// Alt Colors
using ALTCOLOR = RgbArg<ALT_COLOR_ARG, Rgb<0, 127, 0>>;
using ALTCOLOR2 = RgbArg<ALT_COLOR2_ARG, Rgb<0, 0, 127>>;
using ALTCOLOR3 = RgbArg<ALT_COLOR3_ARG, Rgb<0, 127, 127>>;

// Effect Colors
using SWINGCOLOR = RgbArg<SWING_COLOR_ARG, Rgb<127, 0, 127>>;
using IGNITIONCOLOR = RgbArg<IGNITION_COLOR_ARG, Rgb<127, 127, 0>>;
using RETRACTIONCOLOR = RgbArg<RETRACTION_COLOR_ARG, Rgb<127, 127, 0>>;
using PREONCOLOR = RgbArg<PREON_COLOR_ARG, Rgb<127, 127, 127>>;
using POSTOFFCOLOR = RgbArg<POSTOFF_COLOR_ARG, Rgb<127, 127, 127>>;
using EMITTERCOLOR = RgbArg<EMITTER_COLOR_ARG, Rgb<127, 127, 127>>;
using BLASTCOLOR = RgbArg<BLAST_COLOR_ARG, Rgb<127, 127, 127>>;
using LBCOLOR = RgbArg<LB_COLOR_ARG, Rgb<127, 127, 127>>;
using CLASHCOLOR = RgbArg<CLASH_COLOR_ARG, Rgb<127, 127, 127>>;
using LOCKUPCOLOR = RgbArg<LOCKUP_COLOR_ARG, Rgb<127, 127, 127>>;
using DRAGCOLOR = RgbArg<DRAG_COLOR_ARG, Rgb<127, 127, 127>>;
using STABCOLOR = RgbArg<STAB_COLOR_ARG, Rgb<127, 127, 127>>;
using OFFCOLOR = RgbArg<OFF_COLOR_ARG, Rgb<0, 0, 0>>;

// Common Colors
using TRANSPARENT = AlphaL<Black, Int<0>>;

// Common Percentage Ints
using P_75 = Int<24576>;
using P_50 = Int<16384>;
using P_33 = Int<10922>;
using P_25 = Int<8192>;
using P_20 = Int<6554>;
using P_12_5 = Int<4096>;
using P_8 = Int<2621>;
using P_6_25 = Int<2048>;

// Get a % mix of color A and B, using straight values (32768 = 100%)
template<class MIX, class COLORA, class COLORB = Black>
using COLOR_MIX = Mix<
	MIX,
	COLORB,
	COLORA
>;

template<int PERCENT, class COLORA, class COLORB = Black>
using COLOR_MIX_P = Mix<
	Percentage<Int<32768>, PERCENT>,
	COLORB,
	COLORA
>;

/*
// Color 50%
template<class COLORA, class COLORB = Black>
using COLOR_50 = Mix<
	COLOR_PERCENT<50>, //Int<16448>, //50%
	COLORA,
	COLORB
>;

// Color 33%
template<class COLORA, class COLORB = Black>
using COLOR_33 = Mix<
	COLOR_PERCENT<33>, //Int<9921>, //33%
	COLORA,
	COLORB
>;

// Color 25%
template<class COLORA, class COLORB = Black>
using COLOR_25 = Mix<
	COLOR_PERCENT<25>, //Int<8192>, //25%
	COLORA,
	COLORB
>;

// Color 20%
template<class COLORA, class COLORB = Black>
using COLOR_20 = Mix<
	COLOR_PERCENT<20>, //Int<6425>, //20%
	COLORA,
	COLORB
>;
*/

// Color Gradiant
template<class COLORA, class COLORB = Black>
using COLOR_GRADIENT = Gradient<
	COLORA,
	COLORB
>;
