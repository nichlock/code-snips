
Handle kill/pause signals, like ^C (SIGINT):
```c++
#include <signal.h>

void signalHandle(int signalNumber) {
	// handle signal here
}

int main(int argc, char const *argv[]) {
	signal(SIGINT, signalHandle);
	signal(SIGTERM, signalHandle);

	kill(1234, SIGTERM); // Kill another program with PID 1234
	raise(SIGINT); // Kill program by calling a SIGINT to itself
	return 0; // Program never gets here
}

```

Have a function run at exit, regardless of signal:
```c++
void exitHandle() {
	// handle exiting here
}

int main(int argc, char const *argv[]) {
	atexit(exitHandle); // When the program exits, by most means, exitHandle will be called.
}
```
