#include "Day08-HandheldHalting.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day08;

TEST_CLASS(Day08HandheldHalting)
{
public:

    TEST_METHOD(valueInAccAfterFirstDuplicateInstruction_SimpleTests)
    {
        Assert::AreEqual(5, CurrentDay::valueInAccAfterFirstDuplicateInstruction(m_lines));
    }

    TEST_METHOD(valueInAccAfterRepairedProgramTerminates_SimpleTests)
    {
        Assert::AreEqual(8, CurrentDay::valueInAccAfterRepairedProgramTerminates(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "nop +0",
        "acc +1",
        "jmp +4",
        "acc +3",
        "jmp -3",
        "acc -99",
        "acc +1",
        "jmp -4",
        "acc +6"
    };

};
