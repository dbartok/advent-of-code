#include "Day15-OxygenSystem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day15;

TEST_CLASS(Day15OxygenSystem)
{
public:

    TEST_METHOD(fewestNumberOfMovementsToOxygen_SimpleTests)
    {
        CurrentDay::IntcodeNumberType mem = 1000; // Some high memory address
        Assert::AreEqual(1, CurrentDay::fewestNumberOfMovementsToOxygen(
            {
                3, mem, 104, 2, 99
            }
        ));
    }

    TEST_METHOD(numMinutesUntilOxygenSpreads_SimpleTests)
    {
        CurrentDay::IntcodeNumberType mem = 1000; // Some high memory address
        Assert::AreEqual(1, CurrentDay::numMinutesUntilOxygenSpreads(
            {
                3, mem, 104, 2, // Find oxygen
                3, mem, 104, 0, 3, mem, 104, 0, 3, mem, 104, 0, 3, mem, 104, 0, // Hit wall in 4 directions
                3, mem, 104, 1, 99 // Move 1 distance then terminate
            }
        ));
    }

};
