#include "Day11-HexEd.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day11;

TEST_CLASS(Day11HexEd)
{
public:

    TEST_METHOD(numStepsFromStart_SimpleTests)
    {
        Assert::AreEqual(3, CurrentDay::numStepsFromStartAtEnd({"ne", "ne", "ne"}));
        Assert::AreEqual(0, CurrentDay::numStepsFromStartAtEnd({"ne", "ne", "sw", "sw"}));
        Assert::AreEqual(2, CurrentDay::numStepsFromStartAtEnd({"ne", "ne", "s", "s"}));
        Assert::AreEqual(3, CurrentDay::numStepsFromStartAtEnd({"se", "sw", "se", "sw", "sw"}));
    }

    TEST_METHOD(maxNumStepsFromStart_MaxDistanceEqualsDistanceAtEnd_ReturnDistanceAtEnd)
    {
        Assert::AreEqual(3, CurrentDay::maxNumStepsFromStart({"ne", "ne", "ne"}));
        Assert::AreEqual(2, CurrentDay::maxNumStepsFromStart({"ne", "ne", "s", "s"}));
        Assert::AreEqual(3, CurrentDay::maxNumStepsFromStart({"se", "sw", "se", "sw", "sw"}));
    }

    TEST_METHOD(maxNumStepsFromStart_MaxDistanceReachedNotAtEnd_ReturnMaxDistance)
    {
        Assert::AreEqual(2, CurrentDay::maxNumStepsFromStart({"ne", "ne", "sw", "sw"}));
        Assert::AreEqual(4, CurrentDay::maxNumStepsFromStart({"n", "s", "se", "sw", "s", "s", "s", "n"}));
    }

};
