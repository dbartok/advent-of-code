#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
#include <map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day13
{

class ScannerCorridor
{
public:
    // Ordered map allows iterating in increasing order of depth
    using RangeToDepthMap = std::map<unsigned, unsigned>;

    ScannerCorridor(RangeToDepthMap rangeToDepthMap);
    unsigned severityOfWholeTrip() const;
    unsigned smallestDelayNotToGetCaught() const;

    static ScannerCorridor fromScannerRangeLines(const std::vector<std::string> scannerRangeLines);
    static constexpr bool isCaught(unsigned range, unsigned depth, unsigned delay = 0);

private:
    RangeToDepthMap m_rangeToDepthMap;
};

}
}
}
