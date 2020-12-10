#include "Day10-AdapterArray.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

class AdapterOrganizer
{
public:
    AdapterOrganizer(std::vector<int> joltageRatings)
        : m_joltageRatings{std::move(joltageRatings)}
    {
        std::sort(m_joltageRatings.begin(), m_joltageRatings.end());

        m_joltageRatings.insert(m_joltageRatings.begin(), 0);
        m_joltageRatings.insert(m_joltageRatings.end(), m_joltageRatings.back() + 3);
    }

    int getNumOneAndThreeJoltDifferencesMultiplied() const
    {
        const int numOneMagnitudeDifferences = numGivenJoltageDifferences(1);
        const int numThreeMagnitudeDifferences = numGivenJoltageDifferences(3);

        return numOneMagnitudeDifferences * numThreeMagnitudeDifferences;
    }

    int64_t getNumDistinctAdapterArrangements() const
    {
        std::vector<int64_t> joltageRatingIndexToNumArrangements(m_joltageRatings.size());
        joltageRatingIndexToNumArrangements.at(0) = 1;

        for (size_t i = 0; i < m_joltageRatings.size(); ++i)
        {
            for (int precursorIndex = i - 1;
                 precursorIndex >= 0 && m_joltageRatings.at(i) - m_joltageRatings.at(precursorIndex) <= 3;
                 --precursorIndex)
            {
                joltageRatingIndexToNumArrangements.at(i) += joltageRatingIndexToNumArrangements.at(precursorIndex);
            }
        }

        return joltageRatingIndexToNumArrangements.back();
    }

private:
    std::vector<int> m_joltageRatings;

    int numGivenJoltageDifferences(int targetDifference) const
    {
        int result = 0;
        for (auto joltageRatingIter = m_joltageRatings.cbegin(); joltageRatingIter != std::prev(m_joltageRatings.cend()); ++joltageRatingIter)
        {
            if (*std::next(joltageRatingIter) - *joltageRatingIter == targetDifference)
            {
                ++result;
            }
        }

        return result;
    }
};


int numOneAndThreeJoltDifferencesMultiplied(std::vector<int> joltageRatings)
{
    AdapterOrganizer adapterOrganizer{joltageRatings};
    return adapterOrganizer.getNumOneAndThreeJoltDifferencesMultiplied();
}

int64_t numDistinctAdapterArrangements(std::vector<int> joltageRatings)
{
    AdapterOrganizer adapterOrganizer{joltageRatings};
    return adapterOrganizer.getNumDistinctAdapterArrangements();
}

}
