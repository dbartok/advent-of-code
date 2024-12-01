#include "Day09-MirageMaintenance.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day09;

TEST_CLASS(Day09MirageMaintenance)
{
public:

    TEST_METHOD(sumOfForwardsExtrapolatedValues_SimpleTests)
    {
        Assert::AreEqual(114, CurrentDay::sumOfForwardsExtrapolatedValues(m_lines));
    }

    TEST_METHOD(sumOfBackwardsExtrapolatedValues_SimpleTests)
    {
        Assert::AreEqual(2, CurrentDay::sumOfBackwardsExtrapolatedValues(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "0 3 6 9 12 15",
        "1 3 6 10 15 21",
        "10 13 16 21 30 45"
    };
};
