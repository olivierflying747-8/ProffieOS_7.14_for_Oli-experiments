// ===================== POWER DOWN STYLES =======================

// Flash
using PowerDown_Flash = TrConcat<
	TRANSITION_DELAY<RETRACTION_TIME, RETRACTION_DELAY>,
	RETRACTIONCOLOR,
	TrFadeX<COOLDOWN_TIME>
>;

// Power Burst Reverse
using PowerDown_Burst_Reverse = TrConcat<
	TRANSITION_DELAY<RETRACTION_TIME, RETRACTION_DELAY>,
	StripesX<
		//Int<5000>, 
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<5000>, Int<2500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<2500>, 
		BLADE_ANGLE_SCLAE<Int<2500>, Int<1500>, Int<500>, Int<4000>>,

		RETRACTIONCOLOR, 
		COLOR_MIX<Int<7710>, RETRACTIONCOLOR>, 
		COLOR_MIX<Int<3855>, RETRACTIONCOLOR>
	>, 
	TrFadeX<COOLDOWN_TIME>
>;

// Unstable Cooldown Reverse
using PowerDown_Unstable_Reverse = TrConcat<
	TRANSITION_DELAY<RETRACTION_TIME, RETRACTION_DELAY>,
	StripesX<
		//Int<3000>, 
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<3500>, 
		BLADE_ANGLE_SCLAE<Int<3500>, Int<2000>, Int<500>, Int<4000>>,

		RETRACTIONCOLOR, 
		RandomPerLEDFlicker<
			COLOR_MIX<Int<7710>, RETRACTIONCOLOR>, 
			Black
		>, 
		BrownNoiseFlicker<
			RETRACTIONCOLOR, 
			COLOR_MIX<Int<3855>, RETRACTIONCOLOR>,
			200
		>, 
		RandomPerLEDFlicker<
			COLOR_MIX<Int<3137>, RETRACTIONCOLOR>,
			COLOR_MIX<Int<3855>, RETRACTIONCOLOR>
		>
	>, 
	TrFadeX<COOLDOWN_TIME>
>;

// Bright Humpflicker
using PowerDown_Bright_Hump = TrConcat<
	TRANSITION_DELAY<RETRACTION_TIME, RETRACTION_DELAY>,
	HumpFlickerL<RETRACTIONCOLOR, 40>, 
	TrFadeX<
		Percentage<COOLDOWN_TIME, 125>
	>
>;