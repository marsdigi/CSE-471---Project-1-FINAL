#include "pch.h"
#include "Effects.h"
#include "CNote.h"

Effects::Effects()
{
	m_queueL.resize(100000);
	m_queueR.resize(100000);
}

Effects::~Effects()
{
}

void Effects::SetNote(CNote* note)
{
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	for (int i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "wet")
		{
			value.ChangeType(VT_R8);
			SetWet(value.dblVal);
		}
		else if (name == "dry")
		{
			value.ChangeType(VT_R8);
			SetDry(value.dblVal);
		}
	}
}