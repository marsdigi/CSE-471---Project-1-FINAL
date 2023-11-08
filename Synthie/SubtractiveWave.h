#pragma once
#include "WaveGen.h"
#include <string>

class SubtractiveWave :
	public WaveGen
{
public:
	SubtractiveWave();
	~SubtractiveWave();

	void Start();
	bool Generate();

	void SetWaveType(std::wstring type) { m_wave_type = type; }
	void SetWavetables();

private:
	std::wstring m_wave_type; 
	double m_time;
};



