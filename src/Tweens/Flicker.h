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

#ifndef FLICKER_H_
#define FLICKER_H_

#include "Tween.h"
#include "../Animately.h"

// The Flicker tween randomly moves between a low and high value. The value range defines the two values that it flickers between. The idle
// duration is how long it can stay in the low state. The sustain duration is how long it can stay in the high state. And the transition
// duration is how long it takes to go from one state to another.
namespace Animately {
    typedef MillisecondRange IdleDurationRange; // Idle is the low state
    typedef MillisecondRange TransitionDurationRange;
    typedef MillisecondRange SustainDurationRange; // Sustain is the high state

    class Flicker: public Tween {
        private:
        enum State {
            STOPPED = 0,
            IDLING = 1,
            TRANSITION_UP = 2,
            SUSTAIN = 3,
            TRANSITION_DOWN = 4
        };
        
        milliseconds stateEntryTime;
        State state;
        FloatRange valueRange;
        IdleDurationRange idleDuration;
        TransitionDurationRange transitionDuration;
        SustainDurationRange sustainDuration;

        milliseconds currentStateDuration;

        void goToState(State newState);
        
    public:
        Flicker(FloatRange valueRange, IdleDurationRange idleDuration, TransitionDurationRange transitionDuration, SustainDurationRange sustainDuration);
        float getValue(float transitionAmount);
    };
}

#endif /* FLICKER_H_ */