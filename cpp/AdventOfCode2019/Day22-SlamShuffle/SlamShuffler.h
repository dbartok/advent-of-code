#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day22
{

using BigNumber = boost::multiprecision::int256_t;

enum ShuffleType
{
    DEAL_INTO_NEW_STACK,
    DEAL_WITH_INCREMENT,
    CUT,
};

struct ShuffleInstruction
{
    ShuffleType type;
    int arg;
};

class SlamShuffler
{
public:
    SlamShuffler(std::vector<ShuffleInstruction> instructions, BigNumber deckSize, BigNumber numIterations);

    BigNumber getCardAtPosition(BigNumber position);

    std::vector<unsigned> getAllCardsAfterSingleIteration();

private:
    std::vector<ShuffleInstruction> m_instructions;
    BigNumber m_deckSize;
    BigNumber m_numIterations;

    BigNumber getWhereCardComesFrom(BigNumber position) const;
    BigNumber executeInReverse(const ShuffleInstruction& instruction, BigNumber position) const;
};

}
}
}
