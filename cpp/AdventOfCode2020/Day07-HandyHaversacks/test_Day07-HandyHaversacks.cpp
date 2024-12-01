#include "Day07-HandyHaversacks.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day07;

TEST_CLASS(Day07HandyHaversacks)
{
public:

    TEST_METHOD(numBagColorsThatCanContainShinyGold_SimpleTests)
    {
        Assert::AreEqual(4, CurrentDay::numBagColorsThatCanContainShinyGold(m_lines));
    }

    TEST_METHOD(numTotalBagsContainedInsideShinyGold_SimpleTests)
    {
        Assert::AreEqual(32, CurrentDay::numTotalBagsContainedInsideShinyGold(m_lines));
    }

    TEST_METHOD(numTotalBagsContainedInsideShinyGold_DeeplyNestedBags)
    {
        std::vector<std::string> lines =
        {
            "shiny gold bags contain 2 dark red bags.",
            "dark red bags contain 2 dark orange bags.",
            "dark orange bags contain 2 dark yellow bags.",
            "dark yellow bags contain 2 dark green bags.",
            "dark green bags contain 2 dark blue bags.",
            "dark blue bags contain 2 dark violet bags.",
            "dark violet bags contain no other bags."
        };

        Assert::AreEqual(126, CurrentDay::numTotalBagsContainedInsideShinyGold(lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "light red bags contain 1 bright white bag, 2 muted yellow bags.",
        "dark orange bags contain 3 bright white bags, 4 muted yellow bags.",
        "bright white bags contain 1 shiny gold bag.",
        "muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.",
        "shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.",
        "dark olive bags contain 3 faded blue bags, 4 dotted black bags.",
        "vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.",
        "faded blue bags contain no other bags.",
        "dotted black bags contain no other bags."
    };

};
