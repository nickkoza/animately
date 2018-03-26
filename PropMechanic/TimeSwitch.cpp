#include "TimeSwitch.h"


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
    Serial.print("TIMESWITCH| - PIN ");
    Serial.print(pin);
    Serial.println(" - Open");
}

void TimeSwitch::close(void *data)
{
    digitalWrite(pin, TIME_SWITCH_CLOSE_STATE);
    state = Closed;
    Serial.print("TIMESWITCH| - PIN ");
    Serial.print(pin);
    Serial.println(" - Close");
}

boolean TimeSwitch::isOpen()
{
    return state == Open;
}

boolean TimeSwitch::isClosed()
{
    return state == Closed;
}

