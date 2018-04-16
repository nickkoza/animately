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

#include "Button.h"

using namespace Animately;

Button::Button(pinNum pin, inputId id, ButtonPressDelegate pressDelegate, ButtonHoldDelegate holdDelegate, ButtonReleaseDelegate releaseDelegate) {
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