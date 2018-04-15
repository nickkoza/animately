// Configuration for Animately must happen BEFORE including Animately.h.
// This #define increases the number of animations that we can schedule at one time.
#define TIMELINE_MAX_SCHEDULED_ENTRIES 20


#include "Animately.h"
#include "Core/Timeline.h"
#include "Parts/LED.h"
#include "Tweens/Flicker.h"


// By defining that we're using the Animately namespace, we don't have to prefix all Animately classes with "Animately::"
using namespace Animately;


// We could schedule animations in the setup() function, but by putting them into a class like Scene
// we can chain them together so an animation ending schedules the start of another animation.
class Scene {
private:
    Timeline *timeline;
    LED *led1;
    LED *led2;
    LED *led3;
    LED *led4;
    Tween *sparkTween;

public:
    Scene(Timeline *timeline, LED *led1, LED *led2, LED *led3, LED *led4, Tween *sparkTween) {
        this->timeline = timeline;
        this->led1 = led1;
        this->led1 = led1;
        this->led1 = led1;
        this->led1 = led1;
        this->sparkTween = sparkTween;
    }
    
    void cueChase() {
        //timeline.schedule();
    }

    void cueFade() {
        //timeline.schedule();
    }

    void cueBounce() {
        //timeline.schedule();
    }
};


// Setup all our parts
Timeline timeline;
LED led1(9);
LED led2(10);
LED led3(11);
LED led4(12);


// Setup all our tweens
Flicker sparkTween({0, 255}, {15, 50}, {2, 10}, {15, 50});


// Create the scene
Scene scene(&timeline, &led1, &led2, &led3, &led4, &sparkTween);


void setup() {
    Serial.begin(9600);
    
    // Start the scene
    scene.cueChase();
}


void loop() {
    // timeline.tick() should be called at least once per ms. Calling it more often is fine.
    timeline.tick();
}
