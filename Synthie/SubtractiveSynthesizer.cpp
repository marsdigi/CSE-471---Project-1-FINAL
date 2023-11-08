#include "pch.h"
#include "SubtractiveSynthesizer.h"
#include "Notes.h"
#include "Envelope.h"
#include "ADSR.h"
#include <string>

using namespace std;

SubtractiveSynthesizer::SubtractiveSynthesizer()
{
	m_duration = 0.1;
}


SubtractiveSynthesizer::~SubtractiveSynthesizer()
{
}
SubtractiveSynthesizer::SubtractiveSynthesizer(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
}
void SubtractiveSynthesizer::SetNote(CNote* note)
{
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	for (int i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal * (60.0 / m_bpm));
		}

		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "wavetype")
		{
			if ((wstring)value.bstrVal == L"Sawtooth") {
				m_wave_type = L"Sawtooth";
				SetWaveType(L"Sawtooth");
			}
			else if ((wstring)value.bstrVal == L"Square") {
				m_wave_type = L"Square";
				SetWaveType(L"Square");
			}
			else if ((wstring)value.bstrVal == L"Triangle") {
				m_wave_type = L"Triangle";
				SetWaveType(L"Triangle");
			}
		}
	}
}

void SubtractiveSynthesizer::Start()
{
	mSubtractiveWave.SetSampleRate(GetSampleRate());
	mSubtractiveWave.Start();
	m_time = 0;

	m_envelope = new ADSR();

	static_cast<ADSR*>(m_envelope)->SetAttack(0.1);
	static_cast<ADSR*>(m_envelope)->SetDecay(0.05);

	static_cast<ADSR*>(m_envelope)->SetSustain(0.8);

	static_cast<ADSR*>(m_envelope)->SetRelease(0.2);

	m_envelope->Start();
}

bool SubtractiveSynthesizer::Generate()
{
	m_envelope->Generate();

	mSubtractiveWave.Generate();

	m_frame[0] = mSubtractiveWave.Frame(0);
	m_frame[1] = mSubtractiveWave.Frame(1);

	m_time += GetSamplePeriod();

	return m_envelope && (m_time < m_duration);
}