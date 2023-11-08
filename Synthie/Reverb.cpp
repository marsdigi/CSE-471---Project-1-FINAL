#include "pch.h"
#include "Reverb.h"
#include <cmath>

const double LEVEL = 0.5;
const double DAMPING = 0.8;

Reverb::Reverb() 
{
}

Reverb::Reverb(double sampleRate, int delayLength, double wet, double dry)
    : sampleRate(sampleRate), delayLength(delayLength), wet(wet), dry(dry) {
    delayLine.resize(delayLength, 0.0);
    wrloc = 0;
}

Reverb::~Reverb() 
{
}

void Reverb::Process(double* input, double* output) {
    double delayedSample = delayLine[wrloc];

    delayLine[wrloc] = input[0] + delayedSample * DAMPING;

    output[0] = input[0] + delayedSample * LEVEL;
    output[0] *= wet;
    output[0] += input[0] * dry;

    wrloc = (wrloc + 1) % delayLength;
}

void Reverb::Start() {
    wrloc = 0;
    std::fill(delayLine.begin(), delayLine.end(), 0.0);
}

