#include "Timeline.h"
#include "TimeSwitch.h"
#include "Button.h"

class Scene {
private:
    Timeline *timeline;
    TimeSwitch *sparkSwitch;
    TimeSwitch *motorSwitch;
    
    Timeline::TimelineDelegate sparkingOn;
    Timeline::TimelineDelegate sparkingOff;
    Timeline::TimelineDelegate motorOn;
    Timeline::TimelineDelegate motorOff;
    
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

    void cueScene1(int id) {
        Serial.println("------ Scene 1 ------");
        timeline->schedule(sparkingOn, 0);
        timeline->schedule(motorOn, 250);
        
        timeline->schedule(sparkingOff, 2000);
        timeline->schedule(motorOff, 2000);
    }
    
    void cueScene2(int id) {
        Serial.println("------ Scene 2 ------");
        timeline->schedule(sparkingOn, 0);
        timeline->schedule(motorOn, 250);
        
        timeline->schedule(sparkingOff, 2000);
        timeline->schedule(motorOff, 2000);
    }
    
    void cueScene3(int id) {
        Serial.println("------ Scene 3 ------");
        timeline->schedule(sparkingOn, 0);
        timeline->schedule(motorOn, 250);
        
        timeline->schedule(sparkingOff, 2000);
        timeline->schedule(motorOff, 2000);
    }
};

Timeline timeline;
TimeSwitch *sparkSwitch = new TimeSwitch(6, 3000L, 5000L);
TimeSwitch *motorSwitch = new TimeSwitch(7, 5000L, 100L);

Scene *scene = new Scene(&timeline, sparkSwitch, motorSwitch);

Button::ButtonPressDelegate scene1 = fastdelegate::MakeDelegate(scene, &Scene::cueScene1);
Button::ButtonPressDelegate scene2 = fastdelegate::MakeDelegate(scene, &Scene::cueScene2);
Button::ButtonPressDelegate scene3 = fastdelegate::MakeDelegate(scene, &Scene::cueScene3);
//Button::ButtonPressDelegate toggleTone = fastdelegate::MakeDelegate(scene, &Scene::cueScene1); // TODO

const int triggerA = A3;
const int triggerB = A1;
const int triggerC = A4;
const int triggerD = A2;
const int triggerAny = A5;
Button *scene1Button = new Button(triggerA, 0, scene1, NULL, NULL);
Button *scene2Button = new Button(triggerB, 0, scene2, NULL, NULL);
Button *scene3Button = new Button(triggerC, 0, scene3, NULL, NULL);
Button *toneToggleButton = new Button(triggerD, 0, NULL, NULL, NULL);

// Tone
const int speaker = 8;
const int hertz = 60;
const int frequencyCycleInMicroSeconds = 1000000 / hertz;
const int halfFrequencyCycleInMicroSeconds = frequencyCycleInMicroSeconds / 2;
boolean playTone = true;

void setup() {
    Serial.begin(9600);
    pinMode(speaker, OUTPUT);
}

void loop() {
  timeline.tick();
  scene1Button->tick();
  scene2Button->tick();
  scene3Button->tick();
  toneToggleButton->tick();
  
  // Tone
  if (playTone) {
      if (micros() % frequencyCycleInMicroSeconds < halfFrequencyCycleInMicroSeconds) {
          analogWrite(speaker, 0);
      }
      else {
          analogWrite(speaker, 255);
      }
  }
  else {
      analogWrite(speaker, 0);
  }
}
