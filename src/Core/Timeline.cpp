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

#include "Timeline.h"

using namespace Animately;

Timeline::Timeline() {
    memset(entriesPool, 0, sizeof(Entry) * TIMELINE_MAX_SCHEDULED_ENTRIES);
}

void Timeline::schedule(int fromValue, int toValue, milliseconds delay, milliseconds duration,
    StartDelegate startDelegate,
    TransitionDelegate transitionDelegate,
    TweenDelegate tweenDelegate,
    EndDelegate endDelegate) {
    schedule(fromValue, toValue, delay, duration, startDelegate, transitionDelegate, tweenDelegate, endDelegate, millis());
}

void Timeline::schedule(milliseconds delay, milliseconds duration,
    StartDelegate startDelegate,
    EndDelegate endDelegate) {
    schedule(0, 0, delay, duration, startDelegate, NULL, NULL, endDelegate);
}

void Timeline::schedule(milliseconds delay, milliseconds duration,
    StartDelegate startDelegate,
    EndDelegate endDelegate,
    milliseconds currentMillis) {
    schedule(0, 0, delay, duration, startDelegate, NULL, NULL, endDelegate, currentMillis);
}

void Timeline::schedule(int fromValue, int toValue, milliseconds delay, milliseconds duration,
    StartDelegate startDelegate,
    TransitionDelegate transitionDelegate,
    TweenDelegate tweenDelegate,
    EndDelegate endDelegate,
    milliseconds currentMillis)
{
    Entry *entry = getEntry();
    if (NULL == entry) {
        ERROR(COULD_NOT_SCHEDULE);
        return;
    }

    LOG("Scheduled entry");

    entry->fromValue = fromValue;
    entry->toValue = toValue;
    entry->duration = duration;
    entry->startDelegate = startDelegate;
    entry->transitionDelegate = transitionDelegate;
    entry->tweenDelegate = tweenDelegate;
    entry->endDelegate = endDelegate;
    entry->used = true;
    entries.push(entry, currentMillis + delay);
}

void Timeline::tick() {
    this->tick(millis());
}

void Timeline::tick(milliseconds currentMillis) {   
    // Start events
    if (entries.isNotEmpty() && entries.peakPriority() <= currentMillis) {
        Entry *entry = entries.pop();
        entry->startedAt = currentMillis;
        activeEntries.add(entry);
        if (NULL != entry->startDelegate) {
            entry->startDelegate(entry->fromValue);
        }
    }
    
    // Active events
    for (int i = 0; i < activeEntries.size(); i++) {
        Entry *entry = activeEntries.get(i);
        if (NULL != entry->transitionDelegate) {
            float transitionAmount = (float)(currentMillis - entry->startedAt) / (float)entry->duration;
            
            if (NULL != entry->tweenDelegate) {
                transitionAmount = entry->tweenDelegate(transitionAmount);
            }
            
            entry->transitionDelegate(round(transitionAmount * (entry->toValue - entry->fromValue)) + entry->fromValue);
        }

        if (entry->startedAt + entry->duration <= currentMillis) {
            if (NULL != entry->endDelegate) {
                entry->endDelegate(entry->toValue);
            }

            returnEntry(entry);
            activeEntries.remove(i);
            i--; // This is janky...
        }
    }
}

Timeline::Entry *Timeline::getEntry() {
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

void Timeline::returnEntry(Entry *entry) {
    entry->used = false;
    entry->startDelegate.clear();
    entry->transitionDelegate.clear();
    entry->endDelegate.clear();
}