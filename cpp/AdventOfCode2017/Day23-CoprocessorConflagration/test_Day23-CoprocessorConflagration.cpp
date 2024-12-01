#include "Day23-CoprocessorConflagration.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day23;

TEST_CLASS(Day23CoprocessorConflagration)
{
public:

    TEST_METHOD(numTimesMultInvoked_OneRegisterSimpleLoop_MultIsInvokedTwice)
    {
        std::vector<std::string> instructionStrings =
        {
            "set a 4",
            "add a 2",
            "mul a a",
            "sub a 2",
            "jnz a -1",
            "mul a 6"
        };

        Assert::AreEqual(2u, CurrentDay::numTimesMultInvoked(instructionStrings));
    }

    // Test is the same as the real puzzle input in this case, because the solution is meant to be optimized solely for that
    TEST_METHOD(overheatFinalValueOfH_Returns911AsTheAnswer)
    {
        Assert::AreEqual(911u, CurrentDay::overheatFinalValueOfH());
    }

};
