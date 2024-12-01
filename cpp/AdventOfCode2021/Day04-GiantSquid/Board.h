#pragma once

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

using NumberTable = std::vector<std::vector<int>>;

class Board
{
public:
    Board(NumberTable numberTable);

    void markNumber(int number);

    bool hasWon() const;
    bool hasJustWon() const;
    int getScore() const;

private:
    NumberTable m_numberTable;
    std::vector<int> m_markedNumbers;

    bool m_hasWon = false;
    bool m_hasJustWon = false;

    bool isAnyRowCompleted() const;
    bool isAnyColumnCompleted() const;
    bool isRowCompleted(int rowIndex) const;
    bool isColumnCompleted(int columnIndex) const;
    bool isMarked(int number) const;
};

}
}
}
