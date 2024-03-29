#pragma once

#include <config.h>
#include <raylib.h>
#include <utils.h>

typedef int          igInt;
typedef unsigned int igUInt;

#define IG_ALIGN(x, mask) (((x)+(mask))&~(mask))

constexpr igUInt MAKEFOUR_BIG(char const p[5])
{
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

constexpr igUInt MAKEFOUR(char const p[5])
{
    return (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
}

enum class igPlatform
{
    IG_PLATFORM_PC = 6,
};