#include "Day03-RucksackReorganization.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day03;

TEST_CLASS(Day03RucksackReorganization)
{
public:

    TEST_METHOD(sumOfSharedItemPriorities_SimpleTests)
    {
        Assert::AreEqual(157, CurrentDay::sumOfSharedItemPriorities(m_lines));
    }

    TEST_METHOD(sumOfGroupBadgePriorities_SimpleTests)
    {
        Assert::AreEqual(70, CurrentDay::sumOfGroupBadgePriorities(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "vJrwpWtwJgWrhcsFMMfFFhFp",
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
        "PmmdzqPrVvPwwTWBwg",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
        "ttgJtRGJQctTZtZT",
        "CrZsJsPPZsGzwwsLwLmpwMDw"
    };
};
