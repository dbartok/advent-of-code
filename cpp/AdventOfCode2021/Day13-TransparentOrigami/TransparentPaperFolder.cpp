#include "TransparentPaperFolder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char FILLED_CHAR = '#';
const char UNFILLED_CHAR = '.';

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day13
{
 
TransparentPaperFolder::TransparentPaperFolder(CoordinatesSet dotCoordinatesSet, FoldInstructions foldInstructions)
    : m_dotCoordinatesSet{std::move(dotCoordinatesSet)}
    , m_foldInstructions{std::move(foldInstructions)}
{

}

void TransparentPaperFolder::foldOnce()
{
    const auto& currentInstruction = m_foldInstructions.at(m_instructionIndex++);
    if (currentInstruction.axis == Axis::Y)
    {
        foldBottomHalfUp(currentInstruction.position);
    }
    else
    {
        foldRightHalfLeft(currentInstruction.position);
    }
}

void TransparentPaperFolder::foldCompletely()
{
    while (m_instructionIndex < m_foldInstructions.size())
    {
        foldOnce();
    }
}

unsigned TransparentPaperFolder::getNumVisibleDots() const
{
    return m_dotCoordinatesSet.size();
}

std::string TransparentPaperFolder::getSerializedMessage() const
{
    const BoundingBox boundingBox = getBoundingBox();

    const int width = boundingBox.size.first;
    const int height = boundingBox.size.second;

    std::vector<std::string> serializedLines(height, std::string(width, UNFILLED_CHAR));

    for (const auto& dotCoordinates : m_dotCoordinatesSet)
    {
        Coordinates offsetDotCoordinates{dotCoordinates.first - boundingBox.offset.first, dotCoordinates.second - boundingBox.offset.second};

        const int xPos = offsetDotCoordinates.first;
        const int yPos = offsetDotCoordinates.second;

        serializedLines.at(yPos).at(xPos) = FILLED_CHAR;
    }

    return boost::algorithm::join(serializedLines, "\n");
}

void TransparentPaperFolder::foldBottomHalfUp(int yThreshold)
{
    std::vector<Coordinates> dotCoordatinesVector{m_dotCoordinatesSet.cbegin(), m_dotCoordinatesSet.cend()};
    for (auto dotCoordinates : dotCoordatinesVector)
    {
        if (dotCoordinates.second > yThreshold)
        {
            m_dotCoordinatesSet.erase(dotCoordinates);
            dotCoordinates.second = yThreshold - (dotCoordinates.second - yThreshold);
            m_dotCoordinatesSet.insert(dotCoordinates);
        }
    }
}

void TransparentPaperFolder::foldRightHalfLeft(int xThreshold)
{
    std::vector<Coordinates> dotCoordatinesVector{m_dotCoordinatesSet.cbegin(), m_dotCoordinatesSet.cend()};
    for (auto dotCoordinates : dotCoordatinesVector)
    {
        if (dotCoordinates.first > xThreshold)
        {
            m_dotCoordinatesSet.erase(dotCoordinates);
            dotCoordinates.first = xThreshold - (dotCoordinates.first - xThreshold);
            m_dotCoordinatesSet.insert(dotCoordinates);
        }
    }
}

BoundingBox TransparentPaperFolder::getBoundingBox() const
{
    const auto minmaxPositionXIter = std::minmax_element(m_dotCoordinatesSet.cbegin(), m_dotCoordinatesSet.cend(), [](const auto& lhs, const auto& rhs)
                                                         {
                                                             return lhs.first < rhs.first;
                                                         });

    const int xMin = minmaxPositionXIter.first->first;
    const int xMax = minmaxPositionXIter.second->first;

    const auto minmaxPositionYIter = std::minmax_element(m_dotCoordinatesSet.cbegin(), m_dotCoordinatesSet.cend(), [](const auto& lhs, const auto& rhs)
                                                         {
                                                             return lhs.second < rhs.second;
                                                         });

    const int yMin = minmaxPositionYIter.first->second;
    const int yMax = minmaxPositionYIter.second->second;

    return BoundingBox{{xMin, yMin}, {xMax - xMin + 1, yMax - yMin + 1}};
}

}
}
}
