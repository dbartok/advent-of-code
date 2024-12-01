#include "Day02-ProgramAlarm.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day02;

TEST_CLASS(Day02ProgramAlarm)
{
public:

    TEST_METHOD(getValueInPositionZeroAfterProgramHalts_SimpleTests)
    {
        Assert::AreEqual(3500, CurrentDay::getValueInPositionZeroAfterProgramHalts(std::vector<int>{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50}, 9, 10));
        Assert::AreEqual(2, CurrentDay::getValueInPositionZeroAfterProgramHalts(std::vector<int>{1, 0, 0, 0, 99}, 0, 0));
        Assert::AreEqual(2, CurrentDay::getValueInPositionZeroAfterProgramHalts(std::vector<int>{2, 3, 0, 3, 99}, 3, 0));
        Assert::AreEqual(2, CurrentDay::getValueInPositionZeroAfterProgramHalts(std::vector<int>{2, 4, 4, 5, 99, 0}, 4, 4));
        Assert::AreEqual(30, CurrentDay::getValueInPositionZeroAfterProgramHalts(std::vector<int>{1, 1, 1, 4, 99, 5, 6, 0, 99}, 1, 1));
    }

    TEST_METHOD(getScoreOfNounAndVerbForSpecificOutput_SimpleTests)
    {
        Assert::AreEqual(910, CurrentDay::getScoreOfNounAndVerbForSpecificOutput(std::vector<int>{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50}, 3500));
    }

};
