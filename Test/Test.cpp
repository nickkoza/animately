#include "ArduinoUnitUtility/ArduinoUnit.h"

#include "Timeline.h"
#include "TimelineTest.h"
#include "ListTest.h"

void setup()
{
    Serial.begin(9600);
    while(!Serial) {} // Portability for Leonardo/Micro
}

void loop()
{
    Test::run();
}