#ifndef FLICKER_H_
#define FLICKER_H_

#include "Tween.h"
#include "../PropMechanic.h"

// The Flicker tween randomly moves between a low and high value. The value range defines the two values that it flickers between. The idle
// duration is how long it can stay in the low state. The sustain duration is how long it can stay in the high state. And the transition
// duration is how long it takes to go from one state to another.
namespace PropMechanic {
    typedef IntRange ValueRange;
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
        ValueRange valueRange;
        IdleDurationRange idleDuration;
        TransitionDurationRange transitionDuration;
        SustainDurationRange sustainDuration;

        milliseconds currentStateDuration;

        void goToState(State newState);
        int getValue();
        
        public:
        Flicker(ValueRange valueRange, IdleDurationRange idleDuration, TransitionDurationRange transitionDuration, SustainDurationRange sustainDuration);
    };
}

#endif /* FLICKER_H_ */