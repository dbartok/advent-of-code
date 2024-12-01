#include "Day18-Duet.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day18;

TEST_CLASS(Day18Duet)
{
public:

    TEST_METHOD(valueOfFirstRecoveredFrequency_SimpleTests)
    {
        std::vector<std::string> instructionStrings =
        {
            "set a 1",
            "add a 2",
            "mul a a",
            "mod a 5",
            "snd a",
            "set a 0",
            "rcv a",
            "jgz a -1",
            "set a 1",
            "jgz a -2"
        };

        Assert::AreEqual(4ll, CurrentDay::valueOfFirstRecoveredFrequency(instructionStrings));
    }

    TEST_METHOD(numTimesProgram1Sent_SimpleTests)
    {
        std::vector<std::string> instructionStrings =
        {
            "snd 1",
            "snd 2",
            "snd p",
            "rcv a",
            "rcv b",
            "rcv c",
            "rcv d"
        };

        Assert::AreEqual(3u, CurrentDay::numTimesProgram1Sent(instructionStrings));
    }

};
