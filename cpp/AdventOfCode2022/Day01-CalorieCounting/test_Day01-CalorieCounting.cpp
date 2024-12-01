#include "Day01-CalorieCounting.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day01;

TEST_CLASS(Day01CalorieCounting)
{
public:

    TEST_METHOD(maxTotalCaloriesCarried_SimpleTests)
    {
        Assert::AreEqual(24000, CurrentDay::maxTotalCaloriesCarried(m_lines));
    }

    TEST_METHOD(totalCaloriesCarriedByTopThreeElves_SimpleTests)
    {
        Assert::AreEqual(45000, CurrentDay::totalCaloriesCarriedByTopThreeElves(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "1000",
        "2000",
        "3000",
        "",
        "4000",
        "",
        "5000",
        "6000",
        "",
        "7000",
        "8000",
        "9000",
        "",
        "10000"
    };
};
