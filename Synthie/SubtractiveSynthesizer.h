#pragma once
#include "CInstrument.h"
#include "SubtractiveWave.h"
#include <string>

class SubtractiveSynthesizer :
	public CInstrument
{
public:
	SubtractiveSynthesizer();
	~SubtractiveSynthesizer();
	SubtractiveSynthesizer(double bpm);

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote* note) override;

	void SetFreq(double freq) { mSubtractiveWave.SetFreq(freq); }
	void SetAmplitude(double amp) { mSubtractiveWave.SetAmp(amp); }
	void SetWaveType(std::wstring type) { mSubtractiveWave.SetWaveType(type); }
	void SetDuration(double d) { m_duration = d; }

private:
	std::wstring m_wave_type;
	double m_duration;
	double m_time;
	SubtractiveWave mSubtractiveWave;

};

