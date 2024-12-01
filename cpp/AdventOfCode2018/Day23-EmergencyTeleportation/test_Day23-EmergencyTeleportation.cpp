#include "Day23-EmergencyTeleportation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day23;

TEST_CLASS(Day23EmergencyTeleportation)
{
public:

    TEST_METHOD(numNanobotsInStrongestRange_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "pos=<0,0,0>, r=4",
            "pos=<1,0,0>, r=1",
            "pos=<4,0,0>, r=3",
            "pos=<0,2,0>, r=1",
            "pos=<0,5,0>, r=3",
            "pos=<0,0,3>, r=1",
            "pos=<1,1,1>, r=1",
            "pos=<1,1,2>, r=1",
            "pos=<1,3,1>, r=1"
        };

        Assert::AreEqual(7u, CurrentDay::numNanobotsInStrongestRange(lines));
    }

    TEST_METHOD(lowestDistanceFromOriginWithMostNanobots_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "pos=<10,12,12>, r=2",
            "pos=<12,14,12>, r=2",
            "pos=<16,12,12>, r=4",
            "pos=<14,14,14>, r=6",
            "pos=<50,50,50>, r=200",
            "pos=<10,10,10>, r=5"
        };

        Assert::AreEqual(36, CurrentDay::lowestDistanceFromOriginWithMostNanobots(lines));
    }

};
