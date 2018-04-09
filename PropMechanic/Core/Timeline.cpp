#include "Timeline.h"

using namespace PropMechanic;

Timeline::Timeline()
{
    memset(entriesPool, 0, sizeof(TimelineEntry) * TIMELINE_MAX_SCHEDULED_ENTRIES);
}

void Timeline::schedule(TimelineEventStartDelegate startDelegate,
    TimelineTransitionDelegate transitionDelegate,
    TimelineTweenDelegate tweenDelegate,
    TimelineEventEndDelegate endDelegate,
    milliseconds delay, milliseconds duration, void *data) {
    schedule(startDelegate, transitionDelegate, tweenDelegate, endDelegate, delay, duration, data, millis());
}

void Timeline::schedule(TimelineEventStartDelegate startDelegate,
    TimelineTransitionDelegate transitionDelegate,
    TimelineTweenDelegate tweenDelegate,
    TimelineEventEndDelegate endDelegate,
    milliseconds delay, milliseconds duration, void *data, milliseconds currentMillis)
{
    TimelineEntry *entry = getEntry();
    if (NULL == entry) {
        ERROR(COULD_NOT_SCHEDULE);
        return;
    }

    LOG("Scheduled entry");

    entry->startDelegate = startDelegate;
    entry->transitionDelegate = transitionDelegate;
    entry->tweenDelegate = tweenDelegate;
    entry->endDelegate = endDelegate;
    entry->data = data;
    entry->used = true;
    entry->duration = duration;
    entries.push(entry, currentMillis + delay);
}

void Timeline::tick() {
    this->tick(millis());
}

void Timeline::tick(milliseconds currentMillis) {   
    // Start events
    if (entries.isNotEmpty() && entries.peakPriority() <= currentMillis) {
        TimelineEntry *entry = entries.pop();
        entry->startedAt = currentMillis;
        activeEntries.add(entry);
        if (NULL != entry->startDelegate) {
            entry->startDelegate(entry->data);
        }
    }
    
    // Active events
    for (int i = 0; i < activeEntries.size(); i++) {
        TimelineEntry *entry = activeEntries.get(i);
        if (NULL != entry->transitionDelegate) {
            float transitionAmount = (float)(currentMillis - entry->startedAt) / (float)entry->duration;
            
            if (NULL != entry->tweenDelegate) {
                transitionAmount = entry->tweenDelegate(transitionAmount, entry->data);
            }
            
            entry->transitionDelegate(transitionAmount, entry->data);
        }

        if (entry->startedAt + entry->duration <= currentMillis) {
            if (NULL != entry->endDelegate) {
                entry->endDelegate(entry->data);
            }

            returnEntry(entry);
            activeEntries.remove(i);
            i--; // This is janky...
        }
    }
}

Timeline::TimelineEntry *Timeline::getEntry() {
    for (int i = 0; i < TIMELINE_MAX_SCHEDULED_ENTRIES; i++) {
        if(entriesPool[i].startDelegate.empty() &&
            entriesPool[i].transitionDelegate.empty() &&
            entriesPool[i].endDelegate.empty() &&
            entriesPool[i].used == false) {

            return &entriesPool[i];
        }
    }
    ERROR(COULD_NOT_ALLOCATE);
    return NULL;
}

void Timeline::returnEntry(TimelineEntry *entry) {
    entry->used = false;
    entry->startDelegate.clear();
    entry->transitionDelegate.clear();
    entry->endDelegate.clear();
}