#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <unordered_map>
#include <array>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day21
{

struct MultiverseGameState
{
    MultiverseGameState(uint64_t numUniverses, int score, int position);

    uint64_t numUniverses;
    int score;
    int position;
};

class DiracDicePlayer
{
public:
    DiracDicePlayer(int startingPosition);

    void simulateSingleTurn(uint64_t universeScalingFactorFromOtherPlayer);

    uint64_t getUniverseScalingFactor() const;
    uint64_t getTotalNumUniversesWherePlayerWon() const;

private:
    std::vector<MultiverseGameState> m_multiverseGameStates;

    uint64_t m_numUniversesWherePlayerWon = 0;

    static std::unordered_map<int, unsigned> getDiceRollToNumUniverses();
};

class DiracDiceGameSimulator
{
public:
    DiracDiceGameSimulator(int playerOneInitialPosition, int playerTwoInitialPosition);

    void play();

    uint64_t getNumUniversesWithMoreWins() const;

private:
    std::array<DiracDicePlayer, 2> m_players;
    int m_currentPlayerIndex = 0;

    DiracDicePlayer& getCurrentPlayer();
    void endTurn();
};

}
}
}
