#include "VpiMain.h"

/**
 * Finds the correct range for the frequency, then adjusts the frequency value given.
 */
inline uint8_t setFreqRangeFromKhz(float *freq) {
	uint8_t range = 0;
	if (*freq < 1) {
		range = 0; // frequency is in Hz
		*freq = *freq * 1000;
	} else if (*freq < 1000) {
		range = 1; // frequency is in kHz, the most common
	} else if (*freq < 1000000) {
		range = 2; // frequency is in MHz
		*freq = *freq / 1000;
	} else {
		range = 3; // Oh my
		*freq = *freq / 1000000;
	}
	return range;
} /* getFreqRange */

/**
 * Always returns three chars for printing. Returns the frequency unit string
 * after autoscaling using setFreqRangeFromKhz
 */

inline const char *freqRangeToString(uint8_t range){
	switch (range) {
	case 0: return "Hz ";
		break;
	case 1: return "kHz";
		break;
	case 2: return "MHz";
		break;
	case 3: return "GHz";
		break;
	default: return "err";
		break;
	} /* switch */
} /* getFreqRangeString */

/**
 * Called at exit to close files and stop timers.
 */
void closeHandler() {
	printf("%s\nClosing\n", NO_COLOR);
	sp0.closePort();
	if (timerRunning) timer_stop(0, 1);
} /* closeHandler */

void signalHandler(int sig) {
	exit(EXIT_SUCCESS);
} // signalHandler

// VPI Functions

// *****************************************************************************

/**
 * GHDL referred functions must be defined with extern "C" since VPI finds
 * functions by name after compiling. See header function definitions
 */

/**
 * Starts a timer which counts how many of these functions are called and prints
 * time when timer_stop is called
 * @param ignoreRepeats Ignores calls that happen after another a timer_start() call.
 */
void timer_start(delay_length sim_time, int ignoreRepeats){
	if (timerRunning) {
		if (!ignoreRepeats)
			error_printf("The timer is already running, call ignored.");
		return;
	}
	timerRunning = true;
	simStartTime_ns = sim_time / 1000000;
	vpiCallCount = 0;
	printf("%sTimer Started.%s\n", ORANGE, NO_COLOR);
	startTime_s = PROG_TIME_NOW_S; // Get real time & processor time at end of call
	processorStartTime = clock();
} /* timer_start */

/**
 * Stops the timer started by timer_start and prints info about how long things took.
 * @param ignoreRepeats Ignores calls that happen without a timer_start() call
 *                      immediately before hand. Usefule for detecting when a
 *                      state changes and ignoreing the state after that.
 */

void timer_stop(delay_length sim_time, int ignoreRepeats) {
	processorEndTime = clock(); // Get processor time
	endTime_s = PROG_TIME_NOW_S; // Get real time
	if (!timerRunning) {
		if (!ignoreRepeats)
			error_printf("The timer was not running, call ignored.");
		return;
	}
	timerRunning = false;
	sim_time /= 1000000;
	printf("\n%sTimer Finished.%s\n", ORANGE, NO_COLOR);
	printf("\tTotal calls:        %10d calls\n", vpiCallCount);
	printf("\tTotal real time:    %10f ms\n",
	       (endTime_s - startTime_s) * 1000);
	if (sim_time > 0) // Only show if the data is available
		printf("\tReported sim time:  %10ld ns\n", sim_time - simStartTime_ns);
	else
		warn_printf("Stop called after program ended, sim time not available.");
	// printf("\tTotal sim time:\tns\t%10d\n", endTime_ns - simStartTime_ns);
} /* timer_stop */

/**
 * Track the clocks and print info about them when needed.
 */

