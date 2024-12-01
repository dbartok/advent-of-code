#include "Day25-FullOfHotAir.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day25;

TEST_CLASS(Day25FullOfHotAir)
{
public:

    TEST_METHOD(snafuNumberRequiredForConsole_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "1=-0-2",
            "12111",
            "2=0=",
            "21",
            "2=01",
            "111",
            "20012",
            "112",
            "1=-1=",
            "1-12",
            "12",
            "1=",
            "122"
        };

        Assert::AreEqual(std::string{"2=-1=0"}, CurrentDay::snafuNumberRequiredForConsole(lines));
    }

};
