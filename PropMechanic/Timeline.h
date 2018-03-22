#ifndef _Timeline_h
#define _Timeline_h

#include <Arduino.h>

#include "PropMechanic.h"
#include "TimelineQueue.h"
#include "FastDelegate.h"

// Timeline let's you schedule future function executions with millisecond granularity.
// Timeline is constant-memory.
// Timeline uses an unsigned long to keep track of time, meaning it can operate for up to _49_days_ before overflowing.
// If you need to run longer than that you'll have to make changes to this system.
class Timeline
{    
public:
    typedef fastdelegate::FastDelegate0<> TimelineDelegate;
    
private:
    struct TimelineEntry {
        TimelineDelegate timelineDelegate;
        boolean used;
    };
    
    TimelineEntry entriesPool[timelineMaxEntries];
    TimelineQueue<TimelineEntry, timelineMaxEntries> entries;
    
    TimelineEntry *getEntry();
    void returnEntry(TimelineEntry *entry);

public:

    Timeline();

    void schedule(TimelineDelegate timelineDelegate, milliseconds delay);

    void tick();
};

#endif // _Timeline_h