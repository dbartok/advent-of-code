#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day20
{

using Pixel = bool;
using ImageRow = std::vector<Pixel>;
using Image = std::vector<ImageRow>;

class ImageEnhancer
{
public:
    ImageEnhancer(ImageRow enhancementAlgorithm, Image originalImage);

    void enhanceRepatedly(unsigned numEnhancementSteps);

    unsigned getNumLitPixels();

private:
    ImageRow m_enhancementAlgorithm;
    Image m_image;

    size_t m_width;
    size_t m_height;

    bool m_areOutOfBoundsPixelsLit = false;

    void addPadding(unsigned paddingLength);
    void enhance();

    Pixel getEnhancedPixelAt(int x, int y) const;
    Pixel getCurrentPixelAt(int x, int y) const;
};

}
}
}
