// ---------- COMPILE VARS ---------- //

// Disables Version "errors" on compile
#define FASTLED_INTERNAL

// Libraries
#include "FastLED.h"
#include "EEPROM.h"
#include "Bounce2.h"

// Unsigned subtraction magic
#define qsubd(x, b) ((x>b)?wave_brightness:0)		// A digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b) ((x>b)?x-b:0)					// Unsigned subtraction macro. if result <0, then => 0.

// Serial vars
#define SERIAL_BAUDRATE 57600 //57600						// TODO check on this?  seirlight options 115200
#define SERIAL_TIMEOUT 500							// TODO seirlight has it set at 5

// Arduino pin setup

// Data and clock pins defined for development testing
#define DATA_PIN 7
#define CLOCK_PIN 14

// Switch pins
#define switchA 3
#define switchB 4

// Acellerometer pins
//#define SDA 18
//#define SCL 19

// LED Meta Defines
#define COLOR_ORDER BGR

// WS2812B used for development testing
#define LED_TYPE APA102

// 576 Length LED strip and mode start number
#define NUM_LEDS 576
#define STRIP_LENGTH 144
#define STARTMODE 0

// ---------- RUNTIME VARS ---------- //

// Some function forward declarations
void strobe_mode(uint8_t newMode, bool mc, bool old);
void updatePaletteIndex(CRGBPalette16 pal);

// Serial Variables
byte in_byte;			// Serial input byte
int this_arg;			// Serial input argument

// LED Meta Variables, particularly palettes
struct CRGB leds[NUM_LEDS];
struct CRGB old_leds[NUM_LEDS];
struct CRGB cur_leds[NUM_LEDS];
struct CRGB jug_leds[NUM_LEDS];
//struct CRGB fire_leds[NUM_LEDS];
struct CRGB blank_leds[NUM_LEDS];
CRGBPalette16 current_palette;         // Current palette we're using
CRGBPalette16 target_palette;          // Next palette to transition to
CRGBPalette16 old_palette;
TBlendType current_blending;           // Linear vs No-Blending
extern const TProgmemRGBGradientPalettePtr g_gradient_palettes[];   // from gradient_palettes.h
extern const uint8_t g_gradient_palette_count;                      // # of fixed palettes
uint8_t g_current_palette_number  = 0;                              // Current palette number
uint8_t current_pattern_index     = 5;                              // Index of current pattern
//uint8_t default_mode              = 34;                             // Default mode to go to

// LED Overall Variables
uint8_t max_bright  = 128;		// Overall brightness, it can be changed on the fly.  TODO: Maybe lower this to 100?
uint8_t max_mode    = 79;		// maximum number of modes
uint8_t demo_run    = 0;		// 0 = regular mode, 1 = demo mode, 2 = shuffle mode
int led_mode;				// Starting mode is typically 0
uint8_t old_mode;
bool transitioning = 0;	// transitioning flag
int blending_ratio = 0;
bool transition_wait = 0;
uint8_t mode_number = 0;

// LED Routine/Shared Variables
uint8_t all_freq        = 32;     // Frequency (width of bars) (sine-routines)
uint8_t bg_clr          = 0;      // Background color
uint8_t bg_bri          = 0;      // Background brightness
bool    glitter         = 0;      // Glitter flag
uint8_t palette_change;           // 1 = similar palette, 2 = random4 palette, 3 = random16 palette
uint8_t start_index     = 0;      // Foreground hue to start with (sine-routines)
uint8_t this_beat;                // Beat tracker (juggle routine)
uint8_t this_bright     = 50;      // Standard brightness
uint8_t that_bright     = 50;     // second brightness
uint8_t this_cutoff     = 192;    // Cutoff value; lower = longer wave
int     this_delay      = 0;      // Standard delay
uint8_t this_diff       = 1;      // Standard palette index jump
uint8_t this_dir        = 0;      // Standard direction
uint8_t this_fade       = 16;     // Standard fade rate
uint8_t this_hue        = 0;      // Standard hue
uint8_t this_index      = 0;      // Standard palette index
uint8_t this_inc        = 1;      // Standard increment. Changes starting color for each pass (sine-routines)
int     this_phase      = 0;      // Standard phase change - sines
int     that_phase      = 0;      // second phase
uint8_t this_rot        = 1;      // Standard hue rotation rate
uint8_t this_sat        = 255;    // Standard saturation
uint8_t this_speed      = 4;      // Standard speed change
uint8_t that_speed      = 4;      // Second speed
uint8_t wave_brightness = 255;    // Brightness of the waves/bars
uint8_t xd[NUM_LEDS];             // X-array for 2d coordinates of leds
uint8_t yd[NUM_LEDS];             // Y-array for 2d coordinates of leds
int ringArray[144][4];      	  // Array for rings
int spiralArray[4][144];		  // Array for spirals
int spiralArrayRev[4][144];
int w = 3; 						  // width of spirals
uint8_t jug_fade = 16;
uint8_t jug_index = 0;
uint16_t jug16_phase = 0;
bool juggle_index_reset = 1;
int ringBeat[] = { 3, 2, 0, 1 };
int numdots_ring_arr[] = {4, 6, 5, 8};
bool fire_it_up = 0;
bool fire_it_down = 0;
uint8_t fire_blend = 0;

