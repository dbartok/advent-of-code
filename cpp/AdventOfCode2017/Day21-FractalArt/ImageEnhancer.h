#pragma once

#include "SmallSquare.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>

#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day21
{

class ImageEnhancer
{
public:
    struct SmallSquareHash
    {
        size_t operator()(const SmallSquare& square) const
        {
            const auto& matrix = square.getMatrix();
            size_t seed = 0;
            for (int i = 0; i < matrix.cols(); ++i)
            {
                for (int j = 0; j < matrix.rows(); ++j)
                {
                    auto elem = matrix(j, i);
                    boost::hash_combine(seed, elem);
                }
            }
            return seed;
        }
    };

    using EnhancementMap = std::unordered_map<SmallSquare, SmallSquare, SmallSquareHash>;

    ImageEnhancer(EnhancementMap enhancementMap);
    void apply(SmallSquare& enhancementTarget) const;

private:
    EnhancementMap m_enhancementMap;

    static std::vector<SmallSquare> generateUniqueEquivalentSquares(const SmallSquare& square);
};

}
}
}
