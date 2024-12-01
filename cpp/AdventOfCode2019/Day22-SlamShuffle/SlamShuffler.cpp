#include "SlamShuffler.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/integer/mod_inverse.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day22
{

SlamShuffler::SlamShuffler(std::vector<ShuffleInstruction> instructions, BigNumber deckSize, BigNumber numIterations)
    : m_instructions{std::move(instructions)}
    , m_deckSize{deckSize}
    , m_numIterations{numIterations}
{

}

BigNumber SlamShuffler::getCardAtPosition(BigNumber position)
{
    BigNumber iterOneResult = getWhereCardComesFrom(position);
    BigNumber iterTwoResult = getWhereCardComesFrom(iterOneResult);

    // Subtract the following equations:
    // slope * position + offset = iterOneResult
    // slope * iterOneResult + offset = iterTwoResult
    // -> slope = (iterOneResult - iterTwoResult) / (position - iterOneResult)
    BigNumber slope = (iterOneResult - iterTwoResult) * boost::integer::mod_inverse(position - iterOneResult + m_deckSize, m_deckSize) % m_deckSize;
    BigNumber offset = (iterOneResult - slope * position + m_deckSize * position * slope) % m_deckSize;

    // For 2 iterations:
    // result = slope * (slope * position + offset) + offset
    // For m_numIterations iterations:
    // (slope^m_numIterations) * position + (slope^(m_numIterations - 1))) * offset + (slope^(m_numIterations - 2))) * offset + ... + offset
    // (slope^m_numIterations) * position + (slope^m_numIterations - 1) / (slope - 1) * B
    BigNumber slopeToTheNumberOfIterations = boost::multiprecision::powm(slope, m_numIterations, m_deckSize);
    BigNumber firstTerm = slopeToTheNumberOfIterations * position;
    BigNumber secondTerm = (slopeToTheNumberOfIterations - 1) * boost::integer::mod_inverse(slope - 1 + m_deckSize, m_deckSize) * offset;

    return (firstTerm + secondTerm) % m_deckSize;
}

std::vector<unsigned> SlamShuffler::getAllCardsAfterSingleIteration()
{
    std::vector<unsigned> allCards;

    for (int i = 0; i < m_deckSize; ++i)
    {
        auto cardAtPosition = getWhereCardComesFrom(i);
        allCards.push_back(unsigned{cardAtPosition});
    }

    return allCards;
}

BigNumber SlamShuffler::getWhereCardComesFrom(BigNumber position) const
{
    for (auto instructionIter = m_instructions.crbegin(); instructionIter != m_instructions.crend(); ++instructionIter)
    {
        position = executeInReverse(*instructionIter, position);
    }

    return position;
}

BigNumber SlamShuffler::executeInReverse(const ShuffleInstruction& instruction, BigNumber position) const
{
    if (instruction.type == DEAL_INTO_NEW_STACK)
    {
        return m_deckSize - 1 - position;
    }
    else if (instruction.type == CUT)
    {
        return (position + instruction.arg + m_deckSize) % m_deckSize;
    }
    else
    {
        BigNumber inverse = boost::integer::mod_inverse(BigNumber{instruction.arg}, m_deckSize);
        return inverse * position % m_deckSize;
    }
}

}
}
}
