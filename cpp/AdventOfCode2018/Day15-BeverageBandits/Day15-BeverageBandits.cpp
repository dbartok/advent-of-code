#include "Day15-BeverageBandits.h"

#include "GameManager.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const int DEFAULT_ATTACK_POWER = 3;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day15
{

GameManager parseGameManager(const std::vector<std::string>& mapLines, int elfAttackPower = DEFAULT_ATTACK_POWER)
{
    WallGrid wallGrid;
    CoordinatesToUnit coordinatesToUnit;

    for (size_t j = 0; j < mapLines.size(); ++j)
    {
        WallsGridLine wallGridLine;
        for (size_t i = 0; i < mapLines[j].size(); ++i)
        {
            const char field = mapLines[j][i];
            wallGridLine.push_back(field == '#');

            if (field == 'E' || field == 'G')
            {
                const bool isElf = (field == 'E');

                Faction faction = isElf ? Faction::ELF : Faction::GOBLIN;
                Coordinates coordinates{j, i};
                int attackPower = isElf ? elfAttackPower : DEFAULT_ATTACK_POWER;

                UnitSharedPtr unitSharedPtr = std::make_shared<Unit>(faction, coordinates, attackPower);

                coordinatesToUnit.emplace(std::move(coordinates), std::move(unitSharedPtr));
            }
        }
        wallGrid.push_back(std::move(wallGridLine));
    }

    return GameManager{std::move(wallGrid), std::move(coordinatesToUnit)};
}

unsigned outcomeOfCombat(const std::vector<std::string>& mapLines)
{
    GameManager gameManager = parseGameManager(mapLines);

    gameManager.play();

    return gameManager.getNumTurnsElapsed() * gameManager.getTotalHitPointsRemaining();
}

unsigned outcomeOfCombatIfElvesBarelyWin(const std::vector<std::string>& mapLines)
{
    unsigned elfAttackPower = DEFAULT_ATTACK_POWER;

    while (true)
    {
        ++elfAttackPower;
        GameManager gameManager = parseGameManager(mapLines, elfAttackPower);

        const unsigned numTotalElves = gameManager.getNumElvesAlive();

        gameManager.play();

        if (gameManager.getNumElvesAlive() == numTotalElves)
        {
            return gameManager.getNumTurnsElapsed() * gameManager.getTotalHitPointsRemaining();
        }
    }
}

}
}
}
