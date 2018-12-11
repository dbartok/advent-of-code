#include "Day11-ChronalCharge.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace AoC = AdventOfCode;

TEST_CLASS(Day11ChronalCharge)
{
public:

    TEST_METHOD(highestPowerSmallSquareCoordinates_SimpleTests)
    {
        Assert::AreEqual(std::string{"33,45"}, AoC::highestPowerSmallSquareCoordinates(18));
        Assert::AreEqual(std::string{"21,61"}, AoC::highestPowerSmallSquareCoordinates(42));
    }

};
