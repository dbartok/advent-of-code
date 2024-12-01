#include "Day12-PassagePathing.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day12;

TEST_CLASS(Day12PassagePathing)
{
public:

    TEST_METHOD(numPathsWithSmallCavesVisitedAtMostOnce_SimpleTests)
    {
        Assert::AreEqual(10u, CurrentDay::numPathsWithSmallCavesVisitedAtMostOnce(m_smallExampleLines));
    }

    TEST_METHOD(numPathsWithSmallCavesVisitedAtMostOnce_LargerExample)
    {
        Assert::AreEqual(19u, CurrentDay::numPathsWithSmallCavesVisitedAtMostOnce(m_largerExampleLines));
    }

    TEST_METHOD(numPathsWithSmallCavesVisitedAtMostOnce_EvenLargerExample)
    {
        Assert::AreEqual(226u, CurrentDay::numPathsWithSmallCavesVisitedAtMostOnce(m_evenLargerExampleLines));
    }

    TEST_METHOD(numPathsWithSmallCavesVisitedAtMostTwice_SimpleTests)
    {
        Assert::AreEqual(36u, CurrentDay::numPathsWithSmallCavesVisitedAtMostTwice(m_smallExampleLines));
    }

    TEST_METHOD(numPathsWithSmallCavesVisitedAtMostTwice_LargerExample)
    {
        Assert::AreEqual(103u, CurrentDay::numPathsWithSmallCavesVisitedAtMostTwice(m_largerExampleLines));
    }

    TEST_METHOD(numPathsWithSmallCavesVisitedAtMostTwice_EvenLargerExample)
    {
        Assert::AreEqual(3509u, CurrentDay::numPathsWithSmallCavesVisitedAtMostTwice(m_evenLargerExampleLines));
    }

private:
    const std::vector<std::string>& m_smallExampleLines =
    {
        "start-A",
        "start-b",
        "A-c",
        "A-b",
        "b-d",
        "A-end",
        "b-end"
    };

    const std::vector<std::string>& m_largerExampleLines =
    {
        "dc-end",
        "HN-start",
        "start-kj",
        "dc-start",
        "dc-HN",
        "LN-dc",
        "HN-end",
        "kj-sa",
        "kj-HN",
        "kj-dc"
    };

    const std::vector<std::string>& m_evenLargerExampleLines =
    {
        "fs-end",
        "he-DX",
        "fs-he",
        "start-DX",
        "pj-DX",
        "end-zg",
        "zg-sl",
        "zg-pj",
        "pj-he",
        "RW-he",
        "fs-DX",
        "pj-RW",
        "zg-RW",
        "start-pj",
        "he-WI",
        "zg-he",
        "pj-fs",
        "start-RW"
    };
};
