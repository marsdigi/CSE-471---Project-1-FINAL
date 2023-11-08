#pragma once
#include "CAudioNode.h"

class CAR :
	public CAudioNode
{
public:
	CAR();
	~CAR();

	virtual void Start();
	virtual bool Generate();

	void SetSource(CAudioNode* const& source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }

private:
	CAudioNode* m_source;

	double m_attack;
	double m_release;
	double m_duration;
	double m_time;
};

