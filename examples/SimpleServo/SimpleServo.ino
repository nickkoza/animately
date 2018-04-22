// This example shows how to animate a single servo. It utilizes the standard Arduino Servo library, which also shows
// how you can use non-Animately classes as parts as long as their function signature matches.

#include <Servo.h> // This is the standard Arduino library, not an Animately library

#include <Animately.h>
#include <Core/Timeline.h>
#include <Parts/LED.h>
#include <Tweens/Quintic.h>

using namespace Animately;

class Scene {
private:
    Timeline *timeline;
    Quintic *quintic;
    Servo *servo;

public:
    Scene(Timeline *timeline, Servo *servo, Quintic *quintic) {
        this->timeline = timeline;
        this->servo = servo;
        this->quintic = quintic;
    }

    void cue(int val) {
        int currTime = 0;
        timeline->schedule(0, 180, currTime, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quintic, &Quintic::inOut),
            DELEGATE(servo, &Servo::write));
        currTime += 3000;

        timeline->schedule(180, 45, currTime, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quintic, &Quintic::inOut),
            DELEGATE(servo, &Servo::write));
        currTime += 3000;

        timeline->schedule(45, 0, currTime, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quintic, &Quintic::inOut),
            DELEGATE(servo, &Servo::write));
        currTime += 3000;

        timeline->schedule(0, 90, currTime, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quintic, &Quintic::inOut),
            DELEGATE(servo, &Servo::write));
        currTime += 3000;

        timeline->schedule(90, 180, currTime, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quintic, &Quintic::inOut),
            DELEGATE(servo, &Servo::write));
        currTime += 3000;

        timeline->schedule(180, 0, currTime, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quintic, &Quintic::inOut),
            DELEGATE(servo, &Servo::write));
        currTime += 3000;

        // Schedule it to play again
        timeline->schedule(currTime, 0, NULL, DELEGATE(this, &Scene::cue));
    }
};

// Setup our timeline, part, tween, and scene
Timeline timeline;
Servo servo;
Quintic quintic;
Scene scene(&timeline, &servo, &quintic);

void setup() {
    Serial.begin(9600);

    servo.attach(11);

    // Kick off the animation
    scene.cue(0);
}

void loop() {
    // Call this at least once per ms. Calling it more is fine.
    timeline.tick();
}

