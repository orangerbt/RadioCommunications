#ifndef SERIALIO
#define SERIALIO

#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/ioctl.h>

using namespace std;

class serialIO
{
public:
	struct serialConfig
	{
		string device;
		speed_t speed;
		int parity;
		bool blocking;
		int timeoutMs;
	};

	~serialIO();
	int initialize(string device, speed_t speed = B9600, int parity = 0, bool blocking = false, int timeoutMs = 50);
	int initialize(serialConfig config);
	int close();

	int writeTo(string toWrite);
	string readFrom();
	string readFrom(int minChars);

	void setRTS();
	void clearRTS();
	void setDTR();
	void clearDTR();

	void getConfig(serialConfig *config);

	static int intToBaud(int speed);

private:

	int setBlocking(bool state, int timeoutMs);
	int setAttributes(speed_t speed, int parity);

	int fd;	
	float timeoutTime;

	serialConfig settings;
};

#endif
