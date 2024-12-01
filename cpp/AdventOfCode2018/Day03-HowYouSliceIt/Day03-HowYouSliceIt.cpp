#include "Day03-HowYouSliceIt.h"

#include "OverlapGrid.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const size_t GRID_SIZE = 1001;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day03
{

OverlapGrid parseOverlapGridFromAreaLines(const std::vector<std::string>& areaLines)
{
    OverlapGrid overlapGrid{GRID_SIZE};

    for (const auto& line : areaLines)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of(" @,:x"), boost::token_compress_on);

        if (tokens.size() < 5)
        {
            throw std::runtime_error("Not enough tokens.");
        }

        const unsigned topLeftX = boost::lexical_cast<unsigned>(tokens[1]);
        const unsigned topLeftY = boost::lexical_cast<unsigned>(tokens[2]);
        const unsigned width = boost::lexical_cast<unsigned>(tokens[3]);
        const unsigned height = boost::lexical_cast<unsigned>(tokens[4]);

        Rectangle r{topLeftX, topLeftY, width, height};

        overlapGrid.addRectangle(std::move(r));
    }

    return overlapGrid;
}

unsigned numOverlappingSquares(const std::vector<std::string>& areaLines)
{
    OverlapGrid OverlapGrid = parseOverlapGridFromAreaLines(areaLines);
    return OverlapGrid.getOverlapSize();
}

unsigned findSingleNonOperlappingSquare(const std::vector<std::string>& areaLines)
{
    OverlapGrid OverlapGrid = parseOverlapGridFromAreaLines(areaLines);
    return OverlapGrid.getSingleNonOverlappingIndex() + 1;
}

}
}
}
