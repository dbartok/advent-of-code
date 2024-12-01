#include "Day19-GoWithTheFlow.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day19;

TEST_CLASS(Day19GoWithTheFlow)
{
public:

    TEST_METHOD(valueInFirstRegisterAfterProcessHalts_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "#ip 0",
            "seti 5 0 1",
            "seti 6 0 2",
            "addi 0 1 0",
            "addr 1 2 3",
            "setr 1 0 0",
            "seti 8 0 4",
            "seti 9 0 5"
        };

        Assert::AreEqual(7u, CurrentDay::valueInFirstRegisterAfterProcessHalts(lines));
    }

    // Same as the real puzzle, because the solution had to be hand optimized for a specific input
    TEST_METHOD(valueInFirstRegisterAfterNewProcessHalts_SimpleTests)
    {
        Assert::AreEqual(10915260u, CurrentDay::valueInFirstRegisterAfterNewProcessHalts());
    }

};
