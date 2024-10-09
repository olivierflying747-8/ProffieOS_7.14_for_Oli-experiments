#ifdef CONFIG_TOP
#include "proffieboard_config.h"
#define NUM_BLADES 1
#define NUM_BUTTONS 1
#define VOLUME 1700
const unsigned int maxLedsPerStrip = 144;
#define CLASH_THRESHOLD_G 17.0
#define MOTION_TIMEOUT 60 * 5 * 1000
#define IDLE_OFF_TIME 60 * 5 * 1000
#define ENABLE_AUDIO
#define ENABLE_MOTION
#define ENABLE_WS2811
#define ENABLE_SD
#define ENABLE_SERIAL
//#define NO_COLOR_SWING
//#define NO_SAVED_PRESET
//#define NO_LOCKUP_HOLD
#define SAVE_STATE //#define SAVE_PRESET
//#define COLOR_CHANGE_DIRECT // this enables "click to change"
// this disables some diagnostic commands to save memory
#define DISABLE_DIAGNOSTIC_COMMANDS
//#define DISABLE_TALKIE // Changes talky to simple beeps
//#define FEMALE_TALKIE_VOICE
#define NO_REPEAT_RANDOM
#define KILL_OLD_PLAYERS
//#define FETT263_TWIST_ON
//#define FETT263_TWIST_ON_NO_BM
//#define FETT263_TWIST_OFF
#define FETT263_SWING_ON
#define FETT263_SWING_ON_NO_BM
#define FETT263_SWING_ON_SPEED 600
#define FETT263_THRUST_ON
#define FETT263_THRUST_ON_NO_BM
#define FETT263_STAB_ON
#define FETT263_STAB_ON_NO_BM
#define FETT263_BATTLE_MODE
#define FETT263_LOCKUP_DELAY 200
#define FETT263_FORCE_PUSH
#define FETT263_FORCE_PUSH_LENGTH 5
#define FETT263_SAY_BATTERY_PERCENT
#define FETT263_MOTION_WAKE_POWER_BUTTON
#define FETT263_SPECIAL_ABILITIES //#define FETT263_MULTI_PHASE
// Edit Mode
#define FETT263_EDIT_MODE_MENU
#define ENABLE_ALL_EDIT_OPTIONS
#define DISABLE_BASIC_PARSER_STYLES
#define KEEP_SAVEFILES_WHEN_PROGRAMMING
#define FETT263_SAY_COLOR_LIST
#define FETT263_SAY_COLOR_LIST_CC
#endif

#ifdef CONFIG_PROP
#include "../props/saber_fett263_buttons.h"
#endif


/* VALID FONT FOlDERS: 47 (+2 for common/tracks)

// Common Folders
common
tracks
.voices
	Ahsoka_CW
	Anakin_CW
	Anakin_HC
	Ben_Kenobi
	Bendu
	C3P0
	Cal_Kestis
	Din_Djarin
	Dooku
	Dooku_CW
	Emperor
	Ezra
	General_Kenobi
	Hati
	Hyang
	Kanan
	Kylo
	Luke_ANH
	Mace
	Malgus
	Maul
	Narrator
	Obi-Wan_CW
	Obi-Wan_EP3
	Princess_Leia
	Qui-Gon
	Rebel_Leia
	Savage
	Skoll
	Starkiller
	The_Ronin
	Thrawn
	Vader
	Ventress
	Yoda

// Free Fonts
001_BLUE
002_GREEN
003_PURPLE
004_RED
005_WHITE
006_YELLOW
007_Battle
008_Battle2
009_Analog
010_Apocalypse
011_Assassin
012_Coda
013_Crispity
014_Deadlink
015_Decay
016_Endure
017_EngineGrip
018_Exalted
019_Grey
020_Magnetic
021_Masterless
022_Mercenary
023_Noble
024_Ra
025_Seethe
026_Splinter
027_Volatile
028_PeaceInOurTime
029_Metropolis
030_Arcane
031_Nameless
032_Rey
033_SenateMajority
034_TheReturn
035_TheMaw
036_Slave
037_Decimate
038_Knighthood
039_Corvus_Tano
040_Kashyyyk_Knight

// Paid Fonts
075_Ascension
076_Proto
077_RM_Ben
078_RM_Darth
079_RM_Third
080_Hero
081_ProjectStardust
082_AncientSaber
083_OneXWing
084_GreyAssassin
085_Quis-Gone
086_TheSurvivor
087_TinyDroid
088_ThunderGod
089_Mother
090_Second
091_GhostSucker
092_Staff
093_SmashSword
094_MagCyl
095_ShockBaton
096_Metamorphose
097_WarpStar
098_Party

// Goofy Fonts
101_PartyFoul
102_Lightsaber_Of_The_Bells
103_Lumos
104_Thanos
105_ThePredator
106_WildChild
107_WitchKing
108_EnergySword
109_Rave
110_Batman
111_JarJar
112_C-137
113_N1_Mod
114_ElectricMouse
115_SailorMoon
116_JurassicPark
117_Alien
118_Godzilla
119_Sebulba
120_

*/

#ifdef CONFIG_PRESETS

// Master Font for Edit mode, create /customize your own blade styles using StylePtr<MasterStyle>() and Fett263's Edit Menu.
#include "master/Master_v3.h"

