// ===================== BASE BLADE STYLES =======================
/*
// Basic Audio Filter, BASE color, 50% BASE color (breathing)
using BaseStyle_AudioFilter = AudioFlicker<
	BASECOLOR,
	BASECOLOR_50 // 50%
>;*/

using BaseStyle_Static = BASECOLOR;

// Basic Audio Filter, BASE / ALT color.
using BaseStyle_AudioFilter = AudioFlicker<
	RotateColorsX<Variation, BASECOLOR>,
	RotateColorsX<Variation, ALTCOLOR>
>;

// Random Flicker, BASE / ALT color
using BaseStyle_RandomFlicker = RandomFlicker<
	BASECOLOR,
	ALTCOLOR
>;

// Brownnoise BASE color
using BaseStyle_BrownNoiseFlicker = BrownNoiseFlicker<
	RotateColorsX<Variation, BASECOLOR>,
	Black,
	300
>;

// Pusling Blade
using BaseStyle_Pulsing = PulsingX<
	RotateColorsX<Variation, BASECOLOR>,
	RotateColorsX<Variation, ALTCOLOR>,
	//1000
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<1000>, Int<600>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
>;

// Stripes (single color)
using BaseStyle_Stripes = StripesX<
	//10000,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT,
		BLADE_ANGLE_SCLAE<PERCENTAGE_S<50>, Int<8192>, Int<500>, Int<6000>>,
		Int<4096>, Int<500>, Int<1000>, Int<4000>, Int<8000>
	>,
	//-1700,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT,
		BLADE_ANGLE_SCLAE<Int<-300>, Int<-750>, Int<500>, Int<6000>>,
		Int<-2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>
	>,
	RotateColorsX<Variation, COLOR_MIX_P<33, BASECOLOR>>,
	RotateColorsX<Variation, BASECOLOR>,
	RotateColorsX<Variation, COLOR_MIX<P_50, BASECOLOR>>,
	RotateColorsX<Variation, COLOR_MIX<P_20, BASECOLOR>>,
	RotateColorsX<Variation, BASECOLOR>
>;

// Stripes (Slownoise Random, 2 color)
using BaseStyle_Stripes_2Color = StripesX<
	//Int<1500>,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<1500>, Int<1000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT,
		Scale<
			SlowNoise<Int<2500>>,
			Int<-2000>,
			Int<-3000>
		>,
		Scale<
			SlowNoise<Int<2500>>,
			Int<-3000>,
			Int<-6000>
		>,
		Int<500>, Int<1000>, Int<4000>, Int<8000>
	>,
	BASECOLOR,
	COLOR_MIX_P<33, ALTCOLOR>,
	BASECOLOR,
	COLOR_MIX_P<8, ALTCOLOR>,
	BASECOLOR
>;

// Unstable Stripes
using BaseStyle_Stripes_RandomPerLEDFlicker = StripesX<
	//Int<3000>, 
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT,
		BLADE_ANGLE_SCLAE<Int<3000>, Int<2000>, Int<500>, Int<6000>>,
		Int<1000>, Int<500>, Int<1000>, Int<4000>, Int<8000>
	>,
	//Int<-3500>,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-1000>, Int<-3500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

	BASECOLOR, 
	RandomPerLEDFlicker<
		COLOR_MIX<Int<7710>, BASECOLOR>,
		Black
	>, 
	BrownNoiseFlicker<
		BASECOLOR,
		COLOR_MIX<Int<3855>, BASECOLOR>,
		200
	>, 
	RandomPerLEDFlicker<
		COLOR_MIX<Int<10280>, BASECOLOR>,
		COLOR_MIX<Int<3855>, BASECOLOR>
	>
>;

// Kestis style
/* // Too similar to above.
using CalKestisStyle = StripesX<
	Int<6000>,
	Scale<
		SlowNoise<Int<2000>>,
		Int<-1600>,
		Int<-3200>
	>,
	BASECOLOR,
	RandomPerLEDFlicker<
		COLOR_MIX<Int<10280>, BASECOLOR>,
		COLOR_MIX<Int<1285>, BASECOLOR>
	>,
	BrownNoiseFlicker<
		COLOR_MIX<Int<1285>, BASECOLOR>,
		COLOR_MIX<Int<16448>, BASECOLOR>,
		300
	>,
	BASECOLOR,
	RandomPerLEDFlickerL<
		//Black,
		COLOR_MIX<Int<16448>, BASECOLOR>
	>,
	BASECOLOR
>;
*/

