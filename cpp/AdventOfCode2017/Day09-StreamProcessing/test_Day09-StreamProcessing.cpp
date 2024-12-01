#include "Day09-StreamProcessing.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day09;

TEST_CLASS(Day09StreamProcessing)
{
public:

    TEST_METHOD(totalScoreForAllGroups_SimpleTests)
    {
        Assert::AreEqual(1u, CurrentDay::totalScoreForAllGroups("{}"));
        Assert::AreEqual(6u, CurrentDay::totalScoreForAllGroups("{{{}}}"));
        Assert::AreEqual(5u, CurrentDay::totalScoreForAllGroups("{{},{}}"));
        Assert::AreEqual(16u, CurrentDay::totalScoreForAllGroups("{{{},{},{{}}}}"));
        Assert::AreEqual(1u, CurrentDay::totalScoreForAllGroups("{<a>,<a>,<a>,<a>}"));
        Assert::AreEqual(9u, CurrentDay::totalScoreForAllGroups("{{<ab>},{<ab>},{<ab>},{<ab>}}"));
        Assert::AreEqual(9u, CurrentDay::totalScoreForAllGroups("{{<!!>},{<!!>},{<!!>},{<!!>}}"));
        Assert::AreEqual(3u, CurrentDay::totalScoreForAllGroups("{{<a!>},{<a!>},{<a!>},{<ab>}}"));
    }

    TEST_METHOD(totalGarbageCount_SimpleTests)
    {
        Assert::AreEqual(0u, CurrentDay::totalGarbageCount("<>"));
        Assert::AreEqual(17u, CurrentDay::totalGarbageCount("<random characters>"));
        Assert::AreEqual(3u, CurrentDay::totalGarbageCount("<<<<>"));
        Assert::AreEqual(2u, CurrentDay::totalGarbageCount("<{!>}>"));
        Assert::AreEqual(0u, CurrentDay::totalGarbageCount("<!!>"));
        Assert::AreEqual(0u, CurrentDay::totalGarbageCount("<!!!>>"));
        Assert::AreEqual(10u, CurrentDay::totalGarbageCount("<{o\"i!a,<{i<a>"));
    }

};
