#include "Day03-GearRatios.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day03;

TEST_CLASS(Day03GearRatios)
{
public:

    TEST_METHOD(sumOfAllPartNumbers_SimpleTests)
    {
        Assert::AreEqual(4361, CurrentDay::sumOfAllPartNumbers(m_lines));
    }

    TEST_METHOD(sumOfAllGearRatios_SimpleTests)
    {
        Assert::AreEqual(467835, CurrentDay::sumOfAllGearRatios(m_lines));
    }

private:
    const std::vector<std::string>& m_lines =
    {
        "467..114..",
        "...*......",
        "..35..633.",
        "......#...",
        "617*......",
        ".....+.58.",
        "..592.....",
        "......755.",
        "...$.*....",
        ".664.598.."
    };
};
