#include "Day19-SeriesOfTubes.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day19;

TEST_CLASS(Day19SeriesOfTubes)
{
public:

    TEST_METHOD(lettersVisited_SimpleTests)
    {
        Assert::AreEqual(std::string{"ABCDEF"}, CurrentDay::lettersVisited(m_diagramLines));
    }

    TEST_METHOD(totalNumStepsForPacket_SimpleTests)
    {
        Assert::AreEqual(38u, CurrentDay::totalNumStepsForPacket(m_diagramLines));
    }

private:
    const std::vector<std::string> m_diagramLines =
    {
        "     |          ",
        "     |  +--+    ",
        "     A  |  C    ",
        " F---|----E|--+ ",
        "     |  |  |  D ",
        "     +B-+  +--+ ",
        "                "
    };
};
