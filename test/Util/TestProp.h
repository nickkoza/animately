#ifndef TESTPROP_H_
#define TESTPROP_H_

#include "Animately.h"

class TestProp {
private:
    int startCounter;
    milliseconds lastStartedAt;
    int transitionCounter;
    int endCounter;
    milliseconds lastEndedAt;
    int value;
    
public:
    void reset() {
        startCounter = 0;
        lastStartedAt = 0;
        transitionCounter = 0;
        endCounter = 0;
        lastEndedAt = 0;
        value = 0;
    }
    
    TestProp() {
        reset();
    }
    
    void start(int value) {
        LOGF("Prop %p start", this);
        startCounter++;
        lastStartedAt = millis();
        this->value = value;
    }
    
    int getStarted() {
        return startCounter;
    }
    
    milliseconds getLastStartedAt() {
        return lastStartedAt;
    }
    
    void transition(int value) {
        transitionCounter++;
        this->value = value;
    }
    
    int getTransitioned() {
        return transitionCounter;
    }
    
    void end(int value) {
        LOGF("Prop %p end", this);
        endCounter++;
        lastEndedAt = millis();
        this->value = value;
    }
    
    int getEnded() {
        return endCounter;
    }
    
    milliseconds getLastEndedAt() {
        return lastEndedAt;
    }
    
    int getValue() {
        return value;
    }
};

#endif /* TESTPROP_H_ */