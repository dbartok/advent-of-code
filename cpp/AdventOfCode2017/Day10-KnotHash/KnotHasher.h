#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day10
{

class KnotHasher
{
public:
    static const size_t STANDARD_LIST_SIZE = 256;
    static const size_t MAX_LIST_SIZE_THAT_FITS_IN_A_BYTE = 256;
    static const unsigned STANDARD_NUM_ROUNDS = 64;
    static const size_t STANDARD_BLOCK_SIZE = 16;

    KnotHasher(std::vector<unsigned char> bytesToHash, size_t listSize = STANDARD_LIST_SIZE, size_t blockSize = STANDARD_BLOCK_SIZE);

    // Execute a single round of the "Knot Hash" algorithm
    // The bytes meant to be hashed are used as knot lengths in the internal list
    void executeHashRound();

    // Get the first two hash elements multiplied together
    unsigned firstTwoMultiplied() const;

    // Get the dense hash string after executing the given number of rounds
    // Hash elements are combined with bitwise XOR in groups of the block size
    std::string denseHashStringAfterMultipleRounds(unsigned numRounds = STANDARD_NUM_ROUNDS);

private:
    std::vector<unsigned char> m_knotLengths;

    std::vector<unsigned> m_hashResultNumbers;
    size_t m_blockSize;

    unsigned m_currentPos;
    unsigned m_skipSize;

    void circularReverseHashResultNumbers(size_t beginPos, size_t endPos);
    std::vector<unsigned char> createDenseHashBytes();

    static std::string bytesToStandardString(const std::vector<unsigned char>& bytes);
};

}
}
}
