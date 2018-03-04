#ifndef _PropMechanic_h
#define _PropMechanic_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define ERROR(msg) Serial.println(msg);

typedef unsigned long milliseconds;

typedef void(*run)();


#endif

