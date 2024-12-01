#include "Day19-BeaconScanner.h"

#include "Scanner.h"
#include "ScannerAligner.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day19
{

using TextSection = std::vector<std::string>;

Vector3D parseBeaconPositionLine(const std::string& beaconPositionLine)
{
    std::vector<int> coordinates;
    Utils::splitStringIntoTypedVector(beaconPositionLine, coordinates, ',');
    return Vector3D{coordinates.at(0), coordinates.at(1), coordinates.at(2)};
}

Scanner parseBeaconPositionsLines(const std::vector<std::string>& beaconPositionsLines)
{
    std::vector<Vector3D> beaconPositions;

    std::regex scannerIdRegex(R"(--- scanner ([0-9]+) ---)");
    std::smatch scannerIdMatch;

    std::regex_match(beaconPositionsLines.front(), scannerIdMatch, scannerIdRegex);

    const int scannerId = std::stoi(scannerIdMatch[1].str());

    for (auto lineIter = std::next(beaconPositionsLines.cbegin()); lineIter != beaconPositionsLines.cend(); ++lineIter)
    {
        Vector3D beaconPosition = parseBeaconPositionLine(*lineIter);
        beaconPositions.push_back(beaconPosition);
    }

    return Scanner{scannerId, std::move(beaconPositions)};
}

std::vector<Scanner> parseAllBeaconPositionsLines(const std::vector<std::string>& allBeaconPositionsLines)
{
    std::vector<TextSection> textSections;
    boost::split(textSections, allBeaconPositionsLines, [](const auto& elem) { return elem.empty(); });

    std::vector<Scanner> scanners;

    for (const auto& textSection : textSections)
    {
        Scanner scanner = parseBeaconPositionsLines(textSection);
        scanners.push_back(std::move(scanner));
    }

    return scanners;
}

unsigned numBeacons(const std::vector<std::string>& allBeaconPositionsLines)
{
    std::vector<Scanner> scanners = parseAllBeaconPositionsLines(allBeaconPositionsLines);
    ScannerAligner scannerAligner{std::move(scanners)};
    scannerAligner.alignAll();
    return scannerAligner.getNumTotalBeacons();
}

unsigned largestManhattanDistanceBetweenAnyTwoScanners(const std::vector<std::string>& allBeaconPositionsLines)
{
    std::vector<Scanner> scanners = parseAllBeaconPositionsLines(allBeaconPositionsLines);
    ScannerAligner scannerAligner{std::move(scanners)};
    scannerAligner.alignAll();
    return scannerAligner.getLargestManhattanDistanceBetweenAnyTwoScanners();
}

}
}
}