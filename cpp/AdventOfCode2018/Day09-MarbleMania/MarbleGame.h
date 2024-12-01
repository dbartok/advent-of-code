#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <list>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day09
{

class MarbleGame
{
public:
    MarbleGame(unsigned numPlayers, unsigned lastMarbleScore);

    void play();

    unsigned getWinningElfsScore() const;

private:
    std::vector<unsigned> m_playerToScore;
    unsigned m_lastMarbleScore;

    std::list<unsigned> m_marbles;
    std::list<unsigned>::iterator m_currentMarbleIter;

    void stepCurrentMarbleIterForwards(unsigned steps);
    void stepCurrentMarbleIterBackwards(unsigned steps);
};

}
}
}
