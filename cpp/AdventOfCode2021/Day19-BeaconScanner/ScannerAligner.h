#pragma once

#include "Scanner.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <vector>
#include <list>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day19
{

class ScannerAligner
{
public:
    ScannerAligner(std::vector<Scanner> scanners);

    void alignAll();

    unsigned getNumTotalBeacons() const;
    unsigned getLargestManhattanDistanceBetweenAnyTwoScanners() const;

private:
    std::vector<Scanner> m_scanners;
    std::list<Scanner> m_alignedScanners;

    void reconstructAllNeighbors(const Scanner& alignedScanner);
    bool isScannerAlignedAlready(const Scanner& scanner) const;

    static boost::optional<Scanner> tryToAlignNeighborCandidate(const Scanner& alignedScanner, const Scanner& neighborCandidate);
    static boost::optional<Scanner> tryToMoveNeighborCandidateToCorrectOffset(const Scanner& alignedScanner, const Scanner& neighborCandidate);
};

}
}
}
