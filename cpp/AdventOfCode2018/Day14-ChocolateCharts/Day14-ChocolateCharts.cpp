#include "Day14-ChocolateCharts.h"

#include "RecipeGenerator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const unsigned NUM_ADDITIONAL_RECIPES = 10;
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day14
{

std::string scoresOfTenRecipesAfterSeveralRecipes(unsigned numRecipes)
{
    RecipeGenerator recipeGenerator;

    recipeGenerator.generateUntilNumRecipesReachThreshold(numRecipes + NUM_ADDITIONAL_RECIPES);

    return recipeGenerator.getLastNRecipesSequence(NUM_ADDITIONAL_RECIPES);
}

unsigned numRecipesBeforeSequenceAppears(const std::string& targetSequence)
{
    RecipeGenerator recipeGenerator;

    recipeGenerator.generateUntilTargetSequenceOccurs(targetSequence);

    return recipeGenerator.getNumRecipes() - targetSequence.length();
}

}
}
}
