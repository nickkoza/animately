#include "Timeline.h"

Timeline::Timeline()
{
    memset(entriesPool, 0, sizeof(TimelineEntry) * timelineMaxEntries);
}

void Timeline::schedule(TimelineDelegate timelineDelegate, milliseconds delay)
{
    TimelineEntry *entry = getEntry();
    if (NULL == entry) {
        ERROR(COULD_NOT_SCHEDULE);
        return;
    }
    
    Serial.println("Scheduled entry");
    
    entry->timelineDelegate = timelineDelegate;
    entry->used = true;
    entries.push(entry, millis() + delay);
}

void Timeline::tick()
{
    if (entries.isNotEmpty() && entries.peakPriority() <= millis()) {
        //priority_t priority = entries.peakPriority();
        //Serial.println(priority);
        TimelineEntry *entry = entries.pop();
        TimelineDelegate currentDelegate = entry->timelineDelegate;
        //Serial.println(entries.size());
        
        returnEntry(entry);
        (currentDelegate)();
    }
}

Timeline::TimelineEntry *Timeline::getEntry() {
    for (int i = 0; i < timelineMaxEntries; i++) {
        if(entriesPool[i].timelineDelegate.empty() && entriesPool[i].used == false) {
            return &entriesPool[i];
        }
    }
    ERROR(COULD_NOT_ALLOCATE);
    return NULL;
}

void Timeline::returnEntry(TimelineEntry *entry) {
    entry->used = false;
    entry->timelineDelegate.clear();
}