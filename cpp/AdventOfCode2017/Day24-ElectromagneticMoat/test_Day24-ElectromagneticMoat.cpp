#include "Day24-ElectromagneticMoat.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day24;

TEST_CLASS(Day24ElectromagneticMoat)
{
public:

    TEST_METHOD(strengthOfStrongestBridge_SimpleTests)
    {
        Assert::AreEqual(31u, CurrentDay::strengthOfStrongestBridge(m_componentLines));
    }

    TEST_METHOD(strengthOfStrongestLongestBridge_SimpleTests)
    {
        Assert::AreEqual(19u, CurrentDay::strengthOfStrongestLongestBridge(m_componentLines));
    }

private:
    const std::vector<std::string> m_componentLines =
    {
        "0/2",
        "2/2",
        "2/3",
        "3/4",
        "3/5",
        "0/1",
        "10/1",
        "9/10"
    };
};
