#include "MarbleGame.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <cmath>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day09
{

MarbleGame::MarbleGame(unsigned numPlayers, unsigned lastMarbleScore)
    : m_playerToScore(numPlayers, 0)
    , m_lastMarbleScore{lastMarbleScore}
    , m_marbles{0}
    , m_currentMarbleIter{m_marbles.begin()}
{

}

void MarbleGame::play()
{
    unsigned currentPlayerIdx = 0;

    for (unsigned currentMarbleScore = 1; currentMarbleScore <= m_lastMarbleScore; ++currentMarbleScore)
    {
        if (currentMarbleScore % 23 == 0)
        {
            m_playerToScore.at(currentPlayerIdx) += currentMarbleScore;

            stepCurrentMarbleIterBackwards(7);
            m_playerToScore.at(currentPlayerIdx) += *m_currentMarbleIter;
            m_currentMarbleIter = m_marbles.erase(m_currentMarbleIter);
        }
        else
        {
            stepCurrentMarbleIterForwards(1);
            m_currentMarbleIter = m_marbles.insert(std::next(m_currentMarbleIter), currentMarbleScore);
        }

        currentPlayerIdx = (currentPlayerIdx + 1) % m_playerToScore.size();
    }
}

unsigned MarbleGame::getWinningElfsScore() const
{
    auto maxIter = std::max_element(m_playerToScore.cbegin(), m_playerToScore.cend());
    return *maxIter;
}

void MarbleGame::stepCurrentMarbleIterForwards(unsigned steps)
{
    for (unsigned i = 0; i < steps; ++i)
    {
        ++m_currentMarbleIter;
        if (m_currentMarbleIter == m_marbles.end())
        {
            m_currentMarbleIter = m_marbles.begin();
        }
    }
}

void MarbleGame::stepCurrentMarbleIterBackwards(unsigned steps)
{
    for (unsigned i = 0; i < steps; ++i)
    {
        if (m_currentMarbleIter == m_marbles.begin())
        {
            m_currentMarbleIter = m_marbles.end();
        }
        --m_currentMarbleIter;
    }
}

}
}
}
