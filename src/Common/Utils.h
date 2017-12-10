#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace AdventOfCode
{
namespace Utils
{

template <typename T>
void splitStringIntoTypedVector(const std::string& inputString, std::vector<T>& outputVector, char delimiter = ' ')
{
    std::istringstream inputStringStream(inputString);
    std::string token;

    T element;
    while (std::getline(inputStringStream, token, delimiter))
    {
        std::istringstream conversionStringStream(token);
        conversionStringStream >> element;

        outputVector.push_back(std::move(element));
    }
}

template <typename Iterator, typename Comparator>
bool allElementsEqual(Iterator first, Iterator last, const Comparator& comparator)
{
    // Zero elemnts
    if (first == last)
    {
        return true;
    }

    // Compare each element with the previous one
    return std::equal(std::next(first), last, first, comparator);
}

template <typename Iterator>
bool allElementsEqual(Iterator first, Iterator last)
{
    return allElementsEqual(first, last, [](const auto& lhs, const auto& rhs)
    {
        return lhs == rhs;
    });
}

}
}
