#include "pch.h"
#include "Flange.h"
#include <cmath>

const double LEVEL = 0.3;

Flange::Flange() {
}
Flange::Flange(double sampleRate, double maxDelayMs, double minDelayMs, double lfoRate, double wet, double dry)
    : sampleRate(sampleRate), maxDelayMs(maxDelayMs), minDelayMs(minDelayMs), lfoRate(lfoRate), wet(wet), dry(dry) {
    lfoPhase = 0.0;
    lfoIncrement = (2.0 * PI * lfoRate) / sampleRate;
    delayLineSize = (int)(maxDelayMs * sampleRate / 1000);
    delayLine.resize(delayLineSize, 0.0);
    outputL.resize(delayLineSize, 0.0);
    outputR.resize(delayLineSize, 0.0);
    wrloc = 0;
    rdloc = 0;
}

Flange::~Flange() 
{
}

void Flange::Process(double* input, double* output) {
    double delayVariance = (maxDelayMs - minDelayMs) * 0.5 * (1.0 + std::sin(lfoPhase));
    double newDelay = minDelayMs + delayVariance;

    wrloc = (wrloc + 1) % delayLineSize;
    delayLine[wrloc] = input[0];

    int delayLength = static_cast<int>((newDelay * sampleRate + 0.5)) * 2;
    rdloc = (wrloc + delayLineSize - delayLength) % delayLineSize;

    // Wet
    output[0] = input[0] / 3 + delayLine[rdloc] / 3 + (outputL[rdloc] * LEVEL) / 3;
    output[0] *= wet;

    // Dry
    output[0] += input[0] * dry;
    outputL[wrloc] = output[0];

    wrloc = (wrloc + 1) % delayLineSize;
    delayLine[wrloc] = input[1];
    rdloc = (wrloc + delayLineSize - delayLength) % delayLineSize;

    // Wet
    output[1] = input[1] / 3 + delayLine[(rdloc + 1) % delayLineSize] / 3 + (outputR[(rdloc + 1) % delayLineSize] * LEVEL) / 3;
    output[1] *= wet;

    // Dry
    output[1] += input[1] * dry;
    outputR[wrloc] = output[1];

    lfoPhase += lfoIncrement;
    if (lfoPhase >= 2.0 * PI) {
        lfoPhase -= 2.0 * PI;
    }
}

void Flange::Start() {
    wrloc = 0;
    rdloc = 0;
    std::fill(outputL.begin(), outputL.end(), 0.0);
    std::fill(outputR.begin(), outputR.end(), 0.0);
}
