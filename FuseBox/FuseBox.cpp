#include "Timeline.h"
#include "TimeSwitch.h"

class Scene {
private:
    Timeline *timeline;
    TimeSwitch *sparkSwitch;
    TimeSwitch *motorSwitch;
    
    Timeline::TimelineDelegate sparkingOn;
    Timeline::TimelineDelegate sparkingOff;
    Timeline::TimelineDelegate motorOn;
    Timeline::TimelineDelegate motorOff;
    
    Timeline::TimelineDelegate cue1 = fastdelegate::MakeDelegate(this, &Scene::cueScene1);
    Timeline::TimelineDelegate cue2 = fastdelegate::MakeDelegate(this, &Scene::cueScene2);
    Timeline::TimelineDelegate cue3 = fastdelegate::MakeDelegate(this, &Scene::cueScene3);
    
public:
    Scene(Timeline *timeline, TimeSwitch *sparkSwitch, TimeSwitch *motorSwitch) {
        this->timeline = timeline;
        this->sparkSwitch = sparkSwitch;
        this->motorSwitch = motorSwitch;
        
        sparkingOn = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::close);
        sparkingOff = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::open);
        motorOn = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::close);
        motorOff = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::open);
    }        

    void cueScene1() {
        Serial.println("------ Scene 1 ------");
        timeline->schedule(sparkingOn, 0);
        timeline->schedule(motorOn, 250);
        
        timeline->schedule(sparkingOff, 2000);
        timeline->schedule(motorOff, 2000);
        
        timeline->schedule(cue2, 5000);
    }
    
    void cueScene2() {
        Serial.println("------ Scene 2 ------");
        timeline->schedule(sparkingOn, 0);
        timeline->schedule(motorOn, 250);
        
        timeline->schedule(sparkingOff, 2000);
        timeline->schedule(motorOff, 2000);
        
        timeline->schedule(cue3, 5000);
    }
    
    void cueScene3() {
        Serial.println("------ Scene 3 ------");
        timeline->schedule(sparkingOn, 0);
        timeline->schedule(motorOn, 250);
        
        timeline->schedule(sparkingOff, 2000);
        timeline->schedule(motorOff, 2000);
        
        timeline->schedule(cue1, 5000);
    }
};

Timeline timeline;
TimeSwitch *sparkSwitch = new TimeSwitch(6, 3000L, 5000L);
TimeSwitch *motorSwitch = new TimeSwitch(7, 5000L, 100L);
Timeline::TimelineDelegate sparkingOn = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::close);
Timeline::TimelineDelegate sparkingOff = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::open);
Timeline::TimelineDelegate motorOn = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::close);
Timeline::TimelineDelegate motorOff = fastdelegate::MakeDelegate(sparkSwitch, &TimeSwitch::open);

Scene *scene = new Scene(&timeline, sparkSwitch, motorSwitch);

void setup() {
    Serial.begin(9600);
    
    scene->cueScene1();
}

void loop() {
  timeline.tick();
}
