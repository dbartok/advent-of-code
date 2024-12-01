#include "Day14-DiskDefragmentation.h"

#include "DefragmenterGrid.h"
#include <AdventOfCode2017/Day10-KnotHash/Day10-KnotHash.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <sstream>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <cassert>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned GRID_SIZE = 128;

}

namespace AdventOfCode
{
namespace Year2017
{
namespace Day14
{

using AdventOfCode::Year2017::Day10::knotHashDenseString;

std::vector<bool> hexStringDigitsToBoolVector(const std::string& hexString)
{
    const size_t numHexCharsFitIn64BitUnsigned = 64 / 4;

    if (hexString.size() % numHexCharsFitIn64BitUnsigned != 0)
    {
        throw std::runtime_error("The hexString size has to be divisible by " + std::to_string(numHexCharsFitIn64BitUnsigned) + ".");
    }

    std::vector<bool> boolVector;

    for (size_t hexStringSubStrBegin = 0; hexStringSubStrBegin < hexString.size(); hexStringSubStrBegin += numHexCharsFitIn64BitUnsigned)
    {
        std::string hexStringSubstr = hexString.substr(hexStringSubStrBegin, numHexCharsFitIn64BitUnsigned);

        std::stringstream hexStringStream;
        hexStringStream << hexStringSubstr;

        uint64_t u;
        hexStringStream >> std::hex >> u;

        const std::bitset<64> bitset{u};

        for (size_t i = 0; i < bitset.size(); ++i)
        {
            boolVector.push_back(bitset.test(bitset.size() - 1 - i));
        }
    }

    return boolVector;
}

DefragmenterGrid::DiskGrid createDiskGridFromKeyString(const std::string& keyString)
{
    DefragmenterGrid::DiskGrid diskGrid;

    for (unsigned rowIndex = 0; rowIndex < GRID_SIZE; ++rowIndex)
    {
        std::string rowKeyString = keyString + "-" + std::to_string(rowIndex);
        std::string rowKnotHashString = knotHashDenseString(rowKeyString);
        std::vector<bool> row = hexStringDigitsToBoolVector(rowKnotHashString);
        diskGrid.push_back(std::move(row));
    }

    return diskGrid;
}

unsigned numSquaresUsed(const std::string& keyString)
{
    DefragmenterGrid::DiskGrid diskGrid = createDiskGridFromKeyString(keyString);
    DefragmenterGrid defragmenterGrid{std::move(diskGrid)};
    return defragmenterGrid.numSquaresUsed();
}

unsigned numRegionsOfAdjcacentSquares(const std::string& keyString)
{
    DefragmenterGrid::DiskGrid diskGrid = createDiskGridFromKeyString(keyString);
    DefragmenterGrid defragmenterGrid{std::move(diskGrid)};
    return defragmenterGrid.numRegionsOfAdjcacentSquares();
}

}
}
}
