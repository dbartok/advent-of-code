#include "Day14-DiskDefragmentation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day14;

TEST_CLASS(Day14DiskDefragmentation)
{
public:

    TEST_METHOD(numSquaresUsed_SimpleTests)
    {
        Assert::AreEqual(8108u, CurrentDay::numSquaresUsed(m_keyString));
    }

    TEST_METHOD(numRegionsOfAdjcacentSquares_SimpleTests)
    {
        Assert::AreEqual(1242u, CurrentDay::numRegionsOfAdjcacentSquares(m_keyString));
    }

private:
    const std::string m_keyString = "flqrgnkx";
};
