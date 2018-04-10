#ifndef TIMELINETEST_H_
#define TIMELINETEST_H_

#include "Core/Timeline.h"
#include "Util/TestProp.h"
#include "Util/TestInverseTween.h"

using namespace PropMechanic;

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