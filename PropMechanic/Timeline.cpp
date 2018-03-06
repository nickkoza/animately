#include "Timeline.h"

Timeline *Timeline::instance = NULL;

Timeline::Timeline(int maxEntries)
{
	this->maxEntries = maxEntries;
	entries = new PriorityQueue<TimelineEntry>(maxEntries);
	entriesPool = new TimelineEntry[maxEntries];
	memset(entriesPool, 0, sizeof(TimelineEntry) * maxEntries);
    if (Timeline::instance != NULL) {
        ERROR("Allocated timeline when one already exists. Only the last one created will have the interrupt available.");
    }
    Timeline::instance = this;
}

Timeline::~Timeline()
{
    delete[] entries;
}

void Timeline::schedule(void *instance, void(*function)(void *instance), milliseconds delay)
{
	TimelineEntry *entry = getEntry();
	entry->instance = instance;
	entry->function = function;
	entries->push(entry, millis() + delay);
}

void Timeline::tick()
{
	unsigned long currentMs = millis();
	
	unsigned long peakedPriority = entries->peakPriority();
	while(entries->size() > 0 && peakedPriority <= currentMs) {
		TimelineEntry *entry = entries->pop();
		Serial.print("POP! ");
		Serial.print(currentMs);
		Serial.print(" - ");
		Serial.print(peakedPriority);
		Serial.print(" - ");
		Serial.print(entries->size());
		Serial.println("");
		
		Serial.flush();
		//entry->function(entry->instance); // THIS IS THE PROBLEM LINE
		returnEntry(entry);
		
		peakedPriority = entries->peakPriority();
	}
}

Timeline::TimelineEntry *Timeline::getEntry() {
	for (int i = 0; i < maxEntries; i++) {
		if (entriesPool[i].instance == NULL && entriesPool[i].function == NULL) {
			return &entriesPool[i];
		}
	}
	return NULL;
}

void Timeline::returnEntry(TimelineEntry *entry) {
	entry->function = NULL;
	entry->instance = NULL;
}