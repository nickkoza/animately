#include "Core/Timeline.h"
#include "Parts/TimeSwitch.h"
#include "Parts/Button.h"
#include "Parts/LED.h"
#include "Tweens/Flicker.h"
#include "Speaker.h"
#include "Memory.h"

using namespace PropMechanic;

class Scene {
private:
    static const int numberOfLEDs = 3;
    Timeline *timeline;
    TimeSwitch *sparkSwitch;
    TimeSwitch *motorSwitch;
    LED *sparkLEDs[numberOfLEDs];
    Tween *sparkTweenInstance;

public:
    Scene(Timeline *timeline, TimeSwitch *sparkSwitch, TimeSwitch *motorSwitch, LED *sparkLEDs[], Tween *sparkTweenInstance) {
        this->timeline = timeline;
        this->sparkSwitch = sparkSwitch;
        this->motorSwitch = motorSwitch;
        memcpy(this->sparkLEDs, sparkLEDs, sizeof(LED*) * numberOfLEDs);
        this->sparkTweenInstance = sparkTweenInstance;
    }

    void cueScene1(inputId id) {
        LOG("Scene 1");
        
        timeline->schedule(
            DELEGATE(sparkSwitch, &TimeSwitch::close),
            NULL,
            NULL,
            DELEGATE(sparkSwitch, &TimeSwitch::open),
            0, 2250, NULL);

        timeline->schedule(
            DELEGATE(motorSwitch, &TimeSwitch::close),
            NULL,
            NULL,
            DELEGATE(motorSwitch, &TimeSwitch::open),
            250, 2000, NULL);

        for (int i = 0; i < numberOfLEDs; i++) {
            timeline->schedule(
                NULL,
                DELEGATE(sparkLEDs[i], &LED::setf),
                DELEGATE(sparkTweenInstance, &Tween::getValue),
                DELEGATE(sparkLEDs[i], &LED::off),
                250, 2000, NULL);
        }
    }
    
    void cueScene2(inputId id) {
        LOG("Scene 2");
        
        timeline->schedule(
        DELEGATE(sparkSwitch, &TimeSwitch::close),
        NULL,
        NULL,
        DELEGATE(sparkSwitch, &TimeSwitch::open),
        0, 3250, NULL);

        timeline->schedule(
        DELEGATE(motorSwitch, &TimeSwitch::close),
        NULL,
        NULL,
        DELEGATE(motorSwitch, &TimeSwitch::open),
        250, 3000, NULL);

        for (int i = 0; i < numberOfLEDs; i++) {
            timeline->schedule(
            NULL,
            DELEGATE(sparkLEDs[i], &LED::setf),
            DELEGATE(sparkTweenInstance, &Tween::getValue),
            DELEGATE(sparkLEDs[i], &LED::off),
            250, 3000, NULL);
        }
    }
    
    void cueScene3(inputId id) {
        LOG("Scene 3");
        
        timeline->schedule(
        DELEGATE(sparkSwitch, &TimeSwitch::close),
        NULL,
        NULL,
        DELEGATE(sparkSwitch, &TimeSwitch::open),
        0, 1250, NULL);

        timeline->schedule(
        DELEGATE(motorSwitch, &TimeSwitch::close),
        NULL,
        NULL,
        DELEGATE(motorSwitch, &TimeSwitch::open),
        250, 1000, NULL);

        for (int i = 0; i < numberOfLEDs; i++) {
            timeline->schedule(
            NULL,
            DELEGATE(sparkLEDs[i], &LED::setf),
            DELEGATE(sparkTweenInstance, &Tween::getValue),
            DELEGATE(sparkLEDs[i], &LED::off),
            250, 1000, NULL);
        }
    }
};

Timeline timeline;
TimeSwitch sparkSwitch(6, 3000L, 5000L);
TimeSwitch motorSwitch(7, 5000L, 100L);
Speaker speaker(8, 60);

Flicker sparkTween({0, 255}, {15, 50}, {2, 10}, {15, 50});

int numberOfLEDs = 3;
LED sparkLED1(9);
LED sparkLED2(10);
LED sparkLED3(11);
LED *sparkLEDs[] = {
    &sparkLED1,
    &sparkLED2,
    &sparkLED3
};

Scene scene(&timeline, &sparkSwitch, &motorSwitch, sparkLEDs, &sparkTween);

const int triggerA = A3;
const int triggerB = A1;
const int triggerC = A4;
const int triggerD = A2;
const int triggerAny = A5;
Button scene1Button(triggerA, 0, fastdelegate::MakeDelegate(&scene, &Scene::cueScene1), NULL, NULL);
Button scene2Button(triggerB, 0, fastdelegate::MakeDelegate(&scene, &Scene::cueScene2), NULL, NULL);
Button scene3Button(triggerC, 0, fastdelegate::MakeDelegate(&scene, &Scene::cueScene3), NULL, NULL);
Button toneToggleButton(triggerD, 0, fastdelegate::MakeDelegate(&speaker, &Speaker::toggleTone), NULL, NULL);

void setup() {
    Serial.begin(9600);
    
    LOGF("Timeline: %d bytes", sizeof(timeline));
    LOGF("Free: %d bytes", freeMemory());
    LOGF("Delegates: %d bytes each", sizeof(fastdelegate::MakeDelegate(&scene, &Scene::cueScene1)));
    
    speaker.playTone(60);
}

void loop() {
    timeline.tick();
    scene1Button.tick();
    scene2Button.tick();
    scene3Button.tick();
    toneToggleButton.tick();
    speaker.tick();
}
