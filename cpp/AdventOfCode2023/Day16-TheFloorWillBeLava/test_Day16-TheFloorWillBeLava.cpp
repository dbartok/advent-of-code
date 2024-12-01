#include "Day16-TheFloorWillBeLava.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day16;

TEST_CLASS(Day16TheFloorWillBeLava)
{
public:

    TEST_METHOD(numEnergizedTiles_SimpleTests)
    {
        Assert::AreEqual(46, CurrentDay::numEnergizedTiles(m_lines));
    }

    TEST_METHOD(maxNumEnergizedTiles_SimpleTests)
    {
        Assert::AreEqual(51, CurrentDay::maxNumEnergizedTiles(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        ".|...\\....",
        "|.-.\\.....",
        ".....|-...",
        "........|.",
        "..........",
        ".........\\",
        "..../.\\\\..",
        ".-.-/..|..",
        ".|....-|.\\",
        "..//.|...."
    };
};