// Fire Blade
using BaseStyle_FireBlade = StyleFire<
	BrownNoiseFlicker<
		RotateColorsX<Variation, BASECOLOR>, //0, 135, 255
		RandomPerLEDFlicker<
			RotateColorsX<Variation, COLOR_MIX_P<10, BASECOLOR>>, //Rgb<0,0,25>  // BASE / 10.2
			RotateColorsX<Variation, COLOR_MIX_P<24, BASECOLOR>> //Rgb<0,0,60> // BASE / 4.25
		>,
		300
	>,
	RotateColorsX<Variation, COLOR_MIX<Int<10280>, BASECOLOR>>, //Rgb<0,0,80> // BASE / 3.1875
	0,
	6,
	FireConfig<10,1000,2>,
	FireConfig<10,1000,2>,
	FireConfig<10,1000,2>,
	FireConfig<10,1000,2>
>;

// Thunderstorm
using BaseStyle_ThunderstormBlade = TransitionLoop<
	RotateColorsX<Variation, BASECOLOR>, //DeepSkyBlue // 0, 135,255
	TrConcat<
		TrBoing<500,3>,
		Layers<
			StripesX<
				//Int<10000>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<10000>, Int<5000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
				//Int<100>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<100>, Int<300>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

				RotateColorsX<Variation, COLOR_MIX<P_50, BASECOLOR>>, //Rgb<0,40,128> // BASECOLOR / 2
				RotateColorsX<Variation, COLOR_MIX<P_12_5, BASECOLOR>>, //Rgb<0,8,30> // Base Color / 8
				RotateColorsX<Variation, ALTCOLOR> //Rgb<0,63,200> // Alt Color? DodgerBlue
			>,
			AlphaL<
				StripesX<
					//Int<8000>,
					SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<8000>, Int<3000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
					//Int<-200>,
					SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-200>, Int<-500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

					RotateColorsX<Variation, BASECOLOR>, // Base Color
					RotateColorsX<Variation, COLOR_MIX_P<25, ALTCOLOR>> //Rgb<0,19,60> // Alt color / 4? DodgerBlue
				>,
				PERCENTAGE_S<50> //Int<16384> //50%
			>
		>,
		TrDelayX< // Is this the lightning flash??
			Scale<
				SlowNoise<Int<3000>>,
				Int<100>,
				//Int<2000>
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2000>, Int<1000>, Int<1000>, Int<2000>, Int<4000>, Int<8000>>
			>
		>
	>
>;

// Fett263 Smoke Blade
using BaseStyle_SmokeBlade = StripesX<
	Sin<
		Int<12>,
		Int<3000>,
		Int<7000>
	>,
	Scale<
		SwingSpeed<100>,
		Int<75>,
		Int<125>
	>,
	StripesX<
		Sin<
			Int<10>,
			Int<1000>,
			Int<3000>
		>,
		Scale<
			SwingSpeed<100>,
			Int<75>,
			Int<100>
		>,
		PulsingX<
			RotateColorsX<Variation, BASECOLOR>,
			RotateColorsX<Variation, COLOR_MIX<Int<2570>, BASECOLOR>>, //Rgb<15,14,0>>, // BASECOLOR / 12.75
			//1200
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<1200>, Int<900>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
		>,
		Mix<
			SwingSpeed<200>,
			RotateColorsX<Variation, COLOR_MIX<Int<15420>, BASECOLOR>>, //Rgb<90,87,0> // Mix BASECOLOR / 2.125
			Black
		>
	>,
	RotateColorsX<Variation, COLOR_MIX<Int<7710>, BASECOLOR>>, //Rgb<40,40,0> // BASE / 4.25
	PulsingX<
		RotateColorsX<Variation, COLOR_MIX_P<20, BASECOLOR>>, //Rgb<36,33,0> // BASE / 5.1
		StripesX<
			Sin<
				Int<10>,
				Int<2000>,
				Int<3000>
			>,
			Sin<
				Int<10>,
				Int<75>,
				Int<100>
			>,
			RotateColorsX<Variation, BASECOLOR>,
			RotateColorsX<Variation, COLOR_MIX_P<38, BASECOLOR>> //Rgb<60,58,0> // BASE / 2.65625
		>,
		//2000
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
	>,
	PulsingX<
		RotateColorsX<Variation, COLOR_MIX<Int<15420>, BASECOLOR>>, //Rgb<90,88,0> // BASE / 2.125
		RotateColorsX<Variation, COLOR_MIX<Int<643>, BASECOLOR>>, //Rgb<5,5,0> // BASE / 51
		//3000
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
	>
>;

