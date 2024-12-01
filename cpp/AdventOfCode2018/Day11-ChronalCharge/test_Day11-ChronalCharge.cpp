#include "Day11-ChronalCharge.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day11;

TEST_CLASS(Day11ChronalCharge)
{
public:

    TEST_METHOD(highestPowerSmallSquareCoordinates_SimpleTests)
    {
        Assert::AreEqual(std::string{"33,45"}, CurrentDay::highestPowerSmallSquareCoordinates(18));
        Assert::AreEqual(std::string{"21,61"}, CurrentDay::highestPowerSmallSquareCoordinates(42));
    }

    TEST_METHOD(highestPowerSquareCoordinatesAndSize_SimpleTests)
    {
        Assert::AreEqual(std::string{"90,269,16"}, CurrentDay::highestPowerSquareCoordinatesAndSize(18, 17u));
        Assert::AreEqual(std::string{"232,251,12"}, CurrentDay::highestPowerSquareCoordinatesAndSize(42, 13u));
    }

};
