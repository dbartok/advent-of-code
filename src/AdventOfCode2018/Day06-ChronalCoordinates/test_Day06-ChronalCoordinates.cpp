#include "Day06-ChronalCoordinates.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace AoC = AdventOfCode;

TEST_CLASS(Day06ChronalCoordinates)
{
public:

    TEST_METHOD(sizeOfLargestNonInfiniteArea_SimpleTests)
    {
        Assert::AreEqual(17u, AoC::sizeOfLargestNonInfiniteArea(m_lines));
    }


    TEST_METHOD(sizeOfAreaWithinGivenDistance_SimpleTests)
    {
        Assert::AreEqual(16u, AoC::sizeOfAreaWithinGivenDistance(m_lines, 32));
    }

private:
    std::vector<std::string> m_lines =
    {
        "1, 1",
        "1, 6",
        "8, 3",
        "3, 4",
        "5, 5",
        "8, 9"
    };
};