// Flickery Blade style
using BaseStyle_FlickerBlade = Mix<
	Scale<
		IsLessThan<
			SlowNoise<Int<2000>>, 
			Int<18000>
		>,
		Int<0>, 
		Int<32768>
	>, 
	COLOR_GRADIENT<BASECOLOR, COLOR_MIX_P<33, BASECOLOR>>,
	StripesX<
		//Int<12000>,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<12000>, Int<6000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		//Int<-800>,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-800>, Int<-1600>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

		COLOR_GRADIENT<BASECOLOR, COLOR_MIX_P<33, BASECOLOR>>,
		COLOR_GRADIENT<BASECOLOR, COLOR_MIX_P<33, BASECOLOR>>,
		COLOR_MIX_P<24, COLOR_GRADIENT<BASECOLOR, COLOR_MIX_P<33, BASECOLOR>>>,
		COLOR_GRADIENT<BASECOLOR, COLOR_MIX_P<33, BASECOLOR>>,
		COLOR_MIX_P<50, COLOR_GRADIENT<BASECOLOR, COLOR_MIX_P<33, BASECOLOR>>>
	>
>;

// "Coda"
//Rotates   ^3 times per minute between BASE COLOR and ALT COLOR with subtle ALT COLOR / ALT COLOR 2 audioflicker
using BaseStyle_CodaBlade = Mix<
	Sin<Int<3>>, 
	AudioFlicker<
		RotateColorsX<Variation, BASECOLOR>, //DodgerBlue //2, 72, 255 DodgerBlue // BASE COLOR
		StripesX<
			//Int<5000>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<5000>, Int<3000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			//Int<-90>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-90>, Int<-400>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

			RotateColorsX<Variation, COLOR_MIX<Int<21845>, ALTCOLOR>>, //Rgb<0, 55, 165> //0, 135, 255 // DeepSkyBlue //// ALT COLOR / 1.5
			RotateColorsX<Variation, COLOR_MIX<Int<14894>, ALTCOLOR>>, //Rgb<0, 85, 115> // ALT COLOR / 2.2
			RotateColorsX<Variation, COLOR_MIX<Int<18725>, COLOR_MIX_P<50, BASECOLOR, ALTCOLOR>>>, //Rgb<0, 65, 145> // MIX BASE COLOR / ALT COLOR 50%, ALT COLOR / 1.75
			RotateColorsX<Variation, COLOR_MIX<Int<23206>, COLOR_MIX_P<50, BASECOLOR, ALTCOLOR>>> //Rgb<0, 30, 185> // MIX BASE COLOR / ALT COLOR 50%, ALT COLOR / 1.3
		>
	>, 
	AudioFlicker<
		RotateColorsX<Variation, ALTCOLOR>,  //Rgb<0, 155, 255> // ALT_COLOR_ARG
		StripesX<
			//Int<5000>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<5000>, Int<3000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			//Int<-90>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-90>, Int<-400>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

			RotateColorsX<Variation, COLOR_MIX<Int<21845>, ALTCOLOR>>, //Rgb<0, 95, 170> // ALT COLOR / 1.5
			RotateColorsX<Variation, COLOR_MIX<Int<27769>, ALTCOLOR>>, //Rgb<0, 115, 215> // ALT COLOR / 1.18
			RotateColorsX<Variation, COLOR_MIX<Int<18724>, ALTCOLOR2>>, //Rgb<0, 145, 145> //ALT_COLOR2_ARG / 1.75
			RotateColorsX<Variation, COLOR_MIX<Int<28998>, BASECOLOR>> //Rgb<0, 65, 225> // BASE COLOR / 1.13
		>
	>
>;

// Water blade style
using BaseStyle_WaterBlade = StripesX<
	Scale<
		IsLessThan<
			BladeAngle<>,
			PERCENTAGE_S<50> //Int<16384>
		>,
		Scale<
			BladeAngle<>,
			Int<20000>,
			Int<10000>
		>,
		Scale<
			BladeAngle<>,
			Int<10000>,
			Int<20000>
		>
	>,
	Scale<
		BladeAngle<>,
		Int<-1000>,
		Scale<
			IsGreaterThan<
				HoldPeakF<
					SwingAcceleration<>,
					Scale<
						HoldPeakF<
							SwingAcceleration<>,
							Int<200>,
							Int<4000>
						>,
						Int<100>,
						Int<600>
					>,
					Scale<
						BladeAngle<>,
						Int<3000>,
						Int<6000>
					>
				>,
				PERCENTAGE_S<50> //Int<16384>
			>,
			Int<1000>,
			Int<-1000>
		>
	>,
	BASECOLOR,
	COLOR_MIX_P<50, BASECOLOR>,
	COLOR_MIX<Int<10280>, BASECOLOR>,
	COLOR_MIX<Int<25700>, BASECOLOR>,
	COLOR_MIX<Int<7710>, BASECOLOR>
