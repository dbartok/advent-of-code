#pragma once

#include "GuardDutyKeeper.h"

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day04
{

void Guard::addDay(MinutesToBoolMap hourMap)
{
    m_minuteMapForEachDay.push_back(std::move(hourMap));
}

unsigned Guard::getHoursSlept() const
{
    return std::accumulate(m_minuteMapForEachDay.cbegin(), m_minuteMapForEachDay.cend(), 0u, [](unsigned acc, const MinutesToBoolMap& hourMap)
                           {
                               return acc + std::count(hourMap.cbegin(), hourMap.cend(), true);
                           });
}

MinuteAndAmountPair Guard::getMostSleptMinute() const
{
    MinutesMap<unsigned> initialMinutesSum;
    std::fill(initialMinutesSum.begin(), initialMinutesSum.end(), 0);
    auto sleepValues = std::accumulate(m_minuteMapForEachDay.cbegin(), m_minuteMapForEachDay.cend(), initialMinutesSum,
                                       [](MinutesMap<unsigned>& acc, const MinutesToBoolMap& hourMap) noexcept
                                       {
                                           for (size_t i = 0; i < hourMap.size(); ++i)
                                           {
                                               if (hourMap[i])
                                               {
                                                   ++acc[i];
                                               }
                                           }

                                           return acc;
                                       });

    auto maxIter = std::max_element(sleepValues.cbegin(), sleepValues.cend());
    return std::make_pair(maxIter - sleepValues.cbegin(), *maxIter);
}

void GuardDutyKeeper::addDayForGuard(GuardIDType guardID, MinutesToBoolMap hourMap)
{
    m_guards[guardID].addDay(hourMap);
}

GuardIDType GuardDutyKeeper::getMostSleptGuardID() const
{
    auto maxElemIter = std::max_element(m_guards.cbegin(), m_guards.cend(), [](const auto& lhs, const auto& rhs)
                                        {
                                            return lhs.second.getHoursSlept() < rhs.second.getHoursSlept();
                                        });

    return maxElemIter->first;
}

GuardIDType GuardDutyKeeper::getMostFrequentlySleptMinuteGlobalGuardID() const
{
    std::unordered_map<GuardIDType, unsigned> guardsToMostSleptMinute;

    for (const auto& elem : m_guards)
    {
        guardsToMostSleptMinute.insert(std::make_pair(elem.first, elem.second.getMostSleptMinute().second));
    }

    auto maxElemIter = std::max_element(guardsToMostSleptMinute.cbegin(), guardsToMostSleptMinute.cend(),
                                        [](const auto& lhs, const auto& rhs) noexcept
                                        {
                                            return lhs.second < rhs.second;
                                        });

    return maxElemIter->first;
}

MinuteAndAmountPair GuardDutyKeeper::getMostFrequentlySleptMinute(GuardIDType guardID) const
{
    return m_guards.at(guardID).getMostSleptMinute();
}

}
}
}
