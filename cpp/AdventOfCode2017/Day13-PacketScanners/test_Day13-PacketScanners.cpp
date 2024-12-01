#include "Day13-PacketScanners.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day13;

TEST_CLASS(Day13PacketScanners)
{
public:

    TEST_METHOD(severityOfWholeTrip_SimpleTests)
    {
        Assert::AreEqual(24u, CurrentDay::severityOfWholeTrip(m_scannerRangeLines));
    }

    TEST_METHOD(smallestDelayNotToGetCaught_SimpleTests)
    {
        Assert::AreEqual(10u, CurrentDay::smallestDelayNotToGetCaught(m_scannerRangeLines));
    }

private:
    std::vector<std::string> m_scannerRangeLines =
    {
        "0 : 3",
        "1 : 2",
        "4 : 4",
        "6 : 4"
    };
};
