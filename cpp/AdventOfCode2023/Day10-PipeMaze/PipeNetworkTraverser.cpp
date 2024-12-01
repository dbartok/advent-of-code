#include "PipeNetworkTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char VERTICAL_PIPE = '|';
const char HORIZONTAL_PIPE = '-';
const char NORTH_EAST_BEND = 'L';
const char NORTH_WEST_BEND = 'J';
const char SOUTH_WEST_BEND = '7';
const char SOUTH_EAST_BEND = 'F';
const char GROUND = '.';
const char STARTING_POSITION = 'S';

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day10
{

PipeNetworkTraverser::PipeNetworkTraverser(std::vector<std::string> pipeNetwork)
    : m_pipeNetwork{std::move(pipeNetwork)}
    , m_height{m_pipeNetwork.size()}
    , m_width{m_pipeNetwork.at(0).size()}
{
    initializePipeTypeToInwardsFlowMapping();
    findStartPosition();
}

void PipeNetworkTraverser::traverseMainLoop()
{
    const std::vector<Vector2D> validStartingDirections = getValidDirectionsFrom(m_start);
    const Vector2D startingDirection = validStartingDirections.front();
    m_mainLoopTiles.insert(m_start);

    Vector2D currentCoordinates = m_start;
    Vector2D currentDirection = startingDirection;

    // Go through main loop until tile before start
    while (currentCoordinates + currentDirection != m_start)
    {
        const Vector2D nextCoordinatesWithOneFlow = getStepResultIncludingOneFlow(currentCoordinates, currentDirection).get();

        currentCoordinates += currentDirection;
        currentDirection = nextCoordinatesWithOneFlow - currentCoordinates;

        m_mainLoopTiles.insert(currentCoordinates);
    }

    // Fill in start tile
    for (const auto& pipeTypeAndInwardsFlow : m_pipeTypeToInwardsFlow)
    {
        tileAt(m_start) = pipeTypeAndInwardsFlow.first;
        const boost::optional<Vector2D> maybeNextCoordinatesWithOneFlow = getStepResultIncludingOneFlow(currentCoordinates, currentDirection);
        if (maybeNextCoordinatesWithOneFlow.has_value() && maybeNextCoordinatesWithOneFlow.get() == m_start + startingDirection)
        {
            break;
        }
    }

    if (tileAt(m_start) == STARTING_POSITION)
    {
        throw std::runtime_error("Unable to fill in start tile");
    }
}

int PipeNetworkTraverser::getMainLoopLength() const
{
    return m_mainLoopTiles.size();
}

int PipeNetworkTraverser::getNumTilesEnclosedByMainLoop() const
{
    int numTilesEnclosedByMainLoop = 0;

    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            if (isTileEnclosedByMainLoop({i, j}))
            {
                ++numTilesEnclosedByMainLoop;
            }
        }
    }

    return numTilesEnclosedByMainLoop;
}

void PipeNetworkTraverser::initializePipeTypeToInwardsFlowMapping()
{
    m_pipeTypeToInwardsFlow.emplace(VERTICAL_PIPE, std::make_pair(Vector2D{0, 1}, Vector2D{0, -1}));
    m_pipeTypeToInwardsFlow.emplace(HORIZONTAL_PIPE, std::make_pair(Vector2D{1, 0}, Vector2D{-1, 0}));
    m_pipeTypeToInwardsFlow.emplace(NORTH_EAST_BEND, std::make_pair(Vector2D{0, 1}, Vector2D{-1, 0}));
    m_pipeTypeToInwardsFlow.emplace(NORTH_WEST_BEND, std::make_pair(Vector2D{0, 1}, Vector2D{1, 0}));
    m_pipeTypeToInwardsFlow.emplace(SOUTH_EAST_BEND, std::make_pair(Vector2D{0, -1}, Vector2D{-1, 0}));
    m_pipeTypeToInwardsFlow.emplace(SOUTH_WEST_BEND, std::make_pair(Vector2D{0, -1}, Vector2D{1, 0}));
}

