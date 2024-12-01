#include "Day03-RucksackReorganization.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <numeric>
#include <iterator>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

int LOWERCASE_STARTING_PRIORITY = 1;
int UPPERCASE_STARTING_PRIORITY = 27;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day03
{

std::string getSharedChars(std::string first, std::string second)
{
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    std::string intersection;
    std::set_intersection(first.begin(), first.end(),
                          second.begin(), second.end(),
                          std::back_inserter(intersection));

    auto uniqueRangeEndIter = std::unique(intersection.begin(), intersection.end());
    intersection.erase(uniqueRangeEndIter, intersection.end());

    return intersection;
}

char getSingleSharedItemBetweenCompartments(const std::string& rucksackContents)
{
    const std::string firstCompartment = rucksackContents.substr(0, rucksackContents.size() / 2);
    const std::string secondCompartment = rucksackContents.substr(rucksackContents.size() / 2);

    const std::string sharedItems = getSharedChars(firstCompartment, secondCompartment);

    if (sharedItems.size() != 1)
    {
        throw std::runtime_error("Invalid amount of shared elements: " + std::to_string(sharedItems.size()));
    }

    return sharedItems.front();
}

int getPriority(char item)
{
    if (islower(item))
    {
        return item - 'a' + LOWERCASE_STARTING_PRIORITY;
    }
    else if (isupper(item))
    {
        return item - 'A' + UPPERCASE_STARTING_PRIORITY;
    }

    throw std::runtime_error("Invalid item: " + std::string{item});
}

int getSharedItemPriority(const std::string& rucksackContentsLine)
{
    const char sharedItem = getSingleSharedItemBetweenCompartments(rucksackContentsLine);
    return getPriority(sharedItem);
}

char getSingleSharedItemBetweenRucksacks(const std::string& firstRucksackContents, const std::string& secondRucksackContents, const std::string& thirdRucksackContents)
{
    const std::string sharedItemsBetweenFirstTwoRucksacks = getSharedChars(firstRucksackContents, secondRucksackContents);
    const std::string sharedItemsBetweenAllRucksacks = getSharedChars(sharedItemsBetweenFirstTwoRucksacks, thirdRucksackContents);

    if (sharedItemsBetweenAllRucksacks.size() != 1)
    {
        throw std::runtime_error("Invalid amount of shared elements: " + std::to_string(sharedItemsBetweenAllRucksacks.size()));
    }

    return sharedItemsBetweenAllRucksacks.front();
}

int sumOfSharedItemPriorities(const std::vector<std::string>& rucksackContentsLines)
{
    return std::accumulate(rucksackContentsLines.cbegin(), rucksackContentsLines.cend(), 0, [](const auto& acc, const auto& line) { return acc + getSharedItemPriority(line); });
}

int sumOfGroupBadgePriorities(const std::vector<std::string>& rucksackContentsLines)
{
    int sumOfPriorities = 0;

    for (auto rucksackContentsLineIter = rucksackContentsLines.cbegin(); rucksackContentsLineIter != rucksackContentsLines.cend(); rucksackContentsLineIter += 3)
    {
        const std::string& firstRucksack = *rucksackContentsLineIter;
        const std::string& secondRucksack = *(rucksackContentsLineIter + 1);
        const std::string& thirdRucksack = *(rucksackContentsLineIter + 2);

        const char sharedItem = getSingleSharedItemBetweenRucksacks(firstRucksack, secondRucksack, thirdRucksack);
        sumOfPriorities += getPriority(sharedItem);
    }

    return sumOfPriorities;
}

}
}
}