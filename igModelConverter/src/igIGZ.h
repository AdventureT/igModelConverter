#pragma once
#include "igCore.h"
#include "igFile.h"
#include "igIGZSection.h"

class igIGZ : public igFile
{
public:
	static constexpr igUInt MAX_SECTIONS = 0x20;

private:
	struct Header
	{
		void Validate()
		{
			if (m_magic != MAKEFOUR("IGZ\1") && m_magic != MAKEFOUR_BIG("IGZ\1")) {
				TRACELOG(LOG_FATAL, "Not an IGZ");
			}
			if (m_version != 10) {
				TRACELOG(LOG_ERROR, "Unsupported version");
			}
			if (m_platform != igPlatform::IG_PLATFORM_PC) {
				TRACELOG(LOG_ERROR, "Unsupported platform");
			}
		}

		igUInt m_magic;
		igUInt m_version;
		igUInt m_typeHash;
		igPlatform m_platform;
		igUInt m_numFixups;
	};

	struct Section
	{
		igUInt m_unknown;
		igUInt m_offset;
		igUInt m_length;
		igUInt m_start;
	};

public:

	igIGZ(const char* filepath) : igFile(filepath)
	{
		assert(m_instance == NULL);
		m_instance = this;
		assert(GetSize() >= 0x800 && "Filesize is too small, this can't be an igz");
		m_header = Read<Header>();
		ParseSections();
		ProcessFixupSections();
	}

	void PrintFixups() const;

private:

	void ParseSections()
	{
		for (igUInt i = 0; i < MAX_SECTIONS; i++) {
			m_sections[i] = Read<Section>();
		}
	}

	void ProcessFixupSections();

public:

	static igIGZ* GetInstance() { return m_instance; }

	inline static igIGZ* m_instance = NULL;

private:
	Header m_header;
	Section m_sections[MAX_SECTIONS];
	igIGZTMET m_tmet;
	igIGZTDEP m_tdep;
	igIGZTSTR m_tstr;
	igIGZMTSZ m_mtsz;
};

