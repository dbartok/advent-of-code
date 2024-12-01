#include "SpaceImageFormatDecoder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day08
{

SpaceImageLayer::SpaceImageLayer(Layer layer)
    : m_layer{std::move(layer)}
{

}

unsigned SpaceImageLayer::getNumberCount(int number) const
{
    return std::accumulate(m_layer.cbegin(), m_layer.cend(), 0u, [number](unsigned totalSum, const auto& row)
                            {
                                return totalSum + std::count(row.cbegin(), row.cend(), number);
                            });
}

SpaceImageLayer SpaceImageLayer::operator+(const SpaceImageLayer& topSpaceImageLayer)
{
    Layer result{m_layer};
    const Layer& topLayer = topSpaceImageLayer.m_layer;

    for (size_t j = 0; j < topLayer.size(); ++j)
    {
        for (size_t i = 0; i < topLayer.at(j).size(); ++i)
        {
            if (topLayer.at(j).at(i) != TRANSPARENT_COLOR_CODE)
            {
                result.at(j).at(i) = topLayer.at(j).at(i);
            }
        }
    }

    return SpaceImageLayer{std::move(result)};
}

std::ostream& operator<<(std::ostream& os, const SpaceImageLayer& sil)
{
    const Layer& layer = sil.m_layer;
    for (size_t j = 0; j < layer.size(); ++j)
    {
        for (size_t i = 0; i < layer.at(j).size(); ++i)
        {
            os << ((layer.at(j).at(i) == SpaceImageLayer::WHITE_COLOR_CODE) ? '.' : ' ');
        }
        os << std::endl;
    }

    return os;
}

SpaceImageFormatDecoder::SpaceImageFormatDecoder(std::vector<Layer> layers)
{
    for (auto& layer : layers)
    {
        m_spaceImageLayers.push_back(SpaceImageLayer{std::move(layer)});
    }
}

unsigned SpaceImageFormatDecoder::getChecksumOfLayerWithMostZeroes() const
{
    const auto maxSpaceImageLayer = *std::min_element(m_spaceImageLayers.cbegin(), m_spaceImageLayers.cend(), [](const auto& lhs, const auto& rhs)
                                                        {
                                                            return lhs.getNumberCount(0) < rhs.getNumberCount(0);
                                                        });

    return maxSpaceImageLayer.getNumberCount(1) * maxSpaceImageLayer.getNumberCount(2);
}

SpaceImageLayer SpaceImageFormatDecoder::getDecodedImage() const
{
    auto spaceImageLayerBackToFront{m_spaceImageLayers};
    std::reverse(spaceImageLayerBackToFront.begin(), spaceImageLayerBackToFront.end());

    SpaceImageLayer currentSpaceImageLayer = spaceImageLayerBackToFront.front();

    for (size_t i = 0; i < spaceImageLayerBackToFront.size() - 1; ++i)
    {
        const auto& nextLayer = spaceImageLayerBackToFront.at(i + 1);
        currentSpaceImageLayer = currentSpaceImageLayer + nextLayer;
    }

    return currentSpaceImageLayer;
}

}
}
}
