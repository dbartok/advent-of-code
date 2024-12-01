#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day21
{

using SortedStringVector = std::vector<std::string>;

struct Food
{
    std::vector<std::string> ingredients;
    std::vector<std::string> markedAllergens;
};

class FoodListAnalyzer
{
public:
    FoodListAnalyzer(std::vector<Food> foods);

    void determineIngredientAllergenRelationship();

    int getNumAppearancesOfIngredientsNotContainingAllergens() const;
    std::vector<std::string> getAllergenicIngredientsOrderedByAllergen() const;

private:
    const std::vector<Food> m_foods;
    std::unordered_map<std::string, SortedStringVector> m_allergenToPossibleIngredients;
    std::map<std::string, std::string> m_allergenToContainingIngredient;

    void processIngredientAllergenRelationshipForFood(const Food& food);
    void updateIngredientConstraintsForAllergen(const std::string& allergen, std::vector<std::string> possibleIngredients);
    void resolveNextAllergen();
    void eliminateIngredientFromPossibilities(const std::string& resolvedAllergen, const std::string& resolvedIngredient);
    std::unordered_set<std::string> getIngredientsPossiblyContainingAllergens() const;
};

}
}
}
