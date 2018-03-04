#ifndef _Timeline_h
#define _Timeline_h

#include <Arduino.h>

#include "PropMechanic.h"

// Timeline let's you schedule future function executions with millisecond granularity.
// Timeline is constant-memory after it initializes the required space in the heap during construction.
// Timeline uses an unsigned long to keep track of time, meaning it can operate for up to _49_days_ before overflowing.
// If you need to run longer than that you'll have to make changes to this system.
class Timeline
{
private:
    unsigned long timer;

    struct Entry {
        milliseconds runAtTime;
        void *instance;
        void (*function)(void *instance);
    };

    Entry *entries;
    int entriesIndex;
    int maxEntries;

public:
    Timeline(int maxEntries);
    ~Timeline();

    void schedule(void *instance, void(*function)(void *instance), milliseconds delay);

    static Timeline *instance;

    void tick();
};

#endif // _Timeline_h