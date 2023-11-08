#include "pch.h"
#include "SubtractiveWave.h"
#include <cmath>

SubtractiveWave::SubtractiveWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440;
}


SubtractiveWave::~SubtractiveWave()
{
}

void SubtractiveWave::Start()
{
	m_phase = 0;
	m_time = 0;
	SetWavetables();
}

bool SubtractiveWave::Generate()
{
	m_frame[0] = m_wavetable[m_phase];
	m_frame[1] = m_frame[0];
	m_phase = (m_phase + 1) % m_wavetable.size();

	return true;
}

void SubtractiveWave::SetWavetables()
{
	auto table_size = GetSampleRate();
	m_wavetable.resize(table_size);
	double amplitudeFilter = 1.0;

	if (m_freq > 1000. / 44100) {
		amplitudeFilter = 0.75;
	}
	if (m_freq > 1200. / 44100) {
		amplitudeFilter = 0.65;
	}
	if (m_freq > 1400. / 44100) {
		amplitudeFilter = 0.4;
	}

	double setFreq = m_freq;
	for (auto i = 0; i < table_size; i++, m_time += 1. / GetSampleRate()) {
		double sample = 0.0;

		if (m_wave_type == L"Sawtooth") {

			//Initial sin wave
			sample = amplitudeFilter * m_amp * sin(m_time * 2 * PI * setFreq);

			//Add every harmonic up to nyqist frequency
			for (double h = 2.0; h <= (GetSampleRate() / 2.0) / m_freq; h++) {
				sample += (amplitudeFilter * m_amp / h) * sin(m_time * 2 * PI * setFreq * h);
			}
		}
		else if (m_wave_type == L"Square") {
			//Initial sin wave
			sample = amplitudeFilter * m_amp * sin(m_time * 2 * PI * setFreq);

			//Add every odd harmonic up to nyqist frequency
			for (double h = 3.0; h <= (GetSampleRate() / 2.0) / m_freq; h++) {
				if ((int)h % 2 == 1)
					sample += (amplitudeFilter * m_amp / h) * sin(m_time * 2 * PI * setFreq * h);
			}
		}
		else if (m_wave_type == L"Triangle") {
			int alternatingSign = -1;
			//Initial sin wave
			sample = amplitudeFilter * m_amp * sin(m_time * 2 * PI * setFreq);

			//Add every odd harmonic up to nyqist frequency
			for (double h = 3.0; h <= (GetSampleRate() / 2.0) / m_freq; h++) {
				if ((int)h % 2 == 1) {
					sample += (alternatingSign * amplitudeFilter * m_amp / (h * h)) * sin(m_time * 2 * PI * setFreq * h);
					alternatingSign = -alternatingSign;
				}
			}
		}
		m_wavetable[i] = sample;
	}
}
