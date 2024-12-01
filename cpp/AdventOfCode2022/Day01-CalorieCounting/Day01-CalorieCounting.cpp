#include "Day01-CalorieCounting.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <algorithm>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day01
{
using CalorieTextSection = std::vector<std::string>;
using CalorieSequence = std::vector<int>;
using CalorieWriteup = std::vector<CalorieSequence>;

CalorieSequence parseCalorieTextSection(const CalorieTextSection& calorieTextSection)
{
    CalorieSequence calorieSequence;
    std::transform(calorieTextSection.cbegin(), calorieTextSection.cend(), std::back_inserter(calorieSequence), [](const auto& elem) { return std::stoi(elem);  });
    return calorieSequence;
}

CalorieWriteup parseCalorieLines(const std::vector<std::string>& calorieLines)
{
    std::vector<CalorieTextSection> calorieTextSections;
    boost::split(calorieTextSections, calorieLines, [](const auto& elem) {return elem.empty(); });

    CalorieWriteup calorieWriteup;
    for (const auto& calorieTextSection : calorieTextSections)
    {
        CalorieSequence calorieSequence = parseCalorieTextSection(calorieTextSection);
        calorieWriteup.push_back(std::move(calorieSequence));
    }

    return calorieWriteup;
}

CalorieSequence flattenCalorieWriteup(const CalorieWriteup& calorieWriteup)
{
    CalorieSequence calorieSequence;

    std::transform(calorieWriteup.cbegin(), calorieWriteup.cend(), std::back_inserter(calorieSequence), [](const auto& sequence)
                   {
                       return std::accumulate(sequence.cbegin(), sequence.cend(), 0, [](const auto& acc, const auto& calorie) {return acc + calorie; });
                   });

    return calorieSequence;
}

int maxTotalCaloriesCarried(const std::vector<std::string>& calorieLines)
{
    CalorieWriteup calorieWriteup = parseCalorieLines(calorieLines);
    CalorieSequence totalCalories = flattenCalorieWriteup(calorieWriteup);

    return *std::max_element(totalCalories.cbegin(), totalCalories.cend());
}

int totalCaloriesCarriedByTopThreeElves(const std::vector<std::string>& calorieLines)
{
    CalorieWriteup calorieWriteup = parseCalorieLines(calorieLines);
    CalorieSequence totalCalories = flattenCalorieWriteup(calorieWriteup);

    std::sort(totalCalories.begin(), totalCalories.end(), std::greater<int>());
    return totalCalories.at(0) + totalCalories.at(1) + totalCalories.at(2);
}

}
}
}