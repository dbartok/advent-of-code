#include "Day14-DockingData.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day14;

TEST_CLASS(Day14DockingData)
{
public:

    TEST_METHOD(sumOfValuesInMemoryAfterCompletion_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X",
            "mem[8] = 11",
            "mem[7] = 101",
            "mem[8] = 0"
        };

        Assert::AreEqual(165ull, CurrentDay::sumOfValuesInMemoryAfterCompletion(lines));
    }

    TEST_METHOD(sumOfValuesInMemoryAfterDecoderCompletion_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "mask = 000000000000000000000000000000X1001X",
            "mem[42] = 100",
            "mask = 00000000000000000000000000000000X0XX",
            "mem[26] = 1"
        };

        Assert::AreEqual(208ull, CurrentDay::sumOfValuesInMemoryAfterDecoderCompletion(lines));
    }

};
