#ifndef TWEEN_H_
#define TWEEN_H_

#include "../Animately.h"

namespace Animately {
    class Tween {
    public:  
        virtual float getValue(float transitionAmount) = 0;
    };
}

#endif /* TWEEN_H_ */