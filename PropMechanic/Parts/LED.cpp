#include "LED.h"

using namespace PropMechanic;

LED::LED(pinNum pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
    analogWrite(pin, 0);
}

void LED::set(int brightness) {
    analogWrite(pin, brightness);
}

void LED::off(int val) {
    set(0);
}    