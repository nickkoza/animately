#include <Animately.h>
#include <Core/Timeline.h>

using namespace Animately;

Timeline timeline;

void setup() {
    Serial.begin(9600);
}

void loop() {
    timeline.tick();
}
