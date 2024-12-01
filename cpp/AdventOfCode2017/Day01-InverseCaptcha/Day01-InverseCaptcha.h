#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day01
{

unsigned sumOfDigitsMatchNextDigit(const std::string& digitsString);
unsigned sumOfDigitsMatchHalfwayRoundDigit(const std::string& digitsString);

}
}
}
