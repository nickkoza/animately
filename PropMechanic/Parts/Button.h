#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"
#include "../Core/FastDelegate.h"
#include "../PropMechanic.h"

// Button provides a basic interface for calling delegates and de-bouncing button inputs.
// This class requires that you call the tick() method often.
// This class is not designed for use with hardware interrupts, though you could modify
// it for that use.
namespace PropMechanic {
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