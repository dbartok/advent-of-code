#include "ScannerCorridor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day13
{

ScannerCorridor::ScannerCorridor(RangeToDepthMap rangeToDepthMap)
    : m_rangeToDepthMap{rangeToDepthMap}
{

}

unsigned ScannerCorridor::severityOfWholeTrip() const
{
    unsigned severity = 0;
    for (const auto& depthRangePair : m_rangeToDepthMap)
    {
        unsigned depth;
        unsigned range;
        std::tie(depth, range) = depthRangePair;

        if (isCaught(range, depth))
        {
            severity += depth * range;
        }
    }

    return severity;
}

unsigned ScannerCorridor::smallestDelayNotToGetCaught() const
{
    unsigned smallestDelay = 0;
    while (true)
    {
        bool isEverCaught = false;
        for (const auto& depthRangePair : m_rangeToDepthMap)
        {
            unsigned depth;
            unsigned range;
            std::tie(depth, range) = depthRangePair;

            if (isCaught(range, depth, smallestDelay))
            {
                isEverCaught = true;
                break;
            }
        }

        if (!isEverCaught)
        {
            break;
        }

        ++smallestDelay;
    }

    return smallestDelay;
}

ScannerCorridor ScannerCorridor::fromScannerRangeLines(const std::vector<std::string> scannerRangeLines)
{
    RangeToDepthMap rangeToDepthMap;
    for (const auto& scannerRangeLine : scannerRangeLines)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, scannerRangeLine, boost::is_any_of(": "), boost::token_compress_on);

        if (tokens.size() != 2)
        {
            throw std::runtime_error("Each line needs to have exactly 2 tokens.");
        }

        unsigned depth = boost::lexical_cast<unsigned>(tokens[0]);
        unsigned range = boost::lexical_cast<unsigned>(tokens[1]);

        if (range < 2)
        {
            throw std::runtime_error("Range less than 2 is invalid.");
        }

        bool insertionTookPlace;
        std::tie(std::ignore, insertionTookPlace) = rangeToDepthMap.insert(std::make_pair(depth, range));
        if (!insertionTookPlace)
        {
            throw std::runtime_error("Same depth appears twice in the input lines.");
        }
    }

    return ScannerCorridor{std::move(rangeToDepthMap)};
}

constexpr bool ScannerCorridor::isCaught(unsigned range, unsigned depth, unsigned delay)
{
    unsigned totalStepsInPath = (2 * (range - 1));

    // Smallest delay value that has the equivalent effect
    unsigned minEquivalentDelay = delay % totalStepsInPath;

    // Number of steps the scanner has taken since last being at the top
    unsigned scannerNumStepsFromTop = (depth + minEquivalentDelay) % totalStepsInPath;

    unsigned scannerPos{};

    // Scanner in the first half of its path
    if (scannerNumStepsFromTop <= range - 1)
    {
        scannerPos = scannerNumStepsFromTop;
    }

    // Scanner in the second half of its path
    else
    {
        // Number of steps the scanner has taken since last being at the bottom
        unsigned scannerNumStepsFromBottom = scannerNumStepsFromTop - (range - 1);

        scannerPos = (range - 1) - scannerNumStepsFromBottom;
    }

    return scannerPos == 0;
}

}
}
}
