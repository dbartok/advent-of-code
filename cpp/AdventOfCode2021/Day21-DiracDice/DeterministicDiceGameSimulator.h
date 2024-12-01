#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <array>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day21
{

class DeterministicDiceGameSimulator
{
public:
    DeterministicDiceGameSimulator(int playerOneInitialPosition, int playerTwoInitialPosition);

    void play();

    int getLosingPlayerScore() const;
    int getNumDiceRolls() const;

private:
    std::array<int, 2> m_playerPositions;
    std::array<int, 2> m_playerScores{0, 0};
    int m_currentPlayerIndex = 0;

    int m_deterministicDieValue = 1;
    unsigned m_numDiceRolls = 0;

    int rollDice();
    void moveCurrentPlayer();
    void endTurn();

    int& getCurrentPlayerPosition();
    int& getCurrentPlayerScore();

    bool hasCurrentPlayerWon() const;
    const int& getCurrentPlayerScore() const;
};

}
}
}
