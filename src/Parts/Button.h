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

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"
#include "../Core/FastDelegate.h"
#include "../Animately.h"

// Button provides a basic interface for calling delegates and de-bouncing button inputs.
// This class requires that you call the tick() method often.
// This class is not designed for use with hardware interrupts, though you could modify
// it for that use.
namespace Animately {
    class Button {
        public:
        typedef fastdelegate::FastDelegate1<inputId> ButtonPressDelegate;
        typedef fastdelegate::FastDelegate1<inputId> ButtonHoldDelegate;
        typedef fastdelegate::FastDelegate1<inputId> ButtonReleaseDelegate;
        
        private:
        pinNum pin;
        inputId id;
        
        ButtonPressDelegate pressDelegate;
        ButtonHoldDelegate holdDelegate;
        ButtonReleaseDelegate releaseDelegate;

        boolean pressed;

        public:
        Button(pinNum pin, inputId id, ButtonPressDelegate pressDelegate, ButtonHoldDelegate holdDelegate, ButtonReleaseDelegate releaseDelegate);
        void tick();
    };
}
#endif /* BUTTON_H_ */