>;

// DarkSaber style
using BaseStyle_DarkSaber = AudioFlicker<
	BrownNoiseFlicker<	
		Mix<
			SwingSpeed<400>, 
			BASECOLOR, 
			COLOR_MIX_P<20, BASECOLOR, ALTCOLOR> //20%
		>, 
		StripesX<
			//Int<5000>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<5000>, Int<3000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			//Int<-300>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-300>, Int<-600>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

			COLOR_MIX<Int<7710>, BASECOLOR>, //23%
			COLOR_MIX<Int<25700>, BASECOLOR>, //80%
			COLOR_MIX<Int<1285>, BASECOLOR>, //4%
			COLOR_MIX_P<50, BASECOLOR> //50%
		>,
		300
	>, 
	COLOR_MIX_P<20, BASECOLOR, ALTCOLOR> //20%
>;

// Interactive FirePulse Style
using BaseStyle_FirePulseInteractive = Layers<
	Black,
	ColorSelect<
		IncrementWithReset<
			ThresholdPulseF<
				SwingSpeed<400>,
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
					SwingSpeed<400>,
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
		AudioFlicker<
			BASECOLOR,
			COLOR_MIX_P<50, BASECOLOR>
		>,
		Layers<
			StripesX<
				Int<6000>,
				Scale<
					IncrementWithReset<
						ThresholdPulseF<
							SwingSpeed<400>,
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
				COLOR_MIX<P_33, BASECOLOR>,
				BASECOLOR,
				COLOR_MIX_P<50, BASECOLOR>
			>,
			AlphaL<
				RandomPerLEDFlickerL<Black>,
				IncrementWithReset<
					ThresholdPulseF<
						SwingSpeed<400>,
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
	>
>;

// Ghost Buster
using BaseStyle_GhostBusterBlade = StaticFire<
	Mix<
		SmoothStep<
			Int<2000>,
			Int<-2000>
		>,
		StripesX<
			//Int<16000>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<16000>, Int<8000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			//Int<-3900>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-2500>, Int<-3900>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

			BASECOLOR,
			COLOR_MIX_P<25, BASECOLOR>,
			COLOR_MIX_P<50, BASECOLOR>,
			StripesX<
				//Int<2500>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2500>, Int<1250>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
				//Int<-3500>,
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-2000>, Int<-3500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

				BASECOLOR,
				BASECOLOR,
				ALTCOLOR, // Blue
				COLOR_MIX_P<50, BASECOLOR>,
				ALTCOLOR2 // DodgerBlue
			>
		>,
		White // White
	>,
	ALTCOLOR, // Blue
	0,
	6,
	1,
	2000,
	3
>;

// ElectroStaff Blade
using BaseStyle_StaffBlade = StyleFire<
	Strobe<
		RotateColorsX<Variation, BASECOLOR>, //Rgb<95,0,210>
		Strobe<
			ALTCOLOR, //Rgb<100,100,150>
			RandomPerLEDFlicker<
				RotateColorsX<Variation, BASECOLOR>, //Rgb<95,0,210>
				Black
			>,
			50,
			1
		>,
		100,
		1
	>,
	RotateColorsX<Variation, COLOR_MIX<Int<16000>, BASECOLOR>>, //Rgb<23,0,65> // BASECOLOR / 0.3
	0,
	5,
	FireConfig<2,1000,5>,
	FireConfig<2,1000,5>,
	FireConfig<2,1000,5>,
	FireConfig<2,1000,5>
>;

// Lava Lamp Blade
using BaseStyle_LavaLamp = StripesX<
	Sin<
		Int<4>,
		Int<3000>,
		Int<6000>
	>,
	Scale<
		TwistAngle<>,
		Int<-50>,
		Int<-100>
	>,
	StripesX<
		Sin<
			Int<3>,
			Int<1000>,
			Int<3000>
		>,
		Scale<
			TwistAngle<>,
			Int<25>,
			Int<80>
		>,
		PulsingX<
			COLOR_MIX_P<20, BASECOLOR, White>,
			COLOR_MIX_P<8, BASECOLOR>,
			//3000
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
		>,
		Mix<
			Sin<Int<2>>,
			COLOR_MIX_P<79, BASECOLOR>,
			COLOR_MIX_P<4, BASECOLOR>
		>
	>,
	COLOR_MIX<Int<7710>, BASECOLOR>,
	PulsingX<
		COLOR_MIX<Int<6425>, BASECOLOR>,
		StripesX<
			Sin<
				Int<2>,
				Int<2000>,
				Int<4000>
			>,
			Sin<
				Int<2>,
				Int<25>,
				Int<75>
			>,
			Mix<
				Sin<Int<4>>,
				BASECOLOR,
				COLOR_MIX<Int<6425>, BASECOLOR, White>
			>,
			COLOR_MIX_P<38, BASECOLOR>
		>,
		//2000
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
	>,
	PulsingX<
		COLOR_MIX<P_50, BASECOLOR>,
		COLOR_MIX<Int<6425>, BASECOLOR>,
		//3000
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
	>
