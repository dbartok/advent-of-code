#include "Day15-RambunctiousRecitation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day15;

TEST_CLASS(Day15RambunctiousRecitation)
{
public:

    TEST_METHOD(nthNumberSpokenSmallN_SimpleTests)
    {
        Assert::AreEqual(436, CurrentDay::nthNumberSpokenSmallN({0, 3, 6}));
        Assert::AreEqual(1, CurrentDay::nthNumberSpokenSmallN({1, 3, 2}));
        Assert::AreEqual(10, CurrentDay::nthNumberSpokenSmallN({2, 1, 3}));
        Assert::AreEqual(27, CurrentDay::nthNumberSpokenSmallN({1, 2, 3}));
        Assert::AreEqual(78, CurrentDay::nthNumberSpokenSmallN({2, 3, 1}));
        Assert::AreEqual(438, CurrentDay::nthNumberSpokenSmallN({3, 2, 1}));
        Assert::AreEqual(1836, CurrentDay::nthNumberSpokenSmallN({3, 1, 2}));
    }

    TEST_METHOD(nthNumberSpokenLargeN_SimpleTests)
    {
        Assert::AreEqual(175594, CurrentDay::nthNumberSpokenLargeN({0, 3, 6}));
        Assert::AreEqual(2578, CurrentDay::nthNumberSpokenLargeN({1, 3, 2}));
        Assert::AreEqual(3544142, CurrentDay::nthNumberSpokenLargeN({2, 1, 3}));
        Assert::AreEqual(261214, CurrentDay::nthNumberSpokenLargeN({1, 2, 3}));
        Assert::AreEqual(6895259, CurrentDay::nthNumberSpokenLargeN({2, 3, 1}));
        Assert::AreEqual(18, CurrentDay::nthNumberSpokenLargeN({3, 2, 1}));
        Assert::AreEqual(362, CurrentDay::nthNumberSpokenLargeN({3, 1, 2}));
    }

};
