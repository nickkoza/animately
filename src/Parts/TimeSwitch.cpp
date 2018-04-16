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

#include "TimeSwitch.h"

using namespace Animately;

TimeSwitch::TimeSwitch(pinNum pin, milliseconds maxCloseDuration, milliseconds minCooldownDuration)
{
    this->pin = pin;
    this->maxCloseDuration = maxCloseDuration;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, TIME_SWITCH_OPEN_STATE);
    state = Open;
}

void TimeSwitch::open(int val)
{
    digitalWrite(pin, TIME_SWITCH_OPEN_STATE);
    state = Open;
    LOGF("TIMESWITCH - PIN %d OPEN", pin);
}

void TimeSwitch::close(int val)
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

