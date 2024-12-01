#include "HandComparator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <unordered_map>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const std::string CARD_STRENGTH_ORDER_ASCENDING = "23456789TJQKA";

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day07
{

HandComparator::HandComparator(char joker)
    : m_joker{joker}
{

}

bool HandComparator::operator()(const std::string& firstHand, const std::string& secondHand) const
{
    if (isFirstHandWeakerTypeThanSecondHand(firstHand, secondHand))
    {
        return true;
    }

    if (isFirstHandWeakerTypeThanSecondHand(secondHand, firstHand))
    {
        return false;
    }

    return isFirstHandWeakerCardOrderThanSecondHand(firstHand, secondHand);
}

bool HandComparator::isFirstHandWeakerTypeThanSecondHand(const std::string& firstHand, const std::string& secondHand) const
{
    const std::vector<int> firstHandFrequencies = getFrequenciesForHand(firstHand);
    const std::vector<int> secondHandFrequencies = getFrequenciesForHand(secondHand);

    for (int i = 0; i < firstHandFrequencies.size(); ++i)
    {
        if (firstHandFrequencies.at(i) < secondHandFrequencies.at(i))
        {
            return true;
        }
        else if (firstHandFrequencies.at(i) > secondHandFrequencies.at(i))
        {
            return false;
        }
    }

    return false;
}

bool HandComparator::isFirstHandWeakerCardOrderThanSecondHand(const std::string& firstHand, const std::string& secondHand) const
{
    for (int i = 0; i < firstHand.size(); ++i)
    {
        const int firstHandCurrentCardValue = getCardValue(firstHand.at(i));
        const int secondHandCurrentCardValue = getCardValue(secondHand.at(i));

        if (firstHandCurrentCardValue < secondHandCurrentCardValue)
        {
            return true;
        }
        else if (firstHandCurrentCardValue > secondHandCurrentCardValue)
        {
            return false;
        }
    }

    throw std::runtime_error("Hand strength ordering cannot be determined");
}

std::vector<int> HandComparator::getFrequenciesForHand(const std::string& hand) const
{
    std::unordered_map<char, int> cardToFrequency;
    for (const char card : hand)
    {
        ++cardToFrequency[card];
    }

    int jokerFrequency = 0;
    const auto jokerFrequencyIter = cardToFrequency.find(m_joker);
    if (jokerFrequencyIter != cardToFrequency.cend())
    {
        jokerFrequency = jokerFrequencyIter->second;
        cardToFrequency.erase(jokerFrequencyIter);
    }

    std::vector<int> frequencies;
    for (const auto& cardAndFrequency : cardToFrequency)
    {
        frequencies.push_back(cardAndFrequency.second);
    }
    std::sort(frequencies.begin(), frequencies.end(), std::greater<int>());

    if (!frequencies.empty())
    {
        frequencies.front() += jokerFrequency;
    }
    else
    {
        frequencies.push_back(jokerFrequency);
    }

    return frequencies;
}

int HandComparator::getCardValue(char card) const
{
    if (card == m_joker)
    {
        return -1;
    }

    return CARD_STRENGTH_ORDER_ASCENDING.find(card);
}

}
}
}
