#include "Day22-SlamShuffle.h"

#include <AdventOfCodeCommon/UnittestExtraDefinitions.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day22;

TEST_CLASS(Day22SlamShuffle)
{
public:

    TEST_METHOD(cardsAfterShuffle_SimpleTests)
    {
        std::vector<std::string> instructions1 =
        {
            "deal with increment 7",
            "deal into new stack",
            "deal into new stack",
        };
        Assert::AreEqual(std::vector<unsigned>{0, 3, 6, 9, 2, 5, 8, 1, 4, 7}, CurrentDay::cardsAfterShuffle(instructions1, 10));

        std::vector<std::string> instructions2 =
        {
            "cut 6",
            "deal with increment 7",
            "deal into new stack"
        };
        Assert::AreEqual(std::vector<unsigned>{3, 0, 7, 4, 1, 8, 5, 2, 9, 6}, CurrentDay::cardsAfterShuffle(instructions2, 10));

        std::vector<std::string> instructions3 =
        {
            "deal with increment 7",
            "deal with increment 9",
            "cut -2"
        };
        Assert::AreEqual(std::vector<unsigned>{6, 3, 0, 7, 4, 1, 8, 5, 2, 9}, CurrentDay::cardsAfterShuffle(instructions3, 10));

        std::vector<std::string> instructions4 =
        {
            "deal into new stack",
            "cut -2",
            "deal with increment 7",
            "cut 8",
            "cut -4",
            "deal with increment 7",
            "cut 3",
            "deal with increment 9",
            "deal with increment 3",
            "cut -1"
        };
        Assert::AreEqual(std::vector<unsigned>{9, 2, 5, 8, 1, 4, 7, 0, 3, 6}, CurrentDay::cardsAfterShuffle(instructions4, 10));
    }

    TEST_METHOD(cardAtPositionAfterMultipleShuffles_SimpleTests)
    {
        std::vector<std::string> instructions1 =
        {
            "deal with increment 7",
            "deal into new stack",
            "deal into new stack",
        };

        Assert::AreEqual(0ll, static_cast<long long>(CurrentDay::cardAtPositionAfterMultipleShuffles(instructions1, 7, 2, 0)));
    }
};
