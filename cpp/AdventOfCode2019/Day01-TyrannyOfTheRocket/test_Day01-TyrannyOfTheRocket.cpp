#include "Day01-TyrannyOfTheRocket.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day01;

TEST_CLASS(Day01TyrannyOfTheRocket)
{
public:

    TEST_METHOD(getSumOfFuelRequirements_SimpleTests)
    {
        Assert::AreEqual(34241, CurrentDay::getSumOfFuelRequirements({12, 14, 1969, 100756}));
    }

    TEST_METHOD(getSumOfFuelRequirementsIncludingFuelItself_SimpleTests)
    {
        Assert::AreEqual(51314, CurrentDay::getSumOfFuelRequirementsIncludingFuelItself({14, 1969, 100756}));
    }

};
