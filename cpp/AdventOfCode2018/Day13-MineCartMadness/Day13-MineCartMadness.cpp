#include "Day13-MineCartMadness.h"

#include "MineManager.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day13
{

std::string coordinatesToString(const Coordinates& coordinates)
{
    return std::to_string(coordinates.first) + "," + std::to_string(coordinates.second);
}

bool isCharMineCart(char c)
{
    static const std::unordered_set<char> mineCartChars{'<', '>', '^', 'v'};

    return mineCartChars.find(c) != mineCartChars.end();
}

Orientation parseOrientation(char c)
{
    static const std::unordered_map<char, Orientation> charToOrientation =
    {
        {'<', Orientation::LEFT},
        {'>', Orientation::RIGHT},
        {'^', Orientation::UP},
        {'v', Orientation::DOWN}
    };

    return charToOrientation.at(c);
}

RailPieceSharedPtr parseRailPieceSharedPtr(char c)
{
    RailPieceSharedPtr result;

    switch (c)
    {
        case '|':
        case '-':
        case '^':
        case 'v':
        case '<':
        case '>':
            result = std::make_shared<StraightRailPiece>();
            break;

        case '\\':
            result = std::make_shared<MainDiagonalRailPiece>();
            break;

        case '/':
            result = std::make_shared<AntiDiagonalRailPiece>();
            break;

        case '+':
            result = std::make_shared<IntersectionRailPiece>();
            break;

        default:
            result = std::make_shared<EmptyRailPiece>();
    }

    return result;
}


std::list<MineCart> parseMineCarts(const std::vector<std::string>& mapLines)
{
    std::list<MineCart> mineCarts;

    for (size_t j = 0; j < mapLines.size(); ++j)
    {
        for (size_t i = 0; i < mapLines[j].size(); ++i)
        {
            const char c = mapLines[j][i];
            if (isCharMineCart(c))
            {
                const Orientation orientation = parseOrientation(c);

                MineCart mineCart{orientation, Coordinates{i, j}};
                mineCarts.push_back(std::move(mineCart));
            }
        }
    }

    return mineCarts;
}

MineMap parseMineMap(const std::vector<std::string>& mapLines)
{
    MineMap mineMap;

    for (const auto& lines : mapLines)
    {
        MineMapLine currentMineMapLine;
        for (const char c : lines)
        {
            currentMineMapLine.push_back(parseRailPieceSharedPtr(c));
        }
        mineMap.push_back(std::move(currentMineMapLine));
    }

    return mineMap;
}

MineManager parseMineManager(const std::vector<std::string>& mapLines)
{
    MineMap mineMap = parseMineMap(mapLines);
    std::list<MineCart> mineCarts = parseMineCarts(mapLines);
    return MineManager{std::move(mineMap), std::move(mineCarts)};
}

std::string positionOfFirstCollision(const std::vector<std::string>& mapLines)
{
    MineManager mineManager = parseMineManager(mapLines);

    const auto coordinatesOfFirstCollision = mineManager.coordinatesOfFirstCollision();

    return coordinatesToString(coordinatesOfFirstCollision);
}

std::string positionOfLastRemainingCart(const std::vector<std::string>& mapLines)
{
    MineManager mineManager = parseMineManager(mapLines);

    const auto coordinatesOfLastRemainingCart = mineManager.coordinatesOfLastRemainingCart();

    return coordinatesToString(coordinatesOfLastRemainingCart);
}

}
}
}
