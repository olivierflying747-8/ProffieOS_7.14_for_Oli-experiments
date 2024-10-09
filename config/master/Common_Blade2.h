// ===================== ALTERNATE BLADE STYLES =======================
// Using template passed in Color and variation timers.

// Audio Flicker
template<class COLOR>
using AltStyle_AudioFilter = AudioFlickerL<
	RotateColorsX<Variation, COLOR>
>;

// Random Flicker
template<class COLOR>
using AltStyle_RandomFlicker = RandomL<
	COLOR
>;

// Random Per LED Flicker
template<class COLOR>
using AltStyle_RandomPerLEDFlicker = RandomPerLEDFlickerL<
	COLOR
>;

// Blinking
template<class COLOR, int SWING_SPEED = SWING_SPEED_DEFAULT, class MIN_TIME = Int<1000>, class MAX_TIME = Int<300>, class RATIO = Int<500>, class HOLD_TIME_MIN = Int<100>, class HOLD_TIME_MAX = Int<500>, class HOLD_SPEED_MIN = Int<4000>, class HOLD_SPEED_MAX = Int<8000>>
using AltStyle_Blinking = BlinkingL<
	COLOR,
	SWING_SPEED_SCLAE<SWING_SPEED, MIN_TIME, MAX_TIME, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>,
	RATIO
>;

// Pusling
template<class COLOR, int SWING_SPEED = SWING_SPEED_DEFAULT, class PULSE_MIN = Int<1200>, class PULSE_MAX = Int<1200>, class HOLD_TIME_MIN = Int<0>, class HOLD_TIME_MAX = Int<0>, class HOLD_SPEED_MIN = Int<0>, class HOLD_SPEED_MAX = Int<0>>
using AltStyle_Pulsing = PulsingL<
	RotateColorsX<Variation, COLOR>,
	SWING_SPEED_SCLAE<SWING_SPEED, PULSE_MIN, PULSE_MAX, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>
>;

// Hump Flicker
template<class COLOR, int WIDTH = 10, int SWING_SPEED = SWING_SPEED_DEFAULT, class MIN_SIZE = Int<1024>, class MAX_SIZE = Int<8192>, class HOLD_TIME_MIN = Int<500>, class HOLD_TIME_MAX = Int<1000>, class HOLD_SPEED_MIN = Int<4000>, class HOLD_SPEED_MAX = Int<8000>>
using AltStyle_HumpFlicker_Random = AlphaL<
	HumpFlickerL<COLOR, WIDTH>,
	Bump<
		RandomF,
		SWING_SPEED_SCLAE<SWING_SPEED, MIN_SIZE, MAX_SIZE, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>
	>
>;

// Hump Waves (2 Color)
template<class COLORA, class COLORB, int SWING_SPEED = SWING_SPEED_DEFAULT, class WIDTH_MIN = Int<100>, class WIDTH_MAX = Int<400>, class HOLD_TIME_MIN = Int<500>, class HOLD_TIME_MAX = Int<1000>, class HOLD_SPEED_MIN = Int<4000>, class HOLD_SPEED_MAX = Int<8000>>
using AltStyle_HumpWave = Layers <
	TransitionLoopL<
		TrWaveX<
			HumpFlickerL<RotateColorsX<Variation, COLORA>, 40>,
			Int<250>,
			//Int<100>,
			SWING_SPEED_SCLAE<SWING_SPEED, WIDTH_MIN, WIDTH_MAX, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>,
			Int<200>,
			Int<0>
		>
	>,
	TransitionLoopL<
		TrWaveX<
			HumpFlickerL<RotateColorsX<Variation, COLORB>, 40>,
			Int<350>,
			//Int<100>,
			SWING_SPEED_SCLAE<SWING_SPEED, WIDTH_MIN, WIDTH_MAX, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>,
			Int<300>,
			Int<0>
		>
	>
>;

// Sparkle
template<class COLOR>
using AltStyle_Sparkle = SparkleL<
	COLOR
>;

// Style Fire
template<class COLORA, class COLORB, int SPEED = 2>
using AltStyle_Fire = AlphaL< 
	StyleFire<
		COLORA,
		COLORB,
		0,
		SPEED
	>,
	PERCENTAGE_S<50> //Int<16384>
