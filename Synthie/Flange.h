#pragma once
#include "Effects.h"
#include <vector>

class Flange {
public:
    Flange();
    Flange(double sampleRate, double maxDelayMs, double minDelayMs, double lfoRate, double wet, double dry);
    ~Flange();

    void Process(double* input, double* output);
    void Start();

private:
    double sampleRate;
    double maxDelayMs;
    double minDelayMs;
    double lfoRate;
    double wet;
    double dry;
    double lfoPhase;
    double lfoIncrement;

    int delayLineSize;
    std::vector<double> delayLine;
    std::vector<double> outputL;
    std::vector<double> outputR;
    int wrloc;
    int rdloc;
};



