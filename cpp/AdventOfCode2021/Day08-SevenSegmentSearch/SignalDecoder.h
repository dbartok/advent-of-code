#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <array>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const size_t NUM_DIGITS_IN_OUTPUT = 4;
const size_t NUM_POSSIBLE_DIGITS = 10;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day08
{

class SignalDecoder
{
public:
    SignalDecoder(std::array<std::string, NUM_POSSIBLE_DIGITS> signalPatterns, std::array<std::string, NUM_DIGITS_IN_OUTPUT> outputValues);

    void determineDecodingMapping();

    unsigned getNumEasyDigits() const;
    int getDecodedOutputValue() const;

private:
    std::array<std::string, NUM_POSSIBLE_DIGITS> m_signalPatterns;
    std::array<std::string, NUM_DIGITS_IN_OUTPUT> m_outputDigits;

    std::string m_decodingMapping;

    bool isValidDecodingMappingCandidate(const std::string& decodingMappingCandidate) const;
    std::array<std::string, NUM_POSSIBLE_DIGITS> getDecodedSignalPatterns(const std::string& decodingMappingCandidate) const;
    std::string getDecodedSignalPattern(const std::string& decodingMapping, const std::string& signalPattern) const;
    int getOutputDigitValue(const std::string& outputDigit) const;

    static std::vector<std::string> getAllDecodingMappingCandidates();
};

}
}
}
