#pragma once
#include "igCore.h"
#include "igFile.h"

class igIGZ : igFile
{
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
		if (GetSize() < 0x800) {
			printf("Filesize is too small, this can't be an igz");
			return;
		}
		m_header = ReadStruct<Header>();
		ParseSections();
	}

private:

	void ParseSections()
	{
		for (size_t i = 0; i < MAX_SECTIONS; i++) {
			Seek(sizeof(Header) + sizeof(Section) * i, IGSEEK_SET);
			m_sections[i] = *ReadStruct<Section>();
		}
	}

public:
	static constexpr igUInt MAX_SECTIONS = 0x20;
private:
	Header* m_header;
	Section m_sections[MAX_SECTIONS];
};

