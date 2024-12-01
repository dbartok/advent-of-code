#include "Day08-MemoryManeuver.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day08;

TEST_CLASS(Day08MemoryManeuver)
{
public:

    TEST_METHOD(sumOfAllMetadataEntries_SimpleTests)
    {
        Assert::AreEqual(138u, CurrentDay::sumOfAllMetadataEntries(nodeNumbers));
    }

    TEST_METHOD(valueOfRootNode_SimpleTests)
    {
        Assert::AreEqual(66u, CurrentDay::valueOfRootNode(nodeNumbers));
    }

private:
    std::vector<unsigned> m_nodeNumbers = {2, 3, 0, 3, 10, 11, 12, 1, 1, 0, 1, 99, 2, 1, 1, 2};
};
