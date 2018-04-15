// Configuration for Animately must happen BEFORE including Animately.h.
#define TIMELINE_MAX_SCHEDULED_ENTRIES 20

#include "Animately.h"
#include "Core/Timeline.h"
#include "Parts/LED.h"
#include "Tweens/Flicker.h"

using namespace Animately;

Timeline timeline;

class Scene {
private:
    Timeline timeline;
    LED led1(9);
    LED led2(10);
    LED led3(11);
    LED led4(12);
    Flicker sparkTween({0, 255}, {15, 50}, {2, 10}, {15, 50});

public:
    
    void cueChase() {
        //timeline.schedule();
    }

    void cueFade() {
        //timeline.schedule();
    }

    void cueBounce() {
        //timeline.schedule();
    }

    void tick() {
        timeline.tick();
    }
}

Scene scene;

void setup() {
    Serial.begin(9600);
    scene.cueChase();
}

void loop() {
    scene.tick();
}
