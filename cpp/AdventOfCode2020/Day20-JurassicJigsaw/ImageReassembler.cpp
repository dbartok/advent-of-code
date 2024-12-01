#include "ImageReassembler.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day20
{

ImageReassembler::ImageReassembler(std::vector<Tile> scrambledTiles)
    : m_scrambledTiles{std::move(scrambledTiles)}
    , m_reassembledImageLengthInTiles{static_cast<size_t>(std::sqrt(m_scrambledTiles.size()))}
    , m_reassembledTileGrid(m_reassembledImageLengthInTiles, std::vector<Tile>(m_reassembledImageLengthInTiles))
{

}

void ImageReassembler::reassemble()
{
    populateTopLeftCorner();
    populateSubsequentTiles();
    removeBorders();
}

int64_t ImageReassembler::getCornerTileIDsMultiplied() const
{
    const auto& firstRow = m_reassembledTileGrid.front();
    const auto& lastRow = m_reassembledTileGrid.back();

    return static_cast<int64_t>(firstRow.front().getID())* firstRow.back().getID()* lastRow.front().getID()* lastRow.back().getID();
}

std::vector<Image> ImageReassembler::getAllPossibleImages() const
{
    Tile combinedTile = getAllTilesCombined();
    std::vector<Tile> allPossibleTiles = combinedTile.getAllVariants();

    std::vector<Image> allPossibleImages;
    std::transform(allPossibleTiles.cbegin(), allPossibleTiles.cend(), std::back_inserter(allPossibleImages), [](const auto& tile) {return tile.getImage(); });
    return allPossibleImages;
}

void ImageReassembler::populateTopLeftCorner()
{
    Tile topLeftCorner;

    for (const auto& tile : m_scrambledTiles)
    {
        for (const auto& tileVariant : tile.getAllVariants())
        {
            if (isTileVariantTopLeftCorner(tileVariant))
            {
                topLeftCorner = tileVariant;
                break;
            }
        }
        if (topLeftCorner.isPopulated())
        {
            break;
        }
    }

    m_reassembledTileGrid.at(0).at(0) = topLeftCorner;
}

void ImageReassembler::populateSubsequentTiles()
{
    for (size_t j = 0; j < m_reassembledImageLengthInTiles; ++j)
    {
        for (size_t i = 0; i < m_reassembledImageLengthInTiles; ++i)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            populateTileAt(i, j);
        }
    }
}

void ImageReassembler::populateTileAt(size_t i, size_t j)
{
    boost::optional<std::vector<Tile>> possibleTilesFromUpwardsConstraint = getPossibleTilesFromUpwardsConstraint(i, j);
    boost::optional<std::vector<Tile>> possibleTilesFromLeftwardsConstraint = getPossibleTilesFromLeftwardsConstraint(i, j);

    Tile resolvedTile = resolveTileFromMaybeConstraints(possibleTilesFromUpwardsConstraint, possibleTilesFromLeftwardsConstraint);
    m_reassembledTileGrid.at(j).at(i) = std::move(resolvedTile);
}

void ImageReassembler::removeBorders()
{
    for (auto& row : m_reassembledTileGrid)
    {
        for (auto& tile : row)
        {
            tile.removeBorders();
        }
    }
}

bool ImageReassembler::isTileVariantTopLeftCorner(const Tile& tileVariant) const
{
    std::vector<Tile> allPossibleNeighborsToLeftwards = findAllPossibleNeighborsInDirection(tileVariant, Direction::LEFT);
    std::vector<Tile> allPossibleNeighborsToUpwards = findAllPossibleNeighborsInDirection(tileVariant, Direction::UP);

    return allPossibleNeighborsToLeftwards.empty() && allPossibleNeighborsToUpwards.empty();
}

std::vector<Tile> ImageReassembler::findAllPossibleNeighborsInDirection(const Tile& anchorTileVariant, Direction direction) const
{
    std::vector<Tile> allPossibleNeighborsInDirection;
    for (const auto& tile : m_scrambledTiles)
    {
        if (tile == anchorTileVariant)
        {
            continue;
        }

        for (const auto& tileVariant : tile.getAllVariants())
        {
            if (doesTileVariantFitAnchorInDirection(anchorTileVariant, tileVariant, direction))
            {
                allPossibleNeighborsInDirection.push_back(tileVariant);
            }
        }
    }

    return allPossibleNeighborsInDirection;
}

bool ImageReassembler::doesTileVariantFitAnchorInDirection(Tile anchorTileVariant, Tile tileVariant, Direction direction) const
{
    int numRightRotationsRequired = static_cast<int>(direction);

    while ((numRightRotationsRequired--) > 0)
    {
        anchorTileVariant.rotateRight();
        tileVariant.rotateRight();
    }

    return doesTileVariantFitAnchorToUpwards(anchorTileVariant, tileVariant);
}

