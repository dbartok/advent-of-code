#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day14
{

using PolymerPairToInsertedElement = std::unordered_map<std::string, char>;
using PolymerPairToInt = std::unordered_map<std::string, int64_t>;

class PolymerizationEquipment
{
public:
    PolymerizationEquipment(std::string polymerTemplate, PolymerPairToInsertedElement polymerPairToInsertedElement);

    void growPolymer(size_t numPairInsertions);

    int64_t getMostAndLeastCommonElementQuantityDifference() const;

private:
    PolymerPairToInt m_polymerPairToNumOccurrences;
    PolymerPairToInsertedElement m_polymerPairToInsertedElement;

    void executePairInsertions();

    std::unordered_map<char, int64_t> getElementToNumOccurrencesInPairs() const;
};

}
}
}
