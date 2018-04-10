#ifndef TWEEN_H_
#define TWEEN_H_

#include "../PropMechanic.h"

namespace PropMechanic {
    class Tween {
    public:  
        virtual float getValue(float transitionAmount) = 0;
    };
}

#endif /* TWEEN_H_ */