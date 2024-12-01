#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

unsigned DEFAULT_NUM_ITERATIONS_BASIC = 10'000;
unsigned DEFAULT_NUM_ITERATIONS_EVOLVED = 10'000'000;

}

namespace AdventOfCode
{
namespace Year2017
{
namespace Day22
{

unsigned basicVirusInfectingBursts(const std::vector<std::string>& initialVirusPosLines, unsigned numIterations = DEFAULT_NUM_ITERATIONS_BASIC);
unsigned evolvedVirusInfectingBursts(const std::vector<std::string>& initialVirusPosLines, unsigned numIterations = DEFAULT_NUM_ITERATIONS_EVOLVED);


}
}
}