>;

// Smash Blade
using BaseStyle_SmashBlade = Layers<
	StripesX<
		Sin<
			Int<4>,
			Int<3000>,
			Int<6000>
		>,
		Scale<
			TwistAngle<>,
			Int<-50>,
			Int<-100>
		>,
		StripesX<
			Sin<
				Int<3>,
				Int<1000>,
				Int<3000>
			>,
			Scale<
				TwistAngle<>,
				Int<25>,
				Int<80>
			>,
			PulsingX<
				RotateColorsX<
					Sin<Int<10>>,
					Rgb<255,50,50>
				>,
				RotateColorsX<
					Sin<Int<12>>,
					Rgb<200,0,0>
				>,
				//3000
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
			>,
			Mix<
				Sin<Int<2>>,
				RotateColorsX<
					Sin<Int<12>>,
					Rgb<200,0,0>
				>,
				RotateColorsX<
					Sin<
						Scale<
							TwistAngle<>,
							Int<4>,
							Int<0>
						>
					>,
					Rgb<10,0,0>
				>
			>
		>,
		RotateColorsX<
			Sin<
				Scale<
					TwistAngle<>,
					Int<4>,
					Int<0>
				>
			>,
			Rgb<60,0,0>
		>,
		PulsingX<
			RotateColorsX<
				Sin<
					Scale<
						TwistAngle<>,
						Int<4>,
						Int<0>
					>
				>,
				Rgb<50,0,0>
			>,
			StripesX<
				Sin<
					Int<2>,
					Int<2000>,
					Int<4000>
				>,
				Sin<
					Int<2>,
					Int<25>,
					Int<75>
				>,
				Mix<
					Sin<Int<4>>,
					RotateColorsX<
						Sin<Int<4>>,
						Red
					>,
					RotateColorsX<
						Sin<
							Scale<
								TwistAngle<>,
								Int<14>,
								Int<2>
							>
						>,
						Rgb<255,50,50>
					>
				>,
				RotateColorsX<
					Sin<
						Scale<
							TwistAngle<>,
							Int<4>,
							Int<0>
						>
					>,
					Rgb<96,0,0>
				>
			>,
			//2000
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2000>, Int<1000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
		>,
		PulsingX<
			RotateColorsX<
				Sin<
					Scale<
						TwistAngle<>,
						Int<10>,
						Int<6>
					>
				>,
				Rgb<128,0,0>
			>,
			RotateColorsX<
				Sin<
					Scale<
						TwistAngle<>,
						Int<4>,
						Int<10>
					>
				>,
				Rgb<50,0,0>
			>,
			//3000
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
		>
	>,
	// Blade part 2?
	AlphaL<
		StripesX<
			Sin<
				Int<8>,
				Int<3000>,
				Int<6000>
			>,
			Scale<
				TwistAngle<>,
				Int<60>,
				Int<140>
			>,
			StripesX<
				Sin<
					Int<6>,
					Int<1000>,
					Int<3000>
				>,
				Scale<
					TwistAngle<>,
					Int<-25>,
					Int<-80>
				>,
				PulsingX<
					Mix<
						Sin<Int<4>>,
						RotateColorsX<
							Sin<Int<8>>,
							Red
						>,
						RotateColorsX<
							Sin<Int<6>>,
							Rgb<255,50,50>
						>
					>,
					RotateColorsX<
						Sin<
							Scale<
								TwistAngle<>,
								Int<4>,
								Int<0>
							>
						>,
						Rgb<20,0,0>
					>,
					//4000
					SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<4000>, Int<2000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
				>,
				Mix<
					Sin<Int<2>>,
					RotateColorsX<
						Sin<Int<8>>,
						Rgb<255,50,50>
					>,
					Black
				>
			>,
			RotateColorsX<
				Sin<Int<12>>,
				Rgb<60,0,0>
			>,
			PulsingX<
				RotateColorsX<
					Sin<Int<4>>,
					Rgb<50,0,0>
				>,
				StripesX<
					Sin<
						Int<2>,
						Int<2000>,
						Int<4000>
					>,
					Sin<
						Int<2>,
						Int<-25>,
						Int<-75>
					>,
					Mix<
						Sin<Int<4>>,
						RotateColorsX<
							Sin<Int<5>>,
							Red
						>,
						RotateColorsX<
							Sin<Int<16>>,
							Rgb<255,50,50>
						>
					>,
					RotateColorsX<
						Sin<Int<10>>,
						Rgb<96,0,0>
					>
				>,
				//2000
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<2000>, Int<1000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
			>,
			PulsingX<
				RotateColorsX<
					Sin<Int<9>>,
					Rgb<128,0,0>
				>,
				Black,
				//3000
				SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<3000>, Int<1500>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
			>
		>,
		Int<10000>
	>
