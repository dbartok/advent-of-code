#include "Day12-HillClimbingAlgorithm.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day12;

TEST_CLASS(Day12HillClimbingAlgorithm)
{
public:

    TEST_METHOD(fewestStepsFromStartToEnd_SimpleTests)
    {
        const std::vector<std::string> lines =
        {
            "Sabqponm",
            "abcryxxl",
            "accszExk",
            "acctuvwj",
            "abdefghi"
        };

        Assert::AreEqual(31, CurrentDay::fewestStepsFromStartToEnd(lines));
    }

};
