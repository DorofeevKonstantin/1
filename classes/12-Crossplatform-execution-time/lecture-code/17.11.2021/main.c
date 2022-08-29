#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "executionTime.h"
#include "redirectingIO.h"
#include "crossplatform.h"

typedef unsigned int length;
typedef char* string;

#ifdef _WIN32
#define HelloFunction WindowsFunction
#elif __linux__
#define HelloFunction LinuxFunction
#endif

#ifdef _WIN32
#include <windows.h>
#define msleep(x) Sleep(x)
#else
#include <unistd.h>
#define msleep(x) usleep(x * 1000)
#endif

int main()
{
	timeMeasurementExample();
	redirectingExample();
	HelloFunction();
	msleep(1000);
	return 0;
}