#include "Day08-SpaceImageFormat.h"

#include "SpaceImageFormatDecoder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <sstream>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day08
{

Layer createLayer(std::istringstream& encodedImageStream, size_t width, size_t height)
{
    Layer layer;
    for (size_t j = 0; j < height; ++j)
    {
        Line line;
        for (size_t i = 0; i < width; ++i)
        {
            line.push_back(encodedImageStream.get() - '0');
        }
        layer.push_back(line);
    }
    return layer;
}

std::vector<Layer> createLayers(const std::string& encodedImage, size_t width, size_t height)
{
    std::vector<Layer> layers;

    std::istringstream encodedImageStream{encodedImage};

    while (encodedImageStream.peek() != std::istream::traits_type::eof())
    {
        Layer layer = createLayer(encodedImageStream, width, height);
        layers.push_back(layer);
    }

    return layers;
}

unsigned checksumOfLayerWithMostZeroes(const std::string& encodedImage, size_t width, size_t height)
{
    std::vector<Layer> layers = createLayers(encodedImage, width, height);
    SpaceImageFormatDecoder decoder{std::move(layers)};

    return decoder.getChecksumOfLayerWithMostZeroes();
}

std::string decodeImage(const std::string& encodedImage, size_t width, size_t height)
{
    std::vector<Layer> layers = createLayers(encodedImage, width, height);
    SpaceImageFormatDecoder decoder{std::move(layers)};

    std::ostringstream oss;
    oss << decoder.getDecodedImage();
    return oss.str();
}

}
}
}
