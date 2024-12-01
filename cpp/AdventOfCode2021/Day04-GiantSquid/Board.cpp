#include "Board.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <algorithm>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day04
{

Board::Board(NumberTable numberTable)
    : m_numberTable(std::move(numberTable))
{

}

void Board::markNumber(int number)
{
    m_markedNumbers.push_back(number);
    if (!m_hasWon)
    {
        m_hasWon = isAnyRowCompleted() || isAnyColumnCompleted();
        m_hasJustWon = m_hasWon;
    }
    else
    {
        m_hasJustWon = false;
    }
}

bool Board::hasWon() const
{
    return m_hasWon;
}

bool Board::hasJustWon() const
{
    return m_hasJustWon;
}

int Board::getScore() const
{
    int sumOfUnmarkedNumbers = std::accumulate(m_numberTable.cbegin(), m_numberTable.cend(), 0, [this](const auto& acc, const auto& row)
                                               {
                                                   return acc + std::accumulate(row.cbegin(), row.cend(), 0, [this](const auto& acc, auto number)
                                                                                {
                                                                                    if (!this->isMarked(number))
                                                                                    {
                                                                                        return acc + number;
                                                                                    }

                                                                                    return acc;
                                                                                });
                                               });

    return sumOfUnmarkedNumbers * m_markedNumbers.back();
}

bool Board::isAnyRowCompleted() const
{
    for (size_t j = 0; j < m_numberTable.size(); ++j)
    {
        if (isRowCompleted(j))
        {
            return true;
        }
    }

    return false;
}

bool Board::isAnyColumnCompleted() const
{
    for (size_t i = 0; i < m_numberTable.at(0).size(); ++i)
    {
        if (isColumnCompleted(i))
        {
            return true;
        }
    }

    return false;
}

bool Board::isRowCompleted(int rowIndex) const
{
    for (size_t i = 0; i < m_numberTable.at(0).size(); ++i)
    {
        if (!isMarked(m_numberTable.at(rowIndex).at(i)))
        {
            return false;
        }
    }

    return true;
}


bool Board::isColumnCompleted(int columnIndex) const
{
    for (size_t j = 0; j < m_numberTable.size(); ++j)
    {
        if (!isMarked(m_numberTable.at(j).at(columnIndex)))
        {
            return false;
        }
    }

    return true;
}

bool Board::isMarked(int number) const
{
    return std::find(m_markedNumbers.cbegin(), m_markedNumbers.cend(), number) != m_markedNumbers.cend();
}

}
}
}
