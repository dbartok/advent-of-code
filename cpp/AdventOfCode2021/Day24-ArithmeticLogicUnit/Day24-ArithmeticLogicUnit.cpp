#include "Day24-ArithmeticLogicUnit.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const size_t NUM_INPUT_INSTRUCTIONS = 14;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day24
{

// Example chunk from the puzzle:

// inp w
// mul x 0
// add x z
// mod x 26
// div z 1
// add x 10
// eql x w
// eql x 0
// mul y 0
// add y 25
// mul y x
// add y 1
// mul z y
// mul y 0
// add y w
// add y 12
// mul y x
// add z y

int monadChunkExample(int w, int z)
{
    int x = 0; // mul x 0
    x += z; // add x z
    x %= 26; // mod x 26
    z /= 1; // div z 1
    x += 10; // add x 10
    x = x == w ? 1 : 0; // eql x w
    x = x == 0 ? 1 : 0; // eql x 0
    int y = 0; // mul y 0
    y += 25; // add y 25
    y *= x; // mul y x
    y += 1; // add y 1
    z *= y; // mul z y
    y = 0; // mul y 0
    y += w; // add y w
    y += 12; // add y 12
    y *= x; // mul y x
    z += y; // add z y
    return z;
}

struct Params
{
    bool shouldDivideZBy26;
    int xAdd;
    int yAdd;
};

int monadChunkParametrized_v1(int w, int z, Params params)
{
    int x = 0; // mul x 0
    x += z; // add x z
    x %= 26; // mod x 26
    if (params.shouldDivideZBy26) z /= 26; // div z (1|26)
    x += params.xAdd; // add x (xAdd)
    x = x == w ? 1 : 0; // eql x w
    x = x == 0 ? 1 : 0; // eql x 0
    int y = 0; // mul y 0
    y += 25; // add y 25
    y *= x; // mul y x
    y += 1; // add y 1
    z *= y; // mul z y
    y = 0; // mul y 0
    y += w; // add y w
    y += params.yAdd; // add y (yAdd)
    y *= x; // mul y x
    z += y; // add z y
    return z;
}

int monadChunkParametrized_v2(int w, int z, Params params)
{
    const bool x = (z % 26 + params.xAdd) != w; // mul x 0; add x z; mod x 26; add x (xAdd); eql x w; eql x 0
    if (params.shouldDivideZBy26) z /= 26; // div z (1|26)
    if (x) z *= 26; // mul y 0; add y 25; mul y x; add y 1; mul z y
    if (x) z += w + params.yAdd; // mul y 0; add y w; add y (yAdd); mul y x; add z y
    return z;
}

int monadChunkParametrized_v3(int w, int z, Params params)
{
    const bool shouldIncreaseZ = (z % 26 + params.xAdd != w); // mul x 0; add x z; mod x 26; add x (xAdd); eql x w; eql x 0
    if (params.shouldDivideZBy26)
    {
        z /= 26; // div z (1|26)
    }
    if (shouldIncreaseZ)
    {
        z = z * 26 + w + params.yAdd; // mul y 0; add y 25; mul y x; add y 1; mul z y; mul y 0; add y w; add y (yAdd); mul y x; add z y
    }
    return z;
}

// Params from the input file
std::vector<Params> allParams =
{
                     // |   mod 26 stack                                                |   Equation             |   Simplified equation
                     // |---------------------------------------------------------------|------------------------|-------------------------
    {false, 10, 12}, // |   w1 + 12                                                     |                        |
    {false, 10, 10}, // |   w1 + 12 -> w2 + 10                                          |                        |
    {false, 12, 8},  // |   w1 + 12 -> w2 + 10 -> w3 + 8                                |                        |
    {false, 11, 4},  // |   w1 + 12 -> w2 + 10 -> w3 + 8 -> w4 + 4                      |                        |
    {true, 0, 3},    // |   w1 + 12 -> w2 + 10 -> w3 + 8                                |   w4 + 4 + 0 = w5      |   w4 + 4 = w5
    {false, 15, 10}, // |   w1 + 12 -> w2 + 10 -> w3 + 8 -> w6 + 10                     |                        |
    {false, 13, 6},  // |   w1 + 12 -> w2 + 10 -> w3 + 8 -> w6 + 10 -> w7 + 6           |                        |
    {true, -12, 13}, // |   w1 + 12 -> w2 + 10 -> w3 + 8 -> w6 + 10                     |   w7 + 6 - 12 = w8     |   w7 - 6 = w8
    {true, -15, 8},  // |   w1 + 12 -> w2 + 10 -> w3 + 8                                |   w6 + 10 - 15 = w9    |   w6 - 5 = w9
    {true, -15, 1},  // |   w1 + 12 -> w2 + 10                                          |   w3 + 8 - 15 = w10    |   w3 - 7 = w10
    {true, -4, 7},   // |   w1 + 12                                                     |   w2 + 10 - 4 = w11    |   w2 + 6 = w11
    {false, 10, 6},  // |   w1 + 12 -> w12 + 6                                          |                        |
    {true, -5, 9},   // |   w1 + 12                                                     |   w12 + 6 - 5 = w13    |   w12 + 1 = w13
    {true, -12, 9},  // |   <empty>                                                     |   w1 + 12 - 12 = w14   |   w1 = w14
};

// |   Possible input digit values   |   Largest value   |   Smallest value
// |---------------------------------|-------------------|--------------------
// |   w1 = [1..9]                   |   9               |   1
// |   w2 = w11 - 6                  |   3               |   1
// |   w3 = [8..9]                   |   9               |   8
// |   w4 = w5 - 4                   |   5               |   1
// |   w5 = [5..9]                   |   9               |   5
// |   w6 = [6..9]                   |   9               |   6
// |   w7 = [7..9]                   |   9               |   7
// |   w8 = w7 - 6                   |   3               |   1
// |   w9 = w6 - 5                   |   4               |   1
// |   w10 = w3 - 7                  |   2               |   1
// |   w11 = [7..9]                  |   9               |   7
// |   w12 = w13 - 1                 |   8               |   1
// |   w13 = [2..9]                  |   9               |   2
// |   w14 = w1                      |   9               |   1

const uint64_t SOLUTION_CANDIDATE_PART_ONE = 93959993429899ull;
const uint64_t SOLUTION_CANDIDATE_PART_TWO = 11815671117121ull;

void validateSolutionCandidate(uint64_t solutionCandidate)
{
    std::string solutionCandidateString = std::to_string(solutionCandidate);

    int z = 0;
    for (size_t i = 0; i < NUM_INPUT_INSTRUCTIONS; ++i)
    {
        const char c = solutionCandidateString.at(i);
        const int w = c - '0';
        auto params = allParams.at(i);
        z = monadChunkParametrized_v3(w, z, params);
    }
    if (z != 0)
    {
        throw std::runtime_error("Nonzero validation result: " + std::to_string(z));
    }
}

uint64_t largestModelNumberAcceptedByMonad()
{
    validateSolutionCandidate(SOLUTION_CANDIDATE_PART_ONE);
    return SOLUTION_CANDIDATE_PART_ONE;
}

uint64_t smallestModelNumberAcceptedByMonad()
{
    validateSolutionCandidate(SOLUTION_CANDIDATE_PART_TWO);
    return SOLUTION_CANDIDATE_PART_TWO;
}

}
}
}