void PipeNetworkTraverser::findStartPosition()
{
    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            if (tileAt({i, j}) == STARTING_POSITION)
            {
                m_start = {i, j};
                return;
            }
        }
    }
}

std::vector<Vector2D> PipeNetworkTraverser::getValidDirectionsFrom(const Vector2D& origin) const
{
    std::vector<Vector2D> directionCandidates = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::vector<Vector2D> validDirections;
    for (const auto& directionCandidate : directionCandidates)
    {
        Vector2D neighborTileCoordinates = directionCandidate + origin;
        if (!isInbounds(neighborTileCoordinates))
        {
            continue;
        }

        boost::optional<Vector2D> stepResult = getStepResultIncludingOneFlow(origin, directionCandidate);
        if (stepResult)
        {
            validDirections.push_back(directionCandidate);
        }
    }
    return validDirections;
}

boost::optional<Vector2D> PipeNetworkTraverser::getStepResultIncludingOneFlow(const Vector2D& originTileCoordinates, const Vector2D& direction) const
{
    const Vector2D neighborTileCoordinates = originTileCoordinates + direction;
    const char neighborTile = tileAt(neighborTileCoordinates);

    if (neighborTile == GROUND)
    {
        return boost::none;
    }

    const Flow& neighborFlow = m_pipeTypeToInwardsFlow.at(neighborTile);

    if (direction == neighborFlow.first)
    {
        return neighborTileCoordinates + (-1 * neighborFlow.second);
    }
    else if (direction == neighborFlow.second)
    {
        return neighborTileCoordinates + (-1 * neighborFlow.first);
    }
    else
    {
        return boost::none;
    }
}

bool PipeNetworkTraverser::isInbounds(const Vector2D& coordinates) const
{
    return coordinates.x() >= 0 && coordinates.y() >= 0 && coordinates.x() < m_width && coordinates.y() < m_height;
}

bool PipeNetworkTraverser::isTileEnclosedByMainLoop(const Vector2D& coordinates) const
{
    // Shoot ray towards the east and count the number of intersections with the loop
    // | simply counts as an intersection
    // In the case of corners, only L7 pairs and FJ pairs count as intersections,
    // because if the ray hits an LJ pair or F7 pair, the ray only "skirts" the loop, not crossing it.
    // Any number of - between the corners doesn't change the above.

    if (m_mainLoopTiles.count(coordinates))
    {
        return false;
    }

    int numMainLoopCrossings = 0;
    char lastOpeningCornerSeen = '\0';

    for (int i = coordinates.x() + 1; i < m_width; ++i)
    {
        const Vector2D rayPointCoordinates{i, coordinates.y()};
        if (!m_mainLoopTiles.count(rayPointCoordinates))
        {
            continue;
        }

        char tile = tileAt(rayPointCoordinates);

        if (tile == VERTICAL_PIPE)
        {
            ++numMainLoopCrossings;
        }
        else if (tile == NORTH_EAST_BEND || tile == SOUTH_EAST_BEND)
        {
            lastOpeningCornerSeen = tile;
        }
        else if (tile == NORTH_WEST_BEND && lastOpeningCornerSeen == SOUTH_EAST_BEND)
        {
            ++numMainLoopCrossings;
        }
        else if (tile == SOUTH_WEST_BEND && lastOpeningCornerSeen == NORTH_EAST_BEND)
        {
            ++numMainLoopCrossings;
        }
    }

    return numMainLoopCrossings % 2 == 1;
}

char PipeNetworkTraverser::tileAt(const Vector2D& coordinates) const
{
    return m_pipeNetwork.at(coordinates.y()).at(coordinates.x());
}

char& PipeNetworkTraverser::tileAt(const Vector2D& coordinates)
{
    return m_pipeNetwork.at(coordinates.y()).at(coordinates.x());
}

}
}
}
