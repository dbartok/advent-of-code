#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day08
{

unsigned sumOfAllMetadataEntries(const std::vector<unsigned>& nodeNumbers);
unsigned valueOfRootNode(const std::vector<unsigned>& nodeNumbers);

}
}
}
