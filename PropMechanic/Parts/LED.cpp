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

void LED::setf(float brightness, void *data) {
    set(255.0f * brightness);
}

void LED::off(void *data) {
    set(0);
}    