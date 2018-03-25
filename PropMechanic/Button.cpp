#include "Button.h"

Button::Button(int pin, int id, ButtonPressDelegate pressDelegate, ButtonHoldDelegate holdDelegate, ButtonReleaseDelegate releaseDelegate) {
    this->pin = pin;
    this->id = id;
    this->pressDelegate = pressDelegate;
    this->holdDelegate = holdDelegate;
    this->releaseDelegate = releaseDelegate;
    
    pinMode(pin, INPUT);
}

void Button::tick() {
    if (digitalRead(pin) == HIGH) {
        if (!pressed) {
            pressed = true;
            if (NULL != pressDelegate) {
                pressDelegate(id);
            }
        }
        
        if (NULL != holdDelegate) {
            holdDelegate(id);
        }
    }
    else if (pressed) {
        pressed = false;
        if (NULL != releaseDelegate) {
            releaseDelegate(id);
        }
    }
}