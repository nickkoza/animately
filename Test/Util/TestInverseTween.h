#ifndef TESTINVERSETWEEN_H_
#define TESTINVERSETWEEN_H_

#include "Tweens/Tween.h"

using namespace Animately;

class TestInverseTween: public Tween {
public:
    float getValue(float value) {
        return 1.0f - value;
    }
};

#endif /* TESTINVERSETWEEN_H_ */