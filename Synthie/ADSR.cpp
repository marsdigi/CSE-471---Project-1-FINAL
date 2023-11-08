#include "pch.h"
#include "ADSR.h"

ADSR::ADSR()
{
	m_attack = 0.1;
	m_decay = 0.1;
	m_sustain = 1.;
	m_release = 0.1;
}


ADSR::~ADSR()
{
}


void ADSR::Start()
{
	m_getter = 1;
	m_time = 0;
}


bool ADSR::Generate() {
    double timeInEnvelope = m_time / m_duration;

    if (timeInEnvelope <= m_attack) {
        m_getter = timeInEnvelope / m_attack * m_sustain;
    }
    else if (timeInEnvelope <= 1.0 - m_release) {
        m_getter = (1.0 - timeInEnvelope) * (1.0 - m_sustain) + m_sustain;
    }
    else {
        m_getter = (1.0 - (timeInEnvelope - (1.0 - m_release)) / m_release) * m_sustain;
    }

    m_time += GetSamplePeriod();

    return m_time <= m_duration;
}
