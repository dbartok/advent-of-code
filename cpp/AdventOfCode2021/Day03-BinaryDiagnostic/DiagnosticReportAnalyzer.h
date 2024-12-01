#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
#include <array>
#include <functional>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day03
{

using ZeroAndOneFrequencies = std::array<int, 2>;

class DiagnosticReportAnalyzer
{
public:
    DiagnosticReportAnalyzer(std::vector<std::string> diagnosticReportLines);

    void calculatePowerConsumptionParameters();
    void calculateLifeSupportRatingParameters();

    int getSubmarinePowerConsumption() const;
    int getLifeSupportRating() const;

private:
    std::vector<std::string> m_originalDiagnosticReportLines;
    std::vector<ZeroAndOneFrequencies> m_perPositionFrequencies;

    int m_gammaRate = 0;
    int m_epsilonRate = 0;
    int m_oxygenGeneratorRating = 0;
    int m_co2ScrubberRating = 0;

    void populateFrequenciesForAllPositions(const std::vector<std::string>& diagnosticReportLines);
    void populateFrequenciesForPosition(const std::vector<std::string>& diagnosticReportLines, size_t index);
    int filterForOneValue(const std::function<int(ZeroAndOneFrequencies)>& frequencySelectorFunc);
    std::vector<std::string> filterForValueAtPosition(const std::vector<std::string>& diagnosticReportLines, size_t position, char value);

    int getBitExtractedNumber(const std::function<int(ZeroAndOneFrequencies)>& frequencySelectorFunc) const;
};

}
}
}
