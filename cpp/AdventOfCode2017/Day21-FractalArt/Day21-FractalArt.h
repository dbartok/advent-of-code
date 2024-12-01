#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

unsigned SMALL_NUM_ITERATIONS = 5;
unsigned LARGE_NUM_ITERATIONS = 18;

}

namespace AdventOfCode
{
namespace Year2017
{
namespace Day21
{

unsigned numPixelsOnSmallIterations(const std::vector<std::string>& enhancementRuleLines, unsigned numIterations = SMALL_NUM_ITERATIONS);
unsigned numPixelsOnLargeIterations(const std::vector<std::string>& enhancementRuleLines, unsigned numIterations = LARGE_NUM_ITERATIONS);

}
}
}
