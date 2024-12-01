#include "Day09-StreamProcessing.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day09
{

unsigned totalScoreForAllGroups(const std::string& groupedString)
{
    bool insideGarbage = false;
    unsigned groupNestingLevel = 0;
    unsigned totalScore = 0;

    for (size_t i = 0; i < groupedString.size(); ++i)
    {
        char c = groupedString[i];

        if (insideGarbage)
        {
            switch (c)
            {
                case '!':
                    ++i;
                    break;

                case '>':
                    insideGarbage = false;
                    break;

                default:
                    break;
            }
        }
        else
        {
            switch (c)
            {
                case '<':
                    insideGarbage = true;
                    break;

                case '{':
                    ++groupNestingLevel;
                    break;

                case '}':
                    if (groupNestingLevel == 0)
                    {
                        throw std::runtime_error("Group closing character found without a matching opening character.");
                    }

                    totalScore += groupNestingLevel;

                    --groupNestingLevel;
                    break;

                default:
                    break;
            }
        }
    }

    return totalScore;
}

unsigned totalGarbageCount(const std::string& groupedString)
{
    bool insideGarbage = false;
    unsigned garbageCount = 0;

    for (size_t i = 0; i < groupedString.size(); ++i)
    {
        char c = groupedString[i];

        if (insideGarbage)
        {
            switch (c)
            {
                case '!':
                    ++i;
                    break;

                case '>':
                    insideGarbage = false;
                    break;

                default:
                    ++garbageCount;
            }
        }
        else
        {
            switch (c)
            {
                case '<':
                    insideGarbage = true;
                    break;

                default:
                    break;
            }
        }
    }

    return garbageCount;
}

}
}
}
