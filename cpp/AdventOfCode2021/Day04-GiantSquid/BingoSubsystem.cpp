#include "BingoSubsystem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day04
{

BingoSubsystem::BingoSubsystem(std::vector<int> numbersDrawn, std::vector<Board> boards)
    : m_numbersDrawn(numbersDrawn)
    , m_boards{std::move(boards)}
{

}

void BingoSubsystem::playUntilFirstWinner()
{
    for (auto number : m_numbersDrawn)
    {
        processNumberDrawn(number);
        if (hasAnyBoardWon())
        {
            return;
        }
    }

    throw std::runtime_error("No winning board");
}

void BingoSubsystem::playUntilLastWinner()
{
    for (auto number : m_numbersDrawn)
    {
        processNumberDrawn(number);
        if (haveAllBoardsWon())
        {
            return;
        }
    }

    throw std::runtime_error("Not all boards have won");
}

int BingoSubsystem::getLatestToWinBoardScore() const
{
    const auto lastToWinBoardIter = std::find_if(m_boards.cbegin(), m_boards.cend(), [](const auto& board)
                                                    {
                                                        return board.hasJustWon();
                                                    });

    if (lastToWinBoardIter == m_boards.cend())
    {
        throw std::runtime_error("No boards have just won");
    }

    return lastToWinBoardIter->getScore();
}

void BingoSubsystem::processNumberDrawn(int number)
{
    for (auto& board : m_boards)
    {
        board.markNumber(number);
        if (board.hasWon())
        {

        }
    }
}

bool BingoSubsystem::hasAnyBoardWon() const
{
    return std::any_of(m_boards.cbegin(), m_boards.cend(), [](const auto& board)
                        {
                            return board.hasWon();
                        });
}

bool BingoSubsystem::haveAllBoardsWon() const
{
    return std::all_of(m_boards.cbegin(), m_boards.cend(), [](const auto& board)
                        {
                            return board.hasWon();
                        });
}

}
}
}
