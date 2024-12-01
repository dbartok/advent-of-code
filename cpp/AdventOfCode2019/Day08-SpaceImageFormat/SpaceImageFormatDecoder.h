#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day08
{


using Line = std::vector<int>;
using Layer = std::vector<Line>;

class SpaceImageLayer
{
public:
    SpaceImageLayer(Layer layer);

    unsigned getNumberCount(int number) const;

    SpaceImageLayer operator+(const SpaceImageLayer& topSpaceImageLayer);

    friend std::ostream& operator<<(std::ostream& os, const SpaceImageLayer& sil);

private:
    static const int WHITE_COLOR_CODE = 1;
    static const int TRANSPARENT_COLOR_CODE = 2;

    Layer m_layer;
};

std::ostream& operator<<(std::ostream& os, const SpaceImageLayer& sil);

class SpaceImageFormatDecoder
{
public:
    SpaceImageFormatDecoder(std::vector<Layer> layers);

    unsigned getChecksumOfLayerWithMostZeroes() const;
    SpaceImageLayer getDecodedImage() const;

private:
    std::vector<SpaceImageLayer> m_spaceImageLayers;
};

}
}
}
