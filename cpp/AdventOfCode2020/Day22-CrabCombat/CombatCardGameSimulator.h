#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <deque>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day22
{

using Deck = std::deque<int>;
using DeckPair = std::pair<Deck, Deck>;

enum class Player
{
    ONE,
    TWO,
};

enum class Action
{
    NONE,
    TERMINATE_GAME,
};

struct RoundResult
{
    RoundResult(Player winningPlayer, Action action = Action::NONE);

    Player winningPlayer;
    Action action;
};

class CombatCardGameSimulator
{
public:
    CombatCardGameSimulator(DeckPair startingDecks);

    Player determineWinningPlayer();

    int getPlayerScore(Player player) const;

protected:
    DeckPair m_decks;

    virtual RoundResult determineRoundResult() const;
};

class RecursiveCombatCardGameSimulator : public CombatCardGameSimulator
{
public:
    using CombatCardGameSimulator::CombatCardGameSimulator;

protected:
    RoundResult determineRoundResult() const override;

private:
    mutable std::unordered_set<DeckPair, boost::hash<DeckPair>> m_previouslySeenStates;
};

}
}
}
