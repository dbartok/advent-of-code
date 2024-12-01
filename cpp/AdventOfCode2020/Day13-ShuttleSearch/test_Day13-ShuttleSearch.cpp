#include "Day13-ShuttleSearch.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day13;

TEST_CLASS(Day13ShuttleSearch)
{
public:

    TEST_METHOD(earliestBusIDMultipliedByWaitTime_SimpleTests)
    {
        Assert::AreEqual(295, CurrentDay::earliestBusIDMultipliedByWaitTime(939, "7,13,x,x,59,x,31,19"));
    }

    TEST_METHOD(earliestTimestampWithMatchingDepartures_SimpleTests)
    {
        Assert::AreEqual(1068781ll, CurrentDay::earliestTimestampWithMatchingDepartures("7,13,x,x,59,x,31,19"));
        Assert::AreEqual(3417ll, CurrentDay::earliestTimestampWithMatchingDepartures("17,x,13,19"));
        Assert::AreEqual(754018ll, CurrentDay::earliestTimestampWithMatchingDepartures("67,7,59,61"));
        Assert::AreEqual(779210ll, CurrentDay::earliestTimestampWithMatchingDepartures("67,x,7,59,61"));
        Assert::AreEqual(1261476ll, CurrentDay::earliestTimestampWithMatchingDepartures("67,7,x,59,61"));
        Assert::AreEqual(1202161486ll, CurrentDay::earliestTimestampWithMatchingDepartures("1789,37,47,1889"));
    }

};
