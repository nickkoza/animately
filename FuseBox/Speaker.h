#ifndef __SPEAKER_H__
#define __SPEAKER_H__

#include "Arduino.h"
#include "PropMechanic.h"

class Speaker
{
private:
    pinNum pin;
    boolean playing;
    int hertz;
    int frequencyCycleInMicroSeconds;
    int halfFrequencyCycleInMicroSeconds;
    
public:
	Speaker(pinNum pin, int hertz);
    void tick();
    void playTone(int hertz);
    void stopTone();
    void toggleTone(inputId id);
    void setTone(int hertz);
    boolean isPlaying();
};

#endif //__SPEAKER_H__
