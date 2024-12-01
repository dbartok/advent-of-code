#include "Day03-BinaryDiagnostic.h"

#include "DiagnosticReportAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day03
{

int submarinePowerConsumption(const std::vector<std::string>& diagnosticReportLines)
{
    DiagnosticReportAnalyzer analyzer{diagnosticReportLines};
    analyzer.calculatePowerConsumptionParameters();
    return analyzer.getSubmarinePowerConsumption();
}

int lifeSupportRating(const std::vector<std::string>& diagnosticReportLines)
{
    DiagnosticReportAnalyzer analyzer{diagnosticReportLines};
    analyzer.calculateLifeSupportRatingParameters();
    return analyzer.getLifeSupportRating();
}

}
}
}