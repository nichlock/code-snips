#ifndef VPI_MAIN_PROGRAM
#define VPI_MAIN_PROGRAM

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> // For tracking clocks
#include <signal.h> // SIGINT handle

#include "Serial.h"

// Colorful printout of warnings and errors
#define warn_printf(a, ...) \
	printf("\e[1;33mWarning: " a "\e[0;37m [from %s (in %s:%d)]\e[0m\n" \
	       __VA_OPT__(, ) __VA_ARGS__,  \
	       __FUNCTION__, __FILE__, __LINE__)
#define error_printf(a, ...) \
	printf("\e[1;31mError: " a "\e[0;37m [from %s (in %s:%d)]\e[0m\n" \
	       __VA_OPT__(, ) __VA_ARGS__,  \
	       __FUNCTION__, __FILE__, __LINE__)
// #define eprintf2(a, ...) \
// 	printf("\e[1;31mError: " a "\e[0m [from %s (in %s:%d)]\n" __VA_OPT__(, \
// 	                                                                     ) \
// 	       __VA_ARGS__, \
// 	       __FUNCTION__, __FILE__, __LINE__)

// Returns time since program start in seconds
#define PROG_TIME_NOW_S ((float)clock() / CLOCKS_PER_SEC)

typedef uint64_t delay_length; // Handles 'NOW' calls in vhdl
typedef char std_ulogic; // std_ulogic data follows the table below

// Table for identifying and setting non-binary simulated std_ulogic signals
#define SULV_U  (0) /* Uninitialized   */
#define SULV_X  (1) /* Forcing Unknown */
#define SULV_0  (2) /* Forcing 0       */
#define SULV_1  (3) /* Forcing 1       */
#define SULV_Z  (4) /* High Impedance  */
#define SULV_W  (5) /* Weak Unknown    */
#define SULV_L  (6) /* Weak 0          */
#define SULV_H  (7) /* Weak 1          */
#define SULV__  (8) /* Don't care      */

// Coloring for the console output
const char NUMBER_COLOR[]   = "\e[1;36m"; // Light cyan
const char ORANGE[]   = "\e[0;33m"; // Titles
const char NO_COLOR[]       = "\e[0m"; // Reset to the normal color after using the above

// Clock period configurations
// *****************************************************************************

/**
 * These periods are selected by the call to the startup function, and determine
 * the time delay used during clock_wait() to calibrate the sim clock to a
 * realtime period.
 */
#define CLOCK_SETTINGS_COUNT 4
static float clockPeriods[CLOCK_SETTINGS_COUNT] = {0.00001, // 100 kHz clock
	                                                 0.00001429, // 70 kHz clock
	                                                 0.00002, // 50 kHz clock
	                                                 0.001 // 1 kHz clock
};
static uint8_t clkConfigNum;

// Stores data used to track and calibrate clocks in real time
struct SimClock {
	// Helps determine how long clock_wait() waits. Set with clockPeriods[clkConfigNum]
	float intendedRealPeriodS; // = Clock period in s
	float clockWaitLastCalled;
	// For tracking clock timing
	float firstCycle, avgCycle;
	int cyclesCounted;
};

// Clock object for main clock
static struct SimClock clockData = {clockPeriods[0], 0, 0, 0, 0};

// Recycled variables for multiple functions
static float currentTime;
static float freqCalcd;
static uint8_t freqCalcdRange; // For autoranging

static uint8_t lastRegRecieved = 0;

static int startedUp = 0;

// Serial Control
// *****************************************************************************
static SerialPort sp0;
static char sp0Name[11] = "/dev/ttyS0";
static uint8_t readData[65] = {'\0'};

// Timer Data
// *****************************************************************************
// For timing data
static float startTime_s = 0, endTime_s = 0;
static uint64_t processorStartTime = 0, processorEndTime = 0;
static uint64_t simStartTime_ns = 0;
static uint64_t vpiCallCount = 0; // Tracks how many VPI functions are called during timers
static bool timerRunning = 0;

// Main Program
// *****************************************************************************
// Runs at exit
uint8_t setFreqRangeFromKhz(float *);

const char *freqRangeToString(uint8_t);

void closeHandler();

// VPI Interfacing
// *****************************************************************************
// VPI functions need an extern "C" so C++ compilers don't mangle the function names
extern "C" {
void init_c_prog(int);

void clock_wait(int);

void timer_start(uint64_t, int);

void timer_stop(uint64_t, int);

void clock_count(uint64_t);

void print_8_bit(uint8_t, uint64_t);
} /* extern "C" */

#endif /* end of include guard: VPI_MAIN_PROGRAM */
