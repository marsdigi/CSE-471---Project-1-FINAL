#pragma once
#include "CInstrument.h"
#include <vector>

class Effects : public CInstrument {
public:
	Effects();
	virtual ~Effects();

	virtual void Process(double* frameIn, double* frameOut) = 0;

	void SetDry(double dry) { mDry = dry; }

	void SetWet(double wet) { mWet = wet; }

	virtual void SetNote(CNote* note) override;

private:
	double	mDry;
	double	mWet;
	int mWrloc;
	int mRdloc;
	double mTime = 5.0;

	std::vector<double> m_queueL;
	std::vector<double> m_queueR;
};

