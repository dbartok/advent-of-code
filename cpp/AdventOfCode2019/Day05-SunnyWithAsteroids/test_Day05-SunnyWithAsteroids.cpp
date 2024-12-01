#include "Day05-SunnyWithAsteroids.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day05;

TEST_CLASS(Day05SunnyWithAsteroids)
{
public:

    TEST_METHOD(diagnosticCodeProducedByProgram_SimpleTests)
    {
        Assert::AreEqual(4, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{4, 0, 99}, 0));
    }

    TEST_METHOD(diagnosticCodeProducedByProgram_PositionModeEqualTests)
    {
        Assert::AreEqual(1, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8}, 8));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8}, 7));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8}, 9));
    }

    TEST_METHOD(diagnosticCodeProducedByProgram_PositionModeLessThanTests)
    {
        Assert::AreEqual(1, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8}, 7));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8}, 8));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8}, 9));
    }

    TEST_METHOD(diagnosticCodeProducedByProgram_ImmediateModeEqualTests)
    {
        Assert::AreEqual(1, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 3, 1108, -1, 8, 3, 4, 3, 99}, {8}));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 3, 1108, -1, 8, 3, 4, 3, 99}, {7}));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 3, 1108, -1, 8, 3, 4, 3, 99}, {9}));
    }

    TEST_METHOD(diagnosticCodeProducedByProgram_ImmediateModeLessThanTests)
    {
        Assert::AreEqual(1, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 3, 1107, -1, 8, 3, 4, 3, 99}, {7}));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 3, 1107, -1, 8, 3, 4, 3, 99}, {8}));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 3, 1107, -1, 8, 3, 4, 3, 99}, {9}));
    }

    TEST_METHOD(diagnosticCodeProducedByProgram_PositionModeJumpTests)
    {
        Assert::AreEqual(1, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9}, {1}));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9}, {0}));
    }

    TEST_METHOD(diagnosticCodeProducedByProgram_ImmediateModeJumpTests)
    {
        Assert::AreEqual(1, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1}, {1}));
        Assert::AreEqual(0, CurrentDay::diagnosticCodeProducedByProgram(std::vector<int>{3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1}, {0}));
    }

    TEST_METHOD(diagnosticCodeProducedByProgram_JumpAndComparisonLargerTest)
    {
        std::vector<int> largerProgram
        {
            3, 21, 1008, 21, 8, 20, 1005, 20, 22, 107, 8, 21, 20, 1006, 20, 31,
            1106, 0, 36, 98, 0, 0, 1002, 21, 125, 20, 4, 20, 1105, 1, 46, 104,
            999, 1105, 1, 46, 1101, 1000, 1, 20, 4, 20, 1105, 1, 46, 98, 99
        };

        Assert::AreEqual(999, CurrentDay::diagnosticCodeProducedByProgram(largerProgram, {7}));
        Assert::AreEqual(1000, CurrentDay::diagnosticCodeProducedByProgram(largerProgram, {8}));
        Assert::AreEqual(1001, CurrentDay::diagnosticCodeProducedByProgram(largerProgram, {9}));
    }

};
