#pragma once
#include "igCore.h"
#include <vector>

static constexpr igUInt IG_FIXUP_TMET = MAKEFOUR("TMET");
static constexpr igUInt IG_FIXUP_MTSZ = MAKEFOUR("MTSZ");
static constexpr igUInt IG_FIXUP_TSTR = MAKEFOUR("TSTR");
static constexpr igUInt IG_FIXUP_TDEP = MAKEFOUR("TDEP");
static constexpr igUInt IG_FIXUP_EXID = MAKEFOUR("EXID");
static constexpr igUInt IG_FIXUP_EXNM = MAKEFOUR("EXNM");
static constexpr igUInt IG_FIXUP_TMHN = MAKEFOUR("TMHN");
static constexpr igUInt IG_FIXUP_ONAM = MAKEFOUR("ONAM");
static constexpr igUInt IG_FIXUP_RVTB = MAKEFOUR("RVTB");
static constexpr igUInt IG_FIXUP_ROOT = MAKEFOUR("ROOT");
static constexpr igUInt IG_FIXUP_RHND = MAKEFOUR("RHND");
static constexpr igUInt IG_FIXUP_REXT = MAKEFOUR("REXT");
static constexpr igUInt IG_FIXUP_ROFS = MAKEFOUR("ROFS");
static constexpr igUInt IG_FIXUP_RPID = MAKEFOUR("RPID");
static constexpr igUInt IG_FIXUP_RNEX = MAKEFOUR("RNEX");
static constexpr igUInt IG_FIXUP_RSTT = MAKEFOUR("RSTT");
static constexpr igUInt IG_FIXUP_RSTR = MAKEFOUR("RSTR");

class igIGZSection
{
public:

	virtual void Fixup() {}

public:

	struct Section
	{
		igUInt m_magic;
		igUInt m_count;
		igUInt m_length;
		igUInt m_start;
	} m_section;
};

class igIGZTMET : public igIGZSection
{
public:
	virtual void Fixup() override;
};

class igIGZTDEP : public igIGZSection
{
public:
	virtual void Fixup() override;

	std::vector<char*> m_namespaces;
	std::vector<char*> m_paths;
};