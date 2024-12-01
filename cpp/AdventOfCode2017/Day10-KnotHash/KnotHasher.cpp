#include "KnotHasher.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <cassert>
#include <sstream>
#include <iomanip>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day10
{

KnotHasher::KnotHasher(std::vector<unsigned char> bytesToHash, size_t listSize, size_t blockSize)
    : m_knotLengths{std::move(bytesToHash)}
    , m_hashResultNumbers(listSize) // We'd like to avoid resolving to the initializer list here
    , m_blockSize{blockSize}
    , m_currentPos{0}
    , m_skipSize{0}
{
    if (m_blockSize == 0)
    {
        throw std::runtime_error("Block size has to be non-zero.");
    }

    if (listSize % blockSize != 0)
    {
        throw std::runtime_error("List size has to be divisible by the block size.");
    }

    std::iota(m_hashResultNumbers.begin(), m_hashResultNumbers.end(), 0);
}

void KnotHasher::executeHashRound()
{
    for (auto length : m_knotLengths)
    {
        size_t endPos;
        if (length == 0)
        {
            endPos = m_currentPos;
        }
        else
        {
            endPos = (m_currentPos + length - 1) % m_hashResultNumbers.size();
        }

        circularReverseHashResultNumbers(m_currentPos, endPos);

        m_currentPos = (m_currentPos + length + m_skipSize) % m_hashResultNumbers.size();
        ++m_skipSize;
    }
}

unsigned KnotHasher::firstTwoMultiplied() const
{
    if (m_hashResultNumbers.size() < 2)
    {
        throw std::runtime_error("Not enough elements.");
    }

    return static_cast<unsigned>(m_hashResultNumbers[0]) * m_hashResultNumbers[1];
}

std::string KnotHasher::denseHashStringAfterMultipleRounds(unsigned numRounds)
{
    if (m_hashResultNumbers.size() > MAX_LIST_SIZE_THAT_FITS_IN_A_BYTE)
    {
        throw std::runtime_error("Dense hash string is only available if the selected list size fits in a byte.");
    }

    for (unsigned i = 0; i < numRounds; ++i)
    {
        executeHashRound();
    }

    std::vector<unsigned char> denseBytes = createDenseHashBytes();
    return bytesToStandardString(denseBytes);
}

void KnotHasher::circularReverseHashResultNumbers(size_t beginPos, size_t endPos)
{
    unsigned numSwaps;
    if (endPos >= beginPos)
    {
        numSwaps = (endPos - beginPos + 1) / 2;
    }
    else
    {
        numSwaps = (m_hashResultNumbers.size() - (beginPos - endPos) + 1) / 2;
    }

    for (unsigned i = 0; i < numSwaps; ++i)
    {
        std::swap(m_hashResultNumbers[beginPos], m_hashResultNumbers[endPos]);

        beginPos = (beginPos == m_hashResultNumbers.size() - 1) ? 0 : beginPos + 1;
        endPos = (endPos == 0) ? m_hashResultNumbers.size() - 1 : endPos - 1;
    }
}

std::vector<unsigned char> KnotHasher::createDenseHashBytes()
{
    assert(m_hashResultNumbers.size() <= MAX_LIST_SIZE_THAT_FITS_IN_A_BYTE);
    assert(m_hashResultNumbers.size() % m_blockSize == 0);

    std::vector<unsigned char> denseHashBytes;
    for (size_t i = 0; i < m_hashResultNumbers.size(); i += m_blockSize)
    {
        auto blockBeginIter = m_hashResultNumbers.begin() + i;
        unsigned char blockValue = std::accumulate(blockBeginIter + 1, blockBeginIter + m_blockSize, *blockBeginIter, [](unsigned char acc, unsigned char elem) noexcept
                                                   {
                                                       return acc ^= elem;
                                                   });

        denseHashBytes.push_back(blockValue);
    }

    return denseHashBytes;
}

std::string KnotHasher::bytesToStandardString(const std::vector<unsigned char>& bytes)
{
    std::ostringstream denseHashStringStream;

    for (auto byte : bytes)
    {
        denseHashStringStream << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned>(byte);
    }

    return denseHashStringStream.str();
}

}
}
}
