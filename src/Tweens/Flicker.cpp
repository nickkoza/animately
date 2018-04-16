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

#include "Flicker.h"

using namespace Animately;

Flicker::Flicker(FloatRange valueRange, IdleDurationRange idleDuration, TransitionDurationRange transitionDuration, SustainDurationRange sustainDuration) {
    this->valueRange = valueRange;
    this->idleDuration = idleDuration;
    this->transitionDuration = transitionDuration;
    this->sustainDuration = sustainDuration;
    goToState(STOPPED);
}

float Flicker::getValue(float transitionAmount) {
    milliseconds currentTime = millis();
    
    if (state == IDLING) {
        if (currentTime > stateEntryTime + currentStateDuration) {
            goToState(TRANSITION_UP);
        }
        return valueRange.min;
    }
    else if (state == TRANSITION_UP) {
        float transitionBrightness = ((float)currentTime - (float)stateEntryTime) / (float)currentStateDuration;
        int returnVal = valueRange.min + ((float)valueRange.max - (float)valueRange.min) * transitionBrightness;
        if (currentTime > stateEntryTime + currentStateDuration) {
            goToState(SUSTAIN);
        }
        return returnVal;
    }
    else if (state == SUSTAIN) {
        if (currentTime > stateEntryTime + currentStateDuration) {
            goToState(TRANSITION_DOWN);
        }
        return valueRange.max;
    }
    else if (state == TRANSITION_DOWN) {
        float transitionBrightness = 1.f - (((float)currentTime - (float)stateEntryTime) / (float)currentStateDuration);
        int returnVal = valueRange.min + ((float)valueRange.max - (float)valueRange.min) * transitionBrightness;
        if (currentTime > stateEntryTime + currentStateDuration) {
            goToState(IDLING);
        }
        return returnVal;
    }
    
    // Assumed STOP state
    return valueRange.min;
}

void Flicker::goToState(State newState) {
    state = newState;
    stateEntryTime = millis();

    if (state == IDLING) {
        currentStateDuration = random(idleDuration.min, idleDuration.max);
    }
    else if (state == TRANSITION_UP || state == TRANSITION_DOWN) {
        currentStateDuration = random(transitionDuration.min, transitionDuration.max);
    }
    else if (state == SUSTAIN) {
        currentStateDuration = random(sustainDuration.min, sustainDuration.max);
    }
}
