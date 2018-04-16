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

#ifndef TIMELINETEST_H_
#define TIMELINETEST_H_

#include "Core/Timeline.h"
#include "Util/TestProp.h"
#include "Util/TestInverseTween.h"

using namespace Animately;

TestInverseTween tween;
TestProp prop1;
TestProp prop2;
TestProp prop3;
Timeline timeline;

test(basicScheduling)
{
    prop1.reset();
    timeline.schedule(0, 10, 5, 10,
        fastdelegate::MakeDelegate(&prop1, &TestProp::start),
        fastdelegate::MakeDelegate(&prop1, &TestProp::transition),
        fastdelegate::MakeDelegate(&tween, &TestInverseTween::getValue),
        fastdelegate::MakeDelegate(&prop1, &TestProp::end));
    
    int tickCount = 0;
    for (int i = 0; i < 5; i++) {
        timeline.tick(tickCount);
        assertEqual(prop1.getValue(), 0);
        tickCount++;
    }        
    
    // Check that the test inversion tween is exactly where we expect
    for (int i = 0; i < 10; i++) {
        timeline.tick(tickCount);
        assertEqual(prop1.getValue(), 10 - i); // Check the inversion tween
        tickCount++;
    }
    
    for (int i = 0; i < 10; i++) {
        timeline.tick(tickCount);
        assertEqual(prop1.getValue(), 10);
        tickCount++;
    }

    assertEqual(prop1.getStarted(), 1);
    assertEqual(prop1.getTransitioned(), 11);
    assertEqual(prop1.getEnded(), 1);
}


test(interlacedSchedulings)
{
    prop1.reset();
    prop2.reset();
    prop3.reset();

    timeline.schedule(0, 0, 20L, 40L,
        fastdelegate::MakeDelegate(&prop1, &TestProp::start),
        fastdelegate::MakeDelegate(&prop1, &TestProp::transition),
        NULL,
        fastdelegate::MakeDelegate(&prop1, &TestProp::end),
        0);
        
    timeline.schedule(0, 0, 10, 80,
        fastdelegate::MakeDelegate(&prop2, &TestProp::start),
        fastdelegate::MakeDelegate(&prop2, &TestProp::transition),
        NULL,
        fastdelegate::MakeDelegate(&prop2, &TestProp::end),
        0);
        
    timeline.schedule(0, 0, 30, 10,
        fastdelegate::MakeDelegate(&prop3, &TestProp::start),
        fastdelegate::MakeDelegate(&prop3, &TestProp::transition),
        NULL,
        fastdelegate::MakeDelegate(&prop3, &TestProp::end),
        0);

    for (int i = 0; i < 100; i++) {
        timeline.tick(i);
    }

    assertEqual(prop1.getStarted(), 1);
    assertEqual(prop1.getTransitioned(), 41);
    assertEqual(prop1.getEnded(), 1);
    
    assertEqual(prop2.getStarted(), 1);
    assertEqual(prop2.getTransitioned(), 81);
    assertEqual(prop2.getEnded(), 1);
    
    assertEqual(prop3.getStarted(), 1);
    assertEqual(prop3.getTransitioned(), 11);
    assertEqual(prop3.getEnded(), 1);
}

#endif /* TIMELINETEST_H_ */