bool ImageReassembler::doesTileVariantFitAnchorToUpwards(const Tile& anchorTileVariant, const Tile& tileVariant) const
{
    const auto& anchorTileVariantImage = anchorTileVariant.getImage();
    const auto& tileVariantImage = tileVariant.getImage();

    return tileVariantImage.row(tileVariantImage.rows() - 1) == anchorTileVariantImage.row(0);
}

boost::optional<std::vector<Tile>> ImageReassembler::getPossibleTilesFromUpwardsConstraint(size_t x, size_t y) const
{
    if (y > 0)
    {
        const Tile& upwardsNeighbor = m_reassembledTileGrid.at(y - 1).at(x);
        if (upwardsNeighbor.isPopulated())
        {
            return findAllPossibleNeighborsInDirection(upwardsNeighbor, Direction::DOWN);
        }
    }

    return boost::none;
}

boost::optional<std::vector<Tile>> ImageReassembler::getPossibleTilesFromLeftwardsConstraint(size_t x, size_t y) const
{
    if (x > 0)
    {
        const Tile& leftwardsNeighbor = m_reassembledTileGrid.at(y).at(x - 1);
        if (leftwardsNeighbor.isPopulated())
        {
            return findAllPossibleNeighborsInDirection(leftwardsNeighbor, Direction::RIGHT);
        }
    }

    return boost::none;
}

Tile ImageReassembler::resolveTileFromMaybeConstraints(const boost::optional<std::vector<Tile>>& possibleTilesFromUpwardsConstraint,
                                        const boost::optional<std::vector<Tile>>& possibleTilesFromLeftwardsConstraint) const
{
    if (!(possibleTilesFromUpwardsConstraint.has_value() || possibleTilesFromLeftwardsConstraint.has_value()))
    {
        throw std::runtime_error("Tile has no constraints in either direction");
    }

    if (possibleTilesFromUpwardsConstraint.has_value() && !possibleTilesFromLeftwardsConstraint.has_value())
    {
        if (possibleTilesFromUpwardsConstraint.get().size() != 1)
        {
            throw std::runtime_error("Unable to uniquely resolve tile from upwards constraint");
        }
        return possibleTilesFromUpwardsConstraint.get().front();
    }

    if (possibleTilesFromLeftwardsConstraint.has_value() && !possibleTilesFromUpwardsConstraint.has_value())
    {
        if (possibleTilesFromLeftwardsConstraint.get().size() != 1)
        {
            throw std::runtime_error("Unable to uniquely resolve tile from leftwards constraint");
        }
        return possibleTilesFromLeftwardsConstraint.get().front();
    }

    return resolveTileFromBothConstraints(possibleTilesFromUpwardsConstraint.get(), possibleTilesFromLeftwardsConstraint.get());
}

Tile ImageReassembler::resolveTileFromBothConstraints(std::vector<Tile> possibleTilesFromUpwardsConstraint,
                                    std::vector<Tile> possibleTilesFromLeftwardsConstraint) const
{
    auto sortingFunc = [](const Tile& lhs, const Tile& rhs) {return lhs.getID() < rhs.getID(); };
    std::sort(possibleTilesFromUpwardsConstraint.begin(), possibleTilesFromUpwardsConstraint.end(), sortingFunc);
    std::sort(possibleTilesFromLeftwardsConstraint.begin(), possibleTilesFromLeftwardsConstraint.end(), sortingFunc);

    std::vector<Tile> interectionTiles;
    std::set_intersection(possibleTilesFromUpwardsConstraint.cbegin(), possibleTilesFromUpwardsConstraint.cend(),
                            possibleTilesFromLeftwardsConstraint.cbegin(), possibleTilesFromLeftwardsConstraint.cend(),
                            std::back_inserter(interectionTiles), sortingFunc);

    if (interectionTiles.size() != 1)
    {
        throw std::runtime_error("Unable to uniquely resolve tile from both constraints");
    }

    return interectionTiles.front();
}

Tile ImageReassembler::getAllTilesCombined() const
{
    const Tile& someTile = m_reassembledTileGrid.front().front();
    size_t tileLength = someTile.getImage().rows();
    size_t combinedImageLength = m_reassembledImageLengthInTiles * tileLength;
    Image combinedImage{combinedImageLength, combinedImageLength};

    for (size_t j = 0; j < combinedImageLength; ++j)
    {
        for (size_t i = 0; i < combinedImageLength; ++i)
        {
            size_t tileX = i / tileLength;
            size_t tileY = j / tileLength;
            const Image& tileImage = m_reassembledTileGrid.at(tileY).at(tileX).getImage();

            size_t offsetInTileImageX = i % tileLength;
            size_t offsetInTileImageY = j % tileLength;

            combinedImage(j, i) = tileImage(offsetInTileImageY, offsetInTileImageX);
        }
    }
    return Tile{0, std::move(combinedImage)};
}

}
}
}
