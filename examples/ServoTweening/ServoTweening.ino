// This example slowly goes through various easing/tweening algorithms, increasing the aggressiveness as it goes. It starts with a sine wave, which
// is only slightly modified from linear motion, and ends at exponential, which is super aggressive smoothing compared to linear.

#include <Servo.h>

#include <Animately.h>
#include <Core/Timeline.h>
#include <Parts/LED.h>

#include <Tweens/Sine.h>
#include <Tweens/Quadratic.h>
#include <Tweens/Cubic.h>
#include <Tweens/Quintic.h>
#include <Tweens/Exponential.h>

using namespace Animately;

class Scene {
private:
    Timeline *timeline;
    Sine *sine;
    Quadratic *quadratic;
    Cubic *cubic;
    Quintic *quintic;
    Exponential *exponential;
    Servo *servo;

public:
    Scene(Timeline *timeline, Servo *servo, Sine *sine, Quadratic *quadratic, Cubic *cubic, Quintic *quinticintic, Exponential *exponential) {
        this->timeline = timeline;
        this->sine = sine;
        this->servo = servo;
        this->quadratic = quadratic;
        this->cubic = cubic;
        this->quintic = quintic;
        this->exponential = exponential;
    }

    void cueSine(int val) {
        LOG("Sine");
        timeline->schedule(0, 180, 0, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(sine, &Sine::inOut),
            DELEGATE(servo, &Servo::write));

        timeline->schedule(180, 0, 3000, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(sine, &Sine::inOut),
            DELEGATE(servo, &Servo::write));

        // Schedule the next scene
        timeline->schedule(6000, 0, NULL, DELEGATE(this, &Scene::cueQuadratic));
    }

    void cueQuadratic(int val) {
        LOG("Quadratic");
        timeline->schedule(0, 180, 0, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quadratic, &Quadratic::inOut),
            DELEGATE(servo, &Servo::write));

        timeline->schedule(180, 0, 3000, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quadratic, &Quadratic::inOut),
            DELEGATE(servo, &Servo::write));

        // Schedule the next scene
        timeline->schedule(6000, 0, NULL, DELEGATE(this, &Scene::cueCubic));
    }

    void cueCubic(int val) {
        LOG("Cubic");
        timeline->schedule(0, 180, 0, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(cubic, &Cubic::inOut),
            DELEGATE(servo, &Servo::write));

        timeline->schedule(180, 0, 3000, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(cubic, &Cubic::inOut),
            DELEGATE(servo, &Servo::write));

        // Schedule the next scene
        timeline->schedule(6000, 0, NULL, DELEGATE(this, &Scene::cueQuintic));
    }

    void cueQuintic(int val) {
        LOG("Quintic");
        timeline->schedule(0, 180, 0, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quintic, &Quintic::inOut),
            DELEGATE(servo, &Servo::write));

        timeline->schedule(180, 0, 3000, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(quintic, &Quintic::inOut),
            DELEGATE(servo, &Servo::write));

        // Schedule the next scene
        timeline->schedule(6000, 0, NULL, DELEGATE(this, &Scene::cueExponential));
    }

    void cueExponential(int val) {
        LOG("Exponential");
        timeline->schedule(0, 180, 0, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(exponential, &Exponential::inOut),
            DELEGATE(servo, &Servo::write));

        timeline->schedule(180, 0, 3000, 3000,
            NULL,
            DELEGATE(servo, &Servo::write),
            DELEGATE(exponential, &Exponential::inOut),
            DELEGATE(servo, &Servo::write));

        // Schedule the next scene
        timeline->schedule(6000, 0, NULL, DELEGATE(this, &Scene::cueSine));
    }
};

// Setup our timeline, part, tween, and scene
Timeline timeline;
Servo servo;
Sine sine;
Quadratic quadratic;
Cubic cubic;
Quintic quintic;
Exponential exponential;
Scene scene(&timeline, &servo, &sine, &quadratic, &cubic, &quintic, &exponential);

void setup() {
    Serial.begin(9600);

    servo.attach(11);

    // Kick off the animation
    scene.cueSine(0);
}

void loop() {
    // Call this at least once per ms. Calling it more often is fine.
    timeline.tick();
}

