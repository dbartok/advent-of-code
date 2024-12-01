#include "Day20-GrovePositioningSystem.h"

#include "EncryptedFileMixer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <iterator>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int64_t DECRYPTION_KEY_FIRST_PART = 1;
const int64_t DECRYPTION_KEY_SECOND_PART = 811589153;
const unsigned NUM_MIXES_FIRST_PART = 1;
const unsigned NUM_MIXES_SECOND_PART = 10;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day20
{

std::vector<int64_t> parseEncrypedFileLines(const std::vector<std::string>& encryptedFileLines)
{
    std::vector<int64_t> encryptedFile;

    std::transform(encryptedFileLines.cbegin(), encryptedFileLines.end(), std::back_inserter(encryptedFile), [](const auto& line)
                   {
                       return std::stoi(line);
                   });

    return encryptedFile;
}

int64_t sumOfGroveCoordinates(const std::vector<std::string>& encryptedFileLines)
{
    std::vector<int64_t> encryptedFile = parseEncrypedFileLines(encryptedFileLines);

    EncryptedFileMixer encryptedFileMixer{encryptedFile, DECRYPTION_KEY_FIRST_PART};

    encryptedFileMixer.mix(NUM_MIXES_FIRST_PART);

    return encryptedFileMixer.getSumOfGroveCoordinates();
}

int64_t sumOfGroveCoordinatesWithDecryptionRoutine(const std::vector<std::string>& encryptedFileLines)
{
    std::vector<int64_t> encryptedFile = parseEncrypedFileLines(encryptedFileLines);

    EncryptedFileMixer encryptedFileMixer{encryptedFile, DECRYPTION_KEY_SECOND_PART};

    encryptedFileMixer.mix(NUM_MIXES_SECOND_PART);

    return encryptedFileMixer.getSumOfGroveCoordinates();
}

}
}
}