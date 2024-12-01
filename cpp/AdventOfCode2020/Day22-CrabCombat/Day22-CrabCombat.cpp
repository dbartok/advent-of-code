#include "Day22-CrabCombat.h"

#include "CombatCardGameSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day22
{

Deck createDeck(const std::vector<std::string>& startingDeckSection)
{
    Deck deck;

    for (auto lineIter = std::next(startingDeckSection.cbegin()); lineIter != startingDeckSection.cend(); ++lineIter)
    {
        deck.push_back(std::stoi(*lineIter));
    }

    return deck;
}

DeckPair parseStartingDecksLines(const std::vector<std::string>& startingDecksLines)
{
    std::vector<std::vector<std::string>> startingDeckSections;
    boost::split(startingDeckSections, startingDecksLines, [](const auto& line) {return line.empty(); });

    Deck deckOne = createDeck(startingDeckSections.at(0));
    Deck deckTwo = createDeck(startingDeckSections.at(1));

    return {deckOne, deckTwo};

}

int winningPlayerScore(const std::vector<std::string>& startingDecksLines)
{
    DeckPair startingDeckPair = parseStartingDecksLines(startingDecksLines);
    CombatCardGameSimulator simulator{std::move(startingDeckPair)};
    Player winningPlayer = simulator.determineWinningPlayer();
    return simulator.getPlayerScore(winningPlayer);
}

int winningPlayerScoreRecursiveCombat(const std::vector<std::string>& startingDecksLines)
{
    DeckPair startingDeckPair = parseStartingDecksLines(startingDecksLines);
    RecursiveCombatCardGameSimulator recursiveSimulator{std::move(startingDeckPair)};
    Player winningPlayer = recursiveSimulator.determineWinningPlayer();
    return recursiveSimulator.getPlayerScore(winningPlayer);
}

}
}
}
