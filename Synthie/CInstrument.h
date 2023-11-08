#pragma once
#include "CAudioNode.h"
#include "CNote.h"
#include "Envelope.h"

class CInstrument : public CAudioNode
{
public:
	CInstrument();
	~CInstrument();
	CInstrument(double);

	virtual void SetNote(CNote* note) = 0;

	bool hasEffects(int effect) { return mControls[effect]; }
	void setEffects(int effect) { mControls[effect] = true; }
	int getNumEffects()
	{
		int count = 0;
		for (int i = 0; i < 4; i++)
		{
			if (mControls[i])
				count++;
		}
		return count;
	}

protected:
	Envelope* m_envelope;
	bool mControls[4];
};

