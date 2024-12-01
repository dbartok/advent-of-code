#include "ImageEnhancer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day21
{

ImageEnhancer::ImageEnhancer(EnhancementMap enhancementMap)
    : m_enhancementMap{std::move(enhancementMap)}
{

}

void ImageEnhancer::apply(SmallSquare& enhancementTarget) const
{
    std::vector<SmallSquare> allEquivalentSquares = generateUniqueEquivalentSquares(enhancementTarget);

    std::vector<SmallSquare> transformableSquares;
    std::copy_if(allEquivalentSquares.cbegin(), allEquivalentSquares.cend(), std::back_inserter(transformableSquares), [this](const SmallSquare& square)
                 {
                     return this->m_enhancementMap.find(square) != this->m_enhancementMap.cend();
                 });

    if (transformableSquares.size() != 1)
    {
        throw std::runtime_error("Could not find a single transformation to apply.");
    }

    enhancementTarget = m_enhancementMap.at(transformableSquares.front());
}

std::vector<SmallSquare> ImageEnhancer::generateUniqueEquivalentSquares(const SmallSquare& square)
{
    std::unordered_set<SmallSquare, SmallSquareHash> allEquivalentSquares;

    auto currentSquare{square};

    // Add all 4 orientations
    for (unsigned i = 0; i < 4; ++i)
    {
        // No flip
        allEquivalentSquares.insert(currentSquare);

        // Only horizontal flip
        currentSquare.flipHorizontally();
        allEquivalentSquares.insert(currentSquare);

        // Horizontal and vertical flip
        currentSquare.flipVertically();
        allEquivalentSquares.insert(currentSquare);

        // Only vertical flip
        currentSquare.flipHorizontally();
        allEquivalentSquares.insert(currentSquare);

        currentSquare.rotate();
    }

    return {std::make_move_iterator(allEquivalentSquares.begin()), std::make_move_iterator(allEquivalentSquares.end())};
}

}
}
}
