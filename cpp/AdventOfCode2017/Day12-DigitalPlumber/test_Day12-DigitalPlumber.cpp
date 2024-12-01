#include "Day12-DigitalPlumber.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day12;

TEST_CLASS(Day12DigitalPlumber)
{
public:

    TEST_METHOD(numNodesInGroupNodeZero_SimpleTests)
    {
        Assert::AreEqual(6u, CurrentDay::numNodesInGroupNodeZero(m_neighborsLines));
    }

    TEST_METHOD(numTotalGroups_SimpleTests)
    {
        Assert::AreEqual(2u, CurrentDay::numTotalGroups(m_neighborsLines));
    }

private:
    std::vector<std::string> m_neighborsLines =
    {
        "0 <-> 2",
        "1 <-> 1",
        "2 <-> 0, 3, 4",
        "3 <-> 2, 4",
        "4 <-> 2, 3, 6",
        "5 <-> 6",
        "6 <-> 4, 5"
    };
};
