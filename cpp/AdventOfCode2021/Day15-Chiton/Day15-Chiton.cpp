#include "Day15-Chiton.h"

#include "CaveTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <iterator>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

size_t SCALE_FACTOR_PART_TWO = 5;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day15
{

RiskLevelRow parseRiskLevelLine(const std::string& line)
{
    RiskLevelRow riskLevelRow;
    std::transform(line.cbegin(), line.cend(), std::back_inserter(riskLevelRow), [](const char c)
                   {
                       return c - '0';
                   });

    return riskLevelRow;
}

RiskLevelMap parseRiskLevelLines(const std::vector<std::string>& riskLevelLines)
{
    RiskLevelMap riskLevelMap;

    for (const auto& line : riskLevelLines)
    {
        RiskLevelRow riskLevelRow = parseRiskLevelLine(line);
        riskLevelMap.push_back(std::move(riskLevelRow));
    }

    return riskLevelMap;
}

RiskLevelMap createRepeatedRiskLevelMap(const RiskLevelMap& originalRiskLevelMap, size_t scaleFactor)
{
    const size_t originalWidth = originalRiskLevelMap.at(0).size();
    const size_t originalHeight = originalRiskLevelMap.size();

    RiskLevelMap repeatedRiskLevelMap = RiskLevelMap(originalHeight * scaleFactor, RiskLevelRow(originalWidth * scaleFactor));

    for (size_t j = 0; j < originalHeight * scaleFactor; ++j)
    {
        for (size_t i = 0; i < originalWidth * scaleFactor; ++i)
        {
            const size_t xOriginal = i % originalWidth;
            const size_t yOriginal = j % originalHeight;
            const int baseRiskLevel = originalRiskLevelMap.at(yOriginal).at(xOriginal);
            const int additionalRiskLevel = (i / originalWidth) + (j / originalHeight);
            const int newRiskLevel = baseRiskLevel + additionalRiskLevel;
            const int newRiskLevelWrapped = ((newRiskLevel - 1) % 9) + 1;

            repeatedRiskLevelMap.at(j).at(i) = newRiskLevelWrapped;
        }
    }

    return repeatedRiskLevelMap;
}

int lowestTotalRiskOfAnyPath(const std::vector<std::string>& riskLevelLines)
{
    RiskLevelMap riskLevelMap = parseRiskLevelLines(riskLevelLines);
    CaveTraverser caveTraverser{std::move(riskLevelMap)};
    caveTraverser.traverse();
    return caveTraverser.getMinRiskLevel();
}

int lowestTotalRiskOfAnyPathRepeatedMap(const std::vector<std::string>& riskLevelLines)
{
    RiskLevelMap originalRiskLevelMap = parseRiskLevelLines(riskLevelLines);
    RiskLevelMap repeatedRiskLevelMap = createRepeatedRiskLevelMap(originalRiskLevelMap, SCALE_FACTOR_PART_TWO);
    CaveTraverser caveTraverser{std::move(repeatedRiskLevelMap)};
    caveTraverser.traverse();
    return caveTraverser.getMinRiskLevel();
}

}
}
}
