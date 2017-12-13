#pragma once

#include <vector>
#include <string>
#include <map>

namespace AdventOfCode
{

class ScannerCorridor
{
public:
    // Ordered map allows iterating in increasing order of depth
    using RangeToDepthMap = std::map<unsigned, unsigned>;

    ScannerCorridor(RangeToDepthMap rangeToDepthMap);
    unsigned severityOfWholeTrip() const;

    static ScannerCorridor fromScannerRangeLines(const std::vector<std::string> scannerRangeLines);

private:
    RangeToDepthMap m_rangeToDepthMap;
};

}
