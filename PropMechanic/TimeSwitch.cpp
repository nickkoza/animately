#include "TimeSwitch.h"

using namespace PropMechanic;

TimeSwitch::TimeSwitch(pinNum pin, milliseconds maxCloseDuration, milliseconds minCooldownDuration)
{
    this->pin = pin;
    this->maxCloseDuration = maxCloseDuration;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, TIME_SWITCH_OPEN_STATE);
    state = Open;
}

void TimeSwitch::open(void *data)
{
    digitalWrite(pin, TIME_SWITCH_OPEN_STATE);
    state = Open;
    LOGF("TIMESWITCH - PIN %d OPEN", pin);
}

void TimeSwitch::close(void *data)
{
    digitalWrite(pin, TIME_SWITCH_CLOSE_STATE);
    state = Closed;
    LOGF("TIMESWITCH - PIN %d CLOSE", pin);
}

boolean TimeSwitch::isOpen()
{
    return state == Open;
}

boolean TimeSwitch::isClosed()
{
    return state == Closed;
}

