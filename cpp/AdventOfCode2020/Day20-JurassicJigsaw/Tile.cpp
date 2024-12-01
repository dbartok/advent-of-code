#include "Tile.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day20
{

Tile::Tile(int id, Image image)
    : m_id{id}
    , m_image{std::move(image)}
{

}

Tile::Tile()
    : m_id{-1}
{

}

void Tile::rotateRight()
{
    m_image.transposeInPlace();
    m_image.rowwise().reverseInPlace();
}

void Tile::flipHorizontally()
{
    m_image.rowwise().reverseInPlace();
}

void Tile::removeBorders()
{
    for (int i = 0; i < 2; ++i)
    {
        m_image.conservativeResize(m_image.cols() - 1, m_image.rows() - 1);
        rotateRight();
        rotateRight();
    }
}

bool Tile::isPopulated() const
{
    return m_id != -1;
}

int Tile::getID() const
{
    return m_id;
}

const Image& Tile::getImage() const
{
    return m_image;
}

std::vector<Tile> Tile::getAllVariants() const
{
    std::vector<Tile> variants;

    auto copy{*this};
    for (size_t i = 0; i < 4; ++i)
    {
        variants.push_back(copy);
        copy.flipHorizontally();
        variants.push_back(copy);
        copy.flipHorizontally();
        copy.rotateRight();
    }

    return variants;
}

bool Tile::operator==(const Tile& other) const
{
    return this->m_id == other.m_id;
}

}
}
}
