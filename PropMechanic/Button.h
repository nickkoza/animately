#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"
#include "FastDelegate.h"

// Button provides a basic interface for calling delegates and de-bouncing button inputs.
// This class requires that you call the tick() method often.
// This class is not designed for use with hardware interrupts, though you could modify
// it for that use.
class Button {
public:
    typedef fastdelegate::FastDelegate1<int> ButtonPressDelegate;
    typedef fastdelegate::FastDelegate1<int> ButtonHoldDelegate;
    typedef fastdelegate::FastDelegate1<int> ButtonReleaseDelegate;
    
private:
    int pin;
    int id;
    
    ButtonPressDelegate pressDelegate;
    ButtonHoldDelegate holdDelegate;
    ButtonReleaseDelegate releaseDelegate;
    
    boolean pressed;

public:
    Button(int pin, int id, ButtonPressDelegate pressDelegate, ButtonHoldDelegate holdDelegate, ButtonReleaseDelegate releaseDelegate);
    void tick();
};

#endif /* BUTTON_H_ */