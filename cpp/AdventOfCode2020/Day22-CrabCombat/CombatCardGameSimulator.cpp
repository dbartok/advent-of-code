#include "CombatCardGameSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day22
{

RoundResult::RoundResult(Player winningPlayer, Action action)
    : winningPlayer{winningPlayer}
    , action(action)
{

}

CombatCardGameSimulator::CombatCardGameSimulator(DeckPair startingDecks)
    : m_decks{std::move(startingDecks)}
{

}

Player CombatCardGameSimulator::determineWinningPlayer()
{
    while (true)
    {
        RoundResult roundResult = determineRoundResult();
        if (roundResult.action == Action::TERMINATE_GAME)
        {
            return roundResult.winningPlayer;
        }

        Deck* winnerDeckThisRound = &m_decks.first;
        Deck* loserDeckThisRound = &m_decks.second;
        if (roundResult.winningPlayer != Player::ONE)
        {
            std::swap(winnerDeckThisRound, loserDeckThisRound);
        }

        winnerDeckThisRound->push_back(winnerDeckThisRound->front());
        winnerDeckThisRound->pop_front();

        winnerDeckThisRound->push_back(loserDeckThisRound->front());
        loserDeckThisRound->pop_front();
    }
}

int CombatCardGameSimulator::getPlayerScore(Player player) const
{
    const auto& deck = (player == Player::ONE ? m_decks.first : m_decks.second);
    int multiplier = 1;

    return std::accumulate(deck.crbegin(), deck.crend(), 0, [&multiplier](int acc, int card)
                            {
                                return acc + (multiplier++) * card;
                            });

}

RoundResult CombatCardGameSimulator::determineRoundResult() const
{
    if (m_decks.first.empty() || m_decks.second.empty())
    {
        return {m_decks.second.empty() ? Player::ONE : Player::TWO, Action::TERMINATE_GAME};
    }

    return m_decks.first.front() > m_decks.second.front() ? Player::ONE : Player::TWO;
}

RoundResult RecursiveCombatCardGameSimulator::determineRoundResult() const
{
    bool wasInserted = m_previouslySeenStates.insert(m_decks).second;
    if (!wasInserted)
    {
        return {Player::ONE, Action::TERMINATE_GAME};
    }

    if (m_decks.first.empty() || m_decks.second.empty())
    {
        return {m_decks.second.empty() ? Player::ONE : Player::TWO, Action::TERMINATE_GAME};
    }

    const bool areThereEnoughCardsToRecurse = m_decks.first.front() < m_decks.first.size() && m_decks.second.front() < m_decks.second.size();
    if (!areThereEnoughCardsToRecurse)
    {
        return CombatCardGameSimulator::determineRoundResult();
    }

    Deck newFirstDeck{m_decks.first.cbegin() + 1, m_decks.first.cbegin() + m_decks.first.front() + 1};
    Deck newSecondDeck{m_decks.second.cbegin() + 1, m_decks.second.cbegin() + m_decks.second.front() + 1};
    DeckPair newDeckPair{std::move(newFirstDeck), std::move(newSecondDeck)};
    RecursiveCombatCardGameSimulator recursiveSimulator{std::move(newDeckPair)};

    return recursiveSimulator.determineWinningPlayer();

}

}
}
}
