#include "Day17-ClumsyCrucible.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day17;

TEST_CLASS(Day17ClumsyCrucible)
{
public:

    TEST_METHOD(leastHeatLossIncurred_SimpleTests)
    {
        Assert::AreEqual(102, CurrentDay::leastHeatLossIncurred(m_lines));
    }

    TEST_METHOD(leastHeatLossIncurredForUltraCrucible_SimpleTests)
    {
        Assert::AreEqual(94, CurrentDay::leastHeatLossIncurredForUltraCrucible(m_lines));
    }

    TEST_METHOD(leastHeatLossIncurredForUltraCrucible_ArrivalCondition)
    {
        const std::vector<std::string> lines =
        {
            "111111111111",
            "999999999991",
            "999999999991",
            "999999999991",
            "999999999991"
        };

        Assert::AreEqual(71, CurrentDay::leastHeatLossIncurredForUltraCrucible(lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "2413432311323",
        "3215453535623",
        "3255245654254",
        "3446585845452",
        "4546657867536",
        "1438598798454",
        "4457876987766",
        "3637877979653",
        "4654967986887",
        "4564679986453",
        "1224686865563",
        "2546548887735",
        "4322674655533"
    };

};
