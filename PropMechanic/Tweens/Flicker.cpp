#include "Flicker.h"

using namespace PropMechanic;

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