>;

// Rainbow Stripes
using BaseStyle_Rainbow_Stripes = StripesX<
	//50000,
	SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<50000>, Int<5000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

	SWING_SPEED_SCLAE<
		SWING_SPEED_DEFAULT, 
		Scale<
			TwistAngle<>,
			Int<-100>,
			Int<-300>
		>,
		Scale<
			TwistAngle<>,
			Int<-500>,
			Int<-1000>
		>,
		Int<1000>, Int<2000>, Int<1000>, Int<2000>
	>,
	BASECOLOR,
	RotateColorsX<Int<5461>, BASECOLOR>,
	RotateColorsX<Int<10922>,BASECOLOR>,
	RotateColorsX<Int<16384>,BASECOLOR>,
	RotateColorsX<Int<21845>,BASECOLOR>,
	RotateColorsX<Int<27306>,BASECOLOR>
>;

// Rainbow Fire
using BaseStyle_Rainbow_Fire = StyleFire<
	StripesX<
		//30000,
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<20000>, Int<30000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
		Scale<
			TwistAngle<>,
			Int<-200>,
			Int<-100>
		>,
		BASECOLOR,
		RotateColorsX<Int<5461>,BASECOLOR>,
		RotateColorsX<Int<10922>,BASECOLOR>,
		RotateColorsX<Int<16384>,BASECOLOR>,
		RotateColorsX<Int<21845>,BASECOLOR>,
		RotateColorsX<Int<27306>,BASECOLOR>
	>,
	COLOR_MIX_P<
		50,
		StripesX<
			//30000,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<20000>, Int<30000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			Scale<
				TwistAngle<>,
				Int<-200>,
				Int<-100>
			>,
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
>;

// Omni rotating blade
using BaseStyle_Omni_Blade = RotateColorsX<
	Saw<
		//Int<1>
		SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<1>, Int<5>, Int<500>, Int<1000>, Int<4000>, Int<8000>>
	>,
	BASECOLOR
>;

// Glowstick 
using BaseStyle_Glowstick = Layers<
	Black,
	AlphaL<
		Layers<
			AudioFlicker<
				ALTCOLOR,
				AlphaL<
					Black,
					Int<10000>
				>
			>,
			TransitionLoopL<
				TrConcat<
					TrInstant,
					ALTCOLOR2, //Rgb<100,200,255>,
					TrDelay<50>,
					TRANSPARENT,
					TrDelay<360>
				>
			>,
			TransitionLoopL<
				TrConcat<
					TrInstant,
					AlphaL<
						BASECOLOR,
						SmoothStep<
							Int<30000>,
							Int<0>
						>
					>,
					TrDelay<180>,
					AlphaL<
						BASECOLOR,
						SmoothStep<
							Int<2000>,
							Int<-1>
						>
					>,
					TrDelay<180>
				>
			>
		>,
		Ifon<
			Int<32768>,
			Int<0>
		>
	>
>;

// Fire blade with bright tip? TODO: separate bright tip for secondary/tirtiary styles...
using BaseStyle_FireTipBlade =	Layers<
	StaticFire<
		Mix<
			SmoothStep<
				Scale<
					BladeAngle<>,
					Int<38000>,
					Int<23000>
				>,
				Int<8000>
			>,
			COLOR_MIX_P<2, BASECOLOR>,
			COLOR_MIX_P<20, BASECOLOR>
		>,
		TRANSPARENT,
		0,
		2,
		4,
		2000,
		2
	>
>;

