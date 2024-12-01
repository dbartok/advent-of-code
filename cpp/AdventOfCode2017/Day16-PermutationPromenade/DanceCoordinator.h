#pragma once

#include "DanceMove.h"

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

class DanceCoordinator
{
public:
    DanceCoordinator(std::vector<DanceMove::SharedPtr> danceMoves, unsigned numRepetitions, unsigned numParticipants);
    void executeMoves();
    const std::string& getNameOrderString() const noexcept;

private:
    std::vector<DanceMove::SharedPtr> m_danceMoves;
    unsigned m_numRepetitions;

    std::string m_nameOrderString;
};

}
}
}
