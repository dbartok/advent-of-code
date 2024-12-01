#include "Day21-FractalArt.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day21;

TEST_CLASS(Day21FractalArt)
{
public:

    TEST_METHOD(numPixelsOnSmallIterations_SimpleTests)
    {
        Assert::AreEqual(4u, CurrentDay::numPixelsOnSmallIterations(m_enhancementRuleLines, 1));
    }


    TEST_METHOD(numPixelsOnLargeIterations_SimpleTests)
    {
        Assert::AreEqual(12u, CurrentDay::numPixelsOnLargeIterations(m_enhancementRuleLines, 2));
    }

private:
    const std::vector<std::string> m_enhancementRuleLines =
    {
        "../.# => ##./#../...",
        ".#./..#/### => #..#/..../..../#..#"
    };

};
