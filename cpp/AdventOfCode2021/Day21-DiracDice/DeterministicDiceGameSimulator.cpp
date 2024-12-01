#include "DeterministicDiceGameSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

unsigned NUM_DICE = 3;
unsigned NUM_SPACES = 10;
unsigned WINNING_SCORE_THRESHOLD_PART_ONE = 1000;
unsigned DETERMINISTIC_DIE_NUM_SIDES = 100;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day21
{

DeterministicDiceGameSimulator::DeterministicDiceGameSimulator(int playerOneInitialPosition, int playerTwoInitialPosition)
    : m_playerPositions{playerOneInitialPosition, playerTwoInitialPosition}
{

}

void DeterministicDiceGameSimulator::play()
{
    while (true)
    {
        moveCurrentPlayer();

        if (hasCurrentPlayerWon())
        {
            return;
        }

        endTurn();
    }
}

int DeterministicDiceGameSimulator::getLosingPlayerScore() const
{
    return std::min(m_playerScores.front(), m_playerScores.back());
}

int DeterministicDiceGameSimulator::getNumDiceRolls() const
{
    return m_numDiceRolls;
}

int DeterministicDiceGameSimulator::rollDice()
{
    int diceRollSum = 0;

    for (unsigned die = 0; die < NUM_DICE; ++die)
    {
        ++m_numDiceRolls;
        diceRollSum += m_deterministicDieValue;
        ++m_deterministicDieValue;
        m_deterministicDieValue = ((m_deterministicDieValue - 1) % DETERMINISTIC_DIE_NUM_SIDES) + 1;
    }

    return diceRollSum;
}

void DeterministicDiceGameSimulator::moveCurrentPlayer()
{
    int& currentPlayerPosition = getCurrentPlayerPosition();
    currentPlayerPosition += rollDice();
    currentPlayerPosition = ((currentPlayerPosition - 1) % NUM_SPACES) + 1;

    getCurrentPlayerScore() += currentPlayerPosition;
}

void DeterministicDiceGameSimulator::endTurn()
{
    m_currentPlayerIndex = 1 - m_currentPlayerIndex;
}

int& DeterministicDiceGameSimulator::getCurrentPlayerPosition()
{
    return m_playerPositions.at(m_currentPlayerIndex);
}

int& DeterministicDiceGameSimulator::getCurrentPlayerScore()
{
    return const_cast<int&>(const_cast<const DeterministicDiceGameSimulator&>(*this).getCurrentPlayerScore());
}

bool DeterministicDiceGameSimulator::hasCurrentPlayerWon() const
{
    return getCurrentPlayerScore() >= WINNING_SCORE_THRESHOLD_PART_ONE;
}

const int& DeterministicDiceGameSimulator::getCurrentPlayerScore() const
{
    return m_playerScores.at(m_currentPlayerIndex);
}

}
}
}
