#ifndef __LED_H__
#define __LED_H__

#include "../Animately.h"
#include "../Tweens/Tween.h"

namespace Animately {
    class LED
    {
    private:
        pinNum pin;

    public:
        LED(pinNum pin);
        void set(int brightness);
        void off(int val);
    };
}

#endif //__LED_H__
