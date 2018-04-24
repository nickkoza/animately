// MIT License
//
// Copyright (c) 2018 Nicholas Koza
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _Animately_h
#define _Animately_h

#include "arduino.h"

// CONFIGURATION
#ifndef TIMELINE_MAX_SCHEDULED_ENTRIES
    #define TIMELINE_MAX_SCHEDULED_ENTRIES 15
#endif

#ifndef TIMELINE_MAX_ACTIVE_ENTRIES
    #define TIMELINE_MAX_ACTIVE_ENTRIES 8
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

#ifndef VALUE_OUT_OF_RANGE
    #define VALUE_OUT_OF_RANGE "E05"
#endif


// LOGGING
#ifndef LOG
    #define LOG_BUFFER_SIZE 60
    extern char logBuffer[LOG_BUFFER_SIZE];
    #define LOG(msg) Serial.println(msg)
    #define LOGF(msg, args...) sprintf(logBuffer, msg, args); Serial.println(logBuffer);
#endif

#ifndef ERROR
    #define ERROR(msg) Serial.println(msg);
#endif


// MISC
#define DELEGATE(args...) fastdelegate::MakeDelegate(args)

typedef unsigned long milliseconds;
typedef char pinNum;
typedef char inputId;
typedef char propId;
typedef char tweenId;

struct IntRange {
    int min;
    int max;
};

struct FloatRange {
    float min;
    float max;
};

struct MillisecondRange {
    milliseconds min;
    milliseconds max;
};

#endif // _Animately_h
