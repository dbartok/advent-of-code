#include "Day02-CubeConundrum.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>

#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day02
{

struct CubeSubset
{
    int red = 0;
    int green = 0;
    int blue = 0;

    bool operator<=(const CubeSubset& other) const
    {
        return this->red <= other.red&& this->green <= other.green&& this->blue <= other.blue;
    }

    CubeSubset operator|(const CubeSubset& other) const
    {
        return CubeSubset
        {
            std::max(this->red, other.red),
            std::max(this->green, other.green),
            std::max(this->blue, other.blue)
        };
    }

    int getPower() const
    {
        return red * green * blue;
    }
};

const CubeSubset PRESET_BAG = CubeSubset{12, 13, 14};

using Game = std::vector<CubeSubset>;

CubeSubset parseCubesRevealedString(const std::string& cubesRevealedString)
{
    std::vector<std::string> cubesRevealedTokens;
    boost::split(cubesRevealedTokens, cubesRevealedString, boost::is_any_of(", "), boost::token_compress_on);

    CubeSubset cubeSubset;

    for (size_t i = 1; i < cubesRevealedTokens.size(); i+=2)
    {
        const int quantity = std::stoi(cubesRevealedTokens.at(i - 1));
        const std::string color = cubesRevealedTokens.at(i);

        if (color == "red")
        {
            cubeSubset.red = quantity;
        }
        else if (color == "green")
        {
            cubeSubset.green = quantity;
        }
        else if (color == "blue")
        {
            cubeSubset.blue = quantity;
        }
    }

    return cubeSubset;
}

Game parseGameRecordLine(const std::string& gameRecordLine)
{
    std::vector<std::string> cubesRevealedStrings;
    boost::split(cubesRevealedStrings, gameRecordLine, boost::is_any_of(";:"));

    Game game;

    for (size_t i = 1; i < cubesRevealedStrings.size(); ++i)
    {
        auto cubesRevealedString = std::move(cubesRevealedStrings.at(i));
        boost::trim(cubesRevealedString);
        CubeSubset cubesRevealed = parseCubesRevealedString(cubesRevealedString);
        game.push_back(std::move(cubesRevealed));
    }

    return game;
}

std::vector<Game> parseGameRecordLines(const std::vector<std::string>& gameRecordLines)
{
    std::vector<Game> games;

    for (const auto& gameRecordLine : gameRecordLines)
    {
        Game game = parseGameRecordLine(gameRecordLine);
        games.push_back(std::move(game));
    }

    return games;
}

bool isValidSubsetOfPresetBag(const CubeSubset& cubeSubset)
{
    return cubeSubset <= PRESET_BAG;
}

bool isGamePossibleWithPresetBag(const Game& game)
{
    return std::all_of(game.cbegin(), game.cend(), [](const auto& cubeSubset)
                       {
                           return isValidSubsetOfPresetBag(cubeSubset);
                       });
}


int sumOfIDsOfPossibleGames(const std::vector<std::string>& gameRecordLines)
{
    const std::vector<Game> games = parseGameRecordLines(gameRecordLines);

    int sum = 0;

    for (int gameIndex = 0; gameIndex < games.size(); ++gameIndex)
    {
        if (isGamePossibleWithPresetBag(games.at(gameIndex)))
        {
            const int gameID = gameIndex + 1;
            sum += gameID;
        }
    }

    return sum;
}

CubeSubset getMinimalCubeSubsetToMakeGamePossible(const Game& game)
{
    return std::accumulate(game.cbegin(), game.cend(), CubeSubset{}, [](const CubeSubset& acc, const auto& cubeSubset)
                           {
                               return acc | cubeSubset;
                           });
}

int sumOfPowerOfMinimalSets(const std::vector<std::string>& gameRecordLines)
{
    const std::vector<Game> games = parseGameRecordLines(gameRecordLines);

    return std::accumulate(games.cbegin(), games.cend(), 0, [](int acc, const auto& game)
                           {
                               CubeSubset minimalSubset = getMinimalCubeSubsetToMakeGamePossible(game);
                               return acc + minimalSubset.getPower();
                           });
}

}
}
}