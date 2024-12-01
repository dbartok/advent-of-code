#include "ScannerAligner.h"

#include "Scanner.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

unsigned MIN_NUM_OVERLAPPING_BEACONS_FOR_ALIGNMENT = 12;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day19
{

void getBaseTransformationMatricesRecursive(const Vector3DSet& baseRows, Matrix3D matrixSoFar, std::vector<Matrix3D>& baseTransformationMatrices)
{
    if (baseRows.empty())
    {
        baseTransformationMatrices.push_back(matrixSoFar);
        return;
    }

    size_t rowIndex = 3 - baseRows.size();

    for (const auto& baseRow : baseRows)
    {
        auto baseRowsCopy{baseRows};
        baseRowsCopy.erase(baseRow);

        matrixSoFar.row(rowIndex) = baseRow;
        getBaseTransformationMatricesRecursive(baseRowsCopy, matrixSoFar, baseTransformationMatrices);

        matrixSoFar.row(rowIndex) *= -1;
        getBaseTransformationMatricesRecursive(baseRowsCopy, matrixSoFar, baseTransformationMatrices);
    }
}

std::vector<Matrix3D> getBaseTransformationMatrices()
{
    const Vector3DSet baseRows = {Vector3D(1, 0, 0), Vector3D(0, 1, 0), Vector3D(0, 0, 1)};
    std::vector<Matrix3D> baseTransformationMatrices;

    getBaseTransformationMatricesRecursive(baseRows, {}, baseTransformationMatrices);

    return baseTransformationMatrices;
}

ScannerAligner::ScannerAligner(std::vector<Scanner> scanners)
    : m_scanners{std::move(scanners)}
{

}

void ScannerAligner::alignAll()
{
    m_alignedScanners.push_back(m_scanners.front());

    for (const auto& alignedScanner : m_alignedScanners)
    {
        reconstructAllNeighbors(alignedScanner);
    }
}

unsigned ScannerAligner::getNumTotalBeacons() const
{
    Vector3DSet allBeaconPositions;

    for (const auto& scanner : m_alignedScanners)
    {
        allBeaconPositions = scanner.getBeaconPositionUnion(allBeaconPositions);
    }

    return allBeaconPositions.size();
}

unsigned ScannerAligner::getLargestManhattanDistanceBetweenAnyTwoScanners() const
{
    unsigned largestManhattanDistance = 0;

    for (auto scannerOneIter = m_alignedScanners.cbegin(); scannerOneIter != m_alignedScanners.cend(); ++scannerOneIter)
    {
        for (auto scannerTwoIter = std::next(scannerOneIter); scannerTwoIter != m_alignedScanners.cend(); ++scannerTwoIter)
        {
            largestManhattanDistance = std::max(largestManhattanDistance, scannerOneIter->getManhattanDistanceFrom(*scannerTwoIter));
        }
    }

    return largestManhattanDistance;
}

void ScannerAligner::reconstructAllNeighbors(const Scanner& alignedScanner)
{
    for (const auto& neighborCandidate : m_scanners)
    {
        if (isScannerAlignedAlready(neighborCandidate))
        {
            continue;
        }

        boost::optional<Scanner> alignedNeighbor = tryToAlignNeighborCandidate(alignedScanner, neighborCandidate);
        if (alignedNeighbor)
        {
            m_alignedScanners.push_back(alignedNeighbor.value());
        }
    }
}

bool ScannerAligner::isScannerAlignedAlready(const Scanner& scanner) const
{
    return std::find(m_alignedScanners.cbegin(), m_alignedScanners.cend(), scanner) != m_alignedScanners.cend();
}

boost::optional<Scanner> ScannerAligner::tryToAlignNeighborCandidate(const Scanner& alignedScanner, const Scanner& neighborCandidate)
{
    const std::vector<Matrix3D> baseTransformMatrices = getBaseTransformationMatrices();

    for (const auto& baseTransformMatrix : baseTransformMatrices)
    {
        auto baseTransformedNeighborCandidate{neighborCandidate};
        baseTransformedNeighborCandidate.applyBaseTransform(baseTransformMatrix);
        boost::optional<Scanner> alignedNeighbor = tryToMoveNeighborCandidateToCorrectOffset(alignedScanner, baseTransformedNeighborCandidate);
        if (alignedNeighbor)
        {
            return alignedNeighbor;
        }
    }

    return boost::none;
}

boost::optional<Scanner> ScannerAligner::tryToMoveNeighborCandidateToCorrectOffset(const Scanner& alignedScanner, const Scanner& neighborCandidate)
{
    const Vector3DSet possibleOffsets = neighborCandidate.getPossibleOffsetsFrom(alignedScanner);

    for (const auto& possibleOffset : possibleOffsets)
    {
        auto offsetNeighborCandidate{neighborCandidate};
        offsetNeighborCandidate.applyOffset(possibleOffset);
        const unsigned numOverlappingBeacons = offsetNeighborCandidate.getNumOverlappingBeacons(alignedScanner);
        if (numOverlappingBeacons >= MIN_NUM_OVERLAPPING_BEACONS_FOR_ALIGNMENT)
        {
            return offsetNeighborCandidate;
        }
    }

    return boost::none;
}

}
}
}
