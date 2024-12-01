#include "Day03-SpiralMemory.h"

#include "StressTestWriter.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
#include <cmath>
#include <cassert>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day03
{

unsigned previousOddNumber(unsigned number) noexcept
{
    assert(number >= 1);

    return (number % 2 == 1) ? number : number - 1;
}

constexpr unsigned nextOddNumber(unsigned number)
{
    return (number % 2 == 1) ? number : number + 1;
}

unsigned safeUnsignedDistance(unsigned a, unsigned b) noexcept
{
    return std::max(a, b) - std::min(a, b);
}

unsigned stepsToCarryBack(unsigned location)
{
    if (location == 1)
    {
        return 0;
    }

    double sqrtOfLocation = std::sqrt(location);
    assert(sqrtOfLocation <= std::numeric_limits<unsigned>::max());

    // Side length of the ring containing the location
    unsigned outerRingLength = nextOddNumber(static_cast<unsigned>(std::ceil(sqrtOfLocation)));

    // Side length of the previous ring
    unsigned innerRingLength = previousOddNumber(static_cast<unsigned>(std::floor(sqrtOfLocation)));

    unsigned totalElementsInInnerRings = innerRingLength * innerRingLength;

    // Location in the ring as if the first element of the ring was numbered as 1:
    //        8 7 6 5
    //        * * * * *  4
    //        *       *  3
    //        *       *  2
    //        *       *  1
    //        * * * * *  0 or 16
    unsigned locationRelativeInRing = location - totalElementsInInnerRings;

    // Rings can also be thought of as being composed of 4 sections like this:
    //        8 7 6 5
    //        - - - - |  4
    //        |       |  3
    //        |       |  2
    //        |       |  1
    //        | - - - -  0 or 16
    unsigned locationRelativeInRingSection = locationRelativeInRing % (outerRingLength - 1);

    unsigned radiusOfRing = outerRingLength / 2;

    // With the numbering above, the radius also marks the middle point of a ring section
    unsigned middlePointOfRingSection = radiusOfRing;

    unsigned distanceFromMiddleOfSection = safeUnsignedDistance(locationRelativeInRingSection, middlePointOfRingSection);

    // Outwards component + Perimeter component
    return radiusOfRing + distanceFromMiddleOfSection;
}

unsigned stressTestFirstValueGreaterThan(unsigned threshold)
{
    StressTestWriter writer{};
    writer.writeUntil(threshold);
    return writer.getLastWritten();
}

}
}
}
