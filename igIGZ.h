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
		bool Validate(const char*& errormsg)
		{
			if (m_magic != MAKEFOUR("IGZ\1") && m_magic != MAKEFOUR_BIG("IGZ\1")) {
				errormsg = "Not an IGZ";
				return false;
			}
			if (m_version != 10) {
				errormsg = "Unsupported version";
				return false;
			}
			if (m_platform != igPlatform::IG_PLATFORM_PC) {
				errormsg = "Unsupported platform";
				return false;
			}
			return true;
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
		igUInt m_alignment;
	};

public:

	igIGZ(const char* filepath) : igFile(filepath)
	{
		m_instance = this;
		if (GetSize() < 0x800) {
			printf("Filesize is too small, this can't be an igz");
			return;
		}
		m_header = ReadStruct<Header>();
		ParseSections();
		ProcessFixupSections();
	}

private:

	void ParseSections()
	{
		for (igUInt i = 0; i < MAX_SECTIONS; i++) {
			m_sections[i] = ReadStruct<Section>();
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
};

