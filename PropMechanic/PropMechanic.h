#ifndef _PropMechanic_h
#define _PropMechanic_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

static const int timelineMaxEntries = 20;

#define COULD_NOT_ALLOCATE "E01"
#define REDUNDANT_ALLOCATION "E02"

#define ERROR(msg) Serial.println(msg);

typedef unsigned long milliseconds;

typedef void(*run)();


#endif

