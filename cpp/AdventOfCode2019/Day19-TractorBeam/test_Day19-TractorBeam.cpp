#include "Day19-TractorBeam.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day19;

TEST_CLASS(Day19TractorBeam)
{
public:

    TEST_METHOD(numPointsAffectedByBeam_SimpleTests)
    {
        CurrentDay::IntcodeNumberType mem = 1000; // Some high memory address
        Assert::AreEqual(2500, CurrentDay::numPointsAffectedByBeam(
            {
                3, mem, 3, mem, 104, 1, 99
            }));
    }

    TEST_METHOD(squareClosestPointChecksum_SimpleTests)
    {
        CurrentDay::IntcodeNumberType mem = 1000; // Some high memory address
        Assert::AreEqual(0, CurrentDay::squareClosestPointChecksum(
            {
                3, mem, 3, mem, 104, 1, 99
            }));
    }

};
