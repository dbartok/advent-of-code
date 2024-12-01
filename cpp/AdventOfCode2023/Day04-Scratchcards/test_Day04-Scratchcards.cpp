#include "Day04-Scratchcards.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day04;

TEST_CLASS(Day04Scratchcards)
{
public:

    TEST_METHOD(numPointsWorthInTotal_SimpleTests)
    {
        Assert::AreEqual(13, CurrentDay::numPointsWorthInTotal(m_lines));
    }

    TEST_METHOD(numTotalScratchcardsIncludingOriginalsAndCopies_SimpleTests)
    {
        Assert::AreEqual(30, CurrentDay::numTotalScratchcardsIncludingOriginalsAndCopies(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53",
        "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19",
        "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1",
        "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83",
        "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36",
        "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11"
    };

};
