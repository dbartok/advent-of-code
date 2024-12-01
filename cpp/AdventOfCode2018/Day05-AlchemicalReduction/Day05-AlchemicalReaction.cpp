#include "Day05-AlchemicalReaction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cmath>
#include <list>
#include <unordered_set>
#include <cctype>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const int REDUCIBLE_DISTANCE = std::abs('A' - 'a');
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day05
{

bool isReducible(char a, char b)
{
    return std::abs(a - b) == REDUCIBLE_DISTANCE;
}

std::string getReducedPolymerString(const std::string& polymerString)
{
    std::list<char> charList{polymerString.cbegin(), polymerString.cend()};

    auto currentIter = charList.begin();
    while (currentIter != charList.end())
    {
        auto previousIter = currentIter;
        ++currentIter;

        if (currentIter == charList.end())
        {
            break;
        }

        if (isReducible(*previousIter, *currentIter))
        {
            currentIter = charList.erase(previousIter);
            currentIter = charList.erase(currentIter);
            if (currentIter != charList.begin())
            {
                --currentIter;
            }
        }
    }

    return std::string{charList.cbegin(), charList.cend()};
}

std::unordered_set<char> getAllLowercaseChars(const std::string& s)
{
    std::unordered_set<char> allLowercaseChars;

    for (auto c : s)
    {
        allLowercaseChars.insert(std::tolower(c));
    }

    return allLowercaseChars;
}

std::vector<std::string> getPolymerStringsWithOneUnitRemoved(const std::string& polymerString)
{
    std::unordered_set<char> allLowercaseChars = getAllLowercaseChars(polymerString);

    std::vector<std::string> polymerStringsWithOneUnitRemoved;
    for (auto lowercaseUnit : allLowercaseChars)
    {
        std::string newPolymerString;
        std::copy_if(polymerString.cbegin(), polymerString.cend(), std::back_inserter(newPolymerString), [lowercaseUnit](char c)
                     {
                         return std::tolower(c) != lowercaseUnit;
                     });

        polymerStringsWithOneUnitRemoved.push_back(std::move(newPolymerString));
    }

    return polymerStringsWithOneUnitRemoved;
}

std::string getOneUnitRemovedShortestReducedString(const std::string& polymerString)
{
    std::vector<std::string> polymerStringsWithOneUnitRemoved = getPolymerStringsWithOneUnitRemoved(polymerString);

    auto minIter = std::min_element(polymerStringsWithOneUnitRemoved.cbegin(), polymerStringsWithOneUnitRemoved.cend(),
                                    [](const std::string& s1, const std::string& s2)
                                    {
                                        return getReducedPolymerLength(s1) < getReducedPolymerLength(s2);
                                    });

    return getReducedPolymerString(*minIter);
}

unsigned getReducedPolymerLength(const std::string& polymerString)
{
    std::string reducedPolymerString = getReducedPolymerString(polymerString);

    return reducedPolymerString.length();
}

unsigned getOneUnitRemovedShortestReducedLength(const std::string& polymerString)
{
    std::string oneUnitRemovedReducedPolymerString = getOneUnitRemovedShortestReducedString(polymerString);

    return oneUnitRemovedReducedPolymerString.length();
}

}
}
}
