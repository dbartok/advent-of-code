#include "Day07-TheTreacheryOfWhales.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day07;

TEST_CLASS(Day07TheTreacheryOfWhales)
{
public:

    TEST_METHOD(leastAmountOfFuelSpentToAlign_SimpleTests)
    {
        Assert::AreEqual(37, CurrentDay::leastAmountOfFuelSpentToAlign(m_horizontalPositions));
    }

    TEST_METHOD(leastAmountOfFuelSpentToAlignWithIncreasingCosts_SimpleTests)
    {
        Assert::AreEqual(168, CurrentDay::leastAmountOfFuelSpentToAlignWithIncreasingCosts(m_horizontalPositions));
    }

private:
    std::vector<int> m_horizontalPositions = {16, 1, 2, 0, 4, 2, 7, 1, 2, 14};
};
