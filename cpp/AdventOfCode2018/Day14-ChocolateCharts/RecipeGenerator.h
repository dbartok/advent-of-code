#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <list>
#include <string>
#include <functional>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day14
{

using Recipes = std::list<unsigned>;

class RecipeGenerator
{
public:
    RecipeGenerator();

    std::string getLastNRecipesSequence(unsigned n) const;
    unsigned getNumRecipes() const;

    void generateUntilTargetSequenceOccurs(const std::string& targetSequence);
    void generateUntilNumRecipesReachThreshold(unsigned numRecipesThreshold);

private:
    Recipes m_recipes;
    Recipes::iterator m_elfOneIter;
    Recipes::iterator m_elfTwoIter;

    void generateUntil(const std::function<bool()>& shouldStop);
    void stepRecipeIterForwards(Recipes::iterator& recipeIter, unsigned steps);
};

}
}
}
