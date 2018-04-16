// MIT License
//
// Copyright (c) 2018 Nicholas Koza
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _Timeline_h
#define _Timeline_h

#include <Arduino.h>

#include "../Animately.h"
#include "TimelineQueue.h"
#include "List.h"
#include "FastDelegate.h"

// Timeline let's you schedule future function executions with millisecond granularity.
// Timeline is constant-memory.
// Timeline uses an unsigned long to keep track of time, meaning it can operate for up to _49_days_ before overflowing.
// If you need to run longer than that you'll have to make changes to this system.
namespace Animately {
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
            
        void schedule(milliseconds delay, milliseconds duration,
            TimelineEventStartDelegate startDelegate,
            TimelineEventEndDelegate endDelegate);
            
        void schedule(milliseconds delay, milliseconds duration,
            TimelineEventStartDelegate startDelegate,
            TimelineEventEndDelegate endDelegate,
            milliseconds currentMillis);

        void tick();
        void tick(milliseconds currentMillis);
        // Methods that contain `currentMillis` are for stabilizing the clock for testing
    };
}
#endif // _Timeline_h