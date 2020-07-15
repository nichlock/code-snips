#include <fcntl.h> // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include "Serial.h"

/**
 *
 */

int SerialPort::openPort(char *portName){
	fd = open(portName, O_RDWR | O_NOCTTY | O_NONBLOCK);
	return fd;
} // openPort

/**
 *
 */

bool SerialPort::configDefaults() {
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if (tcgetattr(fd, &tty) != 0) {
		return 0;
	}
	tty.c_cflag &= ~PARENB; // No parity
	tty.c_cflag &= ~CSTOPB; // One stop bit
	tty.c_cflag |= CS8; // 8 bits
	tty.c_cflag &= ~CRTSCTS; // No flow control

	tty.c_cflag |= CREAD | CLOCAL;
	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO;
	tty.c_lflag &= ~ISIG;

	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR;

	tty.c_cc[VTIME] = 0; // non blocking read
	tty.c_cc[VMIN] = 0;

	cfsetispeed(&tty, B115200);
	cfsetospeed(&tty, B115200);

	if (tcsetattr(fd, TCSANOW, &tty) != 0) {
		return 0;
	}
	return 1;
} // SerialPort::configDefaults

/**
 * Writes a single byte to the serial output buffer
 */

size_t SerialPort::writeByte(uint8_t msg){
	if (fd < 0) return -1;
	return write(fd, &msg, 1);
} // SerialPort::writeByte

/**
 * Writes multiple bytes to the serial output buffer.
 */

size_t SerialPort::writeBytes(const uint8_t *msg, size_t len){
	if (fd < 0) return -1;
	return write(fd, msg, len);
} // SerialPort::writeBytes

/**
 * Writes multiple bytes to the serial output buffer.
 */

size_t SerialPort::writeBytes(const char *msg, size_t len){
	if (fd < 0) return -1;
	return write(fd, msg, len);
} // SerialPort::writeBytes

/**
 * Reads at most len bytes into msg array and returns the length of the read.
 */

size_t SerialPort::readBytes(uint8_t *msg, size_t len){
	return read(fd, msg, len);
} // SerialPort::readByte

/**
 * Clears all readable data form the buffer, for use at startup.
 * This might not work
 */

size_t SerialPort::flushReadable(){
	if (fd <= 0)
		return -1;
	size_t flushedLen;
	size_t lastFlushedLen;
	uint8_t msg[64];
	do {
		lastFlushedLen = flushedLen;
		flushedLen += read(fd, msg, 64);
	} while (lastFlushedLen != flushedLen);
	return flushedLen;
} // SerialPort::flushReadable

/**
 * Closes the file used to drive the serial interface
 */

int SerialPort::closePort(){
	return close(fd);
} // SerialPort::close
