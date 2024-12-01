#include "HandOptimizedProgram.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day19
{

// Original program from the puzzle:

// #ip 3
// addi 3 16 3
// seti 1 2 5
// seti 1 3 2
// mulr 5 2 1
// eqrr 1 4 1
// addr 1 3 3
// addi 3 1 3
// addr 5 0 0
// addi 2 1 2
// gtrr 2 4 1
// addr 3 1 3
// seti 2 5 3
// addi 5 1 5
// gtrr 5 4 1
// addr 1 3 3
// seti 1 2 3
// mulr 3 3 3
// addi 4 2 4
// mulr 4 4 4
// mulr 3 4 4
// muli 4 11 4
// addi 1 6 1
// mulr 1 3 1
// addi 1 21 1
// addr 4 1 4
// addr 3 0 3
// seti 0 3 3
// setr 3 4 1
// mulr 1 3 1
// addr 3 1 1
// mulr 3 1 1
// muli 1 14 1
// mulr 1 3 1
// addr 4 1 4
// seti 0 3 0
// seti 0 7 3

void finalValueOfRegister0_v1()
{
    unsigned r0 = 1, r1 = 0, r2 = 0, ip = 0, r4 = 0, r5 = 0;

    ip = ip + 16; // addi 3 16 3
    r5 = 1; // seti 1 2 5
    r2 = 1; // seti 1 3 2
    r1 = r2 * r5; // mulr 5 2 1
    r1 = (r1 == r4); // eqrr 1 4 1
    ip = r1 + ip; // addr 1 3 3
    ip = ip + 1; // addi 3 1 3
    r0 = r5 + r0; // addr 5 0 0
    r2 = r2 + 1; // addi 2 1 2
    r1 = (r2 > r4); // gtrr 2 4 1
    ip = ip + r1; // addr 3 1 3
    ip = 2; // seti 2 5 3
    r5 = r5 + 1; // addi 5 1 5
    r1 = (r5 > r4); // gtrr 5 4 1
    ip = r1 + ip; // addr 1 3 3
    ip = 1; // seti 1 2 3
    ip = ip * ip; // mulr 3 3 3
    r4 = r4 + 2; // addi 4 2 4
    r4 = r4 * r4; // mulr 4 4 4
    r4 = ip * r4; // mulr 3 4 4
    r4 = r4 * 11; // muli 4 11 4
    r1 = r1 + 6; // addi 1 6 1
    r1 = r1 * ip; // mulr 1 3 1
    r1 = r1 + 21; // addi 1 21 1
    r4 = r4 + r1; // addr 4 1 4
    ip = ip + r0; // addr 3 0 3
    ip = 0; // seti 0 3 3
    r1 = ip; // setr 3 4 1
    r1 = r1 * ip; // mulr 1 3 1
    r1 = ip + r1; // addr 3 1 1
    r1 = ip * r1; // mulr 3 1 1
    r1 = r1 * 14; // muli 1 14 1
    r1 = r1 * ip; // mulr 1 3 1
    r4 = r4 + r1; // addr 4 1 4
    r0 = 0; // seti 0 3 0
    ip = 0; // seti 0 7 3
}


void finalValueOfRegister0_v2()
{
    unsigned r0 = 1, r1 = 0, r2 = 0, ip = 0, r4 = 0, r5 = 0;

    goto init;
main_loop: r5 = 1; // seti 1 2 5
loop1: r2 = 1; // seti 1 3 2
loop2: r1 = r2 * r5; // mulr 5 2 1
    r1 = (r1 == r4); // eqrr 1 4 1 <-- If this condition is false, the assignment to r0 is skipped (otherwise the "skip" is skipped and both assignments happen)
    ip = r1 + ip; // addr 1 3 3
    ip = ip + 1; // addi 3 1 3
    r0 = r5 + r0; // addr 5 0 0
    r2 = r2 + 1; // addi 2 1 2
    r1 = (r2 > r4); // gtrr 2 4 1 <-- Termination condition for loop1 (terminates if this is true)
    ip = ip + r1; // addr 3 1 3 <-- Skip next instruction if condition was true
    goto loop2; // seti 2 5 3
    r5 = r5 + 1; // addi 5 1 5
    r1 = (r5 > r4); // gtrr 5 4 1 <-- Termination condition for loop2 (terminates if this is true)
    ip = r1 + ip; // addr 1 3 3 <-- Skip next instruction if condition was true
    goto loop1; // seti 1 2 3
    ip = ip * ip; // mulr 3 3 3 <-- Program termination point
init: r4 = r4 + 2; // addi 4 2 4 <-- The init section sets r1 and r4 to some static value, and r0 to 0 (it was either already 0 or is set to 0 right before going to the main loop)
    r4 = r4 * r4; // mulr 4 4 4
    r4 = ip * r4; // mulr 3 4 4 <-- ip == 19
    r4 = r4 * 11; // muli 4 11 4
    r1 = r1 + 6; // addi 1 6 1
    r1 = r1 * ip; // mulr 1 3 1 <-- ip == 22
    r1 = r1 + 21; // addi 1 21 1
    r4 = r4 + r1; // addr 4 1 4
    ip = ip + r0; // addr 3 0 3 <-- Skips next instruction in part two of the puzzle, because r0 == 1
    goto main_loop; // seti 0 3 3
    r1 = ip; // setr 3 4 1 <-- ip == 27
    r1 = r1 * ip; // mulr 1 3 1 <-- ip == 28
    r1 = ip + r1; // addr 3 1 1 <-- ip == 29
    r1 = ip * r1; // mulr 3 1 1 <-- ip == 30
    r1 = r1 * 14; // muli 1 14 1
    r1 = r1 * ip; // mulr 1 3 1 <-- ip == 32
    r4 = r4 + r1; // addr 4 1 4
    r0 = 0; // seti 0 3 0
    goto main_loop; // seti 0 7 3
}

unsigned finalValueOfRegister0_v3()
{
    unsigned r0 = 1, r1 = 0, r2 = 0, r4 = 0, r5 = 0;

    // First part of init (happens in both Part 1 and Part 2 of the puzzle)
    r4 = r4 + 2;
    r4 = r4 * r4;
    r4 = 19 * r4;
    r4 = r4 * 11;
    r1 = r1 + 6;
    r1 = r1 * 22;
    r1 = r1 + 21;
    r4 = r4 + r1;

    // Second part of init (happens only in Part 2 of the puzzle)
    r1 = 27;
    r1 = r1 * 28;
    r1 = 29 + r1;
    r1 = 30 * r1;
    r1 = r1 * 14;
    r1 = r1 * 32; // <-- r1 is actually only used as a temporary variable in the init, because it's set again in the loop
    r4 = r4 + r1;

    r0 = 0;

    do // Iterate with r5 from 1 to r4
    {
        r5 = 1;
        do // Iterate with r2 from 1 to r4
        {
            r2 = 1;
            r1 = r2 * r5;
            if (r1 == r4) // r2 and r5 are divisors of r4, specifically, r5 is the divisor and r2 is the quotient
                r0 = r5 + r0; // Collect sum of divisors in r0
            r2 = r2 + 1;
        } while (!(r2 > r4));
        r5 = r5 + 1;
    } while (!(r5 > r4));

    return r0;
}

unsigned finalValueOfRegister0_v4()
{
    unsigned number = 0;
    unsigned temp = 0;

    // First part of init
    number = number + 2;
    number = number * number;
    number = 19 * number;
    number = number * 11;
    temp = temp + 6;
    temp = temp * 22;
    temp = temp + 21;
    number = number + temp;

    // Second part of init
    temp = 27;
    temp = temp * 28;
    temp = 29 + temp;
    temp = 30 * temp;
    temp = temp * 14;
    temp = temp * 32;
    number = number + temp;

    unsigned sumOfDivisors = 0;

    for (unsigned divisor = 1; divisor <= number; ++divisor)
    {
        for (unsigned quotient = 1; quotient <= number; ++quotient)
        {
            unsigned product = quotient * divisor;
            if (product == number)
            {
                sumOfDivisors += divisor;
            }
        }
    }

    return sumOfDivisors;
}

unsigned finalValueOfRegister0_v5()
{
    // First part of init
    unsigned number = (2 * 2 * 19 * 11) + ((6 * 22) + 21);

    // Second part of init
    number += (((27 * 28) + 29) * 30 * 14 * 32);

    unsigned sumOfDivisors = 0;

    for (unsigned divisor = 1; divisor * divisor <= number; ++divisor)
    {
        unsigned quotient = number / divisor;
        unsigned product = quotient * divisor;
        if (product == number)
        {
            sumOfDivisors += divisor;
            if (divisor != quotient)
            {
                sumOfDivisors += quotient;
            }
        }
    }

    return sumOfDivisors;
}

}
}
}