// colorwave variables-------------------
uint16_t sPseudotime = 0;
uint16_t sLastMillis = 0;
uint16_t sHue16 = 0;

uint8_t brightdepth, msmultiplier, hue8, bri8, cwave_index;
uint16_t brightnessthetainc16, hue16, hueinc16, ms, deltams, brightnesstheta16, h16_128, b16, bri16, pixelnumber;

// matrix_saw--------------------
uint8_t matrix_rate[] = { 2, 4, 6, 8, 10 };
uint8_t num_mat_dots = 5;
uint8_t this_scale = 30;

// fader
uint8_t fader;

//Variables for plasma-----------------
int plasma_phase1;
int plasma_phase2;
int plasmaIndex;
int plasmaBright;


//Variables for ripple -----------------
int rip_color;
int rip_center = 0;
int rip_step = -1;
int rip_delay = -10;
int rip_pause = -10;
#define rip_maxSteps 16
float rip_fadeRate = 0.8;
//Ripple background color
uint8_t rip_currentBg = random(256);
uint8_t rip_nextBg = rip_currentBg;
uint8_t rip_fade = 255;
// fadeval = 128;
//uint8_t bgcol = 0;



//Twinkle Variables---------------
byte twinkle_speed = 4; // 0 - 8
byte twinkle_density = 5;	// 0 - 8
CRGB twinkle_bg = CRGB::Black; // CRGB(CRGB::FairyLight).nscale8_video(16);
byte auto_select_background_color = 0;
byte cool_like_incandescent = 1;
uint8_t bglight;
uint8_t backgroundBrightness;
CRGB bg;

//Juggle Variables-------------------
uint8_t numdots;
uint8_t numdots_ring;   			// dots for juggle_pal_ring

//Fire Variables-------------------
uint8_t cooling = 55;				// Cooling variable for fire
uint8_t cooling1;
uint8_t cooling2;
uint8_t cooling3;
uint8_t cooling4;
uint8_t sparking = 120;				// Heating variable for fire
uint8_t sparking1;
uint8_t sparking2;
uint8_t sparking3;
uint8_t sparking4;
uint8_t cooling_simple[] = { 75, 84, 92, 80 };
uint8_t sparking_simple[] = { 50, 49, 61, 69 };

////Disco Variables
//uint8_t zooming_beats_per_minute = 122; // zooming for disco
//uint8_t color_index = 0;
//uint8_t color_speed = 1;
//uint8_t color_inc = 3;

// KY-040 Rotary Module variables
int pinA = 21;
int pinB = 22;
int pinSW = 23;
int lastPinSWstate = 1;
int pinSWstate;
int pinALast;
int aVal;
int rotateCount = 0;
int rotary_function = 0;
int palette_index;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

Bounce debouncer = Bounce();

//Spiral Variables----------------
int spiral_start;
int spiral_inc;
int spiral_width;

// noise8 variables--------------

