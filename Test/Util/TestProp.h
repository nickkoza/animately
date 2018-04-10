#ifndef TESTPROP_H_
#define TESTPROP_H_

#include "PropMechanic.h"

class TestProp {
private:
    int startCounter;
    milliseconds lastStartedAt;
    int transitionCounter;
    int endCounter;
    milliseconds lastEndedAt;
    
public:
    void reset() {
        startCounter = 0;
        lastStartedAt = 0;
        transitionCounter = 0;
        endCounter = 0;
        lastEndedAt = 0;
    }
    
    TestProp() {
        reset();
    }
    
    void start(int value) {
        LOGF("Prop %p start", this);
        startCounter++;
        lastStartedAt = millis();
    }
    
    int getStarted() {
        return startCounter;
    }
    
    milliseconds getLastStartedAt() {
        return lastStartedAt;
    }
    
    void transition(int value) {
        transitionCounter++;
    }
    
    int getTransitioned() {
        return transitionCounter;
    }
    
    void end(int value) {
        LOGF("Prop %p end", this);
        endCounter++;
        lastEndedAt = millis();
    }
    
    int getEnded() {
        return endCounter;
    }
    
    milliseconds getLastEndedAt() {
        return lastEndedAt;
    }
};

#endif /* TESTPROP_H_ */