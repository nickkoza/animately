#include "LED.h"

using namespace PropMechanic;

LED::LED(pinNum pin, Tween *tween)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
    analogWrite(pin, 0);
    this->tween = tween;
}

void LED::set(int brightness) {
    analogWrite(pin, brightness);
}

void LED::animate() {
    if (NULL == tween) {
        return;
    }
    
    set(tween->getValue());
}

void LED::off() {
    set(0);
}    