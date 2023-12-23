#include "igIGZ.h"

void igIGZ::ProcessFixupSections()
{
	Seek(m_sections[0].m_offset, IGSEEK_SET);
	for (igUInt i = 0; i < m_header.m_numFixups; i++) {
		igUInt cur = Tell();
		igIGZSection::Section section = ReadStruct<igIGZSection::Section>();
		switch (section.m_magic)
		{
		case IG_FIXUP_TMET:
			m_tmet.m_section = section;
			m_tmet.Fixup();
			break;
		case IG_FIXUP_TDEP:
			m_tdep.m_section = section;
			m_tdep.Fixup();
			break;
		default:
			break;
		}
		// Seek to next Fixup
		Seek(cur + section.m_length, IGSEEK_SET);
	}
}
