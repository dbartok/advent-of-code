#include "FoodListAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day21
{

FoodListAnalyzer::FoodListAnalyzer(std::vector<Food> foods)
    : m_foods{std::move(foods)}
{

}

void FoodListAnalyzer::determineIngredientAllergenRelationship()
{
    for (const auto& food : m_foods)
    {
        processIngredientAllergenRelationshipForFood(food);
    }

    for (size_t i = 0; i < m_allergenToPossibleIngredients.size(); ++i)
    {
        resolveNextAllergen();
    }
}

int FoodListAnalyzer::getNumAppearancesOfIngredientsNotContainingAllergens() const
{
    const std::unordered_set<std::string> excludedIngredients = getIngredientsPossiblyContainingAllergens();

    return std::accumulate(m_foods.cbegin(), m_foods.cend(), 0, [&excludedIngredients](int outerAcc, const auto& food)
                            {
                                const auto& ingredients = food.ingredients;
                                return outerAcc + std::accumulate(ingredients.cbegin(), ingredients.cend(), 0, [&excludedIngredients](int innerAcc, const auto& ingredient)
                                                                    {
                                                                        return innerAcc + (excludedIngredients.find(ingredient) == excludedIngredients.cend());
                                                                    });
                            });
}

std::vector<std::string> FoodListAnalyzer::getAllergenicIngredientsOrderedByAllergen() const
{
    std::vector<std::string> allergenicIngredientsOrderedByAllergen;

    for (const auto& allergenAndContainingIngredient : m_allergenToContainingIngredient)
    {
        allergenicIngredientsOrderedByAllergen.push_back(allergenAndContainingIngredient.second);
    }

    return allergenicIngredientsOrderedByAllergen;
}

void FoodListAnalyzer::processIngredientAllergenRelationshipForFood(const Food& food)
{
    for (const auto& allergen : food.markedAllergens)
    {
        updateIngredientConstraintsForAllergen(allergen, food.ingredients);
    }
}

void FoodListAnalyzer::updateIngredientConstraintsForAllergen(const std::string& allergen, std::vector<std::string> possibleIngredients)
{
    std::sort(possibleIngredients.begin(), possibleIngredients.end());
    auto insertionResult = m_allergenToPossibleIngredients.emplace(allergen, possibleIngredients);
    const auto wasInserted = insertionResult.second;
    if (wasInserted)
    {
        return;
    }

    auto& foundElement = *insertionResult.first;
    auto& preexistingIngredientConstraints = foundElement.second;

    SortedStringVector combinedIngredientConstraints;
    std::set_intersection(preexistingIngredientConstraints.cbegin(), preexistingIngredientConstraints.cend(),
                            possibleIngredients.cbegin(), possibleIngredients.cend(),
                            std::back_inserter(combinedIngredientConstraints));

    preexistingIngredientConstraints = combinedIngredientConstraints;
}

void FoodListAnalyzer::resolveNextAllergen()
{
    for (const auto& allergenAndPossibleIngredients : m_allergenToPossibleIngredients)
    {
        const auto& allergen = allergenAndPossibleIngredients.first;
        const auto& possibleIngredients = allergenAndPossibleIngredients.second;
        if (m_allergenToContainingIngredient.find(allergen) == m_allergenToContainingIngredient.cend() && possibleIngredients.size() == 1)
        {
            const std::string& resolvedIngredient = possibleIngredients.front();
            m_allergenToContainingIngredient[allergen] = resolvedIngredient;
            eliminateIngredientFromPossibilities(allergen, possibleIngredients.front());
            return;
        }
    }
}

void FoodListAnalyzer::eliminateIngredientFromPossibilities(const std::string& resolvedAllergen, const std::string& resolvedIngredient)
{
    for (auto& allergenAndPossibleIngredients : m_allergenToPossibleIngredients)
    {
        const auto& allergen = allergenAndPossibleIngredients.first;
        auto& possibleIngredients = allergenAndPossibleIngredients.second;
        if (allergen != resolvedAllergen)
        {
            possibleIngredients.erase(std::remove(possibleIngredients.begin(), possibleIngredients.end(), resolvedIngredient), possibleIngredients.end());
        }
    }
}

std::unordered_set<std::string> FoodListAnalyzer::getIngredientsPossiblyContainingAllergens() const
{
    std::unordered_set<std::string> ingredientsPossiblyContainingAllergens;

    for (const auto& allergenAndPossibleIngredients : m_allergenToPossibleIngredients)
    {
        for (const auto& possibleIngredient : allergenAndPossibleIngredients.second)
        {
            ingredientsPossiblyContainingAllergens.insert(possibleIngredient);
        }
    }

    return ingredientsPossiblyContainingAllergens;
}

}
}
}
