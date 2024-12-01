#include "SignalDecoder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <algorithm>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const std::array<int, 4> EASY_DIGIT_OUTPUT_LENGTHS = {2, 3, 4, 7};
const std::array<std::string, NUM_POSSIBLE_DIGITS> EXPECTED_DECODED_SIGNAL_PATTERNS =
{
    "abcefg",
    "cf",
    "acdeg",
    "acdfg",
    "bcdf",
    "abdfg",
    "abdefg",
    "acf",
    "abcdefg",
    "abcdfg",
};

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day08
{

SignalDecoder::SignalDecoder(std::array<std::string, NUM_POSSIBLE_DIGITS> signalPatterns, std::array<std::string, NUM_DIGITS_IN_OUTPUT> outputValues)
    : m_signalPatterns{std::move(signalPatterns)}
    , m_outputDigits{std::move(outputValues)}
{

}

unsigned SignalDecoder::getNumEasyDigits() const
{
    return std::count_if(m_outputDigits.cbegin(), m_outputDigits.cend(), [](const auto& outputValue)
                            {
                                return std::find(EASY_DIGIT_OUTPUT_LENGTHS.cbegin(), EASY_DIGIT_OUTPUT_LENGTHS.cend(), outputValue.size()) != EASY_DIGIT_OUTPUT_LENGTHS.cend();
                            });
}

void SignalDecoder::determineDecodingMapping()
{
    const std::vector<std::string> allDecodingMappingCandidates = getAllDecodingMappingCandidates();

    for (const auto& decodingMappingCandidate : allDecodingMappingCandidates)
    {
        if (isValidDecodingMappingCandidate(decodingMappingCandidate))
        {
            m_decodingMapping = decodingMappingCandidate;
            return;
        }
    }

    throw std::runtime_error("No valid decoding found");
}

int SignalDecoder::getDecodedOutputValue() const
{
    int decodedOutputValue = 0;

    for (const auto& outputDigit : m_outputDigits)
    {
        decodedOutputValue *= 10;
        const int currentOutputDigitValue = getOutputDigitValue(outputDigit);
        decodedOutputValue += currentOutputDigitValue;
    }

    return decodedOutputValue;
}

bool SignalDecoder::isValidDecodingMappingCandidate(const std::string& decodingMappingCandidate) const
{
    std::array<std::string, NUM_POSSIBLE_DIGITS> decodedSignalPatterns = getDecodedSignalPatterns(decodingMappingCandidate);

    std::sort(decodedSignalPatterns.begin(), decodedSignalPatterns.end());

    auto expectedDecodedSignalPatterns{EXPECTED_DECODED_SIGNAL_PATTERNS};
    std::sort(expectedDecodedSignalPatterns.begin(), expectedDecodedSignalPatterns.end());

    return decodedSignalPatterns == expectedDecodedSignalPatterns;
}

std::array<std::string, NUM_POSSIBLE_DIGITS> SignalDecoder::getDecodedSignalPatterns(const std::string& decodingMappingCandidate) const
{
    std::array<std::string, NUM_POSSIBLE_DIGITS> decodedSignalPatterns;

    for (size_t i = 0; i < m_signalPatterns.size(); ++i)
    {
        std::string decodedSignalPattern = getDecodedSignalPattern(decodingMappingCandidate, m_signalPatterns.at(i));
        decodedSignalPatterns.at(i) = std::move(decodedSignalPattern);
    }

    return decodedSignalPatterns;
}

std::string SignalDecoder::getDecodedSignalPattern(const std::string& decodingMapping, const std::string& signalPattern) const
{
    std::string decodedSignalPattern;

    for (const char c : signalPattern)
    {
        const char decodedCharacter = decodingMapping.at(c - 'a');
        decodedSignalPattern.push_back(decodedCharacter);
    }

    std::sort(decodedSignalPattern.begin(), decodedSignalPattern.end());

    return decodedSignalPattern;
}

int SignalDecoder::getOutputDigitValue(const std::string& outputDigit) const
{
    const std::string decodedSignalPattern = getDecodedSignalPattern(m_decodingMapping, outputDigit);
    const auto currentDecodedDigitOffsetIter = std::find(EXPECTED_DECODED_SIGNAL_PATTERNS.cbegin(), EXPECTED_DECODED_SIGNAL_PATTERNS.cend(), decodedSignalPattern);

    if (currentDecodedDigitOffsetIter == EXPECTED_DECODED_SIGNAL_PATTERNS.cend())
    {
        throw std::runtime_error("Cannot find output digit in the expected decoded signal patterns");
    }

    return currentDecodedDigitOffsetIter - EXPECTED_DECODED_SIGNAL_PATTERNS.cbegin();
}

std::vector<std::string> SignalDecoder::getAllDecodingMappingCandidates()
{
    std::string decodingMappingCandidate = "abcdefg";
    std::vector<std::string> allDecodingMappingCandidates = {decodingMappingCandidate};

    while (std::next_permutation(decodingMappingCandidate.begin(), decodingMappingCandidate.end()))
    {
        allDecodingMappingCandidates.push_back(decodingMappingCandidate);
    }

    return allDecodingMappingCandidates;
}

}
}
}
