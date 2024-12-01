#include "Day21-FractalArt.h"

#include "FractalImage.h"
#include "ImageEnhancer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day21
{

SmallSquare createSquareFromString(const std::string& matrixString)
{
    std::vector<std::string> rows;
    boost::split(rows, matrixString, boost::is_any_of("/"));

    DynamicBoolMatrix square{rows.size(), rows.size()};

    for (size_t j = 0; j < rows.size(); ++j)
    {
        for (size_t i = 0; i < rows.size(); ++i)
        {
            square(j, i) = (rows[j][i] == '#');
        }
    }

    return square;
}

ImageEnhancer::EnhancementMap createEnhancementMapFromRuleLines(const std::vector<std::string>& enhancementRuleLines)
{
    ImageEnhancer::EnhancementMap enhancementMap;

    for (const auto& line : enhancementRuleLines)
    {
        std::vector<std::string> matrixStrings;
        boost::split(matrixStrings, line, boost::is_any_of("=> "), boost::token_compress_on);
        if (matrixStrings.size() != 2)
        {
            throw std::runtime_error("Expected 2 matrices.");
        }

        SmallSquare from = createSquareFromString(matrixStrings[0]);
        SmallSquare to = createSquareFromString(matrixStrings[1]);

        enhancementMap.emplace(std::move(from), std::move(to));
    }

    return enhancementMap;
}

unsigned numPixelsOnAfterEnhancements(const std::vector<std::string>& enhancementRuleLines, unsigned numIterations)
{
    ImageEnhancer::EnhancementMap enhancementMap = createEnhancementMapFromRuleLines(enhancementRuleLines);

    FractalImage fractalImage{std::move(enhancementMap)};
    fractalImage.enhanceRepeatedly(numIterations);
    return fractalImage.numPixelsOn();
}

unsigned numPixelsOnSmallIterations(const std::vector<std::string>& enhancementRuleLines, unsigned numIterations)
{
    return numPixelsOnAfterEnhancements(enhancementRuleLines, numIterations);
}

unsigned numPixelsOnLargeIterations(const std::vector<std::string>& enhancementRuleLines, unsigned numIterations)
{
    return numPixelsOnAfterEnhancements(enhancementRuleLines, numIterations);
}

}
}
}
