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

#ifndef _TimeSwitch_h
#define _TimeSwitch_h

#include "Arduino.h"
#include "../Animately.h"

#ifndef TIME_SWITCH_OPEN_STATE
    #define TIME_SWITCH_OPEN_STATE LOW
#endif

#ifndef TIME_SWITCH_CLOSE_STATE
    #define TIME_SWITCH_CLOSE_STATE HIGH
#endif

namespace Animately {
    class TimeSwitch
    {
    private:
        enum State { Open = false, Closed = true };

        pinNum pin;
        milliseconds maxCloseDuration;
        milliseconds minCooldownDuration;
        boolean state;
    public:
        TimeSwitch(pinNum pin, milliseconds maxCloseDuration, milliseconds minCooldownDuration);

        void open(int val);
        void close(int val);
        boolean isOpen();
        boolean isClosed();
    };
}
#endif