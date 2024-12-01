#include "Day16-PermutationPromenade.h"

#include "DanceCoordinator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day16
{

std::vector<DanceMove::SharedPtr> danceMoveSharedPtrsFromStrings (const std::vector<std::string>& danceMoveStrings)
{
    std::vector<DanceMove::SharedPtr> danceMoveSharedPtrs;

    std::transform(danceMoveStrings.cbegin(), danceMoveStrings.cend(), std::back_inserter(danceMoveSharedPtrs), [](const std::string& danceMoveString)
                   {
                       return DanceMove::sharedPtrFromString(danceMoveString);
                   });

    return danceMoveSharedPtrs;
}

std::string orderAfterDanceMovesSingleRepetition(const std::vector<std::string>& danceMoveStrings, unsigned numParticipants)
{
    return orderAfterDanceMovesRepetitions(danceMoveStrings, 1, numParticipants);
}

std::string orderAfterDanceMovesRepetitions(const std::vector<std::string>& danceMoveStrings, unsigned numRepetitions, unsigned numParticipants)
{
    std::vector<DanceMove::SharedPtr> danceMoves = danceMoveSharedPtrsFromStrings(danceMoveStrings);
    DanceCoordinator danceCoordinator{danceMoves, numRepetitions, numParticipants};
    danceCoordinator.executeMoves();
    return danceCoordinator.getNameOrderString();
}

}
}
}
