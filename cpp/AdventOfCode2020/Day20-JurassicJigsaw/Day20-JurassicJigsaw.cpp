#include "Day20-JurassicJigsaw.h"

#include "ImageReassembler.h"
#include "SeaMonsterFinder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day20
{

std::vector<std::string> convertImageToStringImage(const Image& image)
{
    std::vector<std::string> result;

    for (size_t j = 0; j < image.rows(); ++j)
    {
        std::string row;
        for (size_t i = 0; i < image.cols(); ++i)
        {
            row.push_back(image(j, i) ? '#' : '.');
        }
        result.push_back(std::move(row));
    }

    return result;
}

int createTileID(const std::string& tileIDLine)
{
    const std::regex idLineRegex{R"(Tile (\d+):)"};
    std::smatch matches;
    std::regex_search(tileIDLine, matches, idLineRegex);
    if (matches.size() != 2)
    {
        throw std::runtime_error("Invalid tile ID line: " + tileIDLine);
    }
    return std::stoi(matches[1]);
}

Image createImage(const std::vector<std::string>& imageLines)
{
    Image image{imageLines.size(), imageLines.at(0).size()};

    for (size_t j = 0; j < imageLines.size(); ++j)
    {
        for (size_t i = 0; i < imageLines.size(); ++i)
        {
            image(j, i) = (imageLines[j][i] == '#');
        }
    }

    return image;
}

Tile createTile(const std::vector<std::string>& tileLines)
{
    int tileID = createTileID(tileLines.front());

    std::vector<std::string> imageLines{std::next(tileLines.cbegin()), tileLines.cend()};
    Image image = createImage(imageLines);

    return Tile{std::move(tileID), std::move(image)};
}

std::vector<Tile> createTiles(const std::vector<std::string>& cameraArrayLines)
{
    std::vector<std::vector<std::string>> tokens;
    boost::split(tokens, cameraArrayLines, [](const auto& line) {return line.empty(); });

    std::vector<Tile> tiles;

    for (const auto& tileLines : tokens)
    {
        if (!tileLines.empty())
        {
            Tile tile = createTile(tileLines);
            tiles.push_back(std::move(tile));
        }
    }

    return tiles;
}

int64_t cornerTileIDsMultiplied(const std::vector<std::string>& cameraArrayLines)
{
    std::vector<Tile> tiles = createTiles(cameraArrayLines);
    ImageReassembler imageReassembler{std::move(tiles)};
    imageReassembler.reassemble();
    return imageReassembler.getCornerTileIDsMultiplied();
}

int numWaterNotPartOfASeaMonster(const std::vector<std::string>& cameraArrayLines)
{
    std::vector<Tile> tiles = createTiles(cameraArrayLines);
    ImageReassembler imageReassembler{std::move(tiles)};
    imageReassembler.reassemble();
    std::vector<Image> allPossibleReassembledImages = imageReassembler.getAllPossibleImages();

    for (const auto& image : allPossibleReassembledImages)
    {
        std::vector<std::string> stringImage = convertImageToStringImage(image);
        SeaMonsterFinder seaMonsterFinder{std::move(stringImage)};

        int originalNumWater = seaMonsterFinder.getNumWaterFields();
        seaMonsterFinder.markSeaMonsterFields();
        int numWaterNotPartOfASeaMonster = seaMonsterFinder.getNumWaterFields();

        if (originalNumWater != numWaterNotPartOfASeaMonster)
        {
            return numWaterNotPartOfASeaMonster;
        }
    }

    throw std::runtime_error("Unable to find any sea monsters in any of the possible images");
}

}
}
}
