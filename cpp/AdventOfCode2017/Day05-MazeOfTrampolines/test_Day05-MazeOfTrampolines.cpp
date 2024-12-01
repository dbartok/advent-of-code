#include "Day05-MazeOfTrampolines.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day05;

TEST_CLASS(Day05MazeOfTrampolines)
{
public:

    TEST_METHOD(jumpInstructionsIncreasing_SimpleTests)
    {
        Assert::AreEqual(5u, CurrentDay::stepsInstructionsIncreasing(m_instructions));
    }

    TEST_METHOD(jumpInstructionsIncreasingDecreasing_SimpleTests)
    {
        Assert::AreEqual(10u, CurrentDay::stepsInstructionsIncreasingDecreasing(m_instructions));
    }

private:
    std::vector<int> m_instructions{0, 3,  0,  1, -3};

};
