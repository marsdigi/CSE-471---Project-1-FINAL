#include "pch.h"
#include "CToneInstrument.h"
#include "Notes.h"

CToneInstrument::CToneInstrument(void)
{
    m_duration = 0.1;
}


CToneInstrument::~CToneInstrument(void)
{
}


void CToneInstrument::Start()
{

    m_ar.SetSource(&m_sinewave);
    m_ar.SetSampleRate(GetSampleRate());
    m_ar.Start();
}


bool CToneInstrument::Generate()
{
    // Tell the component to generate an audio sample

    bool valid = m_ar.Generate();

    m_frame[0] = m_ar.Frame(0);
    m_frame[1] = m_ar.Frame(1);

    m_time += GetSamplePeriod();
    return valid;
}

void CToneInstrument::SetNote(CNote* note)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for (int i = 0; i < len; i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        // Get the value of the attribute
        CComVariant value;
        attrib->get_nodeValue(&value);

        // Handle "duration" and "note" attributes
        if (name == "duration")
        {
            // Change the attribute value to double
            value.ChangeType(VT_R8);

            // Calculate the duration in beats and set it
            m_ar.SetDuration(value.dblVal * (60.0 / m_bpm));
        }
        else if (name == "note")
        {
            // Set the frequency based on the note value
            SetFreq(NoteToFrequency(value.bstrVal));
        }
    }
}