#include "Day16-PermutationPromenade.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day16;

TEST_CLASS(Day16PermutationPromenade)
{
public:

    TEST_METHOD(orderAfterDanceMovesSingleRepetition_SimpleTests)
    {
        Assert::AreEqual(std::string{"baedc"}, CurrentDay::orderAfterDanceMovesSingleRepetition(m_danceMoveStrings, 5u));
    }

    TEST_METHOD(orderAfterDanceMovesRepetitions_SimpleTests)
    {
        Assert::AreEqual(std::string{"ceadb"}, CurrentDay::orderAfterDanceMovesRepetitions(m_danceMoveStrings, 2u, 5u));
    }

    TEST_METHOD(orderAfterDanceMovesRepetitions_RepetitionsLargerThanCycleSize)
    {
        Assert::AreEqual(std::string{"ceadb"}, CurrentDay::orderAfterDanceMovesRepetitions(m_danceMoveStrings, 6u, 5u));
        Assert::AreEqual(std::string{"ceadb"}, CurrentDay::orderAfterDanceMovesRepetitions(m_danceMoveStrings, 10u, 5u));
    }

private:
    const std::vector<std::string> m_danceMoveStrings =
    {
        "s1",
        "x3/4",
        "pe/b"
    };
};
