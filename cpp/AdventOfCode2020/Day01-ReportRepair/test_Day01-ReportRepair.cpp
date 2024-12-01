#include "Day01-ReportRepair.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day01;

TEST_CLASS(Day01ReportRepair)
{
public:

    TEST_METHOD(productOfTwoEntriesWithGivenSum_SimpleTests)
    {
        Assert::AreEqual(514579, CurrentDay::productOfTwoEntriesWithGivenSum(m_entries));
    }

    TEST_METHOD(productOfThreeEntriesWithGivenSum_SimpleTests)
    {
        Assert::AreEqual(241861950, CurrentDay::productOfThreeEntriesWithGivenSum(m_entries));
    }

private:
    std::vector<int> m_entries{1721, 979, 366, 299, 675, 1456};
};
