#include "Day04-GiantSquid.h"

#include "BingoSubsystem.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day04
{

using TextSection = std::vector<std::string>;

Board parseBoardTextSection(const TextSection& boardTextSection)
{
    NumberTable numberTable;

    for (const auto& line : boardTextSection)
    {
        std::vector<int> numbers;
        AdventOfCode::Utils::splitStringIntoTypedVector(line, numbers);
        numberTable.push_back(std::move(numbers));
    }

    return Board{std::move(numberTable)};
}

std::vector<Board> parseBoardTextSections(const std::vector<TextSection>& boardTextSections)
{
    std::vector<Board> boards;

    for (const auto& boardTextSection : boardTextSections)
    {
        auto board = parseBoardTextSection(boardTextSection);
        boards.push_back(std::move(board));
    }

    return boards;
}

BingoSubsystem parseBingoSubsystemInputLines(const std::vector<std::string>& bingoSubsystemInputLines)
{
    std::vector<TextSection> bingoSubsystemInputTextSections;
    boost::split(bingoSubsystemInputTextSections, bingoSubsystemInputLines, [](const auto& elem) { return elem.empty(); });

    std::vector<int> numbersDrawn;
    AdventOfCode::Utils::splitStringIntoTypedVector(bingoSubsystemInputTextSections.at(0).at(0), numbersDrawn, ',');

    std::vector<TextSection> boardTextSections(std::next(bingoSubsystemInputTextSections.cbegin()), bingoSubsystemInputTextSections.cend());
    std::vector<Board> boards = parseBoardTextSections(boardTextSections);

    return BingoSubsystem{std::move(numbersDrawn), std::move(boards)};
}

int winningBoardFinalScore(const std::vector<std::string>& bingoSubsystemInputLines)
{
    BingoSubsystem bingoSubsystem = parseBingoSubsystemInputLines(bingoSubsystemInputLines);
    bingoSubsystem.playUntilFirstWinner();
    return bingoSubsystem.getLatestToWinBoardScore();
}

int lastToWinBoardFinalScore(const std::vector<std::string>& bingoSubsystemInputLines)
{
    BingoSubsystem bingoSubsystem = parseBingoSubsystemInputLines(bingoSubsystemInputLines);
    bingoSubsystem.playUntilLastWinner();
    return bingoSubsystem.getLatestToWinBoardScore();
}

}
}
}