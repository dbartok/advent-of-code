#include "Day05-IfYouGiveASeedAFertilizer.h"

#include "Almanac.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day05
{

using MappingTextSection = std::vector<std::string>;

std::vector<int64_t> parseSeedsLine(const std::string& seedsLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, seedsLine, boost::is_any_of(":"));

    std::vector<int64_t> seeds;
    AdventOfCode::Utils::splitStringIntoTypedVector(tokens.at(1), seeds);
    return seeds;
}

MappingRange parseMappingRangeLine(const std::string& mappingRangeLine)
{
    std::vector<int64_t> mappingRangeNumbers;
    AdventOfCode::Utils::splitStringIntoTypedVector(mappingRangeLine, mappingRangeNumbers);
    return {mappingRangeNumbers.at(0), mappingRangeNumbers.at(1), mappingRangeNumbers.at(2)};
}

Mapping parseMappingTextSection(const MappingTextSection& mappingTextSection)
{
    RawMapping rawMapping;

    for (int i = 1; i < mappingTextSection.size(); ++i)
    {
        MappingRange mappingRange = parseMappingRangeLine(mappingTextSection.at(i));
        rawMapping.push_back(std::move(mappingRange));
    }

    return Mapping{std::move(rawMapping)};
}

Almanac parseAlmanacLines(const std::vector<std::string>& almanacLines)
{
    std::vector<int64_t> seeds = parseSeedsLine(almanacLines.front());

    const std::vector<std::string> allMappingLines{almanacLines.cbegin() + 2, almanacLines.cend()};

    std::vector<MappingTextSection> mappingTextSections;
    boost::split(mappingTextSections, allMappingLines, [](const auto& elem) { return elem.empty(); });

    std::vector<Mapping> mappings;

    for (const auto& mappingTextSection : mappingTextSections)
    {
        Mapping mapping = parseMappingTextSection(mappingTextSection);
        mappings.push_back(std::move(mapping));
    }

    return {seeds, mappings};
}

int64_t lowestLocationNumberCorrespondingToSeed(const std::vector<std::string>& almanacLines)
{
    Almanac almanac = parseAlmanacLines(almanacLines);

    almanac.buildOverallMapping();

    return almanac.getLowestLocationNumberCorrespondingToSeed();
}

int64_t lowestLocationNumberCorrespondingToSeedWithSeedRanges(const std::vector<std::string>& almanacLines)
{
    Almanac almanac = parseAlmanacLines(almanacLines);

    almanac.buildOverallMapping();

    return almanac.getLowestLocationNumberCorrespondingToSeedWithSeedRanges();
}

}
}
}