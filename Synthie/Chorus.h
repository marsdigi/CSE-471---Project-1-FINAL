#pragma once
#include "Effects.h"
#include <vector>

class Chorus {
public:
    Chorus();
    Chorus(double sampleRate, int maxDelayLength, double modulationDepth, double modulationRate, double wet, double dry);
    ~Chorus();

    void Process(double* input, double* output);
    void Start();

private:
    double sampleRate;
    int maxDelayLength;
    double modulationDepth;
    double modulationRate;
    double wet;
    double dry;
    std::vector<double> delayLineL;
    std::vector<double> delayLineR;
    int index;
    double lfoPhase;
};

