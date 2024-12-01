#include "Day23-CrabCups.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day23;

TEST_CLASS(Day23CrabCups)
{
public:

    TEST_METHOD(cupLabelsStartingFromCupOne_SimpleTests)
    {
        Assert::AreEqual(std::string{"92658374"}, CurrentDay::cupLabelsStartingFromCupOne("389125467", 10));
        Assert::AreEqual(std::string{"67384529"}, CurrentDay::cupLabelsStartingFromCupOne("389125467", 100));
    }

    TEST_METHOD(twoCupLabelsAfterCupOneMultipliedManyCups_SimpleTests)
    {
        Assert::AreEqual(149245887792ll, CurrentDay::twoCupLabelsAfterCupOneMultipliedManyCups("389125467", 10'000'000));
    }

};
