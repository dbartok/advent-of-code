#include "DiagnosticReportAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
#include <algorithm>
#include <iterator>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day03
{

int frequencySelectorFunc(const ZeroAndOneFrequencies& frequencies, const std::function<bool(int, int)>& comparatorFunc, int tieBreakerValue = -1)
{
    if (comparatorFunc(frequencies.at(0), frequencies.at(1)))
    {
        return 0;
    }

    if (comparatorFunc(frequencies.at(1), frequencies.at(0)))
    {
        return 1;
    }

    return tieBreakerValue;
}


DiagnosticReportAnalyzer::DiagnosticReportAnalyzer(std::vector<std::string> diagnosticReportLines)
    : m_originalDiagnosticReportLines(std::move(diagnosticReportLines))
{

}

void DiagnosticReportAnalyzer::calculatePowerConsumptionParameters()
{
    populateFrequenciesForAllPositions(m_originalDiagnosticReportLines);

    m_gammaRate = getBitExtractedNumber([](const auto& frequencies)
                                        {
                                            return frequencySelectorFunc(frequencies, std::greater<int>());
                                        });

    m_epsilonRate = getBitExtractedNumber([](const auto& frequencies)
                                            {
                                                return frequencySelectorFunc(frequencies, std::less<int>());
                                            });
}

void DiagnosticReportAnalyzer::calculateLifeSupportRatingParameters()
{
    m_oxygenGeneratorRating = filterForOneValue([](const auto& frequencies)
                                                {
                                                    return frequencySelectorFunc(frequencies, std::greater<int>(), 1);
                                                });

    m_co2ScrubberRating = filterForOneValue([](const auto& frequencies)
                                            {
                                                return frequencySelectorFunc(frequencies, std::less<int>(), 0);
                                            });
}

int DiagnosticReportAnalyzer::getSubmarinePowerConsumption() const
{
    return m_gammaRate * m_epsilonRate;
}

int DiagnosticReportAnalyzer::getLifeSupportRating() const
{
    return m_oxygenGeneratorRating * m_co2ScrubberRating;
}

void DiagnosticReportAnalyzer::populateFrequenciesForAllPositions(const std::vector<std::string>& diagnosticReportLines)
{
    for (size_t position = 0; position < diagnosticReportLines.at(0).size(); ++position)
    {
        populateFrequenciesForPosition(diagnosticReportLines, position);
    }
}

void DiagnosticReportAnalyzer::populateFrequenciesForPosition(const std::vector<std::string>& diagnosticReportLines, size_t index)
{
    m_perPositionFrequencies.resize(std::max(m_perPositionFrequencies.size(), index + 1));
    auto& frequencies = m_perPositionFrequencies.at(index);
    frequencies = ZeroAndOneFrequencies{0, 0};

    for (const auto& diagnosticReportLine : diagnosticReportLines)
    {
        const char diagnosticReportChar = diagnosticReportLine.at(index);
        const int binaryDigit = diagnosticReportChar - '0';
        if (!(binaryDigit == 0 || binaryDigit == 1))
        {
            throw std::runtime_error(std::string{"Invalid binary digit: "} + diagnosticReportChar);
        }
        ++frequencies.at(binaryDigit);
    }
}

int DiagnosticReportAnalyzer::filterForOneValue(const std::function<int(ZeroAndOneFrequencies)>& frequencySelectorFunc)
{
    auto filteredDiagnosticReportLines{m_originalDiagnosticReportLines};

    for (size_t position = 0; position < filteredDiagnosticReportLines.at(0).size(); ++position)
    {
        populateFrequenciesForPosition(filteredDiagnosticReportLines, position);
        const auto& frequencies = m_perPositionFrequencies.at(position);
        const int extractedDigit = frequencySelectorFunc(frequencies);
        const char matchingValue = extractedDigit + '0';

        filteredDiagnosticReportLines = filterForValueAtPosition(filteredDiagnosticReportLines, position, matchingValue);

        if (filteredDiagnosticReportLines.size() == 1)
        {
            return std::stoi(filteredDiagnosticReportLines.front(), nullptr, 2);
        }
    }

    throw std::runtime_error("Unable to filter for a single value");
}

std::vector<std::string> DiagnosticReportAnalyzer::filterForValueAtPosition(const std::vector<std::string>& diagnosticReportLines, size_t position, char value)
{
    std::vector<std::string> filteredDiagnosticReportLines;

    std::copy_if(diagnosticReportLines.cbegin(), diagnosticReportLines.cend(), std::back_inserter(filteredDiagnosticReportLines), [position, value](const auto& diagnosticReportLine)
                    {
                        return diagnosticReportLine.at(position) == value;
                    });

    return filteredDiagnosticReportLines;
}

int DiagnosticReportAnalyzer::getBitExtractedNumber(const std::function<int(ZeroAndOneFrequencies)>& frequencySelectorFunc) const
{
    std::string extractedNumberString;

    int extractedNumber = 0;

    for (const auto& frequencies : m_perPositionFrequencies)
    {
        extractedNumber <<= 1;
        const int extractedDigit = frequencySelectorFunc(frequencies);
        extractedNumber += extractedDigit;
    }

    return extractedNumber;
}

}
}
}