uint16_t dist = 12345;         // A random number for our noise generator.
uint16_t scale = 30;          // Wouldn't recommend changing this_ on the fly, or the animation will be really blocky.
uint16_t dist2 = 12345;         // A random number for our noise generator.
uint16_t scale2 = 30;          // Wouldn't recommend changing this_ on the fly, or the animation will be really blocky.

// serendipitous variables--------------

uint16_t Xorig = 0x013;
uint16_t Yorig = 0x021;
uint16_t X=Xorig;
uint16_t Y=Yorig;
uint16_t Xn;
uint16_t Yn;

uint16_t Xorig2 = 0x013;
uint16_t Yorig2 = 0x021;
uint16_t X2=Xorig2;
uint16_t Y2=Yorig2;
uint16_t Xn2;
uint16_t Yn2;

// three sin variables--------------

int wave1;
int wave2;
int wave3;
uint8_t mul1;
uint8_t mul2;
uint8_t mul3;

// two_sin_pal variables-------------------------------------------------------------------------

uint8_t that_hue = 140;                                        // You can change the starting hue for other wave.
uint8_t that_rot = 0;                                          // You can change how quickly the hue rotates for the other wave. Currently 0.
//int8_t thatspeed = 4;                                         // You can change the speed, and use negative values.
//int that_phase = 0;                                            // Phase change value gets calculated.
uint8_t that_cutoff = 192;                                     // You can change the cutoff value to display that wave. Lower value = longer wave.

// cylon variables---------------
int cylon_step = 1;
int cylon_center = 0;
uint8_t cylon_index = 128;
uint8_t cylon_brightness = 255;

// Bouncing Ball Variables--------------
#define GRAVITY           -1              // Downward (negative) acceleration of gravity in m/s^2
#define h0                1                  // Starting height, in meters, of the ball (strip length)
#define NUM_BALLS         6                  // Number of bouncing balls you want (recommend < 7, but 20 is fun in its own way)
float h[NUM_BALLS];                         // An array of heights
float vImpact0 = sqrt(-2 * GRAVITY * h0);  // Impact velocity of the ball when it hits the ground if "dropped" from the top of the strip
float vImpact[NUM_BALLS];                   // As time goes on the impact velocity will change, so make an array to store those values
float tCycle[NUM_BALLS];                    // The time since the last time the ball struck the ground
int   pos[NUM_BALLS];                       // The integer position of the dot on the strip (LED index)
long  tLast[NUM_BALLS];                     // The clock time of the last ground strike
float COR[NUM_BALLS];                       // Coefficient of Restitution (bounce damping)
uint8_t ball_hue = 0;

// circnoise variables----------------
uint16_t shift_x;
uint16_t shift_y;
uint32_t real_x;
uint32_t real_y;
uint8_t noise;
uint8_t circ_index;
uint8_t circ_bri;
uint32_t real_z;

// moving dot variables--------
CRGB lead_led;
uint8_t blue_angle, blue_low, blue_high, green_angle, green_low, green_high, red_angle, red_low, red_high;










///////// Variables for transitioning:
// LED Routine/Shared Variables
uint8_t old_all_freq, old_bg_clr, old_bg_bri, old_start_index, old_this_beat, old_this_bright, old_that_bright, old_this_cutoff;
int     old_this_delay = 0;      // Standard delay
uint8_t old_this_diff, old_this_dir, old_this_fade, old_this_hue, old_this_index, old_this_inc;
int     old_this_phase = 0;      // Standard phase change - sines
int     old_that_phase = 0;      // second phase
uint8_t old_this_rot = 1;      // Standard hue rotation rate
uint8_t old_this_sat = 255;    // Standard saturation
uint8_t old_this_speed = 4;      // Standard speed change
uint8_t old_that_speed = 4;      // Second speed
uint8_t old_wave_brightness = 255;    // Brightness of the waves/bars
uint8_t old_xd[NUM_LEDS];             // X-array for 2d coordinates of leds
uint8_t old_yd[NUM_LEDS];
uint8_t target_delay = 10;
bool pal_change = 0;

int old_plasma_phase1, old_plasma_phase2, old_plasmaIndex, old_plasmaBright;

int old_rip_color;
int old_rip_center = 0;
int old_rip_step = -1;
float old_rip_fadeRate = 0.8;
uint32_t old_rip_currentBg = random(256);
uint32_t old_rip_nextBg = rip_currentBg;
uint8_t old_rip_fade = 255;
//uint8_t old_fadeval = 128;

