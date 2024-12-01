#include "StarAligner.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include<boost/algorithm/string.hpp>

#include<algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const char DARK = '.';
const char LIGHT = '#';
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day10
{

using CoordinateLongNumericType = long long;

Starlight::Starlight(Vector2D position, Vector2D velocity) noexcept
    : position{std::move(position)}
    , velocity{std::move(velocity)}
{

}

StarBoundingBox::StarBoundingBox(Vector2D offset, Vector2D size) noexcept
    : offset{std::move(offset)}
    , size{std::move(size)}
{

}

StarAligner::StarAligner(std::vector<Starlight> starlights) noexcept
    : m_starlights{std::move(starlights)}
    , m_timeElapsed{0}
{

}

void StarAligner::align()
{
    CoordinateLongNumericType previousBoundingBoxArea = std::numeric_limits<CoordinateLongNumericType>::max();

    while (true)
    {
        stepOneTimeUnit();

        StarBoundingBox currentBoundingBox = getBoundingBox();
        const CoordinateLongNumericType currentBoundingBoxArea = CoordinateLongNumericType{currentBoundingBox.size[0]} *currentBoundingBox.size[1];

        if (currentBoundingBoxArea > previousBoundingBoxArea)
        {
            break;
        }

        previousBoundingBoxArea = currentBoundingBoxArea;
        ++m_timeElapsed;
    }

    rewindOneTimeUnit();
}

std::string StarAligner::getSerializedMessage() const
{
    StarBoundingBox boundingBox = getBoundingBox();

    const CoordinateNumericType width = boundingBox.size[0];
    const CoordinateNumericType height = boundingBox.size[1];

    std::vector<std::string> serializedLines(height, std::string(width, DARK));

    for (const auto& starlight : m_starlights)
    {
        Vector2D offsetStarlightPosition{starlight.position - boundingBox.offset};

        const CoordinateNumericType posX = offsetStarlightPosition[0];
        const CoordinateNumericType posY = offsetStarlightPosition[1];

        serializedLines.at(posY).at(posX) = LIGHT;
    }

    return boost::algorithm::join(serializedLines, "\n");
}

unsigned StarAligner::getTimeUnitsElapsed() const noexcept
{
    return m_timeElapsed;
}

void StarAligner::stepOneTimeUnit()
{
    for (auto& starlight : m_starlights)
    {
        starlight.position += starlight.velocity;
    }
}

void StarAligner::rewindOneTimeUnit()
{
    for (auto& starlight : m_starlights)
    {
        starlight.position -= starlight.velocity;
    }
}

StarBoundingBox StarAligner::getBoundingBox() const
{
    auto minmaxPositionXIter = std::minmax_element(m_starlights.cbegin(), m_starlights.cend(), [](const Starlight& lhs, const Starlight& rhs)
                                                    {
                                                        return lhs.position[0] < rhs.position[0];
                                                    });

    const CoordinateNumericType minX = minmaxPositionXIter.first->position[0];
    const CoordinateNumericType maxX = minmaxPositionXIter.second->position[0];

    auto minmaxPositionYIter = std::minmax_element(m_starlights.cbegin(), m_starlights.cend(), [](const Starlight& lhs, const Starlight& rhs)
                                                    {
                                                        return lhs.position[1] < rhs.position[1];
                                                    });

    const CoordinateNumericType minY = minmaxPositionYIter.first->position[1];
    const CoordinateNumericType maxY = minmaxPositionYIter.second->position[1];

    return StarBoundingBox{Vector2D{minX, minY}, Vector2D{maxX - minX + 1, maxY - minY + 1}};
}

}
}
}