// FireTip Base Blade style (BladeAngle Speed)
using BaseStyle_FireTipBase = Layers<
	StaticFire <
		StripesX<
			//Int<14000>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<14000>, Int<8000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			Scale<
				BladeAngle<>,
				Int<-5>,
				Int<-50>
			>,
			BASECOLOR,
			COLOR_MIX<
				Scale<
					HoldPeakF<
						SwingSpeed<250>,
						Int<1000>,
						Int<8000>
					>,
					Int<6000>,
					Int<16000>
				>,
				BASECOLOR
			>
		>,
		TRANSPARENT,
		0,
		2,
		4,
		2000,
		2
	>
>;

// TODO: Break up into separate pieces? 
// Static Electricity swing blade
using BaseStyle_StaticElectricity = Layers<
	Black,
	ColorSelect<
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
		AudioFlicker<
			BASECOLOR,
			COLOR_MIX<Int<18000>, BASECOLOR>
		>,
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
	>
>;

// Responsive Rotoscope
using BaseStyle_Rotoscope_Responsive = Mix<
	HoldPeakF<
		SwingSpeed<250>,
		Scale<
			SwingAcceleration<100>,
			Int<50>,
			Int<500>
		>,
		Scale<
			SwingAcceleration<>,
			Int<20000>,
			Int<10000>
		>
	>,
	Mix<
		Scale<
			IsLessThan<
				SlowNoise<Int<2000>>,
				Int<18000>
			>,
			Int<0>,
			Int<32768>
		>,
		BASECOLOR,
		StripesX<
			//Int<12000>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<12000>, Int<8000>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,
			//Int<-800>,
			SWING_SPEED_SCLAE<SWING_SPEED_DEFAULT, Int<-800>, Int<-1200>, Int<500>, Int<1000>, Int<4000>, Int<8000>>,

			BASECOLOR,
			BASECOLOR,
			COLOR_MIX<Int<7710>, BASECOLOR>,
			BASECOLOR,
			COLOR_MIX<Int<16448>, BASECOLOR>
		>
	>,
	BASECOLOR
>;

// TEST ME

// Rotoscope (Original Trilogy)
using BaseStyle_Rotoscope_Original = RandomFlicker<
	Stripes<	
		10000,
		-2600,
		BASECOLOR,
		BASECOLOR,
		COLOR_MIX<Int<7710>, BASECOLOR>,
		BASECOLOR,
		COLOR_MIX<Int<16448>, BASECOLOR>
	>,
	BASECOLOR
>;

// Audio Rotoscope (Original Trilogy)
using BaseStyle_Rotoscope_Audio_Original = AudioFlicker<
	Stripes<
		10000,
		-2600,
		BASECOLOR,
		BASECOLOR,
		COLOR_MIX<Int<7710>, BASECOLOR>,
		BASECOLOR,
		COLOR_MIX<Int<16448>, BASECOLOR>
	>,
	BASECOLOR
>;
			
// Rotoscope (Prequels)
using BaseStyle_Rotoscope_Prequel = RandomFlicker<
	Stripes<
		24000,
		-1400,
		BASECOLOR,
		BASECOLOR,
		COLOR_MIX<Int<11565>, BASECOLOR>,
		BASECOLOR,
		COLOR_MIX<Int<16448>, BASECOLOR>
	>,
	BASECOLOR
>;
			
// Rotoroscope (Sequels)
using BaseStyle_Rotoscope_Sequel = RandomFlicker<
	Stripes<
		14000,
		-4000,
		BASECOLOR,
		BASECOLOR,
		COLOR_MIX<Int<7710>, BASECOLOR>,
		BASECOLOR,
		COLOR_MIX<Int<16448>, BASECOLOR>
	>,
	BASECOLOR
>;

