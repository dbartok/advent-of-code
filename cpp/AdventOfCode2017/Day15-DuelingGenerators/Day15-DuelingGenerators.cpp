#include "Day15-DuelingGenerators.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>
#include <cassert>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned GENERATOR_A_MULTIPLIER = 16807;
const unsigned GENERATOR_B_MULTIPLIER = 48271;

const unsigned GENERATOR_A_MULTIPLE_CRITERION = 4;
const unsigned GENERATOR_B_MULTIPLE_CRITERION = 8;

const unsigned GENERATOR_MODULUS = 2'147'483'647;

const unsigned NO_CRITERIA_NUM_ROUNDS = 40'000'000;
const unsigned CRITERIA_NUM_ROUNDS = 5'000'000;

const unsigned JUDGE_NUM_BINARY_DIGITS_TO_MATCH = 16;

}

namespace AdventOfCode
{
namespace Year2017
{
namespace Day15
{

unsigned generatorStartFromLine(const std::string& line)
{
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(" "));

    if (tokens.size() != 5)
    {
        throw std::runtime_error("Input line needs to have exactly 5 tokens.");
    }

    return boost::lexical_cast<unsigned>(tokens[4]);
}

constexpr uint64_t generateNextValue(uint64_t prevValue, unsigned multiplier, unsigned multipleCriterion) noexcept
{
    uint64_t currValue{};
    while (true)
    {
        currValue = (prevValue * multiplier) % GENERATOR_MODULUS;

        if (currValue % multipleCriterion == 0)
        {
            break;
        }

        prevValue = currValue;
    }

    return currValue;

}

unsigned judgeFinalCount(unsigned generatorAStart, unsigned generatorBStart, unsigned numRounds, bool isUsingCriteria)
{
    const double judgeModulusDouble = (pow(2, JUDGE_NUM_BINARY_DIGITS_TO_MATCH));
    assert(judgeModulusDouble <= std::numeric_limits<unsigned>::max());

    const unsigned judgeModulus = static_cast<unsigned>(judgeModulusDouble);

    uint64_t generatorAPrevValue = generatorAStart;
    uint64_t generatorBPrevValue = generatorBStart;

    unsigned judgeScore = 0;

    for (unsigned i = 0; i < numRounds; ++i)
    {
        const uint64_t generatorACurrValue = generateNextValue(generatorAPrevValue, GENERATOR_A_MULTIPLIER, isUsingCriteria ? GENERATOR_A_MULTIPLE_CRITERION : 1);
        const uint64_t generatorBCurrValue = generateNextValue(generatorBPrevValue, GENERATOR_B_MULTIPLIER, isUsingCriteria ? GENERATOR_B_MULTIPLE_CRITERION : 1);

        if (generatorACurrValue % judgeModulus == generatorBCurrValue % judgeModulus)
        {
            ++judgeScore;
        }

        generatorAPrevValue = generatorACurrValue;
        generatorBPrevValue = generatorBCurrValue;
    }

    return judgeScore;
}

unsigned judgeFinalCountNoCriteria(unsigned generatorAStart, unsigned generatorBStart)
{
    return judgeFinalCount(generatorAStart, generatorBStart, NO_CRITERIA_NUM_ROUNDS, false);
}

unsigned judgeFinalCountWithCriteria(unsigned generatorAStart, unsigned generatorBStart)
{
    return judgeFinalCount(generatorAStart, generatorBStart, CRITERIA_NUM_ROUNDS, true);
}

}
}
}
