#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day05
{

struct MappingRange
{
    int64_t destinationFirstValue;
    int64_t sourceFirstValue;
    int64_t length;
};

using RawMapping = std::vector<MappingRange>;

class Mapping
{
public:
    Mapping();
    Mapping(const RawMapping& rawMapping);

    void absorb(const Mapping& otherMapping);

    int64_t getMappedValue(int64_t value) const;
    std::vector<int64_t> getAllLowerBounds() const;

private:
    // Concise representation of a mapping that only stores the lowest element where the mapping changes, along with the offset for that element
    // E.g., take the following mapping:
    // 0 -> 1 (change to 1 offset)
    // 1 -> 2
    // 2 -> 3
    // 3 -> 0 (change to -3 offset)
    // 4 -> 4 (change to 0 offset)
    // 5 -> 5
    // ...
    //
    // Concise representation in the form of element + offset pairs: [{0, 1}, {3, -3}, {4, 0}]
    using IntervalLowerBoundToOffsetMap = std::map<int64_t, int64_t>;

    IntervalLowerBoundToOffsetMap m_compressedMapping;


    std::vector<int64_t> getNewLowerBoundsForAbsorbtion(const Mapping& otherMapping) const;

    int64_t getReverseMappedValue(int64_t value) const;

    static IntervalLowerBoundToOffsetMap convertRawMappingToCompressedMapping(const RawMapping& rawMapping);
};

}
}
}
