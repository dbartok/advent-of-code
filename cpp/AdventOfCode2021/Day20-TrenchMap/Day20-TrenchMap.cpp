#include "Day20-TrenchMap.h"

#include "ImageEnhancer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

unsigned NUM_ENHANCEMENT_STEPS_PART_ONE = 2;
unsigned NUM_ENHANCEMENT_STEPS_PART_TWO = 50;
char LIGHT_PIXEL_CHAR = '#';

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day20
{

ImageRow parseImageLine(const std::string& imageLine)
{
    ImageRow imageRow;

    for (const char c : imageLine)
    {
        if (c == LIGHT_PIXEL_CHAR)
        {
            imageRow.push_back(true);
        }
        else
        {
            imageRow.push_back(false);
        }
    }

    return imageRow;
}

ImageEnhancer parseImageEnhancementAlgorithmAndInputImageLines(const std::vector<std::string>& imageEnhancementAlgorithmAndInputImageLines)
{
    ImageRow enhancementAlgorithm = parseImageLine(imageEnhancementAlgorithmAndInputImageLines.at(0));

    Image image;

    for (auto lineIter = imageEnhancementAlgorithmAndInputImageLines.cbegin() + 2; lineIter != imageEnhancementAlgorithmAndInputImageLines.cend(); ++lineIter)
    {
        ImageRow imageRow = parseImageLine(*lineIter);
        image.push_back(std::move(imageRow));
    }

    return ImageEnhancer{std::move(enhancementAlgorithm), std::move(image)};
}

unsigned numPixelsLitAfterSmallEnhancement(const std::vector<std::string>& imageEnhancementAlgorithmAndInputImageLines)
{
    ImageEnhancer imageEnhancer = parseImageEnhancementAlgorithmAndInputImageLines(imageEnhancementAlgorithmAndInputImageLines);
    imageEnhancer.enhanceRepatedly(NUM_ENHANCEMENT_STEPS_PART_ONE);
    return imageEnhancer.getNumLitPixels();
}

unsigned numPixelsLitAfterLargeEnhancement(const std::vector<std::string>& imageEnhancementAlgorithmAndInputImageLines)
{
    ImageEnhancer imageEnhancer = parseImageEnhancementAlgorithmAndInputImageLines(imageEnhancementAlgorithmAndInputImageLines);
    imageEnhancer.enhanceRepatedly(NUM_ENHANCEMENT_STEPS_PART_TWO);
    return imageEnhancer.getNumLitPixels();
}

}
}
}