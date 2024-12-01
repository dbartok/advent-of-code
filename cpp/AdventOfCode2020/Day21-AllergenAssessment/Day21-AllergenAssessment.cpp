#include "Day21-AllergenAssessment.h"

#include "FoodListAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day21
{

Food parseFoodLine(const std::string& foodLine)
{
    const std::regex foodLineRegex{R"(([\w\s]+)\s\(contains\s([\w\s,]+)\))"};
    std::smatch matches;
    std::regex_search(foodLine, matches, foodLineRegex);

    if (matches.size() != 3)
    {
        throw std::runtime_error("Invalid food line: " + foodLine);
    }

    const std::string ingredientsString = matches[1];
    std::vector<std::string> ingredients;
    boost::split(ingredients, ingredientsString, boost::is_any_of(" "));

    const std::string markedAllergensString = matches[2];
    std::vector<std::string> markedAllergens;
    boost::split(markedAllergens, markedAllergensString, boost::is_any_of(", "), boost::token_compress_on);

    return Food{ingredients, markedAllergens};
}


std::vector<Food> parseFoodLines(const std::vector<std::string>& foodLines)
{
    std::vector<Food> foods;

    for(const auto& line : foodLines)
    {
        Food food = parseFoodLine(line);
        foods.push_back(std::move(food));
    }

    return foods;
}

int numAppearancesOfIngredientsNotContainingAllergens(const std::vector<std::string>& foodLines)
{
    std::vector<Food> foods = parseFoodLines(foodLines);
    FoodListAnalyzer foodListAnalyzer(std::move(foods));
    foodListAnalyzer.determineIngredientAllergenRelationship();
    return foodListAnalyzer.getNumAppearancesOfIngredientsNotContainingAllergens();
}

std::string canonicalDangerousIngredientList(const std::vector<std::string>& foodLines)
{
    std::vector<Food> foods = parseFoodLines(foodLines);
    FoodListAnalyzer foodListAnalyzer(std::move(foods));
    foodListAnalyzer.determineIngredientAllergenRelationship();
    std::vector<std::string> allergenicIngredients = foodListAnalyzer.getAllergenicIngredientsOrderedByAllergen();

    return boost::join(allergenicIngredients, ",");
}

}
}
}