void clock_count(delay_length sim_now) {
	vpiCallCount++;
	clockData.cyclesCounted++;
	if (clockData.cyclesCounted == 1) {
		clockData.firstCycle = PROG_TIME_NOW_S * 1000;
		clockData.cyclesCounted++;
	} else if (clockData.cyclesCounted *
	           clockData.intendedRealPeriodS >= 0.5) { // Prints data less often
		currentTime = PROG_TIME_NOW_S * 1000;
		clockData.avgCycle = (((currentTime - clockData.firstCycle)) /
		                      clockData.cyclesCounted);
		freqCalcd = 1 / clockData.avgCycle;
		freqCalcdRange = setFreqRangeFromKhz(&freqCalcd); // Assigns range value and adjusts freqCalcd
		sim_now /= 1000000; // Scale to ns
		// Print out data after removing previous data on the line
		// for (int c = 0; c < 140; c++) // Remove text on the console line
// 	printf("\b");
		printf(
			"Average clock cycle: %s%10fms%s, real clock frequency: %s%5.2f%s%s, sim time: %s%10ldns%s\n",
			NUMBER_COLOR, clockData.avgCycle, NO_COLOR,
			NUMBER_COLOR, freqCalcd, freqRangeToString(freqCalcdRange), NO_COLOR,
			NUMBER_COLOR, sim_now, NO_COLOR);

		clockData.cyclesCounted = 0; // Reset counter and cycle times for a more recent averaging.
	}
} /* clock_count */

/**
 * Prints the given register and the sim time every time the register changes,
 * if enabled.
 */

void print_8_bit(uint8_t reg, delay_length sim_now) {
	vpiCallCount++;
	if (reg == lastRegRecieved) {
		return;
	}
	// sim_now /= 1000000;
	// printf("Transition at sim time %s%10ldns%s:\n",
	//        NUMBER_COLOR, sim_now, NO_COLOR);
	// for (int c = 0; c < 25; c++) // Remove text on the console line
	// 	printf("\b");
	// // printf("reg: %s0x%2x%s", NUMBER_COLOR, reg, NO_COLOR);
	// printf("reg: %s", NUMBER_COLOR);
	// for (int i = 0; i < sizeof(reg) * 8; i++)
	// 	printf("%d", (reg >> i) & 0b1);
	// printf("%s = %s0x%2x%s\n", NO_COLOR, NUMBER_COLOR, reg, NO_COLOR);
	lastRegRecieved = reg;
	sp0.writeByte(reg);
} /* print_a_reg */

/**
 * Call at end of a clock cycle operation to delay the sim for that time meant for use with only the
 * main clock. Clock timing can be set using the clocks object.
 */
void clock_wait(int xx) { // Needs at least 1 arg for use with VHDL
	vpiCallCount++;
	while (PROG_TIME_NOW_S < clockData.intendedRealPeriodS +
	       clockData.clockWaitLastCalled) {}
	// Technically, the next clock cycle time starts here.
	clockData.clockWaitLastCalled = PROG_TIME_NOW_S;
} /* clock_wait_period */

/**
 * Call at start of VHDL testbench/sim.
 *
 * Sets up serial, clock timing settings and tracking, and prints any issues with
 * the configuration. If this is not called at the start of the VHDL sim, it may
 * break those functionalities.
 */
void init_c_prog(int config) {
	vpiCallCount++;
	printf("%s: %s is starting up.\n", __FILE__, __PRETTY_FUNCTION__);
	// Prints a newline and closes the serial port on exit
	atexit(closeHandler);
	signal(SIGINT, signalHandler);

	clkConfigNum = config; // Set the clock mode
	printf("\tClock setting number: %s%d%s\n", NUMBER_COLOR, clkConfigNum,
	       NO_COLOR);
	if (clkConfigNum >= CLOCK_SETTINGS_COUNT) {
		error_printf("Invalid clock config number selected. Exiting.");
		exit(EXIT_FAILURE);
	}
	freqCalcd = 1 / (clockData.intendedRealPeriodS * 1000); // Scaled to kHz
	freqCalcdRange = setFreqRangeFromKhz(&freqCalcd); // Assigns range value and adjusts freqCalcd

	printf("\tIntended clock frequency: %s%5.2f%s%s\n",
	       NUMBER_COLOR, freqCalcd, freqRangeToString(freqCalcdRange), NO_COLOR);
	if (clockData.intendedRealPeriodS == 0) {
		error_printf("Selected clock config has a zero-value period. Exiting.");
		exit(EXIT_FAILURE);
	}

	printf("Opening serial port %s: %s\n",
	       sp0Name, (sp0.openPort(sp0Name) < 0)?strerror(errno): "Success");
	printf("Configuring serial port %s: %s\n",
	       sp0Name, (sp0.configDefaults() < 0)?strerror(errno): "Success");
	printf("Flushing %d bytes from port %s\n", (uint8_t)sp0.flushReadable(),
	       sp0Name);

	clockData.clockWaitLastCalled = PROG_TIME_NOW_S;
} /* start_c_prog */
