#ifndef _TimeSwitch_h
#define _TimeSwitch_h

#include <Arduino.h>

#include "PropMechanic.h"

class TimeSwitch
{
private:
    enum State { Open = false, Closed = true };

    const int openState = LOW;
    const int closedState = HIGH;
    int pin;
    milliseconds maxCloseDuration;
    milliseconds minCooldownDuration;
    boolean state;
public:
    TimeSwitch(int pin, milliseconds maxCloseDuration, milliseconds minCooldownDuration);

    void open();
    void close();
    boolean isOpen();
    boolean isClosed();
    static void run(void *instance);
};

#endif