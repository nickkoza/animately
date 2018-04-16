// MIT License
//
// Copyright (c) 2018 Nicholas Koza
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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