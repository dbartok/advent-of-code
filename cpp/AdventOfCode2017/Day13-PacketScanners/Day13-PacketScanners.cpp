#include "Day13-PacketScanners.h"

#include "ScannerCorridor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day13
{

unsigned severityOfWholeTrip(const std::vector<std::string>& scannerRangeLines)
{
    ScannerCorridor scannerCorrider = ScannerCorridor::fromScannerRangeLines(scannerRangeLines);
    return scannerCorrider.severityOfWholeTrip();
}

unsigned smallestDelayNotToGetCaught(const std::vector<std::string>& scannerRangeLines)
{
    ScannerCorridor scannerCorrider = ScannerCorridor::fromScannerRangeLines(scannerRangeLines);
    return scannerCorrider.smallestDelayNotToGetCaught();
}

}
}
}