// Font Presets. Just load as many font folders as you want with Master Style.
Preset presets[] = {

	 /*
	// One starter font, use Copy Preset to make more.
	{ "059_RM_Third;common", "tracks/",
	 StylePtr <MasterStyle>	(), ""},
	*/

//	 /*
// Basic Fonts: 6 by Kyberphonic
	{ "001_BLUE;;common","tracks/fates.wav",
		StylePtr <MasterStyle>(), "blue"},

	/*
	{ "002_GREEN;common","tracks/fates.wav",
		StylePtr <MasterStyle>
		() , "green"
	},

	{ "003_PURPLE;common","tracks/fates.wav",
		StylePtr <MasterStyle>
		() , "purple"
	},

	{ "004_RED;common","tracks/fates.wav",
		StylePtr <MasterStyle>
		() , "red"
	},

	{ "005_WHITE;common","tracks/",
		StylePtr <MasterStyle>
		()  //, "white"
	},

	{ "006_YELLOW;common","tracks/fates.wav",
		StylePtr <MasterStyle>
		() , "yellow"
	},

	// /*

// Custom Free Fonts: 33
	
	// Battlefield v1 by Kyberfonic
	{ "007_Battle;common", "tracks/fates.wav",
		StylePtr <MasterStyle>
		() , "battle1"
	},

	// Battlefield v2 by Kyberfonic
	{ "008_Battle2;common","tracks/fates.wav",
		StylePtr <MasterStyle>
		() , "battle2"
	},

	// Analog by Grayscale
	{ "009_Analog;common","tracks/",
		StylePtr <MasterStyle>
		() , "analog"
	},

	// Apocolypse by Grayscale
	{ "010_Apocalypse;common","tracks/",
		StylePtr <MasterStyle>
		() , "apocalypse"
	},

	// Assassin by Grayscale
	{ "011_Assassin;common", "tracks/JFO9.wav",
		StylePtr <MasterStyle>
		() , "assassin" 
	},

	// Coda by Grayscale
	{ "012_Coda;common", "tracks/JFO19.wav",
		StylePtr <MasterStyle>
		() , "coda" 
	},

	// Crispity by Grayscale
	{ "013_Crispity;common","tracks/",
		StylePtr <MasterStyle>
		() , "crispity"
	},

	// Deadlink by Grayscale
	{ "014_Deadlink;common","tracks/",
		StylePtr <MasterStyle>
		() , "deadlink"
	},

	// Decay by Grayscale
	{ "015_Decay;common","tracks/",
		StylePtr <MasterStyle>
		() , "decay"
	},

	// Endure by Grayscale
	{ "016_Endure;common","tracks/",
		StylePtr <MasterStyle>
		() , "endure"
	},

	// EngineGrip by Grayscale
	{ "017_EngineGrip;common","tracks/",
		StylePtr <MasterStyle>
		() , "enginegrip"
	},

	// Exhalted by Grayscale
	{ "018_Exalted;common","tracks/",
		StylePtr <MasterStyle>
		() , "exalted"
	},

	// Grey by Grayscale
	{ "019_Grey;common","tracks/",
		StylePtr <MasterStyle>
		() , "Grey"
	},

	// Magnetic by Grayscale
	{ "020_Magnetic;common","tracks/",
		StylePtr <MasterStyle>
		() , "magnetic"
	},

	// Masterless by Grayscale
	{ "021_Masterless;common","tracks/",
		StylePtr <MasterStyle>
		() , "masterless"
	},

	// Mercenary by Grayscale
	{ "022_Mercenary;common", "tracks/venus.wav",
		StylePtr <MasterStyle>
		() , "mercenary"
	},

	// Noble by Grayscale
	{ "023_Noble;common", "tracks/Spoiler.wav",
		StylePtr <MasterStyle>
		() , "noble"
	},

	// Ra by Grayscale
	{ "024_Ra;common","tracks/",
		StylePtr <MasterStyle>
		() , "ra"
	},

	// Seethe by Grayscale
	{ "025_Seethe;common", "tracks/JFO18.wav",
		StylePtr <MasterStyle>
		() , "seethe" 
	},

	// Splinter by Grayscale
	{ "026_Splinter;common", "tracks/",
		StylePtr<MasterStyle>
		() , "splinter"
	},

	// Volatile by Grayscale
	{ "027_Volatile;common", "tracks/",
		StylePtr< MasterStyle>
		(), //"volatile"
	},

	// Age Of Ultron by Harry Solo
	{ "028_PeaceInOurTime;common","tracks/",
		StylePtr <MasterStyle>
		() , "peaceinourtime"
	},

	// Metropolis by Jasper Aykroyd (The Bacon Wizard)
	{ "029_Metropolis;common", "tracks/",
		StylePtr <MasterStyle>
		() , "metropolis"
	},

	// Arcane by TehMothman
	{ "030_Arcane;common", "tracks/",
		StylePtr <MasterStyle>
		() , "arcane"
	},

	// Nameless by TehMothman
	{ "031_Nameless;common", "tracks/",
		StylePtr <MasterStyle>
		() , "nameless"
	},

	// "Rey Skywalker" Smoothswing Font by Daryl John Donato
	{ "032_Rey;common", "tracks/",
		StylePtr <MasterStyle>
		() , "rey"
	},

	// Senate Majority v2 by ???
	{ "033_SenateMajority;common", "tracks/",
		StylePtr <MasterStyle>
		() , "senatemajority"
	},

	// The Return by ???
	{ "034_TheReturn;common", "tracks/",
		StylePtr <MasterStyle>
		() , "thereturn"
	},

	// The Maw by Brian Conner
	{ "035_TheMaw;common", "tracks/",
		StylePtr <MasterStyle>
		() , "themaw"
	},

	// Slave1 2.1 by Brian Conner
	{ "036_Slave;common", "tracks/",
		StylePtr <MasterStyle>
		() , "slave"
	},

	// Decimate by Jay Dalorian
	{ "037_Decimate;common", "tracks/",
		StylePtr <MasterStyle>
		() , "decimate"
	},

	// Knighthood by Fourze
	{ "038_Knighthood;common", "tracks/",
		StylePtr <MasterStyle>
		() , "knighthood"
	},

	// Corvus_Tano by Ninja Jedi Order
	{ "039_Corvus_Tano;common", "tracks/",
		StylePtr <MasterStyle>
		() , "corvustano"
	},

// Paid Fonts: 18

	// Ascension by KSith
	{ "075_Ascension;common", "tracks/",
		StylePtr <MasterStyle>
		() , "ascension"
	},

	// Proto by KSith
	{ "076_Proto;common", "tracks/",
		StylePtr <MasterStyle>
		() , "proto"
	},

	// The Rematch Bundle - Ben by Kyberphonic
	{ "077_RM_Ben;common", "tracks/",
		StylePtr <MasterStyle>
		() , "rm_ben"
	},

	// The Rematch Bundle - Darth by kyberphonic
	{ "078_RM_Darth;common", "tracks/",
		StylePtr <MasterStyle>
		() , "rm_darth"
	},

	// The Rematch Bundle - Third by kyberphonic
	{ "079_RM_Third;common", "tracks/",
		StylePtr <MasterStyle>
		() , "rm_third"
	},

	// Hero (Obiwan EP3) by kyberphonic
	{ "080_Hero;common", "tracks/",
		StylePtr <MasterStyle>
		() , "hero"
	},

	// Project Stardust by Kyberphonic
	{ "081_ProjectStardust;common", "tracks/",
		StylePtr <MasterStyle>
		() , "projectstardust"
	},

	// Ancient Saber by SaberFont
	{ "082_AncientSaber;common", "tracks/",
		StylePtr <MasterStyle>
		() , "ancientsaber"
	},

	// One X Wing (Mandalorian Luke inspired) by BK Saber Sounds
	{ "083_OneXWing;common", "tracks/",
		StylePtr <MasterStyle>
		() , "onexwing"
	},

	// Grey Assassin by BK Saber Sounds
	{ "084_GreyAssassin;common", "tracks/",
		StylePtr <MasterStyle>
		() , "greyassassin"
	},

	// Qui's-Gone by KSith
	{ "085_Quis-Gone;common","tracks/Fates.wav",
		StylePtr <MasterStyle>
		() , "ginn"
	},

	// The Survivor by BK Saber Sounds
	{ "086_TheSurvivor;common", "tracks/",
		StylePtr <MasterStyle>
		() , "thesurvivor"
	},

	// Tiny Droid by BK Saber Sounds
	{ "087_TinyDroid;common", "tracks/",
		StylePtr <MasterStyle>
		() , "tinydroid"
	},

	// Thunder God (Thor Avengers) by Kyberphonic
	{ "088_ThunderGod;common", "tracks/Ragnorok.wav",
		StylePtr<MasterStyle>
		() , "thundergod"
	},

	// Great Mother by Kyberphonic
	{ "089_Mother;common", "tracks/",
		StylePtr <MasterStyle>
		() , "mother"
	},

	// Second Sister by KSith
	{ "090_Second;common", "tracks/JFO19.wav",
		StylePtr<MasterStyle>
		() , "second"
	},

	// Ghost Sucker by Kyberphonic
	{ "091_GhostSucker;common", "tracks/ReyParkerJr.wav",
		StylePtr<MasterStyle>
		() , "ghostsucker"
	},

	// Electric Staff by Kyberphonic
	{ "092_Staff;common", "tracks/fates.wav",
		StylePtr<MasterStyle>
		() , "staff"
	},

	// Smash Sword by Kyberphonic
	{ "093_SmashSword;common", "tracks/Bro.wav",
		StylePtr<MasterStyle>
		() , "smashsword"
	},

	// Mag-Cyl (The Atom Project) by Kyberphonic
	{ "094_MagCyl;common", "tracks/JFO19.wav",
		StylePtr<MasterStyle>
		() , "magcyl"
	},

	// Shock Baton by Kyberphonic
	{ "095_ShockBaton;common", "tracks/TFA.wav",
		StylePtr<MasterStyle>
		() , "shockbaton"
	},

	// Metamorphose by Kyberphonic
	{ "096_Metamorphose;common", "tracks/Arrival.wav",
		StylePtr<MasterStyle>
		() , "metamorphose"
	},

	// Warp Star by Kyberphonic
	{ "097_WarpStar;common", "tracks/JFO19.wav",
		StylePtr<MasterStyle>
		() , "warpstar"
	},

	// Party by ???
	{ "098_Party;common", "tracks/meco.wav",
		StylePtr<MasterStyle>
		() , "party"
	},

// Free Goofy Fonts

	// Party Foul by BK Saber Sounds
	{ "101_PartyFoul;common", "tracks/",
		StylePtr <MasterStyle>
		() , "partyfoul"
	},

	// Lightsaber of the Bells by Jérôme Tremblay ( Jay DaloRian) 
	{ "102_Lightsaber_Of_The_Bells;common", "tracks/",
		StylePtr <MasterStyle>
		() , "lightsaberofthebells"
	},

	// Lumos by KidsTryThisAtHome / naitsirkc
	{ "103_Lumos;common", "tracks/",
		StylePtr <MasterStyle>
		() , "lumos"
	},

	// Thanos by UltraInstinctKermit
	{ "104_Thanos;common", "tracks/",
		StylePtr <MasterStyle>
		() , "thanos"
	},

	// The Predator by Josh Pearl
	{ "105_ThePredator;common", "tracks/",
		StylePtr <MasterStyle>
		() , "thepredator"
	},

	// Wild Child by ???
	{ "106_WildChild;common", "tracks/",
		StylePtr <MasterStyle>
		() , "wildchild"
	},

	// Witch King by ???
	{ "107_WitchKing;common", "tracks/",
		StylePtr <MasterStyle>
		() , "witchking"
	},

	// Energy Sword by XTwistyBoi
	{ "108_EnergySword;common", "tracks/",
		StylePtr <MasterStyle>
		() , "energysword"
	},

	// Rave by Brian Conner
	{ "109_Rave;common", "tracks/",
		StylePtr <MasterStyle>
		() , "rave"
	},

	// Batman by Meaty Smurf
	{ "110_Batman;common", "tracks/",
		StylePtr <MasterStyle>
		() , "batman"
	},

	// JarJar by Darth Hater
	{ "111_JarJar;common", "tracks/",
		StylePtr <MasterStyle>
		() , "jarjar"
	},

	// C-137 by Harry Solo Fonts and Synplicity
	{ "112_C-137;common", "tracks/",
		StylePtr <MasterStyle>
		() , "c-136"
	},

	// N1_Mod by kyberphonic
	{ "113_N1_Mod;common", "tracks/",
		StylePtr <MasterStyle>
		() , "n1_mod"
	},

	// ElectricMouse by kyberphonic
	{ "114_ElectricMouse;common", "tracks/",
		StylePtr <MasterStyle>
		() , "electricmouse"
	},

	// Sailor Moon by kyberphonic
	{ "115_SailorMoon;common", "tracks/",
		StylePtr <MasterStyle>
		() , "sailormoon"
	},

	// JurassicPark by ???
	{ "116_JurassicPark;common", "tracks/",
		StylePtr <MasterStyle>
		() , "jurassicpark"
	},

	// Alien by Blue Force Sabers
	{ "117_Alien;common", "tracks/",
		StylePtr <MasterStyle>
		() , "alien"
	},

	// Godzilla by ???
	{ "118_Godzilla;common", "tracks/",
		StylePtr <MasterStyle>
		() , "godzilla"
	},

	// Sebulba by 
	{ "119_Sebulba;common", "tracks/",
		StylePtr <MasterStyle>
		() , "sebulba"
	},

	// Silent Hill by me
	{ "120_SilentHill;common", "tracks/",
		StylePtr <MasterStyle>
		() , "silenthill"
	},



	//	*/

	/*
	{ "Coda;common", "tracks/JFO19.wav",
		StylePtr <
			Layers <
				// BASE BLADE
				AudioFlicker<
					Stripes<
						23000,
						-1300,
						RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>,
						RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>,
						Mix<
							Int<11284>,
							Black,
							RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>
						>,
						RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>,
						Mix<
							Int<16384>,
							Black,
							RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>
						>
					>,
					RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>
				>,
				// USER 3 RAIN EFFECT??
				ColorSelect<
					EffectIncrementF<
						EFFECT_USER3,
						Int<2>
					>,
					TrFade<100>,
					AlphaL<
						White,
						Int<0>
					>,
					AlphaL<
						RgbArg<RETRACTION_COLOR_ARG,Rgb<255,255,255>>,
						SparkleF<300,800>
					>
				>,
				// USER 3 SOUND EFFECT
				TransitionEffectL<
					TrDoEffect<
						TrInstant,
						EFFECT_SOUND_LOOP,
						0
					>,
					EFFECT_USER3
				>,
				// STAB EFFECT
				TransitionEffectL<
					TrConcat<
						TrJoin<
							TrDelayX<
								WavLen<>
							>,
							TrWipeIn<200>
						>,
						AlphaL<
							AudioFlickerL<
								RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>
							>,
							SmoothStep<
								IntArg<MELT_SIZE_ARG,28000>,
								Int<2000>
							>
						>,
						TrWipe<200>
					>,
					EFFECT_STAB
				>,

				// BLAST EFFECT
				TransitionEffectL <
					TrRandom <
						TrWaveX<
							RgbArg<BLAST_COLOR_ARG,Rgb<255,199,119>>,
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
							Scale<
								EffectPosition<EFFECT_BLAST>,
								Int<28000>,
								Int<8000>
							>
						>,
						TrConcat<
							TrJoin<
								TrDelay<30>,
								TrInstant
							>,
							RgbArg<BLAST_COLOR_ARG,Rgb<255,199,119>>,
							TrFade<300>
						>
					> ,
					EFFECT_BLAST
				> ,

				// CLASH EFFECT
				Mix <
					IsLessThan<
						ClashImpactF<>,
						Int<26000>
					>,
					TransitionEffectL <
						TrConcat <
							TrInstant,
							AlphaL <
								RgbArg<CLASH_COLOR_ARG,Rgb<255,199,119>>,
								Bump <
									Scale<
										BladeAngle<>,
										Scale<
											BladeAngle<0,16000>,
											Sum<
												IntArg<LOCKUP_POSITION_ARG,16000>,
												Int<-12000>
											>,
											Sum<
												IntArg<LOCKUP_POSITION_ARG,16000>,
												Int<10000>
											>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-10000>
										>
									>,
									Scale<
										ClashImpactF<>,
										Int<12000>,
										Int<60000>
									>
								>
							> ,
							TrFadeX<
								Scale<
									ClashImpactF<>,
									Int<200>,
									Int<400>
								>
							>
						> ,
						EFFECT_CLASH
					> ,
					TransitionEffectL <
						TrWaveX <
							RgbArg<CLASH_COLOR_ARG,Rgb<255,199,119>>,
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
							Scale<
								BladeAngle<>,
								Scale<
									BladeAngle<0,16000>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-12000>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<10000>
									>
								>,
								Sum<
									IntArg<LOCKUP_POSITION_ARG,16000>,
									Int<-10000>
								>
							>
						> ,
						EFFECT_CLASH
					>
				> ,

				// LOCKUP EFFECT
				LockupTrL <
					// LOCKUP BEGIN
					TransitionEffect <
						AlphaL <
							AlphaMixL <
								Bump <
									Scale<
										BladeAngle<>,
										Scale<
											BladeAngle<0,16000>,
											Sum<
												IntArg<LOCKUP_POSITION_ARG,16000>,
												Int<-12000>
											>,
											Sum<
												IntArg<LOCKUP_POSITION_ARG,16000>,
												Int<10000>
											>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-10000>
										>
									>,
									Scale<
										SwingSpeed<100>,
										Int<14000>,
										Int<22000>
									>
								> ,
								AudioFlicker<
									RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>,
									Mix<
										Int<12000>,
										Black,
										RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>
									>
								>,
								BrownNoiseFlicker<
									RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>,
									Mix<
										Int<12000>,
										Black,
										RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>
									>,
									300
								>
							> ,
							Bump <
								Scale<
									BladeAngle<>,
									Scale<
										BladeAngle<0,16000>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-12000>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<10000>
										>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-10000>
									>
								>,
								Scale<
									SwingSpeed<100>,
									Int<14000>,
									Int<22000>
								>
							>
						> ,
						AlphaL <
							AudioFlicker<
								RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>,
								Mix<
									Int<20000>,
									Black,
									RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>
								>
							>,
							Bump <
								Scale<
									BladeAngle<>,
									Scale<
										BladeAngle<0,16000>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-12000>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<10000>
										>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-10000>
									>
								>,
								Scale<
									SwingSpeed<100>,
									Int<14000>,
									Int<18000>
								>
							>
						> ,
						TrExtend<
							5000,
							TrInstant
						>,
						TrFade<5000>,
						EFFECT_LOCKUP_BEGIN
					> ,
					// LOCKUP
					TrConcat <
						TrJoin<
							TrDelay<50>,
							TrInstant
						>,
						Mix <
							IsLessThan<
								ClashImpactF<>,
								Int<26000>
							>,
							RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>,
							AlphaL <
								RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>,
								Bump <
									Scale<
										BladeAngle<>,
										Scale<
											BladeAngle<0,16000>,
											Sum<
												IntArg<LOCKUP_POSITION_ARG,16000>,
												Int<-12000>
											>,
											Sum<
												IntArg<LOCKUP_POSITION_ARG,16000>,
												Int<10000>
											>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-10000>
										>
									>,
									Scale<
										ClashImpactF<>,
										Int<20000>,
										Int<60000>
									>
								>
							>
						> ,
						TrFade<300>
					> ,
					// LOCKUP END
					TrConcat<
						TrInstant,
						RgbArg<LOCKUP_COLOR_ARG,Rgb<255,199,119>>,
						TrFade<400>
					>,
					SaberBase::LOCKUP_NORMAL,
					Int<1>
				> ,

				// LIGHTNING BLOCK
				ResponsiveLightningBlockL <
					// LB
					Strobe<
						RgbArg<LB_COLOR_ARG,Rgb<191,255,255>>,
						AudioFlicker<
							RgbArg<LB_COLOR_ARG,Rgb<191,255,255>>,
							Blue
						>,
						50,
						1
					>,
					// LB START
					TrConcat<
						TrExtend<
							200,
							TrInstant
						>,
						AlphaL<
							RgbArg<LB_COLOR_ARG,Rgb<191,255,255>>,
							Bump<
								Scale<
									BladeAngle<>,
									Int<10000>,
									Int<21000>
								>,
								Int<10000>
							>
						>,
						TrFade<200>
					>,
					// LB END
					TrConcat<
						TrInstant,
						RgbArg<LB_COLOR_ARG,Rgb<191,255,255>>,
						TrFade<400>
					>,
					Int<1>
				> ,

				// DRAG EFFECT
				LockupTrL <
					AlphaL <
					// DRAG BEGIN
					TransitionEffect<
						RandomPerLEDFlickerL<RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>>,
						BrownNoiseFlickerL<
							RgbArg<DRAG_COLOR_ARG,Rgb<255,255,255>>,
							Int<300>
						>,
						TrExtend<
							4000,
							TrInstant
						>,
						TrFade<4000>,
						EFFECT_DRAG_BEGIN
					>,
					// DRAG SIZE
					SmoothStep<
						Scale<
							TwistAngle<>,
							IntArg<DRAG_SIZE_ARG,28000>,
							Int<30000>
						>,
						Int<3000>
					>
				> ,
				// DRAG IN/OUT EFFECT
				TrWipeIn<200>,
				TrWipe<200>,
				SaberBase::LOCKUP_DRAG,
				Int<1>
				> ,

				// STAB EFFECT
				LockupTrL <
					AlphaL <
						Stripes <
							2000,
							4000,
							Mix<
								TwistAngle<>,
								RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,
								RotateColorsX<
									Int<3000>,
									RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>
								>
							>,
							Mix<
								Sin<
									Int<50>
								>,
								Black,
								Mix<
									TwistAngle<>,
									RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,
									RotateColorsX<
										Int<3000>,
										RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>
									>
								>
							>,
							Mix<
								Int<4096>,
								Black,
								Mix<
									TwistAngle<>,
									RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,
									RotateColorsX<
										Int<3000>,
										RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>
									>
								>
							>
						> ,
					// STAB SIZE
					SmoothStep<
						Scale<
							TwistAngle<>,
							IntArg<MELT_SIZE_ARG,28000>,
							Int<30000>
						>,
						Int<3000>
					>
				> ,
				// STAB START EFFECT
				TrConcat <
					TrExtend<
						4000,
						TrWipeIn<200>
					>,
					AlphaL <
						HumpFlicker <
							Mix<
								TwistAngle<>,
								RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,
								RotateColorsX<
									Int<3000>,
									RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>
								>
							>,
							RotateColorsX<
								Int<3000>,
								Mix<
									TwistAngle<>,
									RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>,
									RotateColorsX<
										Int<3000>,
										RgbArg<STAB_COLOR_ARG,Rgb<255,68,0>>
									>
								>
							>,
							100
						> ,
						SmoothStep<
							Scale<
								TwistAngle<>,
								IntArg<MELT_SIZE_ARG,28000>,
								Int<30000>
							>,
							Int<3000>
						>
					> ,
					TrFade<4000>
				> ,
				TrWipe<200>,
				SaberBase::LOCKUP_MELT,
				Int<1>
				> ,

				// BLAST EFFECT
				TransitionEffectL<
					TrConcat<
						TrDelayX<
							Mult<
								WavLen<EFFECT_INTERACTIVE_BLAST>,
								Int<24576>
							>
						>,
						AlphaL<
							White,
							Int<0>
						>,
						TrDoEffect<
							TrInstant,
							EFFECT_GAME_CHOICE
						>
					>,
					EFFECT_INTERACTIVE_BLAST
				>,
				// EFFECT GAME CHOICE: Choose to deflect blast.
				TransitionEffectL<
					TrConcat<
						TrExtendX<
							IntArg<STYLE_OPTION2_ARG,1000>,
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
						TrInstant
					>,
					EFFECT_GAME_CHOICE
				>,

				// IN / OUT EFFECT
				InOutTrL <
					// IGNITION EFFECT
					TrSelect <
						IntArg<IGNITION_OPTION_ARG,0>,
						TrWipeSparkTipX<
							RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>,
							BendTimePowInvX<
								IgnitionTime<300>,
								Mult<
									IntArg<IGNITION_OPTION2_ARG,10992>,
									Int<98304>
								>
							>
						>,
						TrWipeX<
							BendTimePowInvX<
								IgnitionTime<300>,
								Mult<
									IntArg<IGNITION_OPTION2_ARG,10992>,
									Int<98304>
								>
							>
						>
					> ,

					// RETRACTION EFFECT
					TrWipeInX<
						BendTimePowInvX<
							RetractionTime<0>,
							Mult<
								IntArg<RETRACTION_OPTION2_ARG,10992>,
								Int<98304>
							>
						>
					>,
					Black
				> ,

				// EFFECT USER 7
				TransitionEffectL<
					TrConcat<
						TrDelayX<
							Int<1000>
						>,
						AlphaL<
							White,
							Int<0>
						>,
						TrConcat<
							TrInstant,
							AudioFlickerL<
								RgbArg<IGNITION_COLOR_ARG,Rgb<255,255,255>>
							>,
							TrFade<1200>
						>
					>,
					EFFECT_USER7
				>,

				TransitionEffectL<
					TrConcat<
						TrDelayX<
							Int<1000>
						>,
						Black,
						TrWipeX<
							Int<300>
						>
					>,
					EFFECT_USER7
				>,

				TransitionEffectL <
					TrConcat<
						TrDoEffectAlwaysX<
							TrDelayX<
								Int<1000>
							>,
							EFFECT_QUOTE,
							Int<1>,
							Int<-1>
						>,
						AlphaL<
							White,
							Int<0>
						>,
						TrDoEffectAlwaysX<
							TrInstant,
							EFFECT_FAST_ON,
							Int<-1>,
							Int<-1>
						>
					>,
					EFFECT_USER7
				> ,

				// BATTERY LEVEL
				TransitionEffectL<
					TrConcat<
						TrJoin<
							TrDelay<2000>,
							TrWipe<1000>
						>,
						AlphaL<
							Mix<
								BatteryLevel,
								Red,
								Green
							>,
							SmoothStep<
								BatteryLevel,
								Int<-10>
							>
						>,
						TrWipeIn<1000>
					>,
					EFFECT_BATTERY_LEVEL
				>
			>
		>
		() //, “Ezra”
	},


	// Nightsister blade style.
	{ "Mother;common", "tracks/",
		StylePtr<
			IgnitionDelayX<
				Scale<
					IsLessThan<
						BladeAngle<>,
						Int<16000>
					>,
					Int<0>,
					Int<1600>
				>,
				Layers<
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
							Mix<
								Int<400>,
								Black,
								RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>
							>,
							Mix<
								Int<6000>,
								Black,
								RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>
							>
						>,
						StripesX<
							Int<14000>,
							Scale<
								BladeAngle<>,
								Int<-5>,
								Int<-50>
							>,
							RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>,
							Mix<
								Scale<
									HoldPeakF<
										SwingSpeed<250>,
										Int<1000>,
										Int<8000>
									>,
									Int<6000>,
									Int<16000>
								>,
								Black,
								RgbArg<BASE_COLOR_ARG,Rgb<0,255,0>>
							>
						>,
						0,
						2,
						4,
						2000,
						2
					>,
					AlphaL<
						RandomPerLEDFlickerL<
							RgbArg<CLASH_COLOR_ARG,Rgb<0,168,95>>
						>,
						SmoothStep<
							Scale<
								NoisySoundLevel,
								IntArg<EMITTER_SIZE_ARG,2000>,
								Sum<
									IntArg<EMITTER_SIZE_ARG,2000>,
									Int<6000>
								>
							>,
							Int<-6000>
						>
					>,
					Mix <
						IsLessThan<
							ClashImpactF<>,
							Int<26000>
						>,
						TransitionEffectL<
							TrWaveX<
								RgbArg<CLASH_COLOR_ARG,Rgb<0,168,95>>,
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
								Int<0>
							>,
							EFFECT_CLASH
						>,
						AlphaL<
							White,
							Int<0>
						>
					>,
					// Drag Effect
					LockupTrL <
						AlphaL <
							TransitionEffect<
								RandomPerLEDFlickerL<
									RgbArg<DRAG_COLOR_ARG,Rgb<0,255,0>>
								>,
								BrownNoiseFlickerL<
									RgbArg<DRAG_COLOR_ARG,Rgb<0,255,0>>,
									Int<300>
								>,
								TrExtend<
									4000,
									TrInstant
								>,
								TrFade<4000>,
								EFFECT_DRAG_BEGIN
							>,
							SmoothStep<
								Scale<
									TwistAngle<>,
									IntArg<DRAG_SIZE_ARG,31000>,
									Int<30000>
								>,
								Int<3000>
							>
						> ,
						TrWipeIn<200>,
						TrWipe<200>,
						SaberBase::LOCKUP_DRAG,
						Int<1>
					>,
					// Stab effect
					LockupTrL <
						AlphaL <
							Stripes <
								2000,
								4000,
								Mix<
									TwistAngle<>,
									RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>,
									RotateColorsX<
										Int<3000>,
										RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>
									>
								>,
								Mix<
									Sin<
										Int<50>
									>,
									Black,
									Mix<
										TwistAngle<>,
										RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>,
										RotateColorsX<
											Int<3000>,
											RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>
										>
									>
								>,
								Mix<
									Int<4096>,
									Black,
									Mix<
										TwistAngle<>,
										RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>,
										RotateColorsX<
											Int<3000>,
											RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>
										>
									>
								>
							> ,
							SmoothStep<Scale<
								TwistAngle<>,
								IntArg<MELT_SIZE_ARG,26000>,
								Int<30000>
							>,
							Int<3000>
						>
					>,
					// Melt Effect
					TrConcat <
						TrExtend<
							4000,
							TrWipeIn<200>
						>,
						AlphaL<
							HumpFlicker<
								Mix<
									TwistAngle<>,
									RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>,
									RotateColorsX<
										Int<3000>,
										RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>
									>
								>,
								RotateColorsX<
									Int<3000>,
									Mix<
										TwistAngle<>,
										RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>,
										RotateColorsX<
											Int<3000>,
											RgbArg<STAB_COLOR_ARG,Rgb<0,255,0>>
										>
									>
								>,
								100
							>,
							SmoothStep<
								Scale<
									TwistAngle<>,
									IntArg<MELT_SIZE_ARG,26000>,
									Int<30000>
								>,
								Int<3000>
							>
						>,
						TrFade<4000>
					>,
					TrWipe<200>,
					SaberBase::LOCKUP_MELT,
					Int<1>
				>,
				// In/Out Effect
				InOutTrL<
					TrWipeX<
						BendTimePowInvX<
							IgnitionTime<300>,
							Mult<
								IntArg<IGNITION_OPTION2_ARG,10992>,
								Int<98304>
							>
						>
					>,
					TrWipeInX<
						BendTimePowInvX<
							RetractionTime<0>,
							Mult<
								IntArg<RETRACTION_OPTION2_ARG,10992>,
								Int<98304>
							>
						>
					>,
					Black
				>
			>
		>
	> 
	()
},
*/

// Nightsister blade style.
//{ "Mother;common", "tracks/", //{ "Fire Talzin;common", "tracks/mars.wav",
/* copyright Fett263 CustomBlade (Primary Blade) OS7 Style
https://fett263library.com/early-access/#CustomBlade
OS7.12 v2.231
Single Style
Multi Phase (Special Abilities*)
Default: Fire Blade Fast (Sparking) [BaseColorArg (Gradient Color Down = Gradient: 1203)
]
1: Blade of Talzin [AltColorArg]

Multi Phase Control: use Special Abilities controls to change Phase. Requires Alt Font.

NOTE:This style includes Control Layer. Only one Control Layer should be used per preset.

*This style REQUIRES Alt Fonts alt000/ to alt001/ to be set up. Uses altchng.wav on change.
See https://pod.hubbe.net/sound/alt_sounds.html for more information.
--Effects Included--
Interactive Preon: Light the Wick [Color: Multi Phase]
Interactive Preon = activate Preon, point down to light the tip, spark will travel to emitter to ignite. Requires/uses tr02.wav
Ignition Effect: Dual Mode Wipe (Down = Fast) [Color: IgnitionColorArg]
Retraction Effect: Dual Mode Wipe In (Up = Fast) [Color: RetractionColorArg]
CoolDown Effects: 0: Power Burst Reverse 1: Disable [Color:BaseColorArg (Gradient Color Up = Gradient: 1784)
]
PostOff Effect: Emitter Cool Off (Emitter Size) [Color: Multi Phase]
Lockup Effect:
0: mainLockMulti0Shape - Begin: Real Clash - Style: Intensity Flame - End: Full Blade Absorb
1: Responsive Localized - Begin: Real Clash - Style: Intensity Flame - End: Dissipate
[Color: Multi Phase]
Lightning Block Effect:
0: mainLBMulti0Shape - Begin: Responsive Impact - Style: Strobing AudioFlicker - End: Full Blade Absorb
[Color: LBColorArg]
Drag Effect:
0: mainDragMulti0Shape - Begin: Wipe In - Style: Intensity Fire Drag - End: Wipe Out
[Color: Multi Phase]
Melt Effect:
0: mainMeltMulti0Shape - Begin: Wipe In - Style: Fire Melt - End: Wipe Out
[Color: Multi Phase]
Stab Effect: Normal Stab [Color: Multi Phase]
Interactive Blast: Random Blasts - Default Level (Uses Style Option 2 for Editing): 1000 ms
Interactive Blast control requires blast.wav files in font. When Blast is triggered blast.wav will play, to deflect blast (blst.wav and visual effect) swing within 1000ms of blaster sound ending. Random number of blasts from 1 to multiple possible. Only one style per preset can contain.
Blast Effect: Blast Wave (Random) [Color: BlastColorArg]
Clash Effect: Real Clash V1 [Color: Multi Phase]
Swing Effect: Fire Swing (Scaled Responsive Edge) [Color: Multi Phase]
Emitter Effect: Unstable Flare with Random Pulse [Color: Multi Phase]
Battery Level: % Blade (Green to Red)
Special Ability 1: Next Phase
Special Ability 5: Next Phase
Special Ability 7: Play Sound - Ignite Uses tr00.wav or tr/000/000.wav
Special Ability 8: Play Sound - Ignite Uses tr01.wav or tr/001/000.wav

 */
/*
	StylePtr<
		Layers<
			// Blade Style
			Black,
			ColorSelect<
				AltF,
				TrSelect<
					Ifon<
						Int<1>,
						Int<0>
					>,
					TrInstant,
					TrWipeX<
						Int<1000>
					>
				>,
				StaticFire<
					Gradient<
						RotateColorsX<	
							Int<1203>,
							RgbArg<BASE_COLOR_ARG,Red>
						>,
						RgbArg<BASE_COLOR_ARG,Red>
					>,
					Mix<
						Int<10280>,
						Black,
						Gradient<
							RotateColorsX<
								Int<1203>,
								RgbArg<BASE_COLOR_ARG,Red>
							>,
							RgbArg<BASE_COLOR_ARG,Red>
						>
					>,
					0,
					3,
					0,
					3000,
					4
				>,
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
						Mix<
							Int<400>,
							Black,
							RgbArg<ALT_COLOR_ARG,Green>
						>,
						Mix<
							Int<6000>,
							Black,
							RgbArg<ALT_COLOR_ARG,Green>
						>
					>,
					StripesX<
						Int<14000>,
						Scale<
							BladeAngle<>,
							Int<-5>,
							Int<-50>
						>,
						RgbArg<ALT_COLOR_ARG,Green>,
						Mix<
							Scale<
								HoldPeakF<
									SwingSpeed<250>,
									Int<1000>,
									Int<8000>
								>,
								Int<6000>,
								Int<16000>
							>,
							Black,
							RgbArg<ALT_COLOR_ARG,Green>
						>
					>,
					0,
					2,
					4,
					2000,
					2
				>
			>,
			
			// Spark 1
			TransitionLoopL<
				TrConcat<
					TrDelayX<
						Scale<
							SlowNoise<Int<100>>,
							Int<700>,
							Int<6000>
						>
					>,
					AlphaL<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Int<0>
					>,
					TrSparkX<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Scale<
							NoisySoundLevel,
							Int<125>,
							Int<125>
						>,
						Int<150>,
						Int<0>
					>
				>
			>,
			// Spark 2
			TransitionLoopL<
				TrConcat<
					TrDelayX<
						Scale<	
							SlowNoise<Int<100>>,
							Int<600>,
							Int<5000>
						>
					>,
					AlphaL<
						ColorSelect<	
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Int<0>
					>,
					TrSparkX<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Scale<
							NoisySoundLevel,
							Int<125>,
							Int<125>
						>,
						Int<125>,
						Int<0>
					>
				>
			>,
			// Spark 3
			TransitionLoopL<
				TrConcat<
					TrDelayX<
						Scale<
							SlowNoise<Int<100>>,
							Int<500>,
							Int<4000>
						>
					>,
					AlphaL<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Int<0>
					>,
					TrSparkX<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Scale<
							NoisySoundLevel,
							Int<125>,
							Int<125>
						>,
						Int<100>,
						Int<0>
					>
				>
			>,
			// Spark 4
			TransitionLoopL<
				TrConcat<
					TrDelayX<
						Scale<
							SlowNoise<Int<100>>,
							Int<500>,
							Int<3000>
						>
					>,
					AlphaL<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Int<0>
					>,
					TrSparkX<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Scale<
							NoisySoundLevel,
							Int<125>,
							Int<125>
						>,
						Int<75>,
						Int<0>
					>
				>
			>,
			// Spark 5
			TransitionLoopL<
				TrConcat<
					TrDelayX<
						Scale<
							SlowNoise<Int<100>>,
							Int<300>,
							Int<2000>
						>
					>,
					AlphaL<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Int<0>
					>,
					TrSparkX<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Scale<
							NoisySoundLevel,
							Int<125>,
							Int<125>
						>,
						Int<50>,
						Int<0>
					>
				>
			>,
			// Spark 6
			TransitionLoopL<
				TrConcat<
					TrDelayX<
						Scale<
							SlowNoise<Int<100>>,
							Int<200>,
							Int<1000>
						>
					>,
					AlphaL<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Int<0>
					>,
					TrSparkX<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
							Black
						>,
						Scale<
							NoisySoundLevel,
							Int<125>,
							Int<125>
						>,
						Int<25>,
						Int<0>
					>
				>
			>,
  
			// Sparking Emitter
			AlphaL<
				RandomPerLEDFlickerL<
					ColorSelect<
						AltF,
						TrInstant,
						RgbArg<EMITTER_COLOR_ARG,DodgerBlue>,
						Black
					>
				>,
				SmoothStep<
					Scale<
						NoisySoundLevel,
						IntArg<EMITTER_SIZE_ARG,2000>,
						Sum<
							IntArg<EMITTER_SIZE_ARG,2000>,
							Int<6000>
						>
					>,
					Int<-6000>
				>
			>,
		
			// Swing Effects
			AlphaL<
				AlphaL<
					Stripes<
						2800,
						-3000,
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<SWING_COLOR_ARG,Rgb<100,100,150>>,
							RgbArg<OFF_COLOR_ARG,Rgb<55,251,55>>
						>,
						Mix<
							Int<2096>,
							Black,
							ColorSelect<
								AltF,
								TrInstant,
								RgbArg<SWING_COLOR_ARG,Rgb<100,100,150>>,
								RgbArg<OFF_COLOR_ARG,Rgb<55,251,55>>
							>
						>,
						Mix<
							Int<16384>,
							Black,
							ColorSelect<
								AltF,
								TrInstant,
								RgbArg<SWING_COLOR_ARG,Rgb<100,100,150>>,
								RgbArg<OFF_COLOR_ARG,Rgb<55,251,55>>
							>
						>
					>,
					Scale<
						IsLessThan<
							SwingSpeed<600>,
							Int<13600>
						>,
						Scale<
							SwingSpeed<600>,
							Int<-19300>,
							Int<32768>
						>,
						Int<0>
					>
				>,
				SmoothStep<
					Scale<
						Scale<
							IsLessThan<
								SwingSpeed<600>,
								Int<13600>
							>,
							Scale<
								SwingSpeed<600>,
								Int<-19300>,
								Int<32768>
							>,
							Int<0>
						>,
						Int<28000>,
						Int<14000>
					>,
					Int<16000>
				>
			>,
		
			// Retraction Effect
			TransitionEffectL<
				TrSelect<	
					AltF,
					TrConcat<
						TrJoin<
							TrDelayX<
								RetractionTime<>
							>,
							TrInstant
						>,
						Stripes<
							5000,
							2500,
							Gradient<
								RgbArg<BASE_COLOR_ARG,Red>,
								RotateColorsX<
									Int<1784>,
									RgbArg<BASE_COLOR_ARG,Red>
								>
							>,
							Mix<
								Int<7710>,
								Black,
								Gradient<
									RgbArg<BASE_COLOR_ARG,Red>,
									RotateColorsX<
										Int<1784>,
										RgbArg<BASE_COLOR_ARG,Red>
									>
								>
							>,
							Mix<
								Int<3855>,
								Black,
								Gradient<
									RgbArg<BASE_COLOR_ARG,Red>,
									RotateColorsX<
										Int<1784>,
										RgbArg<BASE_COLOR_ARG,Red>
									>
								>
							>
						>,
						TrFade<800>
					>,
					TrInstant
				>,
				EFFECT_RETRACTION
			>,
	
			// Effect User 1?
			TransitionEffectL<
				TrDoEffectAlwaysX<
					TrInstant,
					EFFECT_ALT_SOUND,
					ModF<
						Sum<
							AltF,
							Int<1>
						>,
						Int<2>
					>,
					Int<-1>
				>,
				EFFECT_USER1
			>,
		
			// Stab Effect
			TransitionEffectL<
				TrConcat<
					TrJoin<
						TrDelayX<
							WavLen<>
						>,
						TrWipeIn<200>
					>,
					AlphaL<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<STAB_COLOR_ARG,DarkOrange>,
							RgbArg<ALT_COLOR2_ARG,Green>
						>,
						SmoothStep<
							IntArg<MELT_SIZE_ARG,28000>,
							Int<2000>
						>
					>,
					TrWipe<200>
				>,
				EFFECT_STAB
			>,
		
			// Blast Effect
			TransitionEffectL<
				TrWaveX<
					RgbArg<BLAST_COLOR_ARG,White>,
					Scale<
						EffectRandomF<EFFECT_BLAST>,
						Int<100>,
						Int<400>
					>,
					Int<100>,
					Scale<
						EffectPosition<EFFECT_BLAST>,
						Int<100>,
						Int<400>
					>,
					Scale<
						EffectPosition<EFFECT_BLAST>,
						Int<28000>,
						Int<8000>
					>
				>,
				EFFECT_BLAST
			>,
		
			// Clash Effect
			Mix<
				IsLessThan<
					ClashImpactF<>,
					Int<26000>
				>,
				// Clash A
				TransitionEffectL<
					TrConcat<
						TrInstant,
						AlphaL<
							ColorSelect<
								AltF,
								TrInstant,
								RgbArg<CLASH_COLOR_ARG,White>,
								Rgb<0,173,98>
							>,
							Bump<
								Scale<
									BladeAngle<>,
									Scale<
										BladeAngle<0,16000>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-12000>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<10000>
										>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-10000>
									>
								>,
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
				>,
				// Clash B
				TransitionEffectL<
					TrWaveX<
						ColorSelect<
							AltF,
							TrInstant,
							RgbArg<CLASH_COLOR_ARG,White>,
							Rgb<0,173,98>
						>,
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
						Scale<
							BladeAngle<>,
							Scale<
								BladeAngle<0,16000>,
								Sum<
									IntArg<LOCKUP_POSITION_ARG,16000>,
									Int<-12000>
								>,
								Sum<
									IntArg<LOCKUP_POSITION_ARG,16000>,
									Int<10000>
								>
							>,
							Sum<
								IntArg<LOCKUP_POSITION_ARG,16000>,
								Int<-10000>
							>
						>
					>,
					EFFECT_CLASH
				>
			>,
		
			// Lockup Effect
			LockupTrL<
				// Lockup Effect Begin?
				TransitionEffect<
					AlphaL<
						Remap<
							CenterDistF<
								Scale<
									BladeAngle<>,
									Scale<
										BladeAngle<0,16000>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-12000>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<10000>
										>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-10000>
									>
								>
							>,
							Stripes<
								3600,
								-1600,
								Gradient<
									RotateColorsX<
										Scale<
											Sin<Int<46>>,
											Int<0>,
											Int<4652>
										>,
										ColorSelect<
											AltF,
											TrInstant,
											RgbArg<LOCKUP_COLOR_ARG,Orange>,
											Rgb<5,255,147>
										>
									>,
									RotateColorsX<
										Scale<
											Sin<Int<46>>,
											Int<4652>,
											Int<0>
										>,
										ColorSelect<
											AltF,
											TrInstant,
											RgbArg<LOCKUP_COLOR_ARG,Orange>,
											Rgb<5,255,147>
										>
									>
								>,
								Mix<
									Scale<
										SlowNoise<Int<1600>>,
										Int<4000>,
										Int<20000>
									>,
									Black,
									Gradient<
										RotateColorsX<
											Scale<
												Sin<Int<46>>,
												Int<0>,
												Int<4652>
											>,
											ColorSelect<
												AltF,
												TrInstant,
												RgbArg<LOCKUP_COLOR_ARG,Orange>,
												Rgb<5,255,147>
											>
										>,
										RotateColorsX<
											Scale<
												Sin<Int<46>>,
												Int<4652>,
												Int<0>
											>,
											ColorSelect<
												AltF,
												TrInstant,
												RgbArg<LOCKUP_COLOR_ARG,Orange>,
												Rgb<5,255,147>
											>
										>
									>
								>,
								Mix<
									Scale<
										SlowNoise<Int<2000>>,
										Int<16000>,
										Int<2000>
									>,
									Black,
									Gradient<
										RotateColorsX<
											Scale<
												Sin<Int<46>>,
												Int<0>,
												Int<4652>
											>,
											ColorSelect<
												AltF,
												TrInstant,
												RgbArg<LOCKUP_COLOR_ARG,Orange>,
												Rgb<5,255,147>
											>
										>,
										RotateColorsX<
											Scale<
												Sin<Int<46>>,
												Int<4652>,
												Int<0>
											>,
											ColorSelect<
												AltF,
												TrInstant,
												RgbArg<LOCKUP_COLOR_ARG,Orange>,
												Rgb<5,255,147>
											>
										>
									>
								>
							>
						>,
						Bump<
							Scale<
								BladeAngle<>,
								Scale<
									BladeAngle<0,16000>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-12000>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<10000>
									>
								>,
								Sum<
									IntArg<LOCKUP_POSITION_ARG,16000>,
									Int<-10000>
								>
							>,
							Scale<
								SwingSpeed<100>,
								Int<17000>,
								Int<25000>
							>
						>
					>,
					AlphaL<
						Remap<
							CenterDistF<
								Scale<
									BladeAngle<>,
									Scale<
										BladeAngle<0,16000>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-12000>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<10000>
										>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-10000>
									>
								>
							>,
							Stripes<
								4200,
								-1200,
								Gradient<
									RotateColorsX<
										Scale<
											Sin<Int<46>>,
											Int<0>,
											Int<4652>
										>,
										ColorSelect<
											AltF,
											TrInstant,
											RgbArg<LOCKUP_COLOR_ARG,Orange>,
											Rgb<5,255,147>
										>
									>,
									RotateColorsX<
										Scale<
											Sin<Int<46>>,
											Int<4652>,
											Int<0>
										>,
										ColorSelect<
											AltF,
											TrInstant,
											RgbArg<LOCKUP_COLOR_ARG,Orange>,
											Rgb<5,255,147>
										>
									>
								>,
								Mix<
									Scale<
										SlowNoise<Int<1600>>,
										Int<4000>,
										Int<20000>
									>,
									Black,
									Gradient<
										RotateColorsX<
											Scale<
												Sin<Int<46>>,
												Int<0>,
												Int<4652>
											>,
											ColorSelect<
												AltF,
												TrInstant,
												RgbArg<LOCKUP_COLOR_ARG,Orange>,
												Rgb<5,255,147>
											>
										>,
										RotateColorsX<
											Scale<
												Sin<Int<46>>,
												Int<4652>,
												Int<0>
											>,
											ColorSelect<
												AltF,
												TrInstant,
												RgbArg<LOCKUP_COLOR_ARG,Orange>,
												Rgb<5,255,147>
											>
										>
									>
								>,
								Mix<
									Scale<
										SlowNoise<Int<2000>>,
										Int<16000>,
										Int<2000>
									>,
									Black,
									Gradient<
										RotateColorsX<
											Scale<
												Sin<Int<46>>,
												Int<0>,
												Int<4652>
											>,
											ColorSelect<
												AltF,
												TrInstant,
												RgbArg<LOCKUP_COLOR_ARG,Orange>,
												Rgb<5,255,147>
											>
										>,
										RotateColorsX<
											Scale<
												Sin<Int<46>>,
												Int<4652>,
												Int<0>
											>,
											ColorSelect<
												AltF,
												TrInstant,
												RgbArg<LOCKUP_COLOR_ARG,Orange>,
												Rgb<5,255,147>
											>
										>
									>
								>
							>
						>,
						Bump<
							Scale<
								BladeAngle<>,
								Scale<
									BladeAngle<0,16000>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-12000>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<10000>
									>
								>,
								Sum<
									IntArg<LOCKUP_POSITION_ARG,16000>,
									Int<-10000>
								>
							>,
							Scale<
								SwingSpeed<100>,
								Int<17000>,
								Int<25000>
							>
						>
					>,
					TrExtend<
						5000,
						TrInstant
					>,
					TrFade<5000>,
					EFFECT_LOCKUP_BEGIN
				>,
				// Lockup Effect
				TrConcat<
					TrJoin<
						TrDelay<50>,
						TrInstant
					>,
					Mix<
						IsLessThan<
							ClashImpactF<>,
							Int<26000>
						>,
						Gradient<
							RotateColorsX<
								Scale<
									Sin<Int<46>>,
									Int<0>,
									Int<4652>
								>,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<LOCKUP_COLOR_ARG,Orange>,
									Rgb<5,255,147>
								>
							>,
							RotateColorsX<
								Scale<
									Sin<Int<46>>,
									Int<4652>,
									Int<0>
								>,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<LOCKUP_COLOR_ARG,Orange>,
									Rgb<5,255,147>
								>
							>
						>,
						AlphaL<
							Gradient<
								RotateColorsX<
									Scale<
										Sin<Int<46>>,
										Int<0>,
										Int<4652>
									>,
									ColorSelect<
										AltF,
										TrInstant,
										RgbArg<LOCKUP_COLOR_ARG,Orange>,
										Rgb<5,255,147>
									>
								>,
								RotateColorsX<
									Scale<
										Sin<Int<46>>,
										Int<4652>,
										Int<0>
									>,
									ColorSelect<
										AltF,
										TrInstant,
										RgbArg<LOCKUP_COLOR_ARG,Orange>,
										Rgb<5,255,147>
									>
								>
							>,
							Bump<
								Scale<
									BladeAngle<>,
									Scale<
										BladeAngle<0,16000>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<-12000>
										>,
										Sum<
											IntArg<LOCKUP_POSITION_ARG,16000>,
											Int<10000>
										>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-10000>
									>
								>,
								Scale<
									ClashImpactF<>,
									Int<20000>,
									Int<60000>
								>
							>
						>
					>,
					TrFade<300>
				>,
				// Lockup Effect End?
				TrConcat<
					TrInstant,
					AlphaL<
						Gradient<
							RotateColorsX<
								Scale<
									Sin<Int<46>>,
									Int<0>,
									Int<4652>
								>,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<LOCKUP_COLOR_ARG,Orange>,
									Rgb<5,255,147>
								>
							>,
							RotateColorsX<
								Scale<
									Sin<Int<46>>,
									Int<4652>,
									Int<0>
								>,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<LOCKUP_COLOR_ARG,Orange>,
									Rgb<5,255,147>
								>
							>
						>,
						Bump<
							Scale<
								BladeAngle<>,
								Scale<
									BladeAngle<0,16000>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<-12000>
									>,
									Sum<
										IntArg<LOCKUP_POSITION_ARG,16000>,
										Int<10000>
									>
								>,
								Sum<
									IntArg<LOCKUP_POSITION_ARG,16000>,
									Int<-10000>
								>
							>,
							Int<13000>
						>
					>,
					TrFade<400>
				>,
				SaberBase::LOCKUP_NORMAL
			>,
		
			// Lightning Block
			ResponsiveLightningBlockL<
				Strobe<
					Gradient<
						RotateColorsX<
							Scale<
								Sin<Int<73>>,
								Int<0>,
								Int<8817>
							>,
							RgbArg<LB_COLOR_ARG,Rgb<85,85,200>>
						>,
						RotateColorsX<
							Scale<
								Sin<Int<73>>,
								Int<8817>,
								Int<0>
							>,
							RgbArg<LB_COLOR_ARG,Rgb<85,85,200>>
						>
					>,
					AudioFlicker<
						Gradient<
							RotateColorsX<
								Scale<
									Sin<Int<73>>,
									Int<0>,
									Int<8817>
								>,
								RgbArg<LB_COLOR_ARG,Rgb<85,85,200>>
							>,
							RotateColorsX<
								Scale<
									Sin<Int<73>>,
									Int<8817>,
									Int<0>
								>,
								RgbArg<LB_COLOR_ARG,Rgb<85,85,200>>
							>
						>,
						Blue
					>,
					50,
					1
				>,
				TrConcat<
					TrExtend<
						200,
						TrInstant
					>,
					AlphaL<
						Gradient<
							RotateColorsX<
								Scale<
									Sin<Int<73>>,
									Int<0>,
									Int<8817>
								>,
								RgbArg<LB_COLOR_ARG,Rgb<85,85,200>>
							>,
							RotateColorsX<
								Scale<
									Sin<Int<73>>,
									Int<8817>,
									Int<0>
								>,
								RgbArg<LB_COLOR_ARG,Rgb<85,85,200>>
							>
						>,
						Bump<
							Scale<
								BladeAngle<>,
								Int<10000>,
								Int<21000>
							>,
							Int<10000>
						>
					>,
					TrFade<200>
				>,
				TrConcat<
					TrInstant,
					Gradient<
						RotateColorsX<
							Scale<
								Sin<Int<73>>,
								Int<0>,
								Int<8817>
							>,
							RgbArg<LB_COLOR_ARG,Rgb<85,85,200>>
						>,
						RotateColorsX<
							Scale<
								Sin<Int<73>>,
								Int<8817>,
								Int<0>
							>,
							RgbArg<LB_COLOR_ARG,Rgb<85,85,200>>
						>
					>,
					TrFade<400>
				>
			>,
		
			// Drag Effect
			LockupTrL<
				AlphaL<
					TransitionEffect<
						Stripes<
							2000,
							4000,
							ColorSelect<
								AltF,
								TrInstant,
								RgbArg<STAB_COLOR_ARG,DarkOrange>,
								Aquamarine
							>,
							Mix<
								Sin<Int<50>>,
								Black,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<STAB_COLOR_ARG,DarkOrange>,
									Aquamarine
								>
							>,
							Mix<
								Int<4096>,
								Black,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<STAB_COLOR_ARG,DarkOrange>,
									Aquamarine
								>
							>
						>,
						Stripes<
							2000,
							3000,
							ColorSelect<
								AltF,
								TrInstant,
								RgbArg<STAB_COLOR_ARG,DarkOrange>,
								Aquamarine
							>,
							Mix<
								Sin<Int<30>>,
								Black,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<STAB_COLOR_ARG,DarkOrange>,
									Aquamarine
								>
							>,
							Mix<
								Int<8192>,
								Black,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<STAB_COLOR_ARG,DarkOrange>,
									Aquamarine
								>
							>
						>,
						TrExtend<
							4000,
							TrInstant
						>,
						TrFade<4000>,
						EFFECT_DRAG_BEGIN
					>,
					SmoothStep<
						Scale<
							TwistAngle<>,
							IntArg<DRAG_SIZE_ARG,28000>,
							Int<30000>
						>,
						Int<3000>
					>
				>,
				TrWipeIn<200>,
				TrWipe<200>,
				SaberBase::LOCKUP_DRAG
			>,
		
			// Melt Effect
			LockupTrL<
				AlphaL<
					Stripes<
						2000,
						3000,
						Gradient<
							RotateColorsX<
								Scale<
									Sin<Int<20>>,
									Int<0>,
									Int<4096>
								>,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<STAB_COLOR_ARG,DarkOrange>,
									RgbArg<ALT_COLOR2_ARG,Green>
								>
							>,
							RotateColorsX<
								Scale<
									Sin<Int<20>>,
									Int<4096>,
									Int<0>
								>,
								ColorSelect<
									AltF,
									TrInstant,
									RgbArg<STAB_COLOR_ARG,DarkOrange>,
									RgbArg<ALT_COLOR2_ARG,Green>
								>
							>
						>,
						Mix<
							Sin<Int<30>>,
							Black,
							Gradient<
								RotateColorsX<
									Scale<
										Sin<Int<20>>,
										Int<0>,
										Int<4096>
									>,
									ColorSelect<
										AltF,
										TrInstant,
										RgbArg<STAB_COLOR_ARG,DarkOrange>,
										RgbArg<ALT_COLOR2_ARG,Green>
									>
								>,
								RotateColorsX<
									Scale<
										Sin<Int<20>>,
										Int<4096>,
										Int<0>
									>,
									ColorSelect<
										AltF,
										TrInstant,
										RgbArg<STAB_COLOR_ARG,DarkOrange>,
										RgbArg<ALT_COLOR2_ARG,Green>
									>
								>
							>
						>,
						Mix<
							Int<8192>,
							Black,
							Gradient<
								RotateColorsX<
									Scale<
										Sin<Int<20>>,
										Int<0>,
										Int<4096>
									>,
									ColorSelect<
										AltF,
										TrInstant,
										RgbArg<STAB_COLOR_ARG,DarkOrange>,
										RgbArg<ALT_COLOR2_ARG,Green>
									>
								>,
								RotateColorsX<
									Scale<
										Sin<Int<20>>,
										Int<4096>,
										Int<0>
									>,
									ColorSelect<
										AltF,
										TrInstant,
										RgbArg<STAB_COLOR_ARG,DarkOrange>,
										RgbArg<ALT_COLOR2_ARG,Green>
									>
								>
							>
						>
					>,
					SmoothStep<
						Scale<
							TwistAngle<>,
							IntArg<MELT_SIZE_ARG,28000>,
							Int<30000>
						>,
						Int<3000>
					>
				>,
				TrWipeIn<200>,
				TrWipe<200>,
				SaberBase::LOCKUP_MELT
			>,
  
			// Interactive Blast
			TransitionEffectL<
				TrConcat<
					TrDelay<100>,
					AlphaL<
						White,
						Int<0>
					>,
					TrDoEffect<
						TrInstant,
						EFFECT_GAME_CHOICE
					>
				>,
				EFFECT_INTERACTIVE_BLAST
			>,
			// Interactive Blast Choice
			TransitionEffectL<
				TrConcat<
					TrExtendX<
						Sum<
							WavLen<EFFECT_INTERACTIVE_BLAST>,
							IntArg<STYLE_OPTION2_ARG,1000>
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
							TrDoEffect<
								TrInstant,
								EFFECT_INTERACTIVE_BLAST
							>,
							TrInstant,
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
				EFFECT_GAME_CHOICE
			>,
		
			// In/Out Effect
			InOutTrL<
				// Ignition Effect
				TrSelect<
					IncrementWithReset<
						ThresholdPulseF<
							Sum<
								EffectPulseF<EFFECT_USER7>,
								EffectPulseF<EFFECT_USER8>
							>,
							Int<30000>
						>,
						EffectPulseF<EFFECT_RETRACTION>,
						Int<1>
					>,
					TrWipeX<
						Scale<
							IsLessThan<
								BladeAngle<>,
								Int<16000>
							>,
							IgnitionTime<>,
							Mult<
								IgnitionTime<>,
								Int<16384>
							>
						>
					>,
					TrInstant
				>,
				// Retraction Effect
				TrWipeInX<
					Scale<
						IsLessThan<
							BladeAngle<>,
							Int<16000>
						>,
						Mult<
							RetractionTime<>,
							Int<16384>
						>,
						RetractionTime<>
					>
				>,
				// Off Color / Interactive Preon?
				Layers<
					Black,
					// Interactive Preon?
					TransitionEffectL<
						TrConcat<
							TrFade<100>,
							AlphaL<
								Gradient<
									RotateColorsX<
										Scale<
											Sin<Int<41>>,
											Int<0>,
											Int<2153>
										>,
										ColorSelect<
											AltF,
											TrInstant,
											RgbArg<PREON_COLOR_ARG,Red>,
											Green
										>
									>,
									RotateColorsX<
										Scale<
											Sin<Int<41>>,
											Int<2153>,
											Int<0>
										>,
										ColorSelect<
											AltF,
											TrInstant,
											RgbArg<PREON_COLOR_ARG,Red>,
											Green
										>
									>
								>,
								SmoothStep<
									Int<4000>,
									Int<-2000>
								>
							>,
							TrExtend<
								4000,
								TrInstant
							>,
							TransitionPulseL<
								TrConcat<
									TrDoEffectAlways<
										TrInstant,
										EFFECT_TRANSITION_SOUND,
										2
									>,
									AlphaL<
										White,
										Int<0>
									>,
									TrSparkX<
										BrownNoiseFlickerL<
											Gradient<
												RotateColorsX<
													Scale<
														Sin<Int<41>>,
														Int<0>,
														Int<2153>
													>,
													ColorSelect<
														AltF,
														TrInstant,
														RgbArg<PREON_COLOR_ARG,Red>,
														Green
													>
												>,
												RotateColorsX<
													Scale<
														Sin<Int<41>>,
														Int<2153>,
														Int<0>
													>,
													ColorSelect<
														AltF,
														TrInstant,
														RgbArg<PREON_COLOR_ARG,Red>,
														Green
													>
												>
											>,
											Int<200>
										>,
										Int<400>,
										WavLen<EFFECT_TRANSITION_SOUND>,
										Int<32768>
									>,
									AlphaL<
										White,
										Int<0>
									>,
									TrDelay<100>,
									AlphaL<
										White,
										Int<0>
									>,
									TrDoEffectAlways<
										TrInstant,
										EFFECT_FAST_ON
									>
								>,
								ThresholdPulseF<
									IsLessThan<
										BladeAngle<>,
										Int<2000>
									>,
									Int<30000>
								>
							>,
							TrInstant
						>,
						EFFECT_INTERACTIVE_PREON
					>
				>
			>,
		
			// EffecT User 7
			TransitionEffectL<
				TrConcat<
					TrInstant,
					Black,
					TrWipeSparkTipX<
						RgbArg<IGNITION_COLOR_ARG,Rgb<85,85,200>>,
						Int<300>
					>
				>,
				EFFECT_USER7
			>,
		
			// Effect User 8
			TransitionEffectL<
				TrConcat<
					TrInstant,
					HumpFlickerL<
						RgbArg<IGNITION_COLOR_ARG,Rgb<85,85,200>>,
						40
					>,
					TrFade<1200>
				>,
				EFFECT_USER8
			>,
			// Effect User 8 ??
			TransitionEffectL<
				TrConcat<
					TrInstant,
					Black,
					TrJoinR<
						TrCenterWipeInX<
							Int<300>
						>,
						TrSmoothFadeX<
							Int<300>
						>
					>
				>,
				EFFECT_USER8
			>,
		
			// Effect User5
			TransitionEffectL<
				TrDoEffectAlwaysX<
					TrInstant,
					EFFECT_ALT_SOUND,
					ModF<
						Sum<
							AltF,
							Int<1>
						>,
						Int<2>
					>,
					Int<-1>
				>,
				EFFECT_USER5
			>,
		
			// Effect User 7 FastOn
			TransitionEffectL<
				TrDoEffectAlwaysX<
					TrDoEffectAlwaysX<
						TrInstant,
						EFFECT_FAST_ON,
						Int<-1>,
						Int<-1>
					>,
					EFFECT_TRANSITION_SOUND,
					Int<0>,
					Int<-1>
				>,
				EFFECT_USER7
			>,
		
			// Effect User8  FastOn
			TransitionEffectL<
				TrDoEffectAlwaysX<
					TrDoEffectAlwaysX<
						TrInstant,
						EFFECT_FAST_ON,
						Int<-1>,
						Int<-1>
					>,
					EFFECT_TRANSITION_SOUND,
					Int<1>,
					Int<-1>
				>,
				EFFECT_USER8
			>,
		
			// Post Off Effect
			TransitionEffectL<
				TrConcat<
					TrInstant,
					AlphaL<
						Magenta,
						SmoothStep<
							IntArg<EMITTER_SIZE_ARG,2000>,
							Int<-4000>
						>
					>,
					TrFadeX<
						Mult<
							Scale<
								IsLessThan<
									WavLen<EFFECT_POSTOFF>,
									Int<200>
								>,
								WavLen<EFFECT_POSTOFF>,
								Int<4000>
							>,
							Int<10923>
						>
					>,
					AlphaL<
						SteelBlue,
						SmoothStep<
							IntArg<EMITTER_SIZE_ARG,2000>,
							Int<-4000>
						>
					>,
					TrFadeX<
						Mult<
							Scale<
								IsLessThan<
									WavLen<EFFECT_POSTOFF>,
									Int<200>
								>,
								WavLen<EFFECT_POSTOFF>,
								Int<4000>
							>,
							Int<10923>
						>
					>,
					AlphaL<
						White,
						SmoothStep<
							IntArg<EMITTER_SIZE_ARG,2000>,
							Int<-2000>
						>
					>,
					TrFadeX<
						Mult<
							Scale<
								IsLessThan<
									WavLen<EFFECT_POSTOFF>,
									Int<200>
								>,
								WavLen<EFFECT_POSTOFF>,
								Int<4000>
							>,
							Int<10923>
						>
					>
				>,
				EFFECT_POSTOFF
			>,
		
			// Battery Level
			TransitionEffectL<
				TrConcat<
					TrJoin<
						TrDelay<2000>,
						TrWipe<1000>
					>,
					AlphaL<
						Mix<
							BatteryLevel,
							Red,
							Green
						>,
						SmoothStep<
							BatteryLevel,
							Int<-10>
						>
					>,
					TrWipeIn<1000>
				>,
				EFFECT_BATTERY_LEVEL
			>
		>
	>
	()
},
*/

};

BladeConfig blades[] = {
 { 0, WS2811BladePtr<132, WS2811_ACTUALLY_800kHz | WS2811_GRB>(), CONFIGARRAY(presets) },
  };
#endif

#ifdef CONFIG_BUTTONS
Button PowerButton(BUTTON_POWER, powerButtonPin, "pow");
/*Button AuxButton(BUTTON_AUX, auxPin, "aux");*/
#endif
