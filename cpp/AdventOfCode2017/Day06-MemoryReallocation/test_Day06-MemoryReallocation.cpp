#include "Day06-MemoryReallocation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day06;

TEST_CLASS(Day06MemoryReallocation)
{
public:

    TEST_METHOD(numUniqueRedistributions_SimpleTests)
    {
        CurrentDay::MemoryBanks banks{0, 2, 7, 0};
        Assert::AreEqual(5u, CurrentDay::numUniqueRedistributions(banks));
    }

    TEST_METHOD(cyclesUntilReoccurs_SimpleTests)
    {
        CurrentDay::MemoryBanks banks{2, 4, 1, 2};
        Assert::AreEqual(4u, CurrentDay::cyclesUntilReoccurs(banks));
    }

};
