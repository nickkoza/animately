#include "Timeline.h"

Timeline::Timeline()
{
	memset(entriesPool, 0, sizeof(TimelineEntry) * timelineMaxEntries);
}

void Timeline::schedule(TimelineDelegate timelineDelegate, milliseconds delay)
{
	for (int i = 0; i < timelineMaxEntries; i++) {
		if(entriesPool[i].timelineDelegate.empty() && entriesPool[i].used == false) {
			Serial.println("Scheduled entry");
			
			entriesPool[i].timelineDelegate = timelineDelegate;
			entriesPool[i].used = true;
			entries.push(&entriesPool[i], millis() + delay);
			return;
		}
	}
	ERROR(COULD_NOT_ALLOCATE);
}

void Timeline::tick()
{
	if (entries.size() > 0 && entries.peakPriority() <= millis()) {
		TimelineEntry *entry = entries.pop();
		TimelineDelegate currentDelegate = entry->timelineDelegate;
		Serial.println(entries.size());
		
		returnEntry(entry);
		(currentDelegate)();
	}
}

Timeline::TimelineEntry *Timeline::getEntry() {
	for (int i = 0; i < timelineMaxEntries; i++) {
		if(entriesPool[i].timelineDelegate.empty() && entriesPool[i].used == false) {
			Serial.println("GET ENTRY");
			return &entriesPool[i];
		}
	}
	ERROR(COULD_NOT_ALLOCATE);
	return NULL;
}

void Timeline::returnEntry(TimelineEntry *entry) {
	entry->used == false;
	entry->timelineDelegate.clear();
}