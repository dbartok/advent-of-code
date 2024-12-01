#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
#include <vector>
#include <deque>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day11
{

using LargeNumberType = int64_t;

class Operation
{
public:
    using SharedPtr = std::shared_ptr<Operation>;

    virtual LargeNumberType apply(LargeNumberType operand) const = 0;
};

class Addition : public Operation
{
public:
    Addition(int addend)
        : m_factor{addend}
    {

    }

    LargeNumberType apply(LargeNumberType operand) const override
    {
        return operand + m_factor;
    }

private:
    int m_factor;
};

class Multiplication : public Operation
{
public:
    Multiplication(int factor)
        : m_factor{factor}
    {

    }

    LargeNumberType apply(LargeNumberType operand) const override
    {
        return operand * m_factor;
    }

private:
    int m_factor;
};

class Square : public Operation
{
public:
    LargeNumberType apply(LargeNumberType operand) const override
    {
        return operand * operand;
    }
};

class Monkey
{
public:
    Monkey(std::vector<int> startingItems, Operation::SharedPtr operation, int testModulus, unsigned testTrueTarget, unsigned testFalseTarget);

    void setAllMonkeys(std::vector<Monkey>* allMonkeys);
    void setStorageModulus(int storageModulus);
    void executeTurn(int worryLevelDivisor);
    void receiveItem(int item);

    int getNumItemsInspected() const;
    int getTestModulus() const;

private:
    std::deque<LargeNumberType> m_currentItems;
    Operation::SharedPtr m_operation;
    int m_testModulus;
    unsigned m_testTrueTarget;
    unsigned m_testFalseTarget;

    std::vector<Monkey>* m_allMonkeys;
    int m_storageModulus = -1;

    int m_numItemsInspected = 0;

    void processItem(LargeNumberType item, int worryLevelDivisor);
};

class MonkeyGroupSimulator
{
public:
    MonkeyGroupSimulator(std::vector<Monkey> monkeys, int worryLevelDivisor);

    void simulate(unsigned numRounds);

    int64_t getLevelOfMonkeyBusiness() const;

private:
    std::vector<Monkey> m_monkeys;
    int m_worryLevelDivisor;

    void simulateRound();

    int determineStorageModulus() const;
};

}
}
}
