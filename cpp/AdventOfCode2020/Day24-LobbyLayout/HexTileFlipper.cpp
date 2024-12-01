#include "HexTileFlipper.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day24
{

HexTileFlipper::HexTileFlipper(std::vector<std::string> tilePaths)
    : m_tilePaths{std::move(tilePaths)}
{
    m_directionToUnitVector =
    {
        {"e", {1, 0}},
        {"w", {-1, 0}},
        {"nw", {0, -1}},
        {"ne", {1, -1}},
        {"sw", {-1, 1}},
        {"se", {0, 1}},
    };
}

void HexTileFlipper::setupInitialState()
{
    for (const auto& tilePath : m_tilePaths)
    {
        flipTileAtPath(tilePath);
    }
}

void HexTileFlipper::simulateMultipleDays(unsigned numDaysToSimulate)
{
    for (unsigned i = 0; i < numDaysToSimulate; ++i)
    {
        simulateSingleDay();
    }
}

int HexTileFlipper::getNumBlackTiles() const
{
    return m_blackTileCoordinatesSet.size();
}

void HexTileFlipper::flipTileAtPath(const std::string& tilePath)
{
    Vector2D tileCoordinates = getTileCoordinatesForPath(tilePath);
    flipTileAtCoordinates(tileCoordinates);
}

void HexTileFlipper::flipTileAtCoordinates(const Vector2D& coordinates)
{
    const auto insertionResult = m_blackTileCoordinatesSet.insert(coordinates);
    const bool wasInserted = insertionResult.second;
    if (!wasInserted)
    {
        const auto existingElementIterator = insertionResult.first;
        m_blackTileCoordinatesSet.erase(existingElementIterator);
    }
}

void HexTileFlipper::simulateSingleDay()
{
    std::unordered_set<Vector2D, Vector2DHash> nextRoundBlackTileCoordinatesSet;

    for (const auto& coordinates : getAllRelevantCoordinatesForNextRound())
    {
        if (isTileBlackInNextRound(coordinates))
        {
            nextRoundBlackTileCoordinatesSet.insert(coordinates);
        }
    }

    m_blackTileCoordinatesSet = nextRoundBlackTileCoordinatesSet;
}

Vector2D HexTileFlipper::getTileCoordinatesForPath(const std::string& tilePath) const
{
    Vector2D coordinates{0, 0};
    std::string direction;

    for (const auto c : tilePath)
    {
        direction += c;
        const auto findResult = m_directionToUnitVector.find(direction);
        if (findResult != m_directionToUnitVector.cend())
        {
            coordinates += findResult->second;
            direction = "";
        }
    }

    return coordinates;
}

std::unordered_set<Vector2D, Vector2DHash> HexTileFlipper::getAllRelevantCoordinatesForNextRound() const
{
    std::unordered_set<Vector2D, Vector2DHash> allRelevantCoordinatesForNextRound;

    for (const auto& blackTileCoordinates : m_blackTileCoordinatesSet)
    {
        allRelevantCoordinatesForNextRound.insert(blackTileCoordinates);

        std::vector<Vector2D> allNeighborCoordinates = getAllAdjacentTileCoordinates(blackTileCoordinates);
        for (const auto& neighborCoordinates : allNeighborCoordinates)
        {
            allRelevantCoordinatesForNextRound.insert(neighborCoordinates);
        }
    }

    return allRelevantCoordinatesForNextRound;
}

bool HexTileFlipper::isTileBlackInNextRound(const Vector2D& coordinates) const
{
    const bool isTileCurrentlyBlack = (m_blackTileCoordinatesSet.find(coordinates) != m_blackTileCoordinatesSet.cend());
    const int numAdjacentBlackTiles = getNumAdjacentBlackTiles(coordinates);

    const bool isBlackTileRemainingBlack = isTileCurrentlyBlack && (numAdjacentBlackTiles == 1 || numAdjacentBlackTiles == 2);
    const bool isWhiteTileTurningOverToBlack = !isTileCurrentlyBlack && numAdjacentBlackTiles == 2;

    return isBlackTileRemainingBlack || isWhiteTileTurningOverToBlack;
}

std::vector<Vector2D> HexTileFlipper::getAllAdjacentTileCoordinates(const Vector2D& coordinates) const
{
    std::vector<Vector2D> allAdjacentTileCoordinates;

    for (const auto& directionAndUnitVector : m_directionToUnitVector)
    {
        const auto& unitVector = directionAndUnitVector.second;
        allAdjacentTileCoordinates.push_back(coordinates + unitVector);
    }

    return allAdjacentTileCoordinates;
}

int HexTileFlipper::getNumAdjacentBlackTiles(const Vector2D& coordinates) const
{
    std::vector<Vector2D> allAdjacentTileCoordinates = getAllAdjacentTileCoordinates(coordinates);
    return std::count_if(allAdjacentTileCoordinates.cbegin(), allAdjacentTileCoordinates.cend(), [this](const auto& coords)
                            {
                                return this->m_blackTileCoordinatesSet.find(coords) != this->m_blackTileCoordinatesSet.cend();
                            });
}

}
}
}
