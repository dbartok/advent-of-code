#include "Day03-BinaryDiagnostic.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day03;

TEST_CLASS(Day03BinaryDiagnostic)
{
public:

    TEST_METHOD(submarinePowerConsumption_SimpleTests)
    {
        Assert::AreEqual(198, CurrentDay::submarinePowerConsumption(m_lines));
    }

    TEST_METHOD(lifeSupportRating_SimpleTests)
    {
        Assert::AreEqual(230, CurrentDay::lifeSupportRating(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "00100",
        "11110",
        "10110",
        "10111",
        "10101",
        "01111",
        "00111",
        "11100",
        "10000",
        "11001",
        "00010",
        "01010"
    };
};