>;

// Brown Noise with Stripes
template<class COLOR, int SWING_SPEED = SWING_SPEED_DEFAULT, class WIDTH_MIN = Int<3000>, class WIDTH_MAX = Int<1000>, class SPEED_MIN = Int<-2000>, class SPEED_MAX = Int<-4000>, class HOLD_TIME_MIN = Int<500>, class HOLD_TIME_MAX = Int<1000>, class HOLD_SPEED_MIN = Int<4000>, class HOLD_SPEED_MAX = Int<8000>>
using AltStyle_BrownNoise_Stripes = BrownNoiseFlickerL<
	//TRANSPARENT,
	StripesX<
		SWING_SPEED_SCLAE<SWING_SPEED, WIDTH_MIN, WIDTH_MAX, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>,
		SWING_SPEED_SCLAE<SWING_SPEED, SPEED_MIN, SPEED_MAX, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>,
		COLOR_MIX<Int<9638>, COLOR>, //Rgb<50, 50, 75>, // ALT COLOR / 3.4
		COLOR_MIX<Int<19275>, COLOR>, //Rgb<100, 100, 150>, // ALT COLOR / 1.7
		COLOR_MIX<Int<1928>, COLOR>, //Rgb<10, 10, 15>, // ALT COLOR / 17
		COLOR //Rgb<150, 150, 225> // ALT COLOR
	>, 
	Int<200>
>;

// Fett263 Smoke Blade Fire layer
template<class COLOR, int SPEED = 1, int BASE = 10, int RAND = 2000, int COOLING = 2>
using AltStyle_SmokeBlade = AlphaL <
	StaticFire<
		RotateColorsX<Variation, COLOR>,
		RotateColorsX<
			Variation,
			COLOR_MIX<Int<256>, COLOR> //Rgb<2,2,0> // ALT / 127.5
		>,
		0,
		SPEED,
		BASE,
		RAND,
		COOLING
	>,
	Int<10000>
>;

// Lightning Flash
template<class COLOR, int SWING_SPEED = SWING_SPEED_DEFAULT, class HOLD_TIME_MIN = Int<500>, class HOLD_TIME_MAX = Int<1000>, class HOLD_SPEED_MIN = Int<4000>, class HOLD_SPEED_MAX = Int<8000>>
using AltStyle_LightningFlash = TransitionLoopL<
	TrConcat<
		TrBoing<800, 3>,
		TrConcat<
			TrFadeX<Scale<RandomF, Int<100>, Int<200>>>,
			AlphaL<
				HumpFlickerL<COLOR, 10>,
				Bump<
					BrownNoiseF<Int<10>>, //RandomF,
					//Int<20000>
					SWING_SPEED_SCLAE<SWING_SPEED, Int<20000>, Int<10000>, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>
				>
			>,
			TrFadeX<Scale<RandomF, Int<100>, Int<200>>>
		>,
		TrDelayX< // Random Timer
			Scale<
				SlowNoise<Int<3000>>,
				Int<400>,
				//Int<2000>
				SWING_SPEED_SCLAE<SWING_SPEED, Int<2500>, Int<1000>, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>
			>
		>
	>
>;

// Cylon
template<class COLOR, int SIZE = 5, int SPEED = 20>
using AltStyle_Cylon = AlphaL<
	Cylon<
		COLOR,
		SIZE,
		SPEED
	>,
	PERCENTAGE_S<50> //Int<16384>
>;

// Blade Tip Flame
template<class COLOR>
using AltStyle_Blade_Tip_Flame = AlphaL<
	Layers <
		Gradient<COLOR, TRANSPARENT>,
		HumpFlickerL<
			Layers<
				AudioFlickerL<COLOR>, 
				BrownNoiseFlickerL<
					//TRANSPARENT,
					COLOR,
					Int<200>
				>
			>,
			10
		>
	>,
	Bump<
		Scale<
			BladeAngle<>,
			Int<28000>,
			Int<32000>
		>,
		Scale<
			BladeAngle<>,
			Int<20000>,
			Int<8000>
		>
	>
>;


