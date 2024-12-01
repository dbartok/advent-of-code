#include "Day22-ModeMaze.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day22;

TEST_CLASS(Day22ModeMaze)
{
public:

    TEST_METHOD(riskLevelOfSmallestArea_SimpleTests)
    {
        Assert::AreEqual(114u, CurrentDay::riskLevelOfSmallestArea(m_lines));
    }

    TEST_METHOD(fewestMinutesToTarget_SimpleTests)
    {
        Assert::AreEqual(45u, CurrentDay::fewestMinutesToTarget(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "depth: 510",
        "target: 10,10"
    };
};
