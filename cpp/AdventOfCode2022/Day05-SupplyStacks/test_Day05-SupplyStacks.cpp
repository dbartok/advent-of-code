#include "Day05-SupplyStacks.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day05;

TEST_CLASS(Day05SupplyStacks)
{
public:

    TEST_METHOD(cratesOnTopOfEachStack_SimpleTests)
    {
        Assert::AreEqual(std::string{"CMZ"}, CurrentDay::cratesOnTopOfEachStack(m_lines));
    }

    TEST_METHOD(cratesOnTopOfEachStackWithNewerTypeCrane_SimpleTests)
    {
        Assert::AreEqual(std::string{"MCD"}, CurrentDay::cratesOnTopOfEachStackWithNewerTypeCrane(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "    [D]    ",
        "[N] [C]    ",
        "[Z] [M] [P]",
        " 1   2   3 ",
        "",
        "move 1 from 2 to 1",
        "move 3 from 1 to 3",
        "move 2 from 2 to 1",
        "move 1 from 1 to 2"
    };
};
