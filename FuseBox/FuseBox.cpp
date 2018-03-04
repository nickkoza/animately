#include "Timeline.h"
#include "TimeSwitch.h"

TimeSwitch *timeSwitch;
Timeline *timeline;
void setup() {
    Serial.begin(9600);

    timeSwitch = new TimeSwitch(0, 1000L, 2000L);

    timeline = new Timeline(15);
    timeline->schedule(timeSwitch, TimeSwitch::run, 1000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 2000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 3000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 4000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 5000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 6000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 7000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 8000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 9000);
    timeline->schedule(timeSwitch, TimeSwitch::run, 10000);

	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;

	OCR1A = 31250;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	interrupts();
}

ISR(TIMER1_COMPA_vect)
{
    Timeline::instance->tick();
}

void loop() {
  
}
