#include "Day10-KnotHash.h"

#include "KnotHasher.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <array>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

std::array<unsigned char, 5> EXTRA_SALT_BYTES = {17, 31, 73, 47, 23};

}

namespace AdventOfCode
{
namespace Year2017
{
namespace Day10
{

unsigned firstTwoMultipliedAfterKnotting(size_t listSize, const std::vector<unsigned>& lengths)
{
    std::vector<unsigned char> bytesToHash;
    bytesToHash.reserve(lengths.size());

    // Lengths are taken directly from the input, so we need to validate the numbers
    std::transform(lengths.cbegin(), lengths.cend(), std::back_inserter(bytesToHash), [](unsigned lengthElem)
                   {
                       if (lengthElem > 255)
                       {
                           throw std::runtime_error("An input is larger than 255.");
                       }

                       return static_cast<unsigned char>(lengthElem);
                   });

    // We are only interested in the first round of the hashing, so the block size is actually irrelevant as long as it's valid
    // Let's use 1 as the block size as that can divide any number of elements, therefore always valid
    KnotHasher knotHasher{bytesToHash, listSize, 1};
    knotHasher.executeHashRound();
    return knotHasher.firstTwoMultiplied();
}

std::string knotHashDenseString(const std::string& stringToHash)
{
    auto stringToHashTrimmed(stringToHash);
    boost::trim(stringToHashTrimmed);

    std::vector<unsigned char> bytesToHash;
    bytesToHash.reserve(stringToHashTrimmed.size());

    // Each character is converted to a byte
    std::transform(stringToHashTrimmed.cbegin(), stringToHashTrimmed.cend(), std::back_inserter(bytesToHash), [](char c) noexcept
                   {
                       return static_cast<unsigned char>(c);
                   });

    // Add the extra bytes defined in the puzzle
    bytesToHash.insert(bytesToHash.end(), EXTRA_SALT_BYTES.cbegin(), EXTRA_SALT_BYTES.cend());

    KnotHasher knotHasher{bytesToHash};
    return knotHasher.denseHashStringAfterMultipleRounds();
}

}
}
}
