#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <array>
#include <vector>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day04
{

using GuardIDType = unsigned;

template <typename T>
using MinutesMap = std::array<T, 60>;

using MinutesToBoolMap = MinutesMap<bool>;
using MinuteAndAmountPair = std::pair<unsigned, unsigned>;

class Guard
{
public:
    void addDay(MinutesToBoolMap hourMap);

    unsigned getHoursSlept() const;
    MinuteAndAmountPair getMostSleptMinute() const;

private:
    std::vector<MinutesToBoolMap> m_minuteMapForEachDay;
};

class GuardDutyKeeper
{
public:
    void addDayForGuard(GuardIDType guardID, MinutesToBoolMap hourMap);

    GuardIDType getMostSleptGuardID() const;
    GuardIDType getMostFrequentlySleptMinuteGlobalGuardID() const;
    MinuteAndAmountPair getMostFrequentlySleptMinute(GuardIDType guardID) const;

private:
    std::unordered_map<GuardIDType, Guard> m_guards;
};

}
}
}
