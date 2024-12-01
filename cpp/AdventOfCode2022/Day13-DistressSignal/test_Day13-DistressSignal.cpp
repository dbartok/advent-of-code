#include "Day13-DistressSignal.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day13;

TEST_CLASS(Day13DistressSignal)
{
public:

    TEST_METHOD(sumOfIndicesOfPairsInRightOrder_SimpleTests)
    {
        Assert::AreEqual(13, CurrentDay::sumOfIndicesOfPairsInRightOrder(m_lines));
    }

    TEST_METHOD(decoderKeyForDistressSignal_SimpleTests)
    {
        Assert::AreEqual(140, CurrentDay::decoderKeyForDistressSignal(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "[1,1,3,1,1]",
        "[1,1,5,1,1]",
        "",
        "[[1],[2,3,4]]",
        "[[1],4]",
        "",
        "[9]",
        "[[8,7,6]]",
        "",
        "[[4,4],4,4]",
        "[[4,4],4,4,4]",
        "",
        "[7,7,7,7]",
        "[7,7,7]",
        "",
        "[]",
        "[3]",
        "",
        "[[[]]]",
        "[[]]",
        "",
        "[1,[2,[3,[4,[5,6,7]]]],8,9]",
        "[1,[2,[3,[4,[5,6,0]]]],8,9]"
    };
};
