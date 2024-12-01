#include "Day02-InventoryManagement.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day02;

TEST_CLASS(Day02InventoryManagement)
{
public:

    TEST_METHOD(checksumTwoOrThreeOfAnyLetter_SimpleTests)
    {
        std::vector<std::string> words =
        {
            "abcdef",
            "bababc",
            "abbcde",
            "abcccd",
            "aabcdd",
            "abcdee",
            "ababab"
        };

        Assert::AreEqual(4u * 3u, CurrentDay::checksumTwoOrThreeOfAnyLetter(words));
    }

    TEST_METHOD(commonLettersBetweenOneCharacterDiff_SimpleTests)
    {
        std::vector<std::string> words =
        {
            "abcde",
            "fghij",
            "klmno",
            "pqrst",
            "fguij",
            "axcye",
            "wvxyz"
        };

        Assert::AreEqual(std::string{"fgij"}, CurrentDay::commonLettersBetweenOneCharacterDiff(words));
    }



};
