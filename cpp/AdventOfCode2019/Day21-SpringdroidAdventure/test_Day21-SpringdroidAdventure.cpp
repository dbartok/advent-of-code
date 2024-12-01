#include "Day21-SpringdroidAdventure.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day21;

TEST_CLASS(Day21SpringdroidAdventure)
{
public:

    TEST_METHOD(amountOfHullDamage_SimpleTests)
    {
        CurrentDay::IntcodeNumberType mem = 1000; // Some high memory address
        Assert::AreEqual(10000ll, CurrentDay::amountOfHullDamage(
            {
                3, mem, 104, 10000, 99
            }));
    }

    TEST_METHOD(amountOfHullDamageExtendedSensors_SimpleTests)
    {
        CurrentDay::IntcodeNumberType mem = 1000; // Some high memory address
        Assert::AreEqual(12345ll, CurrentDay::amountOfHullDamageExtendedSensors(
            {
                3, mem, 104, 12345, 99
            }));
    }

};
