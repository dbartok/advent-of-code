#include "Day16-PacketDecoder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day16;

TEST_CLASS(Day16PacketDecoder)
{
public:

    TEST_METHOD(sumOfAllVersionNumbersInPackets_SimpleTests)
    {
        Assert::AreEqual(16ll, CurrentDay::sumOfAllVersionNumbersInPackets("8A004A801A8002F478"));
        Assert::AreEqual(12ll, CurrentDay::sumOfAllVersionNumbersInPackets("620080001611562C8802118E34"));
        Assert::AreEqual(23ll, CurrentDay::sumOfAllVersionNumbersInPackets("C0015000016115A2E0802F182340"));
        Assert::AreEqual(31ll, CurrentDay::sumOfAllVersionNumbersInPackets("A0016C880162017C3686B18A3D4780"));
    }

    TEST_METHOD(evaluateExpression_SimpleTests)
    {
        Assert::AreEqual(3ll, CurrentDay::evaluateExpression("C200B40A82"));
        Assert::AreEqual(54ll, CurrentDay::evaluateExpression("04005AC33890"));
        Assert::AreEqual(7ll, CurrentDay::evaluateExpression("880086C3E88112"));
        Assert::AreEqual(9ll, CurrentDay::evaluateExpression("CE00C43D881120"));
        Assert::AreEqual(1ll, CurrentDay::evaluateExpression("D8005AC2A8F0"));
        Assert::AreEqual(0ll, CurrentDay::evaluateExpression("F600BC2D8F"));
        Assert::AreEqual(0ll, CurrentDay::evaluateExpression("9C005AC2F8F0"));
        Assert::AreEqual(1ll, CurrentDay::evaluateExpression("9C0141080250320F1802104A08"));
    }

};
