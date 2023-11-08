#pragma once
#include "CAudioNode.h"

class Envelope : public CAudioNode
{
public:
	Envelope();
	virtual ~Envelope();

	virtual void Start() override {};
	virtual bool Generate() override { return false; }

	double GetEnvelope() { return m_getter; }
	void SetDuration(double d) { m_duration = d; }

protected:
	double m_duration;
	double m_getter;
	double m_time;
};

