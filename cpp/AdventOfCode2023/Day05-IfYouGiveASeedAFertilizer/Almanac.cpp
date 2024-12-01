#include "Almanac.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day05
{

Almanac::Almanac(std::vector<int64_t> seeds, std::vector<Mapping> mappings)
    : m_seeds{std::move(seeds)}
    , m_mappings{std::move(mappings)}
{

}

void Almanac::buildOverallMapping()
{
    for (const auto& mapping : m_mappings)
    {
        m_overallMapping.absorb(mapping);
    }
}

int64_t Almanac::getLowestLocationNumberCorrespondingToSeed() const
{
    const auto seedWithLowestLocationNumberIter = std::min_element(m_seeds.cbegin(), m_seeds.cend(), [this](const auto& lhs, const auto& rhs)
                                                                    {
                                                                        return this->m_overallMapping.getMappedValue(lhs) < this->m_overallMapping.getMappedValue(rhs);
                                                                    });

    return this->m_overallMapping.getMappedValue(*seedWithLowestLocationNumberIter);
}

int64_t Almanac::getLowestLocationNumberCorrespondingToSeedWithSeedRanges() const
{
    const std::unordered_set<int64_t> interestingSeedValues = getInterestingSeedValuesForSeedRanges();

    const auto seedWithLowestLocationNumberIter = std::min_element(interestingSeedValues.cbegin(), interestingSeedValues.cend(), [this](const auto& lhs, const auto& rhs)
                                                                    {
                                                                        return this->m_overallMapping.getMappedValue(lhs) < this->m_overallMapping.getMappedValue(rhs);
                                                                    });

    return this->m_overallMapping.getMappedValue(*seedWithLowestLocationNumberIter);
}

std::unordered_set<int64_t> Almanac::getInterestingSeedValuesForSeedRanges() const
{
    const std::vector<int64_t> overallMappingLowerBounds = m_overallMapping.getAllLowerBounds();

    auto overallMappingLowerBoundIter = overallMappingLowerBounds.cbegin();
    auto seedIter = m_seeds.cbegin();

    std::unordered_set<int64_t> interestingSeedValues;

    while (overallMappingLowerBoundIter != overallMappingLowerBounds.cend() && seedIter != m_seeds.cend())
    {
        const int64_t overallMappingLowerBound = *overallMappingLowerBoundIter;

        const int64_t seedRangeStart = *seedIter;
        const int64_t seedRangeEnd = seedRangeStart + *std::next(seedIter) - 1;
        interestingSeedValues.insert(seedRangeStart);
        interestingSeedValues.insert(seedRangeEnd);

        if (seedRangeStart > overallMappingLowerBound)
        {
            ++overallMappingLowerBoundIter;
        }
        else if (overallMappingLowerBound >= seedRangeStart && overallMappingLowerBound <= seedRangeEnd)
        {
            interestingSeedValues.insert(overallMappingLowerBound);
            ++overallMappingLowerBoundIter;
        }
        else
        {
            seedIter += 2;
        }
    }

    return interestingSeedValues;
}

}
}
}
