#include "Day04-HighEntropyPassphrases.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"

#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day04;

TEST_CLASS(Day04HighEntropyPassphrases)
{
public:

    TEST_METHOD(numPassphrasesNoDuplicateWords_SimpleTests)
    {
        std::vector<std::string> passphrases =
        {
            "aa bb cc dd ee",
            "aa bb cc dd aa",
            "aa bb cc dd aaa"
        };

        Assert::AreEqual(2u, CurrentDay::numPassphrasesNoDuplicateWords(passphrases));
    }

    TEST_METHOD(numPassphrasesNoAnagramWords_SimpleTests)
    {
        std::vector<std::string> passphrases =
        {
            "abcde fghij",
            "abcde xyz ecdab",
            "a ab abc abd abf abj",
            "iiii oiii ooii oooi oooo",
            "oiii ioii iioi iiio"
        };

        Assert::AreEqual(3u, CurrentDay::numPassphrasesNoAnagramWords(passphrases));
    }

};
