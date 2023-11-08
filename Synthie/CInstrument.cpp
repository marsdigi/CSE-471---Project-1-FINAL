#include "pch.h"
#include "CInstrument.h"

CInstrument::CInstrument()
{
	for (int i = 0; i < 4; i++)
	{
		mControls[i] = false;
	}
}


CInstrument::~CInstrument()
{
}

CInstrument::CInstrument(double bpm)
{
	m_bpm = bpm;
}