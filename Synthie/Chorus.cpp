#include "pch.h"
#include "Chorus.h"
#include <cmath>

Chorus::Chorus() 
{
}

Chorus::Chorus(double sampleRate, int maxDelayLength, double modulationDepth, double modulationRate, double wet, double dry)
    : sampleRate(sampleRate), maxDelayLength(maxDelayLength), modulationDepth(modulationDepth), modulationRate(modulationRate), wet(wet), dry(dry) {
    delayLineL.resize(maxDelayLength, 0.0);
    delayLineR.resize(maxDelayLength, 0.0);
    index = 0;
    lfoPhase = 0.0;
}

Chorus::~Chorus() 
{
}

void Chorus::Process(double* input, double* output) {
    double delayLength = maxDelayLength * 0.5 + modulationDepth * maxDelayLength * 0.5 * std::sin(lfoPhase);
    int readIndex = (index - static_cast<int>(delayLength)) % maxDelayLength;

    if (readIndex < 0) {
        readIndex += maxDelayLength;
    }

    double delayedSampleL = delayLineL[readIndex];
    delayLineL[index] = input[0] + delayedSampleL * 0.5;
    output[0] = input[0] * dry + delayedSampleL * wet;

    double delayedSampleR = delayLineR[readIndex];
    delayLineR[index] = input[1] + delayedSampleR * 0.5;
    output[1] = input[1] * dry + delayedSampleR * wet;

    index = (index + 1) % maxDelayLength;
    lfoPhase += modulationRate / sampleRate;
    if (lfoPhase >= 2.0 * PI) {
        lfoPhase -= 2.0 * PI;
    }
}

void Chorus::Start() {
    index = 0;
    std::fill(delayLineL.begin(), delayLineL.end(), 0.0);
    std::fill(delayLineR.begin(), delayLineR.end(), 0.0);
}

