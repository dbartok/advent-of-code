#include "Day25-HaltingProblem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day25;

TEST_CLASS(Day25HaltingProblem)
{
public:

    TEST_METHOD(diagnosticChecksum_SimpleTests)
    {
        const std::vector<std::string> turingMachineLines =
        {
            "Begin in state A.",
            "Perform a diagnostic checksum after 6 steps.",
            "                                 ",
            "In state A:                      ",
            "  If the current value is 0:     ",
            "    - Write the value 1.         ",
            "    - Move one slot to the right.",
            "    - Continue with state B.     ",
            "  If the current value is 1:     ",
            "    - Write the value 0.         ",
            "    - Move one slot to the left. ",
            "    - Continue with state B.     ",
            "                                 ",
            "In state B:                      ",
            "  If the current value is 0:     ",
            "    - Write the value 1.         ",
            "    - Move one slot to the left. ",
            "    - Continue with state A.     ",
            "  If the current value is 1:     ",
            "    - Write the value 1.         ",
            "    - Move one slot to the right.",
            "    - Continue with state A.     "
        };

        Assert::AreEqual(3u, CurrentDay::diagnosticChecksum(turingMachineLines));
    }

};
