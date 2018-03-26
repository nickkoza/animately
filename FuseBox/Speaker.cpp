#include "Speaker.h"

Speaker::Speaker(pinNum pin, int hertz)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
    stopTone();
    setTone(hertz);
}

void Speaker::tick() {
    if (!playing) {
        return;
    }
    
    if (micros() % frequencyCycleInMicroSeconds < halfFrequencyCycleInMicroSeconds) {
        analogWrite(pin, 0);
    }
    else {
        analogWrite(pin, 255);
    }
}    

void Speaker::playTone(int hertz) {
    playing = true;
    setTone(hertz);
}

void Speaker::stopTone() {
    playing = false;
    analogWrite(pin, 0);
}

void Speaker::toggleTone(inputId id) {
    if (isPlaying()) {
        stopTone();
    }
    else {
        playTone(hertz);
    }
}

boolean Speaker::isPlaying() {
    return playing;
}

void Speaker::setTone(int hertz) {
    this->hertz = hertz;
    frequencyCycleInMicroSeconds = 1000000 / hertz;
    halfFrequencyCycleInMicroSeconds = frequencyCycleInMicroSeconds / 2;
}
