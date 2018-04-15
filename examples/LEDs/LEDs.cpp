// Configuration for Animately must happen BEFORE including Animately.h.
// This #define increases the number of animations that we can schedule at one time.
#define TIMELINE_MAX_SCHEDULED_ENTRIES 20

#include "Animately.h"
#include "Core/Timeline.h"
#include "Parts/LED.h"
#include "Tweens/Quadratic.h"
#include "Tweens/Quintic.h"
#include "Tweens/Exponential.h"
#include "Tweens/Sine.h"
#include "Tweens/BounceOut.h"


// By defining that we're using the Animately namespace, we don't have to prefix all Animately classes with "Animately::"
using namespace Animately;


// We could schedule animations in the setup() function, but by putting them into scene classes like this
// we can chain them together so an animation ending schedules the start of another animation.

// The chase animation triggers the LEDs one after the other, with a smoothed overlap using quadratic easing
class ChaseScene {
private:
    Timeline *timeline;
    LED *leds[4];
    Quadratic *tween;

public:
    ChaseScene(Timeline *timeline, LED *leds[], Quadratic *tween) {
        this->timeline = timeline;
        memcpy(this->leds, leds, sizeof(LED*) * 4);
        this->tween = tween;
    }
    
    // The chase animation triggers the LEDs one after the other, with a smoothed overlap using quadratic easing
    void cue(int val) {
        
        for (int i = 0; i < 4; i++) {
            int offset = i * 500;
            timeline->schedule(0, 255, offset, 200,
                NULL,
                DELEGATE(leds[i], &LED::set),
                DELEGATE(tween, &Quadratic::inOut),
                DELEGATE(leds[i], &LED::set));    

            timeline->schedule(255, 0, offset + 300, 200,
                NULL,
                DELEGATE(leds[i], &LED::set),
                DELEGATE(tween, &Quadratic::inOut),
                DELEGATE(leds[i], &LED::off));
        }

        // Schedule it to play again
        timeline->schedule(2000, 0, NULL, DELEGATE(this, &ChaseScene::cue));
    }
};


// The fade animation slowly fades all 4 LEDs in and out, with 4 different tweens/easings
class FadeScene {
private:
    Timeline *timeline;
    LED *leds[4];
    Quadratic *quadratic;
    Exponential *exponential;
    Quintic *quintic;
    Sine *sine;

public:
    FadeScene(Timeline *timeline, LED *leds[], Quadratic *quadratic, Exponential *exponential, Quintic *quintic, Sine *sine) {
        this->timeline = timeline;
        memcpy(this->leds, leds, sizeof(LED*) * 4);
        this->quadratic = quadratic;
        this->exponential = exponential;
        this->quintic = quintic;
        this->sine = sine;
    }        

    void cue(int val) {
        timeline->schedule(0, 255, 0, 1000,
            NULL,
            DELEGATE(leds[0], &LED::set),
            DELEGATE(quadratic, &Quadratic::in),
            DELEGATE(leds[0], &LED::set));

        timeline->schedule(255, 0, 1000, 1000,
            NULL,
            DELEGATE(leds[0], &LED::set),
            DELEGATE(quadratic, &Quadratic::out),
            DELEGATE(leds[0], &LED::off));
        
            
        timeline->schedule(0, 255, 0, 1000,
            NULL,
            DELEGATE(leds[1], &LED::set),
            DELEGATE(exponential, &Exponential::in),
            DELEGATE(leds[1], &LED::set));

        timeline->schedule(255, 0, 1000, 1000,
            NULL,
            DELEGATE(leds[1], &LED::set),
            DELEGATE(exponential, &Exponential::out),
            DELEGATE(leds[1], &LED::off));

 
        timeline->schedule(0, 255, 0, 1000,
            NULL,
            DELEGATE(leds[2], &LED::set),
            DELEGATE(quintic, &Quintic::in),
            DELEGATE(leds[2], &LED::set));

        timeline->schedule(255, 0, 1000, 1000,
            NULL,
            DELEGATE(leds[2], &LED::set),
            DELEGATE(quintic, &Quintic::out),
            DELEGATE(leds[2], &LED::off));


        timeline->schedule(0, 255, 0, 1000,
            NULL,
            DELEGATE(leds[3], &LED::set),
            DELEGATE(sine, &Sine::in),
            DELEGATE(leds[3], &LED::set));

        timeline->schedule(255, 0, 1000, 1000,
            NULL,
            DELEGATE(leds[3], &LED::set),
            DELEGATE(sine, &Sine::out),
            DELEGATE(leds[3], &LED::off));

        // Schedule it to play again
        timeline->schedule(2000, 0, NULL, DELEGATE(this, &FadeScene::cue));
    }
};


// The bounce animation runs a basic chase but "bounces" at the end
class BounceScene {
private:
    Timeline *timeline;
    LED *leds[4];
    Exponential *tween;
    BounceOut *bounceTween;
    
public:
    BounceScene(Timeline *timeline, LED *leds[], Exponential *tween, BounceOut *bounceTween) {
        this->timeline = timeline;
        memcpy(this->leds, leds, sizeof(LED*) * 4);
        this->tween = tween;
        this->bounceTween = bounceTween;
    }
    
    void cue(int val) {
        timeline->schedule(0, 255, 0, 200,
            NULL,
            DELEGATE(leds[0], &LED::set),
            DELEGATE(tween, &Exponential::in),
            DELEGATE(leds[0], &LED::off));

        timeline->schedule(0, 255, 200, 200,
            NULL,
            DELEGATE(leds[1], &LED::set),
            DELEGATE(tween, &Exponential::in),
            DELEGATE(leds[1], &LED::off));

        timeline->schedule(0, 255, 400, 200,
            NULL,
            DELEGATE(leds[2], &LED::set),
            DELEGATE(tween, &Exponential::in),
            DELEGATE(leds[2], &LED::off));

        timeline->schedule(0, 255, 600, 100,
            NULL,
            DELEGATE(leds[3], &LED::set),
            DELEGATE(tween, &Exponential::in),
            DELEGATE(leds[3], &LED::set));

        timeline->schedule(255, 0, 700, 600,
            NULL,
            DELEGATE(leds[3], &LED::set),
            DELEGATE(bounceTween, &BounceOut::getValue),
            DELEGATE(leds[3], &LED::off));
        
        // Schedule it to play again
        timeline->schedule(2000, 0, NULL, DELEGATE(this, &BounceScene::cue));
    }
};


// Setup all our parts
Timeline timeline;
LED led1(6);
LED led2(9);
LED led3(10);
LED led4(11);

LED *leds[] = {
    &led1,
    &led2,
    &led3,
    &led4
};


// Setup all our tweens
Quadratic quadratic;
Quintic quintic;
Exponential exponential;
Sine sine;
BounceOut bounceOut;


// Create the scenes
ChaseScene chaseScene(&timeline, leds, &quadratic);
FadeScene fadeScene(&timeline, leds, &quadratic, &exponential, &quintic, &sine);
BounceScene bounceScene(&timeline, leds, &exponential, &bounceOut);



void setup() {
    Serial.begin(9600);
    
    // Choose a scene to start:
    //chaseScene.cue(0);
    //bounceScene.cue(0);
    fadeScene.cue(0);
}


void loop() {
    // timeline.tick() should be called at least once per ms. Calling it more often is fine.
    timeline.tick();
}
