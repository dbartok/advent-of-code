#include "Day11-SeatingSystem.h"
#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace AoC = AdventOfCode;

TEST_CLASS(Day11SeatingSystem)
{
public:

    TEST_METHOD(numOccupiedSeatsInStabilizedState_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "L.LL.LL.LL",
            "LLLLLLL.LL",
            "L.L.L..L..",
            "LLLL.LL.LL",
            "L.LL.LL.LL",
            "L.LLLLL.LL",
            "..L.L.....",
            "LLLLLLLLLL",
            "L.LLLLLL.L",
            "L.LLLLL.LL"
        };

        Assert::AreEqual(37, AoC::numOccupiedSeatsInStabilizedState(lines));
    }

};
