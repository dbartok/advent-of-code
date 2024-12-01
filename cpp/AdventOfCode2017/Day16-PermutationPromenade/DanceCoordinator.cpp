#include "DanceCoordinator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <tuple>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day16
{

DanceCoordinator::DanceCoordinator(std::vector<DanceMove::SharedPtr> danceMoves, unsigned numRepetitions, unsigned numParticipants)
    : m_danceMoves{std::move(danceMoves)}
    , m_numRepetitions{numRepetitions}
    , m_nameOrderString(numParticipants, ' ') // Fill constructor
{
    const char firstProgramName = 'a';
    assert(static_cast<int>(numParticipants) <= 'z' - firstProgramName);

    std::iota(m_nameOrderString.begin(), m_nameOrderString.end(), firstProgramName);
}

void DanceCoordinator::executeMoves()
{
    // All orderStrings seen so far, for detecting the first duplicate (i.e., the start of cycle)
    std::unordered_set<std::string> orderStringsEncountered{m_nameOrderString};

    // All orderStrings in same sequence as they appeared, for determining the final order once a cycle is found
    std::vector<std::string> orderStringsInSequence{m_nameOrderString};

    for (unsigned i = 0; i < m_numRepetitions; ++i)
    {
        // Execute all dance moves once
        for (const auto& danceMove : m_danceMoves)
        {
            danceMove->execute(m_nameOrderString);
        }

        bool insertionTookPlace;
        std::tie(std::ignore, insertionTookPlace) = orderStringsEncountered.insert(m_nameOrderString);

        // Found the start of a cycle, we are able to calculate the final orderString
        if (!insertionTookPlace)
        {
            // orderStringsInSequence has the following structure, with the continuation that we don't have to calculate in parentheses:
            // element1 -> element2 -> element3 -> element4 -> element5 (-> element3 -> element4 -> element5 -> element3 -> ...)
            //      m_nameOrderString (start of cycle)^           ^orderStringsInSequence.back()

            const auto cycleStartIter = std::find(orderStringsInSequence.cbegin(), orderStringsInSequence.cend(), m_nameOrderString);
            assert(cycleStartIter != orderStringsInSequence.cend());

            // Starting position of the cycle in orderStringsInSequence
            const size_t cycleStartPos = cycleStartIter - orderStringsInSequence.cbegin();

            // Number of elements in the cycle
            const size_t cycleSize = orderStringsInSequence.size() - cycleStartPos;

            // i starts at 0 and the current repetetion was executed, so we've already done i + 1 repetitions in total
            const unsigned remainingRepetitions = m_numRepetitions - (i + 1);

            // If another cycleSize repetitions are executed, we end up with the same orderString as now
            // Therefore, the only relevant part for the final position inside the cycle is the remainder
            const size_t finalOffsetInsideCycle = remainingRepetitions % cycleSize;

            const size_t finalAbsolutePosition = cycleStartPos + finalOffsetInsideCycle;

            m_nameOrderString = orderStringsInSequence[finalAbsolutePosition];
            return;
        }

        orderStringsInSequence.push_back(m_nameOrderString);
    }
}

const std::string& DanceCoordinator::getNameOrderString() const noexcept
{
    return m_nameOrderString;
}

}
}
}
