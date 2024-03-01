#include "igIGZ.h"

void igIGZ::ProcessFixupSections()
{
	Seek(m_sections[0].m_offset, IGSEEK_SET);
	for (igUInt i = 0; i < m_header.m_numFixups; i++) {
		igUInt cur = Tell();
		igIGZSection::Section section = Read<igIGZSection::Section>();
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
		case IG_FIXUP_TSTR:
			m_tstr.m_section = section;
			m_tstr.Fixup();
			break;
		case IG_FIXUP_MTSZ:
			m_mtsz.m_section = section;
			m_mtsz.Fixup();
			break;
		default:
			break;
		}
		// Seek to next Fixup
		//Seek(cur + section.m_length, IGSEEK_SET);
	}
}

void igIGZ::PrintFixups() const
{
	TRACELOG(LOG_NONE, "==================================================");
	TRACELOG(LOG_NONE, "Fixups");
	TRACELOG(LOG_NONE, "==================================================");
	m_tmet.PrintFixup();
	m_tdep.PrintFixup();
	m_tstr.PrintFixup();
}
