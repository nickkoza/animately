#ifndef __LED_H__
#define __LED_H__

#include "../PropMechanic.h"
#include "../Tweens/Tween.h"

namespace PropMechanic {
    class LED
    {
    private:
        pinNum pin;
        Tween *tween;

    public:
	    LED(pinNum pin, Tween *tween);
        void set(int brightness);
        void animate();
        void off();
    };
}

#endif //__LED_H__
