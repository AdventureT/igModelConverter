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

static constexpr igUInt MAX_BUFFER = 0xFF;

class igIGZSection
{
public:

	virtual void Fixup() {}

	bool IsEncoded() const
	{
		return (char)m_section.m_magic == 'R';
	}

	virtual void PrintFixup() const
	{
		TRACELOG(LOG_NONE, "%.4s", &m_section.m_magic);
	}

public:

	struct Section
	{
		igUInt m_magic;
		igUInt m_count;
		igUInt m_length;
		igUInt m_alignment;
	} m_section;
};

class igIGZTMET : public igIGZSection
{
public:
	virtual void Fixup() override;

	virtual void PrintFixup() const override
	{
		igIGZSection::PrintFixup();
		for (char* vtable : GetVTables()) {
			TRACELOG(LOG_NONE, "  %s", vtable);
		}
	}

	std::vector<char*> GetVTables() const
	{
		return m_vtables;
	}

private:
	std::vector<char*> m_vtables;
};

class igIGZMTSZ : public igIGZSection
{
public:
	virtual void Fixup() override;

	virtual void PrintFixup() const override
	{
		igIGZSection::PrintFixup();
		for (igUInt metasize : GetMetaSizes()) {
			TRACELOG(LOG_NONE, "  %d", metasize);
		}
	}

	std::vector<igUInt> GetMetaSizes() const
	{
		return m_metaSizes;
	}

private:
	std::vector<igUInt> m_metaSizes;
};

class igIGZTDEP : public igIGZSection
{
public:
	virtual void Fixup() override;

	virtual void PrintFixup() const override
	{
		igIGZSection::PrintFixup();
		TRACELOG(LOG_NONE, "  Namespaces");
		for (char* namespaces : GetNamespaces()) {
			TRACELOG(LOG_NONE, "    %s", namespaces);
		}
		TRACELOG(LOG_NONE, "  Paths");
		for (char* paths : GetPaths()) {
			TRACELOG(LOG_NONE, "    %s", paths);
		}
	}

	std::vector<char*> GetNamespaces() const
	{
		return m_namespaces;
	}
	std::vector<char*> GetPaths() const
	{
		return m_paths;
	}

private:

	std::vector<char*> m_namespaces;
	std::vector<char*> m_paths;
};

class igIGZTSTR : public igIGZSection
{
public:
	virtual void Fixup() override;

	virtual void PrintFixup() const override
	{
		igIGZSection::PrintFixup();
		for (char* string : GetStrings()) {
			TRACELOG(LOG_NONE, "  %s", string);
		}
	}

	std::vector<char*> GetStrings() const
	{
		return m_stringTable;
	}

private:

	std::vector<char*> m_stringTable;
};