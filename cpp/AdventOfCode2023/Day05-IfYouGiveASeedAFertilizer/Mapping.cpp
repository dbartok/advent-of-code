#include "Mapping.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day05
{

Mapping::Mapping()
{

}

Mapping::Mapping(const RawMapping& rawMapping)
{
    m_compressedMapping = convertRawMappingToCompressedMapping(rawMapping);
}

void Mapping::absorb(const Mapping& otherMapping)
{
    if (m_compressedMapping.empty())
    {
        m_compressedMapping = otherMapping.m_compressedMapping;
        return;
    }

    std::vector<int64_t> newMappingIntervalLowerBounds = getNewLowerBoundsForAbsorbtion(otherMapping);

    IntervalLowerBoundToOffsetMap newCompressedMapping;

    // Add all lower bounds along with their new overall offsets to new map
    for (const int64_t newLowerBound : newMappingIntervalLowerBounds)
    {
        const int64_t originalMappedValue = getMappedValue(newLowerBound);
        const int64_t overallMappedValueWhenCombiningBothMappings = otherMapping.getMappedValue(originalMappedValue);
        const int64_t newOverallOffset = overallMappedValueWhenCombiningBothMappings - newLowerBound;

        newCompressedMapping.emplace(newLowerBound, newOverallOffset);
    }

    m_compressedMapping = newCompressedMapping;
}

int64_t Mapping::getMappedValue(int64_t value) const
{
    const auto upperBoundIter = m_compressedMapping.upper_bound(value);

    if (upperBoundIter == m_compressedMapping.cbegin())
    {
        return value;
    }

    const auto lowerBoundIter = std::prev(upperBoundIter);

    return value + lowerBoundIter->second;
}

std::vector<int64_t> Mapping::getAllLowerBounds() const
{
    std::vector<int64_t> allLowerBounds;

    for (const auto& mappingElement : m_compressedMapping)
    {
        allLowerBounds.push_back(mappingElement.first);
    }

    return allLowerBounds;
}

std::vector<int64_t> Mapping::getNewLowerBoundsForAbsorbtion(const Mapping& otherMapping) const
{
    std::vector<int64_t> newMappingIntervalLowerBounds;

    // Carry forward existing lower bounds
    for (const auto& existingMappingElement : m_compressedMapping)
    {
        newMappingIntervalLowerBounds.push_back(existingMappingElement.first);
    }

    // Add new lower bounds based on the mapping that is absorbed
    for (const auto& otherMappingElement : otherMapping.m_compressedMapping)
    {
        const int64_t lowerBoundRelativeToOtherMapping = otherMappingElement.first;
        const int64_t lowerBoundRelativeToExistingOverallMapping = getReverseMappedValue(lowerBoundRelativeToOtherMapping);

        newMappingIntervalLowerBounds.push_back(lowerBoundRelativeToExistingOverallMapping);
    }

    return newMappingIntervalLowerBounds;
}

int64_t Mapping::getReverseMappedValue(int64_t value) const
{
    IntervalLowerBoundToOffsetMap compressedReverseLookupMapping;

    for (const auto& mappingElement : m_compressedMapping)
    {
        const int64_t invertedIntervalStart = mappingElement.first + mappingElement.second;
        const int64_t invertedOffset = -mappingElement.second;

        compressedReverseLookupMapping.emplace(invertedIntervalStart, invertedOffset);
    }

    Mapping reverseMapping;
    reverseMapping.m_compressedMapping = compressedReverseLookupMapping;
    return reverseMapping.getMappedValue(value);
}

Mapping::IntervalLowerBoundToOffsetMap Mapping::convertRawMappingToCompressedMapping(const RawMapping& rawMapping)
{
    IntervalLowerBoundToOffsetMap compressedMapping;

    for (const auto& mappingRange : rawMapping)
    {
        const int64_t offset = mappingRange.destinationFirstValue - mappingRange.sourceFirstValue;

        // Insert with overwrite to erase any default mapping
        compressedMapping[mappingRange.sourceFirstValue] = offset;

        // Insert without overwrite to only add the default mapping if there isn't a different mapping already
        compressedMapping.emplace(mappingRange.sourceFirstValue + mappingRange.length, 0);
    }

    return compressedMapping;
}

}
}
}
