#include "igIGZSection.h"
#include "igIGZ.h"

void igIGZTMET::Fixup()
{
	m_vtables.reserve(m_section.m_count);
	for (igUInt i = 0; i < m_section.m_count; i++) {
		m_vtables.push_back(igIGZ::GetInstance()->ReadString());
	}
}

void igIGZTDEP::Fixup()
{
	m_namespaces.reserve(m_section.m_count);
	m_paths.reserve(m_section.m_count);
	for (igUInt i = 0; i < m_section.m_count; i++) {
		m_namespaces.push_back(igIGZ::GetInstance()->ReadString());
		m_paths.push_back(igIGZ::GetInstance()->ReadString());
	}
}

void igIGZTSTR::Fixup()
{
	m_stringTable.reserve(m_section.m_count);
	for (igUInt i = 0; i < m_section.m_count; i++) {
		m_stringTable.push_back(igIGZ::GetInstance()->ReadString());
	}
}

void igIGZMTSZ::Fixup()
{
	m_metaSizes.reserve(m_section.m_count);
	for (igUInt i = 0; i < m_section.m_count; i++) {
		m_metaSizes.push_back(igIGZ::GetInstance()->Read<igUInt>());
	}
}