byte old_twinkle_speed = 4;
byte old_twinkle_density = 5;
CRGB old_twinkle_bg = CRGB::Black;
byte old_auto_select_background_color = 0;
byte old_cool_like_incandescent = 1;
uint8_t old_bglight;
uint8_t old_backgroundBrightness;
CRGB old_bg;

uint8_t old_numdots, old_numdots_ring;
bool old_juggle_index_reset;
uint16_t old_jug16_phase;

uint8_t old_cooling, old_cooling1, old_cooling2, old_cooling3, old_cooling4;
uint8_t old_sparking, old_sparking1, old_sparking2, old_sparking3, old_sparking4;
uint8_t old_cooling_simple[] = { 75, 84, 92, 80 };
uint8_t old_sparking_simple[] = { 50, 49, 61, 69 };

//uint8_t old_zooming_beats_per_minute = 122;
//uint8_t old_color_index = 0;
//uint8_t old_color_speed = 1;
//uint8_t old_color_inc = 3;

uint16_t old_dist = 12345;
uint16_t old_scale = 30;
uint16_t old_dist2 = 12345;
uint16_t old_scale2 = 30;

uint16_t old_Xorig = 0x013;
uint16_t old_Yorig = 0x021;
uint16_t old_X = old_Xorig;
uint16_t old_Y = old_Yorig;
uint16_t old_Xn;
uint16_t old_Yn;

uint16_t old_Xorig2 = 0x013;
uint16_t old_Yorig2 = 0x021;
uint16_t old_X2 = old_Xorig;
uint16_t old_Y2 = old_Yorig;
uint16_t old_Xn2;
uint16_t old_Yn2;

int old_wave1, old_wave2, old_wave3;
uint8_t old_mul1, old_mul2, old_mul3;

uint8_t old_that_hue = 140;
uint8_t old_that_rot = 0;
//int8_t old_thatspeed = 4;
//int old_thatphase = 0;
uint8_t old_that_cutoff = 192;

int old_spiral_start;
int old_spiral_inc;
int old_spiral_width;

int old_ringBeat[] = {3,2,0,1};
int old_numdots_ring_arr[] = {4,5,6,7};

// cylon variables
int old_cylon_step = 1;
int old_cylon_center = 0;
uint8_t old_cylon_index = 128;
uint8_t old_cylon_brightness = 255;

// colorwave variables
uint16_t old_sPseudotime;
uint16_t old_sLastMillis;
uint16_t old_sHue16;
uint8_t old_brightdepth, old_msmultiplier, old_hue8, old_bri8, old_cwave_index;
uint16_t old_brightnessthetainc16, old_hue16, old_hueinc16, old_ms, old_deltams, old_brightnesstheta16, old_h16_128, old_b16, old_bri16, old_pixelnumber;

// Bouncing ball variables
float old_h[NUM_BALLS];                         // An array of heights
float old_vImpact0 = sqrt(-2 * GRAVITY * h0);  // Impact velocity of the ball when it hits the ground if "dropped" from the top of the strip
float old_vImpact[NUM_BALLS];                   // As time goes on the impact velocity will change, so make an array to store those values
float old_tCycle[NUM_BALLS];                    // The time since the last time the ball struck the ground
int   old_pos[NUM_BALLS];                       // The integer position of the dot on the strip (LED index)
long  old_tLast[NUM_BALLS];                     // The clock time of the last ground strike
float old_COR[NUM_BALLS];                       // Coefficient of Restitution (bounce damping)
uint8_t old_ball_hue;

// circnosie variables
uint16_t old_shift_x;
uint16_t old_shift_y;
uint32_t old_real_x;
uint32_t old_real_y;
uint32_t old_real_z;
uint8_t old_noise;
uint8_t old_circ_index;
uint8_t old_circ_bri;

uint8_t old_fader = 0;

// moving dot variables
CRGB old_lead_led;
uint8_t old_blue_angle, old_blue_low, old_blue_high, old_green_angle, old_green_low, old_green_high, old_red_angle, old_red_low, old_red_high;
