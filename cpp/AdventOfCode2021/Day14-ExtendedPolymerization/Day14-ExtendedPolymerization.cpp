#include "Day14-ExtendedPolymerization.h"

#include "PolymerizationEquipment.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

size_t NUM_PAIR_INSERTIONS_PART_ONE = 10;
size_t NUM_PAIR_INSERTIONS_PART_TWO = 40;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day14
{

using TextSection = std::vector<std::string>;

PolymerPairToInsertedElement parsePairInsertionRulesTextSection(const TextSection& pairInsertionRulesTextSection)
{
    PolymerPairToInsertedElement polymerPairToInsertedElement;

    for (const auto& line : pairInsertionRulesTextSection)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of(" ->"), boost::token_compress_on);
        polymerPairToInsertedElement[tokens.at(0)] = tokens.at(1).front();
    }

    return polymerPairToInsertedElement;
}

PolymerizationEquipment parsePolymerFormulaLines(const std::vector<std::string>& polymerFormulaLines)
{
    std::vector<TextSection> textSections;
    boost::split(textSections, polymerFormulaLines, [](const auto& elem) { return elem.empty(); });

    std::string polymerTemplate = textSections.at(0).at(0);
    PolymerPairToInsertedElement polymerPairToInsertedElement = parsePairInsertionRulesTextSection(textSections.at(1));

    return PolymerizationEquipment{std::move(polymerTemplate), std::move(polymerPairToInsertedElement)};
}

int64_t mostAndLeastCommonElementQuantityDifference(const std::vector<std::string>& polymerFormulaLines)
{
    PolymerizationEquipment polymerizationEquipment = parsePolymerFormulaLines(polymerFormulaLines);
    polymerizationEquipment.growPolymer(NUM_PAIR_INSERTIONS_PART_ONE);
    return polymerizationEquipment.getMostAndLeastCommonElementQuantityDifference();
}

int64_t mostAndLeastCommonElementQuantityDifferenceReinforced(const std::vector<std::string>& polymerFormulaLines)
{
    PolymerizationEquipment polymerizationEquipment = parsePolymerFormulaLines(polymerFormulaLines);
    polymerizationEquipment.growPolymer(NUM_PAIR_INSERTIONS_PART_TWO);
    return polymerizationEquipment.getMostAndLeastCommonElementQuantityDifference();
}

}
}
}