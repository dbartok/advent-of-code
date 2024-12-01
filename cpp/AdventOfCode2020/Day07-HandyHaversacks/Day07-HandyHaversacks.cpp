#include "Day07-HandyHaversacks.h"

#include "BagTypesAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day07
{

void processContainedBagsSubstring(BagTypesAnalyzer& bagTypesAnalyzer, const std::string& containerBagColor, const std::string& containedBagsString)
{
    std::vector<std::string> containedBagsSubstrings;
    boost::split(containedBagsSubstrings, containedBagsString, boost::is_any_of(","));

    for (const auto& containedBagsSubstring : containedBagsSubstrings)
    {
        std::regex containedBagsSubstringRegex(R"((?:\s?)(\d+) ([\w ]+) bag(?:s?))");
        std::smatch containedBagsSubstringMatches;
        std::regex_search(containedBagsSubstring, containedBagsSubstringMatches, containedBagsSubstringRegex);

        if (containedBagsSubstringMatches.size() == 3)
        {
            bagTypesAnalyzer.addRelationship(containerBagColor, containedBagsSubstringMatches[2], std::stoi(containedBagsSubstringMatches[1]));
        }
    }

}

BagTypesAnalyzer initializeBagTypesAnalyzer(const std::vector<std::string>& lines)
{
    BagTypesAnalyzer bagTypesAnalyzer;

    for (const auto& line : lines)
    {
        std::regex lineRegex(R"(([\w ]+) bags contain (.+)\.)");
        std::smatch lineMatches;
        std::regex_search(line, lineMatches, lineRegex);

        processContainedBagsSubstring(bagTypesAnalyzer, lineMatches[1], lineMatches[2]);
    }

    return bagTypesAnalyzer;
}

int numBagColorsThatCanContainShinyGold(const std::vector<std::string>& lines)
{
    BagTypesAnalyzer bagTypesAnalyzer = initializeBagTypesAnalyzer(lines);
    return bagTypesAnalyzer.getNumBagColorsThatCanContainShinyGold();
}

int numTotalBagsContainedInsideShinyGold(const std::vector<std::string>& lines)
{
    BagTypesAnalyzer bagTypesAnalyzer = initializeBagTypesAnalyzer(lines);
    return bagTypesAnalyzer.getNumTotalBagsContainedInsideShinyGold();
}

}
}
}
