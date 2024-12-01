#include "Day06-TuningTrouble.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <stdexcept>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

size_t PACKET_MARKER_LENGTH = 4;
size_t MESSAGE_MARKER_LENGTH = 14;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day06
{

bool isMarkerEndPosition(const std::string& data, size_t markerLength, size_t endIndex)
{
    std::string possibleMarker = data.substr(endIndex - (markerLength - 1), markerLength);
    std::unordered_set<char> uniqueCharsInPossibleMarker{possibleMarker.cbegin(), possibleMarker.cend()};

    return possibleMarker.size() == uniqueCharsInPossibleMarker.size();
}

int getNumCharactersProcessedBeforeMarkerWithGivenLength(const std::string& data, size_t markerLength)
{
    for (size_t endIndex = markerLength - 1; endIndex < data.size(); ++endIndex)
    {
        if (isMarkerEndPosition(data, markerLength, endIndex))
        {
            return endIndex + 1;
        }
    }

    throw std::runtime_error("Marker not found");
}

int numCharactersProcessedBeforeStartOfPacketMarker(const std::string& data)
{
    return getNumCharactersProcessedBeforeMarkerWithGivenLength(data, PACKET_MARKER_LENGTH);
}

int numCharactersProcessedBeforeStartOfMessage(const std::string& data)
{
    return getNumCharactersProcessedBeforeMarkerWithGivenLength(data, MESSAGE_MARKER_LENGTH);
}

}
}
}