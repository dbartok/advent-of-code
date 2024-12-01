#include "Day24-ArithmeticLogicUnit.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day24;

TEST_CLASS(Day24ArithmeticLogicUnit)
{
public:

    TEST_METHOD(largestModelNumberAcceptedByMonad_SimpleTests)
    {
        Assert::AreEqual(93959993429899ull, CurrentDay::largestModelNumberAcceptedByMonad());
    }

    TEST_METHOD(smallestModelNumberAcceptedByMonadd_SimpleTests)
    {
        Assert::AreEqual(11815671117121ull, CurrentDay::smallestModelNumberAcceptedByMonad());
    }
};
