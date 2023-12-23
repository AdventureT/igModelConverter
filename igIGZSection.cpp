#include "igIGZSection.h"
#include "igIGZ.h"

void igIGZTMET::Fixup()
{

}

void igIGZTDEP::Fixup()
{
	// Reserve entries for speed
	m_namespaces.reserve(m_section.m_count);
	m_paths.reserve(m_section.m_count);
	for (igUInt i = 0; i < m_section.m_count; i++) {
		char* ns = new char[MAX_BUFFER];
		char* path = new char[MAX_BUFFER];
		m_namespaces.push_back(igIGZ::GetInstance()->ReadString(ns));
		m_paths.push_back(igIGZ::GetInstance()->ReadString(path));
	}
}

void igIGZTSTR::Fixup()
{
	// Reserve entries for speed
	m_stringTable.reserve(m_section.m_count);
	for (igUInt i = 0; i < m_section.m_count; i++) {
		char* str = new char[MAX_BUFFER];
		m_stringTable.push_back(igIGZ::GetInstance()->ReadString(str));
	}
}
