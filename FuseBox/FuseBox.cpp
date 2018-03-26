#include "Timeline.h"
#include "TimeSwitch.h"
#include "Button.h"
#include "Speaker.h"
#include "Memory.h"

class Scene {
private:
    Timeline *timeline;
    TimeSwitch *sparkSwitch;
    TimeSwitch *motorSwitch;
    
    Timeline::TimelineEventStartDelegate sparkingOn;
    Timeline::TimelineEventEndDelegate sparkingOff;
    Timeline::TimelineEventStartDelegate motorOn;
    Timeline::TimelineEventEndDelegate motorOff;

public:
    Scene(Timeline *timeline, TimeSwitch *sparkSwitch, TimeSwitch *motorSwitch) {
        this->timeline = timeline;
        this->sparkSwitch = sparkSwitch;
        this->motorSwitch = motorSwitch;
        
        sparkingOn = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::close);
        sparkingOff = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::open);
        motorOn = fastdelegate::MakeDelegate(motorSwitch, &TimeSwitch::close);
        motorOff = fastdelegate::MakeDelegate(motorSwitch, &TimeSwitch::open);
    }        

    void cueScene1(inputId id) {
        Serial.println("Scene 1");
        timeline->schedule(sparkingOn, NULL, sparkingOff, NULL, 0, 2250);
        timeline->schedule(motorOn, NULL, motorOff, NULL, 250, 2000);
    }
    
    void cueScene2(inputId id) {
        Serial.println("Scene 2");
        timeline->schedule(sparkingOn, NULL, sparkingOff, NULL, 0, 3250);
        timeline->schedule(motorOn, NULL, motorOff, NULL, 250, 3000);
    }
    
    void cueScene3(inputId id) {
        Serial.println("Scene 3");
        timeline->schedule(sparkingOn, NULL, sparkingOff, NULL, 0, 1250);
        timeline->schedule(motorOn, NULL, motorOff, NULL, 250, 1000);
    }
};

Timeline timeline;
TimeSwitch *sparkSwitch = new TimeSwitch(6, 3000L, 5000L);
TimeSwitch *motorSwitch = new TimeSwitch(7, 5000L, 100L);
Speaker *speaker = new Speaker(8, 60);

Scene *scene = new Scene(&timeline, sparkSwitch, motorSwitch);

Button::ButtonPressDelegate scene1 = fastdelegate::MakeDelegate(scene, &Scene::cueScene1);
Button::ButtonPressDelegate scene2 = fastdelegate::MakeDelegate(scene, &Scene::cueScene2);
Button::ButtonPressDelegate scene3 = fastdelegate::MakeDelegate(scene, &Scene::cueScene3);
Button::ButtonPressDelegate toggleTone = fastdelegate::MakeDelegate(speaker, &Speaker::toggleTone);

const int triggerA = A3;
const int triggerB = A1;
const int triggerC = A4;
const int triggerD = A2;
const int triggerAny = A5;
Button *scene1Button = new Button(triggerA, 0, scene1, NULL, NULL);
Button *scene2Button = new Button(triggerB, 0, scene2, NULL, NULL);
Button *scene3Button = new Button(triggerC, 0, scene3, NULL, NULL);
Button *toneToggleButton = new Button(triggerD, 0, toggleTone, NULL, NULL);


void setup() {
    Serial.begin(9600);
    
    Serial.print("Timeline: ");
    Serial.print(sizeof(timeline));
    Serial.println(" bytes");
    
    Serial.print("Free: ");
    Serial.print(freeMemory());
    Serial.println(" bytes.");
    
    Serial.print("Delegates: ");
    Serial.print(sizeof(scene1));
    Serial.println(" bytes each.");
    
    speaker->playTone(60);
}

void loop() {
  timeline.tick();
  scene1Button->tick();
  scene2Button->tick();
  scene3Button->tick();
  toneToggleButton->tick();
  speaker->tick();
}
