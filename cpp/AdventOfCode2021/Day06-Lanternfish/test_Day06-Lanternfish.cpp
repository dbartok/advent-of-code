#include "Day06-Lanternfish.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day06;

TEST_CLASS(Day06Lanternfish)
{
public:

    TEST_METHOD(numLanternfishAfterSmallNumberOfDays_SimpleTests)
    {
        Assert::AreEqual(5934ull, CurrentDay::numLanternfishAfterSmallNumberOfDays(m_initialState));
    }

    TEST_METHOD(numLanternfishAfterLargeNumberOfDays_SimpleTests)
    {
        Assert::AreEqual(26984457539ull, CurrentDay::numLanternfishAfterLargeNumberOfDays(m_initialState));
    }

public:
    const std::vector<int> m_initialState = {3, 4, 3, 1, 2};

};
