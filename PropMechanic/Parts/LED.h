#ifndef __LED_H__
#define __LED_H__

#include "../PropMechanic.h"
#include "../Tweens/Tween.h"

namespace PropMechanic {
    class LED
    {
    private:
        pinNum pin;

    public:
	    LED(pinNum pin);
        void set(int brightness);
        void setf(float brightness, void *data);
        void off(void *data);
    };
}

#endif //__LED_H__
