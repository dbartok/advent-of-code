#include "Day22-SandSlabs.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day22;

TEST_CLASS(Day22SandSlabs)
{
public:

    TEST_METHOD(numBricksSafeToDisintegrate_SimpleTests)
    {
        Assert::AreEqual(5, CurrentDay::numBricksSafeToDisintegrate(m_lines));
    }

    TEST_METHOD(sumOfNumBricksFallingAcrossAllDisintegrations_SimpleTests)
    {
        Assert::AreEqual(7, CurrentDay::sumOfNumBricksFallingAcrossAllDisintegrations(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "1,0,1~1,2,1",
        "0,0,2~2,0,2",
        "0,2,3~2,2,3",
        "0,0,4~0,2,4",
        "2,0,5~2,2,5",
        "0,1,6~2,1,6",
        "1,1,8~1,1,9"
    };
};
