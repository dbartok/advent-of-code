#include "FractalImage.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day21
{

FractalImage::FractalImage(ImageEnhancer imageEnhancer)
    : m_imageEnhancer{std::move(imageEnhancer)}
{
    m_image.resize(3, 3);
    m_image <<
        false, true, false,
        false, false, true,
        true, true, true;
}

void FractalImage::enhanceRepeatedly(unsigned numIterations)
{
    for (unsigned i = 0; i < numIterations; ++i)
    {
        enhance();
    }
}

unsigned FractalImage::numPixelsOn()
{
    return (m_image.array() == true).count();
}

void FractalImage::enhance()
{
    const int imageSize = m_image.rows();

    // Split into blocks

    const int smallSquareSize = (imageSize % 2) == 0 ? 2 : 3;
    const int smallSquaresPerDimension = imageSize / smallSquareSize;

    std::vector<std::vector<SmallSquare>> blockMatrix{};

    for (int j = 0; j < imageSize; j += smallSquareSize)
    {
        blockMatrix.emplace_back();
        for (int i = 0; i < imageSize; i += smallSquareSize)
        {
            DynamicBoolMatrix block = m_image.block(j, i, smallSquareSize, smallSquareSize);
            SmallSquare square{block};
            blockMatrix.back().push_back(square);
        }
    }

    // Apply enhancement to individual blocks
    for (auto& blockRow : blockMatrix)
    {
        for (auto& block : blockRow)
        {
            m_imageEnhancer.apply(block);
        }
    }

    // Rebuild image from enhanced blocks

    const int newSmallSquareSize = smallSquareSize + 1;
    const int newSize = smallSquaresPerDimension * newSmallSquareSize;

    DynamicBoolMatrix completeMatrix{0, newSize};

    for (auto& blockRow : blockMatrix)
    {
        DynamicBoolMatrix rowMatrix{newSmallSquareSize, 0};
        for (auto& block : blockRow)
        {
            DynamicBoolMatrix newRowMatrix{rowMatrix.rows(), rowMatrix.cols() + newSmallSquareSize};
            newRowMatrix << rowMatrix, block.getMatrix();
            rowMatrix = newRowMatrix;
        }
        DynamicBoolMatrix newCompleteMatrix{completeMatrix.rows() + rowMatrix.rows(), completeMatrix.cols()};
        newCompleteMatrix <<
            completeMatrix,
            rowMatrix;
        completeMatrix = newCompleteMatrix;
    }

    m_image = completeMatrix;
}

}
}
}
