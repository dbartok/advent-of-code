#include "Day17-Spinlock.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned FIRST_PART_NUM_INSERTIONS = 2017;

}

namespace AdventOfCode
{
namespace Year2017
{
namespace Day17
{

unsigned valueAfterLastWritten(unsigned numStepsForward)
{
    std::vector<unsigned> spinLockValues{0};
    size_t currentPos = 0;

    for (unsigned insertedValue = 1; insertedValue <= FIRST_PART_NUM_INSERTIONS; ++insertedValue)
    {
        currentPos = (currentPos + numStepsForward) % spinLockValues.size();
        ++currentPos;
        spinLockValues.insert(spinLockValues.begin() + currentPos, insertedValue);
    }

    return spinLockValues[(currentPos + 1) % spinLockValues.size()];
}

}
}
}
