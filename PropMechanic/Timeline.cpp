#include "Timeline.h"

Timeline *Timeline::instance = NULL;

Timeline::Timeline(int maxEntries)
{
    this->maxEntries = maxEntries;
    entriesIndex = 0;
    Entry *entries = new Entry[maxEntries];
    memset(entries, 0, sizeof(Entry) * maxEntries);

    if (Timeline::instance != NULL) {
        ERROR("Allocated timeline when one already exists. Only the last one created will have the interupt available.");
    }
    Timeline::instance = this;
}

Timeline::~Timeline()
{
    delete[] entries;
}

void Timeline::schedule(void *instance, void(*function)(void *instance), milliseconds delay)
{
    // A sorted insert would make more sense here if you have an extremely long timeline, since it
    // would allow you to check fewer entries per-tick
    for (int i = 0; i < maxEntries; i++) {
        Entry *entry = entries + i;
        if (entry->instance == NULL) {
            entry->instance = instance;
            entry->function = function;
            entry->runAtTime = timer + delay;
            return;
        }
    }
    ERROR("Timeline max entries exceeded")
}

void Timeline::tick()
{
    timer++;

    if (timer % 1000 == 0) {
        Serial.println(timer);
        Serial.flush();
    }

    for (int i = 0; i < maxEntries; i++) {
        Entry *entry = entries + i;
        if (entry->instance != NULL && entry->runAtTime <= timer) {
            entry->function(entry->instance);
            entry->instance = NULL;
        }
    }
}
