#include "Day23-Amphipod.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day23;

TEST_CLASS(Day23Amphipod)
{
public:

    TEST_METHOD(leastEnergyRequiredToOrganize_SimpleTests)
    {
        const std::vector<std::string> lines =
        {
            "#############",
            "#...........#",
            "###B#C#B#D###",
            "  #A#D#C#A#",
            "  #########"
        };

        Assert::AreEqual(12521u, CurrentDay::leastEnergyRequiredToOrganize(lines));
    }

};
