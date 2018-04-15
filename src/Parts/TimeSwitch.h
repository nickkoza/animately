#ifndef _TimeSwitch_h
#define _TimeSwitch_h

#include "Arduino.h"
#include "../Animately.h"

#ifndef TIME_SWITCH_OPEN_STATE
    #define TIME_SWITCH_OPEN_STATE LOW
#endif

#ifndef TIME_SWITCH_CLOSE_STATE
    #define TIME_SWITCH_CLOSE_STATE HIGH
#endif

namespace Animately {
    class TimeSwitch
    {
    private:
        enum State { Open = false, Closed = true };

        pinNum pin;
        milliseconds maxCloseDuration;
        milliseconds minCooldownDuration;
        boolean state;
    public:
        TimeSwitch(pinNum pin, milliseconds maxCloseDuration, milliseconds minCooldownDuration);

        void open(int val);
        void close(int val);
        boolean isOpen();
        boolean isClosed();
    };
}
#endif