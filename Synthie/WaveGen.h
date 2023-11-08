#pragma once
#include "CAudioNode.h"
#include <vector>

class WaveGen:
	public CAudioNode
{
public:
	WaveGen();
	virtual ~WaveGen();

	void SetFreq(double f) { m_freq = f; }
	void SetAmp(double a) { m_amp = a; }

protected:
	std::vector<double> m_wavetable;
	double m_freq;
	double m_amp;
	int m_phase;
};