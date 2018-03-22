#include "Timeline.h"
#include "TimeSwitch.h"

Timeline timeline;
TimeSwitch *timeSwitch = new TimeSwitch(0, 1000L, 2000L);
Timeline::TimelineDelegate timelineDelegate = fastdelegate::MakeDelegate(timeSwitch, &TimeSwitch::close);

unsigned long lastMillis;

void setup() {
    Serial.begin(9600);

    timeline.schedule(timelineDelegate, 1000);
	timeline.schedule(timelineDelegate, 2000);
	timeline.schedule(timelineDelegate, 3000);
	timeline.schedule(timelineDelegate, 4000);
	timeline.schedule(timelineDelegate, 5000);
	timeline.schedule(timelineDelegate, 6000);
	timeline.schedule(timelineDelegate, 7000);
	timeline.schedule(timelineDelegate, 8000);
	
	lastMillis = millis();
}

void loop() {
  timeline.tick();
}
