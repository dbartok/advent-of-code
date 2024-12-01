#include "PolymerizationEquipment.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day14
{

PolymerizationEquipment::PolymerizationEquipment(std::string polymerTemplate, PolymerPairToInsertedElement polymerPairToInsertedElement)
    : m_polymerPairToInsertedElement{std::move(polymerPairToInsertedElement)}
{
    for (auto polymerIter = polymerTemplate.cbegin(); polymerIter < polymerTemplate.cend() - 1; ++polymerIter)
    {
        std::string polymerPair = {*polymerIter, *(std::next(polymerIter))};
        ++m_polymerPairToNumOccurrences[polymerPair];
    }
}

void PolymerizationEquipment::growPolymer(size_t numPairInsertions)
{
    for (size_t i = 0; i < numPairInsertions; ++i)
    {
        executePairInsertions();
    }
}

int64_t PolymerizationEquipment::getMostAndLeastCommonElementQuantityDifference() const
{
    auto elementToNumOccurrencesInPairs = getElementToNumOccurrencesInPairs();

    const auto minmaxElementToNumOccurrencesInPairsIter = std::minmax_element(elementToNumOccurrencesInPairs.cbegin(), elementToNumOccurrencesInPairs.cend(), [](const auto& lhs, const auto& rhs)
                                                                                {
                                                                                    return lhs.second < rhs.second;
                                                                                });

    const int64_t minPolymerNumOccurrencesInPairs = minmaxElementToNumOccurrencesInPairsIter.first->second;
    const int64_t maxPolymerNumOccurrencesInPairs = minmaxElementToNumOccurrencesInPairsIter.second->second;

    // Account for elements at the beginning and end of the polymer
    const int64_t minPolymerQuantity = std::ceil(static_cast<double>(minPolymerNumOccurrencesInPairs) / 2);
    const int64_t maxPolymerQuantity = std::ceil(static_cast<double>(maxPolymerNumOccurrencesInPairs) / 2);

    return maxPolymerQuantity - minPolymerQuantity;
}

void PolymerizationEquipment::executePairInsertions()
{
    PolymerPairToInt updatedPolymerPairToNumOccurrences;

    for (const auto& polymerPairAndNumOccurrences : m_polymerPairToNumOccurrences)
    {
        const std::string& polymerPair = polymerPairAndNumOccurrences.first;
        const int64_t numOccurrences = polymerPairAndNumOccurrences.second;

        const char insertedElement = m_polymerPairToInsertedElement.at(polymerPair);

        std::string leftPair{polymerPair.front(), insertedElement};
        std::string rightRight{insertedElement, polymerPair.back()};

        updatedPolymerPairToNumOccurrences[leftPair] += numOccurrences;
        updatedPolymerPairToNumOccurrences[rightRight] += numOccurrences;
    }

    m_polymerPairToNumOccurrences = updatedPolymerPairToNumOccurrences;
}

std::unordered_map<char, int64_t> PolymerizationEquipment::getElementToNumOccurrencesInPairs() const
{
    std::unordered_map<char, int64_t> elementToNumOccurrencesInPairs;

    for (const auto& polymerPairAndNumOccurrences : m_polymerPairToNumOccurrences)
    {
        const std::string& polymerPair = polymerPairAndNumOccurrences.first;
        const int64_t numOccurrences = polymerPairAndNumOccurrences.second;

        elementToNumOccurrencesInPairs[polymerPair.front()] += numOccurrences;
        elementToNumOccurrencesInPairs[polymerPair.back()] += numOccurrences;
    }

    return elementToNumOccurrencesInPairs;
}

}
}
}
