#pragma once
#include "Effects.h"
#include <vector>

class Reverb {
public:
    Reverb();
    Reverb(double sampleRate, int delayLength, double wet, double dry);
    ~Reverb();

    void Process(double* input, double* output);
    void Start();

private:
    double sampleRate;
    int delayLength;
    double wet;
    double dry;
    std::vector<double> delayLine;
    int wrloc;
};
