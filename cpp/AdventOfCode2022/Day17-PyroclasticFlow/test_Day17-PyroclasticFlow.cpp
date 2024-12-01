#include "Day17-PyroclasticFlow.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day17;

TEST_CLASS(Day17PyroclasticFlow)
{
public:

    TEST_METHOD(towerHeightAfterRocksStoppedFalling_SimpleTests)
    {
        Assert::AreEqual(3068ll, CurrentDay::towerHeightAfterRocksStoppedFalling(m_jetPattern));
    }

    TEST_METHOD(towerHeightAfterRocksStoppedFallingWithManyRocks_SimpleTests)
    {
        Assert::AreEqual(1514285714288ll, CurrentDay::towerHeightAfterRocksStoppedFallingWithManyRocks(m_jetPattern));
    }

private:
    const std::string m_jetPattern = ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>";
};
