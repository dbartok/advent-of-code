#include "Day21-DiracDice.h"

#include "DeterministicDiceGameSimulator.h"
#include "DiracDiceGameSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day21
{

int parseStartingPositionLine(const std::string& startingPositionLines)
{
    return startingPositionLines.back() - '0';
}

std::pair<int, int> parseStartingPositionLines(const std::vector<std::string>& startingPositionLines)
{
    const int playerOneStartingPosition = parseStartingPositionLine(startingPositionLines.front());
    const int playerTwoStartingPosition = parseStartingPositionLine(startingPositionLines.back());

    return {playerOneStartingPosition, playerTwoStartingPosition};
}

int losingPlayerScoreTimesNumDiceRollsDeterministicDice(const std::vector<std::string>& startingPositionLines)
{
    const std::pair<int, int> startingPositions = parseStartingPositionLines(startingPositionLines);
    DeterministicDiceGameSimulator simulator{startingPositions.first, startingPositions.second};
    simulator.play();
    return simulator.getLosingPlayerScore() * simulator.getNumDiceRolls();
}

uint64_t numUniversesWithMoreWins(const std::vector<std::string>& startingPositionLines)
{
    const std::pair<int, int> startingPositions = parseStartingPositionLines(startingPositionLines);
    DiracDiceGameSimulator simulator{startingPositions.first, startingPositions.second};
    simulator.play();
    return simulator.getNumUniversesWithMoreWins();
}

}
}
}