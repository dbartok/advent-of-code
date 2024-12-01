#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day01
{

int sumOfAllCalibrationValues(const std::vector<std::string>& calibrationDocumentLines);
int sumOfAllCalibrationValuesSpelledOutWithLetters(const std::vector<std::string>& calibrationDocumentLines);

}
}
}
