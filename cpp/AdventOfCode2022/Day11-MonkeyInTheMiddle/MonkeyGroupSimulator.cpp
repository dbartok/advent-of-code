#include "MonkeyGroupSimulator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/integer/common_factor.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day11
{

Monkey::Monkey(std::vector<int> startingItems, Operation::SharedPtr operation, int testModulus, unsigned testTrueTarget, unsigned testFalseTarget)
    : m_operation{std::move(operation)}
    , m_testModulus{testModulus}
    , m_testTrueTarget{testTrueTarget}
    , m_testFalseTarget{testFalseTarget}
{
    m_currentItems = {std::make_move_iterator(startingItems.begin()), std::make_move_iterator(startingItems.end())};
}

void Monkey::setAllMonkeys(std::vector<Monkey>* allMonkeys)
{
    m_allMonkeys = std::move(allMonkeys);
}

void Monkey::setStorageModulus(int storageModulus)
{
    m_storageModulus = storageModulus;
}

void Monkey::executeTurn(int worryLevelDivisor)
{
    while (!m_currentItems.empty())
    {
        const LargeNumberType item = m_currentItems.front();
        m_currentItems.pop_front();
        processItem(item, worryLevelDivisor);
    }
}

void Monkey::receiveItem(int item)
{
    m_currentItems.push_back(item);
}

int Monkey::getNumItemsInspected() const
{
    return m_numItemsInspected;
}

int Monkey::getTestModulus() const
{
    return m_testModulus;
}

void Monkey::processItem(LargeNumberType item, int worryLevelDivisor)
{
    LargeNumberType newWorryLevel = m_operation->apply(item);
    newWorryLevel /= worryLevelDivisor;
    newWorryLevel %= m_storageModulus;

    const unsigned target = (newWorryLevel % m_testModulus == 0) ? m_testTrueTarget : m_testFalseTarget;
    m_allMonkeys->at(target).receiveItem(newWorryLevel);

    ++m_numItemsInspected;
}

MonkeyGroupSimulator::MonkeyGroupSimulator(std::vector<Monkey> monkeys, int worryLevelDivisor)
    : m_monkeys{std::move(monkeys)}
    , m_worryLevelDivisor{worryLevelDivisor}
{
    const int storageModulus = determineStorageModulus();

    for (auto& monkey : m_monkeys)
    {
        monkey.setAllMonkeys(&m_monkeys);
        monkey.setStorageModulus(storageModulus);
    }
}

void MonkeyGroupSimulator::simulate(unsigned numRounds)
{
    for (unsigned iteration = 0; iteration < numRounds; ++iteration)
    {
        simulateRound();
    }
}

int64_t MonkeyGroupSimulator::getLevelOfMonkeyBusiness() const
{
    std::vector<Monkey> monkeysSortedAccordingToNumItemsInspected{m_monkeys.cbegin(), m_monkeys.cend()};
    std::sort(monkeysSortedAccordingToNumItemsInspected.begin(), monkeysSortedAccordingToNumItemsInspected.end(), [](const auto& lhs, const auto& rhs)
                {
                    return lhs.getNumItemsInspected() > rhs.getNumItemsInspected();
                });

    const Monkey& mostActiveMonkey = *monkeysSortedAccordingToNumItemsInspected.cbegin();
    const Monkey& secondMostActiveMonkey = *(monkeysSortedAccordingToNumItemsInspected.cbegin() + 1);

    return int64_t{mostActiveMonkey.getNumItemsInspected()} *secondMostActiveMonkey.getNumItemsInspected();
}

void MonkeyGroupSimulator::simulateRound()
{
    for (auto& monkey : m_monkeys)
    {
        monkey.executeTurn(m_worryLevelDivisor);
    }
}

int MonkeyGroupSimulator::determineStorageModulus() const
{
    return std::accumulate(m_monkeys.cbegin(), m_monkeys.cend(), 1, [](auto acc, const auto& monkey)
                           {
                               return boost::integer::lcm(acc, monkey.getTestModulus());
                           });
}

}
}
}
