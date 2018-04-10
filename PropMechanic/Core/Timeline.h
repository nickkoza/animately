#ifndef _Timeline_h
#define _Timeline_h

#include <Arduino.h>

#include "../PropMechanic.h"
#include "TimelineQueue.h"
#include "List.h"
#include "FastDelegate.h"

// Timeline let's you schedule future function executions with millisecond granularity.
// Timeline is constant-memory.
// Timeline uses an unsigned long to keep track of time, meaning it can operate for up to _49_days_ before overflowing.
// If you need to run longer than that you'll have to make changes to this system.
namespace PropMechanic {
    class Timeline
    {
    public:
        typedef fastdelegate::FastDelegate1<int> TimelineEventStartDelegate;
        typedef fastdelegate::FastDelegate1<int> TimelineTransitionDelegate;
        typedef fastdelegate::FastDelegate1<float, float> TimelineTweenDelegate;
        typedef fastdelegate::FastDelegate1<int> TimelineEventEndDelegate;

    private:
        struct TimelineEntry {
            TimelineEventStartDelegate startDelegate;
            TimelineTransitionDelegate transitionDelegate;
            TimelineTweenDelegate tweenDelegate;
            TimelineEventEndDelegate endDelegate;
            int fromValue;
            int toValue;
            milliseconds startedAt;
            milliseconds duration;
            boolean used;
        };

        // TODO - TimelineQueue can be made to hold onto type T instead of T*, which would allocate the memory right there in the
        // queue rather than requiring this pool. It'd require a bit more work to copy the instance into place, but it'd save SRAM
        TimelineEntry entriesPool[TIMELINE_MAX_SCHEDULED_ENTRIES];
        TimelineQueue<TimelineEntry*, TIMELINE_MAX_SCHEDULED_ENTRIES> entries;
        List<TimelineEntry*, TIMELINE_MAX_ACTIVE_ENTRIES> activeEntries;

        TimelineEntry *getEntry();
        void returnEntry(TimelineEntry *entry);

    public:

        Timeline();

        void schedule(int fromValue, int toValue, milliseconds delay, milliseconds duration,
            TimelineEventStartDelegate startDelegate,
            TimelineTransitionDelegate transitionDelegate,
            TimelineTweenDelegate tweenDelegate,
            TimelineEventEndDelegate endDelegate);

        void schedule(int fromValue, int toValue, milliseconds delay, milliseconds duration,
            TimelineEventStartDelegate startDelegate,
            TimelineTransitionDelegate transitionDelegate,
            TimelineTweenDelegate tweenDelegate,
            TimelineEventEndDelegate endDelegate,
            milliseconds currentMillis);

        void tick();
        void tick(milliseconds currentMillis);
        // Methods that contain `currentMillis` are for stabilizing the clock for testing
    };
}
#endif // _Timeline_h