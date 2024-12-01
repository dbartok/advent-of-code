#include "ContraptionAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char MAIN_DIAGONAL_MIRROR = '\\';
const char SECONDARY_DIAGONAL_MIRROR = '/';
const char VERTICAL_SPLITTER = '|';
const char HORIZONTAL_SPLITTER = '-';

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day16
{

ContraptionAnalyzer::ContraptionAnalyzer(const std::vector<std::string>& map)
    : m_map{std::move(map)}
{

}

void ContraptionAnalyzer::shootBeamFrom(const BeamHead& beamHead)
{
    m_beamHeads.push_back(beamHead);

    while (!m_beamHeads.empty())
    {
        processAllBeamHeads();
    }
}

int ContraptionAnalyzer::getNumEnergizedTiles() const
{
    std::unordered_set<Coordinates, boost::hash<Coordinates>> uniqueEnergizedTiles;

    for (const auto& beamHead : m_visited)
    {
        uniqueEnergizedTiles.insert(beamHead.position);
    }

    return uniqueEnergizedTiles.size();
}

void ContraptionAnalyzer::processAllBeamHeads()
{
    std::vector<BeamHead> allNewBeamHeads;

    for (const auto& currentBeamHead : m_beamHeads)
    {
        bool wasInserted = m_visited.insert(currentBeamHead).second;
        if (!wasInserted)
        {
            continue;
        }

        std::vector<BeamHead> newBeamHeads = getNewBeamHeadsFor(currentBeamHead);
        allNewBeamHeads.insert(allNewBeamHeads.end(), std::make_move_iterator(newBeamHeads.begin()), std::make_move_iterator(newBeamHeads.end()));
    }

    m_beamHeads = allNewBeamHeads;
}

std::vector<BeamHead> ContraptionAnalyzer::getNewBeamHeadsFor(const BeamHead& currentBeamHead) const
{
    const char tileAtCurrentPosition = m_map.at(currentBeamHead.position.second).at(currentBeamHead.position.first);

    std::vector<Coordinates> newDirections = getDirectionsForTile(tileAtCurrentPosition, currentBeamHead.direction);

    std::vector<BeamHead> newBeamHeads;
    for (const auto& newDirection : newDirections)
    {
        const Coordinates newPosition{currentBeamHead.position.first + newDirection.first, currentBeamHead.position.second + newDirection.second};

        if (newPosition.first >= 0 && newPosition.second >= 0 && newPosition.first < m_map.front().size() && newPosition.second < m_map.size())
        {
            newBeamHeads.emplace_back(newPosition, newDirection);
        }
    }
    return newBeamHeads;
}

std::vector<Coordinates> ContraptionAnalyzer::getDirectionsForTile(char tile, const Coordinates& currentDirection)
{
    switch (tile)
    {
        case MAIN_DIAGONAL_MIRROR:
            return getDirectionsForMainDiagonalMirror(currentDirection);
            break;
        case SECONDARY_DIAGONAL_MIRROR:
            return getDirectionsForSecondaryDiagonalMirror(currentDirection);
            break;
        case VERTICAL_SPLITTER:
            return getDirectionsForVerticalSplitter(currentDirection);
            break;
        case HORIZONTAL_SPLITTER:
            return getDirectionsForHorizontalSplitter(currentDirection);
            break;
        default:
            return {currentDirection};
            break;
    }
}

std::vector<Coordinates> ContraptionAnalyzer::getDirectionsForMainDiagonalMirror(const Coordinates& currentDirection)
{
    if (currentDirection == LEFT)
    {
        return {UP};
    }
    else if (currentDirection == UP)
    {
        return {LEFT};
    }
    else if (currentDirection == RIGHT)
    {
        return {DOWN};
    }
    else if (currentDirection == DOWN)
    {
        return {RIGHT};
    }

    throw std::runtime_error("Invalid direction");
}

std::vector<Coordinates> ContraptionAnalyzer::getDirectionsForSecondaryDiagonalMirror(const Coordinates& currentDirection)
{
    if (currentDirection == LEFT)
    {
        return {DOWN};
    }
    else if (currentDirection == DOWN)
    {
        return {LEFT};
    }
    else if (currentDirection == RIGHT)
    {
        return {UP};
    }
    else if (currentDirection == UP)
    {
        return {RIGHT};
    }

    throw std::runtime_error("Invalid direction");
}

std::vector<Coordinates> ContraptionAnalyzer::getDirectionsForVerticalSplitter(const Coordinates& currentDirection)
{
    if (currentDirection == LEFT || currentDirection == RIGHT)
    {
        return {UP, DOWN};
    }
    else
    {
        return {currentDirection};
    }
}

std::vector<Coordinates> ContraptionAnalyzer::getDirectionsForHorizontalSplitter(const Coordinates& currentDirection)
{
    if (currentDirection == UP || currentDirection == DOWN)
    {
        return {LEFT, RIGHT};
    }
    else
    {
        return {currentDirection};
    }
}

}
}
}
