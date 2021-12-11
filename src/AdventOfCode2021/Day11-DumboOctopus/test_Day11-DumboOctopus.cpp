#include "Day11-DumboOctopus.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day11;

TEST_CLASS(Day11DumboOctopus)
{
public:

    TEST_METHOD(numTotalFlashes_SimpleTests)
    {
        const std::vector<std::string> lines =
        {
            "5483143223",
            "2745854711",
            "5264556173",
            "6141336146",
            "6357385478",
            "4167524645",
            "2176841721",
            "6882881134",
            "4846848554",
            "5283751526"
        };

        Assert::AreEqual(1656u, CurrentDay::numTotalFlashes(lines));
    }

};
