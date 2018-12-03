#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
using Register = long long;

// Hand optimized version of the original assembly code
unsigned optimizedFinalValueOfH() noexcept;

}
