#include "pch.h"
#include "CAR.h"

CAR::CAR()
{
    m_attack = 0.05;
    m_release = 0.05;
	m_duration = 0.1;
    m_time = 0;
}


CAR::~CAR()
{
}

void CAR::Start()
{
	m_source->SetSampleRate(GetSampleRate());
	m_source->Start();
}

bool CAR::Generate()
{
    m_source->Generate();

    double amplitude = 1.0; 

    if (m_time < m_attack)
    {
        amplitude = m_time / m_attack;
    }
    else if (m_time > m_duration - m_release)
    {
        amplitude = (m_duration - m_time) / m_release;
    }

    m_frame[0] = m_source->Frame(0) * amplitude;
    m_frame[1] = m_source->Frame(1) * amplitude;

    m_time += GetSamplePeriod();

    return m_time < m_duration;
}

