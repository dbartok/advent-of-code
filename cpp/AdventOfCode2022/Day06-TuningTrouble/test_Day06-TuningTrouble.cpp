#include "Day06-TuningTrouble.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day06;

TEST_CLASS(Day06TuningTrouble)
{
public:

    TEST_METHOD(numCharactersProcessedBeforeStartOfPacketMarker_SimpleTests)
    {
        Assert::AreEqual(7, CurrentDay::numCharactersProcessedBeforeStartOfPacketMarker(m_testInput1));
        Assert::AreEqual(5, CurrentDay::numCharactersProcessedBeforeStartOfPacketMarker(m_testInput2));
        Assert::AreEqual(6, CurrentDay::numCharactersProcessedBeforeStartOfPacketMarker(m_testInput3));
        Assert::AreEqual(10, CurrentDay::numCharactersProcessedBeforeStartOfPacketMarker(m_testInput4));
        Assert::AreEqual(11, CurrentDay::numCharactersProcessedBeforeStartOfPacketMarker(m_testInput5));
    }

    TEST_METHOD(numCharactersProcessedBeforeStartOfMessage_SimpleTests)
    {
        Assert::AreEqual(19, CurrentDay::numCharactersProcessedBeforeStartOfMessage(m_testInput1));
        Assert::AreEqual(23, CurrentDay::numCharactersProcessedBeforeStartOfMessage(m_testInput2));
        Assert::AreEqual(23, CurrentDay::numCharactersProcessedBeforeStartOfMessage(m_testInput3));
        Assert::AreEqual(29, CurrentDay::numCharactersProcessedBeforeStartOfMessage(m_testInput4));
        Assert::AreEqual(26, CurrentDay::numCharactersProcessedBeforeStartOfMessage(m_testInput5));
    }

private:
    const std::string m_testInput1 = "mjqjpqmgbljsphdztnvjfqwrcgsmlb";
    const std::string m_testInput2 = "bvwbjplbgvbhsrlpgdmjqwftvncz";
    const std::string m_testInput3 = "nppdvjthqldpwncqszvftbrmjlhg";
    const std::string m_testInput4 = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg";
    const std::string m_testInput5 = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";

};
