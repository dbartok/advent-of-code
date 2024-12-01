#include "HandOptimizedAssembly.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cmath>
#include <cassert>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day23
{

// --- Original assembly code from the puzzle ---
// set b 93
// set c b
// jnz a 2
// jnz 1 5
// mul b 100
// sub b -100000
// set c b
// sub c -17000
// set f 1
// set d 2
// set e 2
// set g d
// mul g e
// sub g b
// jnz g 2
// set f 0
// sub e -1
// set g e
// sub g b
// jnz g -8
// sub d -1
// set g d
// sub g b
// jnz g -13
// jnz f 2
// sub h -1
// set g b
// sub g c
// jnz g 2
// jnz 1 3
// sub b -17
// jnz 1 -23

// The below functions are refactorings of the assembly code above
// Only the final version is meant to actually be run

__BEGIN_DISABLE_WARNINGS(26438)
Register finalValueOfH_Initial() noexcept
{
    Register a = 1, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;

    b = 93;
    c = b;
    if (a != 0) goto label1;
    goto label2;
label1:
    b *= 100;
    b += 100'000;
    c = b;
    c += 17'000;
label2:
    f = 1;
    d = 2;
label5:
    e = 2;
label4:
    g = d;
    g *= e;
    g -= b;
    if (g != 0) goto label3;
    f = 0;
label3:
    e += 1;
    g = e;
    g -= b;
    if (g != 0) goto label4;
    d += 1;
    g = d;
    g -= b;
    if (g != 0) goto label5;
    if (f != 0) goto label6;
    h += 1;
label6:
    g = b;
    g -= c;
    if (g != 0) goto label7;
    return h;
label7:
    b += 17;
    goto label2;
}
__END_DISABLE_WARNINGS


Register finalValueOfH_NoGotos() noexcept
{
    Register a = 1, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;

    b = 93 * 100 + 100'000;
    c = b + 17'000;
    while (true)
    {
        f = 1;
        d = 2;
        do
        {
            e = 2;
            do
            {
                g = d;
                g *= e;
                g -= b;
                if (g == 0)
                    f = 0;
                e += 1;
                g = e;
                g -= b;
            } while (g != 0);
            d += 1;
            g = d;
            g -= b;
        } while (g != 0);
        if (f == 0)
            h += 1;
        g = b;
        g -= c;
        if (g == 0)
            break;
        b += 17;
    }

    return h;
}

Register finalValueOfH_ForLoops() noexcept
{
    Register a = 1, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;

    b = 93 * 100 + 100'000;
    c = b + 17'000;
    for(b; b != c + 17; b += 17)
    {
        f = 1;
        for(d = 2; d != b + 1; ++d)
        {
            for (e = 2; e != b + 1; ++e)
            {
                if (d * e == 0)
                    f = 0;
            }
        }
        if (f == 0)
            h += 1;
    }

    return h;
}

Register finalValueOfH_Renames() noexcept
{
    Register testedNumber = 0, testUntil = 0, factor1 = 0, factor2 = 0, isPrime = 0, numComposites = 0;

    testedNumber = 93 * 100 + 100'000;
    testUntil = testedNumber + 17'000;
    for (testedNumber; testedNumber != testUntil + 17; testedNumber += 17)
    {
        isPrime = 1;
        for (factor1 = 2; factor1 != testedNumber + 1; ++factor1)
        {
            for (factor2 = 2; factor2 != testedNumber + 1; ++factor2)
            {
                if (factor1 * factor2 == testedNumber)
                    isPrime = 0;
            }
        }
        if (isPrime == 0)
            numComposites += 1;
    }

    return numComposites;
}

// Final implementation

// Helper - very basic trial division prime check
bool isPrime(unsigned num) noexcept
{
    if (num == 0 || num == 1)
    {
        return false;
    }

    if (num == 2)
    {
        return true;
    }

    if (num % 2 == 0)
    {
        return false;
    }

    for (unsigned i = 3; i * i <= num; i += 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

unsigned optimizedFinalValueOfH() noexcept
{
    const unsigned firstTestedNumber = 93 * 100 + 100'000;
    const unsigned testUntil = firstTestedNumber + 17'000;
    const unsigned increments = 17;

    unsigned numComposites = 0;

    for (unsigned currentNum = firstTestedNumber; currentNum <= testUntil; currentNum += increments)
    {
        if (!isPrime(currentNum))
        {
            ++numComposites;
        }
    }

    return numComposites;
}

}
}
}
