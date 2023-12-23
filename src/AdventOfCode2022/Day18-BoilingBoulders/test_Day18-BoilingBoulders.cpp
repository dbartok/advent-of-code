#include "Day18-BoilingBoulders.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day18;

TEST_CLASS(Day18BoilingBoulders)
{
public:

    TEST_METHOD(surfaceAreaOfScannedLavaDroplet_SimpleTests)
    {
        const std::vector<std::string> lines =
        {
            "2,2,2",
            "1,2,2",
            "3,2,2",
            "2,1,2",
            "2,3,2",
            "2,2,1",
            "2,2,3",
            "2,2,4",
            "2,2,6",
            "1,2,5",
            "3,2,5",
            "2,1,5",
            "2,3,5"
        };

        Assert::AreEqual(64u, CurrentDay::surfaceAreaOfScannedLavaDroplet(lines));
    }

};
