#include "DiracDiceGameSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

unsigned NUM_DICE = 3;
unsigned NUM_SPACES = 10;
unsigned WINNING_SCORE_THRESHOLD_PART_TWO = 21;
unsigned DIRAC_DIE_NUM_SIDES = 3;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day21
{

MultiverseGameState::MultiverseGameState(uint64_t numUniverses, int score, int position)
    : numUniverses{numUniverses}
    , score{score}
    , position{position}
{

}

DiracDicePlayer::DiracDicePlayer(int startingPosition)
{
    m_multiverseGameStates.emplace_back(1, 0, startingPosition);
}

void DiracDicePlayer::simulateSingleTurn(uint64_t universeScalingFactorFromOtherPlayer)
{
    std::vector<MultiverseGameState> newMultiverseGameStates;

    for (const auto& diceRollAndNumUniverses : getDiceRollToNumUniverses())
    {
        for (const auto& multiverseGameState : m_multiverseGameStates)
        {
            MultiverseGameState newGameState{multiverseGameState};
            newGameState.numUniverses *= diceRollAndNumUniverses.second;
            newGameState.position += diceRollAndNumUniverses.first;
            newGameState.position = ((newGameState.position - 1) % NUM_SPACES) + 1;
            newGameState.score += newGameState.position;

            if (newGameState.score >= WINNING_SCORE_THRESHOLD_PART_TWO)
            {
                m_numUniversesWherePlayerWon += newGameState.numUniverses * universeScalingFactorFromOtherPlayer;
            }
            else
            {
                newMultiverseGameStates.push_back(std::move(newGameState));
            }
        }
    }

    m_multiverseGameStates = newMultiverseGameStates;
}

uint64_t DiracDicePlayer::getUniverseScalingFactor() const
{
    return std::accumulate(m_multiverseGameStates.cbegin(), m_multiverseGameStates.cend(), 0ull, [](const auto& acc, const auto& multiverseGameState)
                            {
                                return acc + multiverseGameState.numUniverses;
                            });
}

uint64_t DiracDicePlayer::getTotalNumUniversesWherePlayerWon() const
{
    return m_numUniversesWherePlayerWon;
}

std::unordered_map<int, unsigned> DiracDicePlayer::getDiceRollToNumUniverses()
{
    std::unordered_map<int, unsigned> diceRollToNumUniverses{{0, 1}};

    for (unsigned die = 0; die < NUM_DICE; ++die)
    {
        std::unordered_map<int, unsigned> newDiceRollToNumUniverses;

        for (unsigned side = 1; side <= DIRAC_DIE_NUM_SIDES; ++side)
        {
            for (const auto& diceRollAndNumUniverses : diceRollToNumUniverses)
            {
                newDiceRollToNumUniverses[diceRollAndNumUniverses.first + side] += diceRollAndNumUniverses.second;
            }
        }

        diceRollToNumUniverses = newDiceRollToNumUniverses;
    }

    return diceRollToNumUniverses;
}

DiracDiceGameSimulator::DiracDiceGameSimulator(int playerOneInitialPosition, int playerTwoInitialPosition)
    : m_players{DiracDicePlayer{std::move(playerOneInitialPosition)}, DiracDicePlayer{std::move(playerTwoInitialPosition)}}
{

}

void DiracDiceGameSimulator::play()
{
    uint64_t universeScalingFactorFromOtherPlayer = 1;
    while (universeScalingFactorFromOtherPlayer != 0)
    {
        DiracDicePlayer& currentPlayer = getCurrentPlayer();
        currentPlayer.simulateSingleTurn(universeScalingFactorFromOtherPlayer);
        universeScalingFactorFromOtherPlayer = currentPlayer.getUniverseScalingFactor();
        endTurn();
    }
}

uint64_t DiracDiceGameSimulator::getNumUniversesWithMoreWins() const
{
    return std::max(m_players.front().getTotalNumUniversesWherePlayerWon(), m_players.back().getTotalNumUniversesWherePlayerWon());
}

DiracDicePlayer& DiracDiceGameSimulator::getCurrentPlayer()
{
    return m_players.at(m_currentPlayerIndex);
}

void DiracDiceGameSimulator::endTurn()
{
    m_currentPlayerIndex = 1 - m_currentPlayerIndex;
}

}
}
}
