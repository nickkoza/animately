# Animately
Animately is an Arduino library that allows for precise animation of props, down to the millisecond, without the need for thread-blocking (`delay()`) or complex state machines. This frees you to focus on the creative aspects of animating a prop rather than the technical details.

Animately provides an animation timeline, tweening options, and several basic classes for interfacing with aspects of the prop (LEDs, servos, switches, etc.) It's built around delegates and has an event-driven architecture. This provides a flexible DSL that's easy to plug new methods into. If a method signature matches what Animately is expecting you can plug that method in to the system regardless of whether you've inherited any interfaces or are using a Animately class at all. This means you can easily create new parts and tweening algorithms as you go.

Animately is optimized for integrated systems and has a memory footprint that can be tuned based on the needs of the prop and microcontroller (see Configuration below.)


# Installation
TO DO


# Configuration

## Overall

#### `TIMELINE_MAX_SCHEDULED_ENTRIES`
How many actions can be put on the schedule at the same time. Once an action starts it will be removed from this list, freeing up the space. Adding actions when the timeline is already full will result in the action not getting scheduled. This setting has a substantial impact on SRAM usage.
  
Default value: 10

#### `TIMELINE_MAX_ACTIVE_ENTRIES`
How many actions can be in progress simultaneously. Once an action moves from being scheduled to actually starting, it will persist in this data store until the action completes. This setting has a substantial impact on SRAM usage.

Default value: 5

## Logging
#### `LOG`
If you overwrite this with a no-op (`#define LOG`) then you'll disable the entire logging system and free up a non-trivial amount of SRAM.

#### `LOG_BUFFER_SIZE`
You can define a higher limit if you're like to create longer log messages.

Default value: 60 bytes

#### `ERROR`
If you overwrite this with a no-op (`#define ERROR`) then you'll free up a tiny bit of memory but at the cost of not knowing when the program does something unexpected. *Changing this is not recommended.*

## Error Codes
Animately uses error codes to cut down on the length of error messages that it has to store and transmit. You can overwrite any of these with empty strings to cut down on SRAM usage, or change the names to something more meaningful if you have SRAM to spare.

#### `COULD_NOT_ALLOCATE`
Could not allocate for an operation. This likely means that you have `TIMELINE_MAX_SCHEDULED_ENTRIES` or `TIMELINE_MAX_ACTIVE_ENTRIES` set too low.

Default value: "E01"

#### `COULD_NOT_SCHEDULE`
Could not schedule the prop as requested for some reason. See the surrounding logs for more information.

Default value: "E03"

#### `INVALID_INDEX`
An invalid index was supplied (less than zero or equal to or greater than `size`.

Default value: "E04"


# Usage

TO DO


# Events and Delegates
All delegates can take in a pointer to any instance method, as long as the method signature matches what is expected below. This means you can very easily schedule arbitrary method invocations as part of your animation, or create new tweening algorithms.

#### Action Start Delegate
Method signature: `void methodName(int fromValue)`
  
The Action Start Delegate is called when a scheduled action is started. This is where you can setup your variables, turn on an LED, set the starting position of a servo, etc. It will always supply the `fromValue` that was supplied during scheduling.

#### Action Transition Delegate
Method signature: `void methodName(int transitionValue)`

Action Transition Delegate provides a place to smoothly transition between two states/values. The delegate is called every time the timeline ticks. This means that it may be invoked more often than once per millisecond, depending on how fast the main timeline tick is being called. Because of this, all behavior in this method must be time-independent and rely only on the incoming value to determine how to respond.

`transitionValue` has already been passed through the tweening algorithm when it reaches this point, so it may progress from `fromValue` to `toValue` non-linearly, depending on how the tween is tuning the value. There's a chance the tweening algorithm may push the value outside of the `fromValue` to `toValue` range, if it's doing something like an overshoot smoothing or spring smoothing.

#### Action Tween Delegate
Method signature: `float methodName(float transitionAmount)`
  
TO DO


#### Action End Delegate
Method signature: `void methodName(int toValue)`
  
TO DO