// Emitter Flare
template<class COLOR>
using AltStyle_Emitter_Flare = AlphaL<
	AudioFlickerL<COLOR>, 
	Bump<
		Int<0>,
		Scale<
			NoisySoundLevel,
			EMITTER_SIZE,
			Percentage<EMITTER_SIZE, 200>
		>
	>
>;

// Timed "breathing" emitter flare 
//- NOTE: Due to the way Proffie works, this isn't always "lined up" and might be slightly ahead or slightly behind the hum's breathing. To fix you can turn the saber off and back on until it's lined up. The timing is right, but the code runs in the background even after turning the saber off so it doesn't always start "on time."
template<class COLOR>
using AltStyle_Emitter_Breathe = Mix<
	Sin<Int<8>>,
	AlphaL<
		RotateColorsX<Variation, COLOR>,
		Bump<
			Int<0>,
			//Int<6000>
			Percentage<EMITTER_SIZE, 100>
			/*
			Mult<
				Int<8937>, //33%
				EMITTER_SIZE
			>
			*/
		>
	>,
	AlphaL<
		RotateColorsX<Variation, COLOR>,
		Bump<
			Int<0>,
			//Int<22000>
			Percentage<EMITTER_SIZE, 200>
		>
	>
>;

// Emitter Pulse
template<class COLOR>
using AltStyle_Emitter_Pulse = TransitionLoopL<
	TrConcat<
		TrDelayX<
			Scale<
				SlowNoise<Int<1000>>,
				Int<300>,
				Int<3000>
			>
		>,
		TRANSPARENT,
		TrSparkX<
			COLOR,
			Scale<
				NoisySoundLevel,
				Int<200>,
				Int<600>
			>,
			Int<250>,
			Int<0>
		>
	>
>;

// Emitter Flicker
template<class COLOR, int SWING_SPEED = SWING_SPEED_DEFAULT, class PULSE_MIN = Int<1200>, class PULSE_MAX = Int<600>, class HOLD_TIME_MIN = Int<500>, class HOLD_TIME_MAX = Int<1000>, class HOLD_SPEED_MIN = Int<4000>, class HOLD_SPEED_MAX = Int<8000>>
using AltStyle_Emitter_Fade = AlphaMixL<
	Bump<
		Int<2048>, 
		Int<131070>
	>, 
	TRANSPARENT, 
	PulsingX< //AudioFlicker<
		COLOR_MIX<
			SWING_SPEED_SCLAE<SWING_SPEED, Int<16384>, Int<32768>, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>,
			RotateColorsX<Variation, COLOR>
		>,
		COLOR_MIX<
			SWING_SPEED_SCLAE<SWING_SPEED, Int<12288>, Int<24576>, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>,
			RotateColorsX<Variation, COLOR>
		>,
		SWING_SPEED_SCLAE<SWING_SPEED, PULSE_MIN, PULSE_MAX, HOLD_TIME_MIN, HOLD_TIME_MAX, HOLD_SPEED_MIN, HOLD_SPEED_MAX>
	>
>;

// Spark moving with BladeAngle
template<class COLOR>
using AltStyle_Spark_BladeAngle = AlphaL<
	Mix<
		BladeAngle<>,
		AudioFlickerL<
			RotateColorsX<Variation, COLOR>
		>,
		PulsingL<
			RotateColorsX<Variation, COLOR>,
			Int<100>
		>
	>,
	Bump<
		BladeAngle<0, 32000>,
		Int<4000>
	>
>;

/* // Stripes doens't support Transparency, so it never looks good.
// StripesX Slownoise
template<class COLOR>
using AltStyle_StripesX_SlowNoise = AlphaL<
	StripesX<
		Int<1500>,
		Scale<
			SlowNoise<Int<2500>>,
			Int<-3000>,
			Int<-5000>
		>,
		Black,
		COLOR_MIX<10280, RotateColorsX<Variation, COLOR>>, //33%
		Black,
		COLOR_MIX<2570,	RotateColorsX<Variation, COLOR>>,
		Black
	>,
	PERCENTAGE_S<50> //Int<16384>
>;
//*/


// Style Fire TEST
template<class COLOR>
using AltStyle_FireTEST = AlphaL< 
	StyleFire<
		COLOR,
		TRANSPARENT,
		0,
		2
	>,
	PERCENTAGE_S<50> //Int<16384>
>;
