#include "Day14-ParabolicReflectorDish.h"

#include "Platform.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned NUM_SPIN_CYCLES = 1'000'000'000;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day14
{

Platform parsePlatformLines(const std::vector<std::string>& platformLines)
{
    Matrix matrix = Matrix::Zero(platformLines.size(), platformLines.front().size());

    for (int j = 0; j < matrix.rows(); ++j)
    {
        for (int i = 0; i < matrix.cols(); ++i)
        {
            matrix(j, i) = platformLines.at(j).at(i);
        }
    }

    return Platform{std::move(matrix)};
}

int totalLoadOnNorthSupportBeamsAfterNorthSlide(const std::vector<std::string>& platformLines)
{
    Platform platform = parsePlatformLines(platformLines);

    platform.slideNorth();

    return platform.getTotalLoadOnNorthSupportBeams();
}

int totalLoadOnNorthSupportBeamsAfterSeveralCycles(const std::vector<std::string>& platformLines)
{
    Platform platform = parsePlatformLines(platformLines);

    platform.executeSpinCycles(NUM_SPIN_CYCLES);

    return platform.getTotalLoadOnNorthSupportBeams();
}

}
}
}