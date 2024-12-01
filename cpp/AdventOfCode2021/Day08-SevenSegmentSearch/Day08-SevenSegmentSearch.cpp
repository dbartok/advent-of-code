#include "Day08-SevenSegmentSearch.h"

#include "SignalDecoder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day08
{

SignalDecoder parseSignalDecodingEntryLine(const std::string& signalDecodingEntryLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, signalDecodingEntryLine, boost::is_any_of("|"));

    std::vector<std::string> signalPatterns;
    boost::trim(tokens.at(0));
    boost::split(signalPatterns, tokens.at(0), boost::is_any_of(" "));
    std::array<std::string, NUM_POSSIBLE_DIGITS> signalPatternsArray;
    std::copy_n(signalPatterns.begin(), NUM_POSSIBLE_DIGITS, signalPatternsArray.begin());

    std::vector<std::string> outputDigits;
    boost::trim(tokens.at(1));
    boost::split(outputDigits, tokens.at(1), boost::is_any_of(" "));
    std::array<std::string, NUM_DIGITS_IN_OUTPUT> outputDigitsArray;
    std::copy_n(outputDigits.begin(), NUM_DIGITS_IN_OUTPUT, outputDigitsArray.begin());

    return SignalDecoder{std::move(signalPatternsArray), std::move(outputDigitsArray)};
}

std::vector<SignalDecoder> parseSignalDecodingEntryLines(const std::vector<std::string>& signalDecodingEntryLines)
{
    std::vector<SignalDecoder> signalDecoders;

    for (const auto& line : signalDecodingEntryLines)
    {
        SignalDecoder signalDecoder = parseSignalDecodingEntryLine(line);
        signalDecoders.push_back(std::move(signalDecoder));
    }

    return signalDecoders;
}

unsigned numEasyDigitsInOutput(const std::vector<std::string>& signalDecodingEntryLines)
{
    const std::vector<SignalDecoder> signalDecoders = parseSignalDecodingEntryLines(signalDecodingEntryLines);
    return std::accumulate(signalDecoders.cbegin(), signalDecoders.cend(), 0u, [](const auto& acc, const auto& signalDecoder)
                           {
                               return acc + signalDecoder.getNumEasyDigits();
                           });
}

int sumOfDecodedOutputValues(const std::vector<std::string>& signalDecodingEntryLines)
{
    std::vector<SignalDecoder> signalDecoders = parseSignalDecodingEntryLines(signalDecodingEntryLines);
    
    for (auto& signalDecoder : signalDecoders)
    {
        signalDecoder.determineDecodingMapping();
    }
    
    return std::accumulate(signalDecoders.cbegin(), signalDecoders.cend(), 0u, [](const auto& acc, const auto& signalDecoder)
                           {
                               return acc + signalDecoder.getDecodedOutputValue();
                           });
}

}
}
}