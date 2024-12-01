#include "Day13-TransparentOrigami.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day13;

TEST_CLASS(Day13TransparentOrigami)
{
public:

    TEST_METHOD(numVisibleDotsAfterFirstFold_SimpleTests)
    {
        Assert::AreEqual(17u, CurrentDay::numVisibleDotsAfterFirstFold(m_lines));
    }

    TEST_METHOD(thermalCameraActivationCode_SimpleTests)
    {
        std::string expectedSerializedMessage =
            std::string{"#####\n"} +
            std::string{"#...#\n"} +
            std::string{"#...#\n"} +
            std::string{"#...#\n"} +
            std::string{"#####"};

        Assert::AreEqual(expectedSerializedMessage, CurrentDay::thermalCameraActivationCode(m_lines));
    }

private:
    const std::vector<std::string>& m_lines =
    {
        "6,10",
        "0,14",
        "9,10",
        "0,3",
        "10,4",
        "4,11",
        "6,0",
        "6,12",
        "4,1",
        "0,13",
        "10,12",
        "3,4",
        "3,0",
        "8,4",
        "1,10",
        "2,14",
        "8,10",
        "9,0",
        "",
        "fold along y=7",
        "fold along x=5"
    };
};
