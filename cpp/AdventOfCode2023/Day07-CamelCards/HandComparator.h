#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day07
{

class HandComparator
{
public:
    HandComparator(char joker = '\0');

    bool operator()(const std::string& firstHand, const std::string& secondHand) const;

private:
    char m_joker;

    bool isFirstHandWeakerTypeThanSecondHand(const std::string& firstHand, const std::string& secondHand) const;
    bool isFirstHandWeakerCardOrderThanSecondHand(const std::string& firstHand, const std::string& secondHand) const;
    std::vector<int> getFrequenciesForHand(const std::string& hand) const;
    int getCardValue(char card) const;
};

}
}
}
