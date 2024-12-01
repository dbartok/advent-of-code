#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day03
{

template <class T>
class InfiniteGrid
{
public:
    // Get a copy of the value at the given coordinates
    // If the value is unset, return the default-initialized value of T
    T getValue(int x, int y) const;

    // Set value at the given coordinates
    void setValue(int x, int y, T value);

private:
    using IntPair = std::pair<int, int>;

    // This is very simplistic, recommend to use boost::hash_combine or similar if performance is a concern at all
    struct SimpleIntPairHash
    {
        size_t operator()(const IntPair& ip) const noexcept
        {
            return 31 * static_cast<size_t>(ip.first) + static_cast<size_t>(ip.second);
        }
    };

    std::unordered_map<IntPair, T, SimpleIntPairHash> m_valueToCoordinateMap;
};

template <class T>
T InfiniteGrid<T>::getValue(int x, int y) const
{
    IntPair key{x, y};

    auto foundIter = m_valueToCoordinateMap.find(key);
    if (foundIter == m_valueToCoordinateMap.end())
    {
        return T{};
    }
    else
    {
        return foundIter->second;
    }
}

template <class T>
void InfiniteGrid<T>::setValue(int x, int y, T value)
{
    IntPair key{x, y};

    auto foundIter = m_valueToCoordinateMap.find(key);
    if (foundIter == m_valueToCoordinateMap.end())
    {
        m_valueToCoordinateMap.emplace(key, std::move(value));
    }
    else
    {
        foundIter->second = std::move(value);
    }
}

}
}
}