// TEST Survivor font, uses USER1 - 4 options to change colors.
using BaseStyle_Survivor = ColorSelect<
	AltF,
	TrInstant,
			
	// BaseColor
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<8000>,
			Int<3000>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<-2600>,
			Int<-3600>
		>,
		RgbArg<BASE_COLOR_ARG,Rgb<0,0,255>>,
		Mix<
			Int<12000>,
			Black,
			RgbArg<BASE_COLOR_ARG,Rgb<0,0,255>>
		>,
		Pulsing<
			RgbArg<BASE_COLOR_ARG,Rgb<0,0,255>>,
			Mix<
				Int<8000>,
				Black,
				RgbArg<BASE_COLOR_ARG,Rgb<0,0,255>>
			>,
			1400
		>
	>,
			
	// AltColor
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<10000>,
			Int<5000>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<-2000>,
			Int<-3000>
		>,
		RgbArg<ALT_COLOR_ARG,Rgb<0,255,255>>,
		Mix<
			Int<12000>,
			Black,
			RgbArg<ALT_COLOR_ARG,Rgb<0,255,255>>
		>,
		Pulsing<
			RgbArg<ALT_COLOR_ARG,Rgb<0,255,255>>,
			Mix<
				Int<8000>,
				Black,
				RgbArg<ALT_COLOR_ARG,Rgb<0,255,255>>
			>,
			1400
		>
	>,
			
	// Alt Color 2
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<4000>,
			Int<1800>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<2000>,
				Int<4000>
			>,
			Int<-2800>,
			Int<-4000>
		>,
		Mix<
			Int<16000>,
			Black,
			RgbArg<ALT_COLOR2_ARG,Rgb<0,255,0>>
		>,
		Mix<
			Sin<
				Int<20>,
				Int<22000>,
				Int<32768>
			>,
			Black,
			RgbArg<ALT_COLOR2_ARG,Rgb<0,255,0>>
		>,
		Mix<
			Int<8000>,
			Black,
			RgbArg<ALT_COLOR2_ARG,Rgb<0,255,0>>
		>
	>,
			
	// Alt Color 3
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<9000>,
			Int<4000>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<-2400>,
			Int<-3000>
		>,
		RgbArg<ALT_COLOR3_ARG,Rgb<80,50,210>>,
		Mix<
			Int<15000>,
			Black,
			RgbArg<ALT_COLOR3_ARG,Rgb<80,50,210>>
		>,
		Pulsing<
			RgbArg<ALT_COLOR3_ARG,Rgb<80,50,210>>,
			Mix<
				Int<10000>,
				Black,
				RgbArg<ALT_COLOR3_ARG,Rgb<80,50,210>>
			>,
			600
		>
	>,
			
	// MAGENTA
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<9000>,
			Int<4000>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<-2000>,
			Int<-3000>
		>,
		Rgb<255,0,255>,
		Mix<
			Int<12000>,
			Black,
			Rgb<255,0,255>
		>,
		Pulsing<
			Rgb<255,0,255>,
			Mix<
				Int<8000>,
				Black,
				Rgb<255,0,255>
			>,
			800
		>
	>,
			
	// Orange
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<4000>,
			Int<1800>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<2000>,
				Int<4000>
			>,
			Int<-2800>,
			Int<-4000>
		>,
		Mix<
			Int<16000>,
			Black,
			Rgb<255,68,0>
		>,
		Mix<
			Sin<
				Int<20>,
				Int<20000>,
				Int<32768>
			>,
			Black,
			Rgb<255,68,0>
		>,
		Mix<
			Int<10000>,
			Black,
			Rgb<255,68,0>
		>
	>,
			
	// Purple
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Sin<
				Int<20>,
				Int<10000>,
				Int<7000>
			>,
			Int<3000>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<2000>,
				Int<4000>
			>,
			Int<-2300>,
			Int<-4000>
		>,
		Rgb<115,15,240>,
		Mix<
			Int<12000>,
			Black,
			Rgb<115,15,240>
		>,
		Pulsing<
			Rgb<115,15,240>,
			Mix<
				Int<20000>,
				Black,
				Rgb<115,15,240>
			>,
			2000
		>
	>,
			
	// White
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<4000>,
			Int<1800>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<2000>,
				Int<4000>
			>,
			Int<-3000>
			,Int<-4500>
		>,
		Mix<
			Int<16000>,
			Black,
			Rgb<100,100,150>
		>,
		Mix<
			Sin<
				Int<20>,
				Int<22000>,
				Int<32768>
			>,
			Black,
			Rgb<100,100,150>
		>,
		Mix<
			Int<8000>,
			Black,
			Rgb<100,100,150>
		>
	>,
			
	// Yellow
	StripesX<
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<3000>,
				Int<3000>
			>,
			Int<3600>,
			Int<1600>
		>,
		Scale<
			HoldPeakF<
				Sum<
					EffectPulseF<EFFECT_IGNITION>,
					EffectPulseF<EFFECT_ALT_SOUND>
				>,
				Int<2000>,
				Int<4000>
			>,
			Int<-2700>,
			Int<-4100>
		>,
		Mix<
			Int<16000>,
			Black,
			Rgb<180,130,0>
		>,
		Mix<
			Sin<
				Int<20>,
				Int<22000>,
				Int<32768>
			>,
			Black,
			Rgb<180,130,0>
		>,
		Mix<
			Int<8000>,
			Black,
			Rgb<180,130,0>
		>
	>
>;