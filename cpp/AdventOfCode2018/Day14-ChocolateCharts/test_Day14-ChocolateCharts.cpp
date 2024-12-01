#include "Day14-ChocolateCharts.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day14;

TEST_CLASS(Day14ChocolateCharts)
{
public:

    TEST_METHOD(scoresOfTenRecipesAfterSeveralRecipes_SimpleTests)
    {
        Assert::AreEqual(std::string{"5158916779"}, CurrentDay::scoresOfTenRecipesAfterSeveralRecipes(9));
        Assert::AreEqual(std::string{"0124515891"}, CurrentDay::scoresOfTenRecipesAfterSeveralRecipes(5));
        Assert::AreEqual(std::string{"9251071085"}, CurrentDay::scoresOfTenRecipesAfterSeveralRecipes(18));
        Assert::AreEqual(std::string{"5941429882"}, CurrentDay::scoresOfTenRecipesAfterSeveralRecipes(2018));
    }

    TEST_METHOD(numRecipesBeforeSequenceAppears_SimpleTests)
    {
        Assert::AreEqual(9u, CurrentDay::numRecipesBeforeSequenceAppears("51589"));
        Assert::AreEqual(5u, CurrentDay::numRecipesBeforeSequenceAppears("01245"));
        Assert::AreEqual(18u, CurrentDay::numRecipesBeforeSequenceAppears("92510"));
        Assert::AreEqual(2018u, CurrentDay::numRecipesBeforeSequenceAppears("59414"));
    }

};
