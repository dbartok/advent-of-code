#include "Day18-Snailfish.h"

#include "SnailfishNumberParser.h"
#include "SnailfishNumberCalculator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day18
{

int getSumMagnitude(const std::string& lineOne, const std::string& lineTwo)
{
    SnailfishNumberCalculator calculator;

    SnailfishNumberParser parserOne{lineOne};
    Node::SharedPtr firstNumberNode = parserOne.createRootNode();
    calculator.addNumber(firstNumberNode);

    SnailfishNumberParser parserTwo{lineTwo};
    Node::SharedPtr secondNumberNode = parserTwo.createRootNode();
    calculator.addNumber(secondNumberNode);

    return calculator.getMagnitude();
}

int magnitudeOfFinalSum(const std::vector<std::string>& snailfishNumberStringLines)
{
    SnailfishNumberCalculator calculator;

    for (auto lineIter = snailfishNumberStringLines.cbegin(); lineIter != snailfishNumberStringLines.cend(); ++lineIter)
    {
        SnailfishNumberParser parser{*lineIter};
        Node::SharedPtr currentNumberNode = parser.createRootNode();
        calculator.addNumber(std::move(currentNumberNode));
    }

    return calculator.getMagnitude();
}

int largestMagnitudeOfAnyTwoAddendSum(const std::vector<std::string>& snailfishNumberStringLines)
{
    int maxSumMagnitude = std::numeric_limits<int>::min();

    for (auto lineOneIter = snailfishNumberStringLines.cbegin(); lineOneIter != snailfishNumberStringLines.cend(); ++lineOneIter)
    {
        for (auto lineTwoIter = snailfishNumberStringLines.cbegin(); lineTwoIter != snailfishNumberStringLines.cend(); ++lineTwoIter)
        {
            if (lineOneIter != lineTwoIter)
            {
                const int currentSumMagnitude = getSumMagnitude(*lineOneIter, *lineTwoIter);
                maxSumMagnitude = std::max(currentSumMagnitude, maxSumMagnitude);
            }
        }
    }

    return maxSumMagnitude;
}

}
}
}