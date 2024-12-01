#include "Day12-RainRisk.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day12;

TEST_CLASS(Day12RainRisk)
{
public:

    TEST_METHOD(distanceToEndLocationShipMoves_SimpleTests)
    {
        Assert::AreEqual(25, CurrentDay::distanceToEndLocationShipMoves(m_lines));
    }

    TEST_METHOD(distanceToEndLocationWaypointMoves_SimpleTests)
    {
        Assert::AreEqual(286, CurrentDay::distanceToEndLocationWaypointMoves(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "F10",
        "N3",
        "F7",
        "R90",
        "F11"
    };

};
