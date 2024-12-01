#pragma once

#include "DanceMove.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned DEFAULT_NUM_PARTICIPANTS = 16;
const unsigned DEFAULT_NUM_REPETITIONS = 1'000'000'000;

}

namespace AdventOfCode
{
namespace Year2017
{
namespace Day16
{

std::string orderAfterDanceMovesSingleRepetition(const std::vector<std::string>& danceMoveStrings, unsigned numParticipants = DEFAULT_NUM_PARTICIPANTS);

std::string orderAfterDanceMovesRepetitions(const std::vector<std::string>& danceMoveStrings,
                                            unsigned numRepetitions = DEFAULT_NUM_REPETITIONS,
                                            unsigned numParticipants = DEFAULT_NUM_PARTICIPANTS);

}
}
}
