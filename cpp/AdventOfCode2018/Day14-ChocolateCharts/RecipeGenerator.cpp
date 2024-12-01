#include "RecipeGenerator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <sstream>
#include <iterator>
#include <algorithm>
#include <array>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const std::array<unsigned, 2> DEFAULT_RECIPES = {3, 7};
}

namespace AdventOfCode
{
namespace Year2018
{
namespace Day14
{

RecipeGenerator::RecipeGenerator()
    : m_recipes{DEFAULT_RECIPES.cbegin(), DEFAULT_RECIPES.cend()}
    , m_elfOneIter{m_recipes.begin()}
    , m_elfTwoIter{std::next(m_recipes.begin())}
{

}

std::string RecipeGenerator::getLastNRecipesSequence(unsigned n) const
{
    auto beginIter = m_recipes.begin();
    if (m_recipes.size() > n)
    {
        beginIter = m_recipes.end();
        while (n-- > 0)
        {
            --beginIter;
        }
    }

    std::ostringstream recipesStream;
    std::copy(beginIter, m_recipes.end(), std::ostream_iterator<unsigned>(recipesStream));

    return recipesStream.str();
}

unsigned RecipeGenerator::getNumRecipes() const
{
    return m_recipes.size();
}

void RecipeGenerator::generateUntilTargetSequenceOccurs(const std::string& targetSequence)
{
    generateUntil([this, targetSequence]() {return this->getLastNRecipesSequence(targetSequence.length()) == targetSequence; });
}


void RecipeGenerator::generateUntilNumRecipesReachThreshold(unsigned numRecipesThreshold)
{
    generateUntil([this, numRecipesThreshold]() {return this->m_recipes.size() == numRecipesThreshold; });
}

void RecipeGenerator::generateUntil(const std::function<bool()>& shouldStop)
{
    while (!shouldStop())
    {
        const unsigned nextRecipe = *m_elfOneIter + *m_elfTwoIter;

        if (nextRecipe >= 10)
        {
            m_recipes.push_back(1);

            if (shouldStop())
            {
                break;
            }
        }

        m_recipes.push_back(nextRecipe % 10);

        stepRecipeIterForwards(m_elfOneIter, (*m_elfOneIter) + 1);
        stepRecipeIterForwards(m_elfTwoIter, (*m_elfTwoIter) + 1);
    }
}

void RecipeGenerator::stepRecipeIterForwards(std::list<unsigned>::iterator& recipeIter, unsigned steps)
{
    for (unsigned i = 0; i < steps; ++i)
    {
        ++recipeIter;
        if (recipeIter == m_recipes.end())
        {
            recipeIter = m_recipes.begin();
        }
    }
}

}
}
}
