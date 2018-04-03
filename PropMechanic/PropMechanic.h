#ifndef _PropMechanic_h
#define _PropMechanic_h

#include "arduino.h"

// CONFIGURATION
#ifndef TIMELINE_MAX_SCHEDULED_ENTRIES
    #define TIMELINE_MAX_SCHEDULED_ENTRIES 10
#endif

#ifndef TIMELINE_MAX_ACTIVE_ENTRIES
    #define TIMELINE_MAX_ACTIVE_ENTRIES 5
#endif


// ERROR MESSAGES
#ifndef COULD_NOT_ALLOCATE
    #define COULD_NOT_ALLOCATE "E01"
#endif

#ifndef REDUNDANT_ALLOCATION
    #define REDUNDANT_ALLOCATION "E02"
#endif

#ifndef COULD_NOT_SCHEDULE
    #define COULD_NOT_SCHEDULE "E03"
#endif

#ifndef INVALID_INDEX
    #define INVALID_INDEX "E04"
#endif


// MISC
#ifndef LOG
    #define LOG_BUFFER_SIZE 60
    extern char logBuffer[LOG_BUFFER_SIZE];
    #define LOG(msg) Serial.println(msg)
    #define LOGF(msg, args...) sprintf(logBuffer, msg, args); Serial.println(logBuffer);
#endif

#ifndef ERROR
    #define ERROR(msg) Serial.println(msg);
#endif

typedef unsigned long milliseconds;
typedef char pinNum;
typedef char inputId;

#endif // _PropMechanic_h
