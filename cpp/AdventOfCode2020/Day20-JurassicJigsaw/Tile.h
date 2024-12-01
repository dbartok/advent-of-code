#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Dense>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day20
{

using Image = Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>;

class Tile
{
public:
    Tile(int id, Image image);
    Tile();

    void rotateRight();
    void flipHorizontally();
    void removeBorders();

    bool isPopulated() const;
    int getID() const;
    const Image& getImage() const;
    std::vector<Tile> getAllVariants() const;

    bool operator==(const Tile& other) const;

private:
    int m_id = -1;
    Image m_image;
};

}
}
}
