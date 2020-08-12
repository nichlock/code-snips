#ifndef SERIAL_H
#define SERIAL_H

#include <errno.h> // Error integer and strerror() function
#include <stdint.h>
#include <string.h>
// #include <iostream.h>

using namespace std;

/**
 */
class SerialPort {
private:
	// const static int MAX_READ = 256;
public:
	int fd;

	// void runPort();

	int openPort(char *portName);

	bool configure( /*configs go here */); // Should be for variable settings

	bool configDefaults();

	size_t writeByte(uint8_t msg);

	size_t writeBytes(const uint8_t *msg, size_t len);

	size_t writeBytes(const char *msg, size_t len);

	size_t readBytes(uint8_t *msg, size_t len);

	size_t flushReadable();

	int closePort();
}

;

#endif /* ifndef SERIAL_H */
