#include "Day09-MarbleMania.h"

#include "MarbleGame.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/lexical_cast.hpp>

#include <regex>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const unsigned LONGER_GAME_MULTIPLYING_FACTOR = 100;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day09
{

MarbleGame parseMarbleGame(const std::string& gameDescriptionLine, bool longerGame = false)
{
    std::regex numbersRegex("([0-9]+)");
    std::smatch matchResults;

    std::regex_search(gameDescriptionLine, matchResults, numbersRegex);
    const unsigned numPlayers = boost::lexical_cast<unsigned>(matchResults[1]);

    std::string suffix = matchResults.suffix();
    std::regex_search(suffix, matchResults, numbersRegex);
    unsigned lastMarbleScore = boost::lexical_cast<unsigned>(matchResults[1]);

    if (longerGame)
    {
        lastMarbleScore *= LONGER_GAME_MULTIPLYING_FACTOR;
    }

    MarbleGame marbleGame{numPlayers, lastMarbleScore};

    return marbleGame;
}

unsigned winningElfsScore(const std::string& gameDescriptionLine)
{
    MarbleGame marbleGame = parseMarbleGame(gameDescriptionLine);

    marbleGame.play();

    return marbleGame.getWinningElfsScore();
}

unsigned winningElfsScoreLongerGame(const std::string& gameDescriptionLine)
{
    MarbleGame marbleGame = parseMarbleGame(gameDescriptionLine, true);

    marbleGame.play();

    return marbleGame.getWinningElfsScore();
}

}
}
}
