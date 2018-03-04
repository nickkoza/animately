#include "TimeSwitch.h"


TimeSwitch::TimeSwitch(int pin, milliseconds maxCloseDuration, milliseconds minCooldownDuration)
{
    this->pin = pin;
    this->maxCloseDuration = maxCloseDuration;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, openState);
    state = Open;
}

void TimeSwitch::open()
{
    digitalWrite(pin, openState);
    state = Open;
    Serial.print("TIMESWITCH| - PIN ");
    Serial.print(pin);
    Serial.println(" - Open");
}

void TimeSwitch::close()
{
    digitalWrite(pin, closedState);
    state = Closed;
    Serial.print("TIMESWITCH - PIN ");
    Serial.print(pin);
    Serial.println(" - Close");
	// TODO - Remove the timeline entry if it still exists
}

boolean TimeSwitch::isOpen()
{
    return state == Open;
}

boolean TimeSwitch::isClosed()
{
    return state == Closed;
}

void TimeSwitch::run(void *instance)
{
    TimeSwitch *switchInstance = (TimeSwitch *)instance;
    switchInstance->close();
}

