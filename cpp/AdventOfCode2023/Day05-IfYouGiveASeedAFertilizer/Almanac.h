#pragma once

#include "Mapping.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day05
{

class Almanac
{
public:
    Almanac(std::vector<int64_t> seeds, std::vector<Mapping> mappings);

    void buildOverallMapping();

    int64_t getLowestLocationNumberCorrespondingToSeed() const;
    int64_t getLowestLocationNumberCorrespondingToSeedWithSeedRanges() const;

private:
    std::vector<int64_t> m_seeds;
    std::vector<Mapping> m_mappings;

    Mapping m_overallMapping;

    std::unordered_set<int64_t> getInterestingSeedValuesForSeedRanges() const;
};

}
}
}
