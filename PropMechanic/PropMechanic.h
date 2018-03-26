#ifndef _PropMechanic_h
#define _PropMechanic_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif


// CONFIGURATION
#ifndef TIMELINE_MAX_SCHEDULED_ENTRIES
    #define TIMELINE_MAX_SCHEDULED_ENTRIES 10
#endif

#ifndef TIMELINE_MAX_ACTIVE_ENTRIES
    #define TIMELINE_MAX_ACTIVE_ENTRIES 5
#endif


// ERROR MESSAGES
#define COULD_NOT_ALLOCATE "E01"
#define REDUNDANT_ALLOCATION "E02"
#define COULD_NOT_SCHEDULE "E03"
#define INVALID_INDEX "E04"


// MISC
#define ERROR(msg) Serial.println(msg);

typedef unsigned long milliseconds;
typedef char pinNum;
typedef char inputId;

#endif

