#include "igIGZSection.h"
#include "igIGZ.h"

void igIGZTMET::Fixup()
{

}

void igIGZTDEP::Fixup()
{
	for (igUInt i = 0; i < m_section.m_count; i++) {
		char ns[256];
		char path[256];
		m_namespaces.push_back(igIGZ::GetInstance()->ReadString(ns));
		m_paths.push_back(igIGZ::GetInstance()->ReadString(path));
	}
}
