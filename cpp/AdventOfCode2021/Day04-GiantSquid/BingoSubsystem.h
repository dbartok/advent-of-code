#pragma once

#include "Board.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day04
{

class BingoSubsystem
{
public:
    BingoSubsystem(std::vector<int> numbersDrawn, std::vector<Board> boards);

    void playUntilFirstWinner();
    void playUntilLastWinner();
    int getLatestToWinBoardScore() const;

private:
    std::vector<int> m_numbersDrawn;
    std::vector<Board> m_boards;

    void processNumberDrawn(int number);

    bool hasAnyBoardWon() const;
    bool haveAllBoardsWon() const;
};

}
}
}
