
#pragma once
#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include "msxml2.h"
#include "CInstrument.h"
#include "CNote.h"
#include "SubtractiveSynthesizer.h"
#include "Flange.h"
#include "Reverb.h"
#include "Chorus.h"

using namespace std;

class CSynthesizer
{

public:
    CSynthesizer(void);
    virtual ~CSynthesizer(void);

    void Start();

    bool Generate(double* frame);

    void Clear(void);

    void OpenScore(CString& filename);

    //! Number of audio channels
    int GetNumChannels() { return m_channels; }

    //! Sample rate in samples per second
    double GetSampleRate() { return m_sampleRate; }

    //! Sample period in seconds (1/samplerate)
    double GetSamplePeriod() { return m_samplePeriod; }

    //! Set the number of channels
    void SetNumChannels(int n) { m_channels = n; }

    //! Set the sample rate
    void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

    //! Get the time since we started generating audio
    double GetTime() { return m_time; }

    void XmlLoadScore(IXMLDOMNode* xml);

    void XmlLoadInstrument(IXMLDOMNode* xml);

    void XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument);

    double GetBeatsPerMinute() { return m_bpm; }

private:
    int		m_channels;
    double	m_sampleRate;
    double	m_samplePeriod;
    double  m_time;
    double  m_bpm;                  //!< Beats per minute
    int     m_beatspermeasure;  //!< Beats per measure
    double  m_secperbeat;        //!< Seconds per beat
    int m_currentNote;          //!< The current note we are playing
    int m_measure;              //!< The current measure
    double m_beat;              //!< The current beat within the measure

    std::list<CInstrument*>  m_instruments;

    std::vector<CNote> m_notes;

    Flange mFlangeEffect;
    Flange mReverbEffect;
    Flange mChorusEffect;
    bool m_flangeActivation;
    bool m_reverbActivation;
    bool m_chorusActivation;
};

#pragma comment(lib, "msxml2.lib")