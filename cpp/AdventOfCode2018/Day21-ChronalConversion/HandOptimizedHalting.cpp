#include "HandOptimizedHalting.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day21
{

// Original program from the puzzle:

// #ip 1
// seti 123 0 5
// bani 5 456 5
// eqri 5 72 5
// addr 5 1 1
// seti 0 0 1
// seti 0 9 5
// bori 5 65536 2
// seti 7571367 9 5
// bani 2 255 4
// addr 5 4 5
// bani 5 16777215 5
// muli 5 65899 5
// bani 5 16777215 5
// gtir 256 2 4
// addr 4 1 1
// addi 1 1 1
// seti 27 1 1
// seti 0 2 4
// addi 4 1 3
// muli 3 256 3
// gtrr 3 2 3
// addr 3 1 1
// addi 1 1 1
// seti 25 6 1
// addi 4 1 4
// seti 17 8 1
// setr 4 6 2
// seti 7 4 1
// eqrr 5 0 4
// addr 4 1 1
// seti 5 5 1

void transpiledProgram_v1()
{
    unsigned r0 = 0, ip = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0;

    r5 = 123; // seti 123 0 5
    r5 = 456 & r5; // bani 5 456 5
    r5 = (r5 == 72); // eqri 5 72 5
    ip = r5 + ip; // addr 5 1 1
    ip = 0; // seti 0 0 1 <-- end of instruction testing part
    r5 = 0; // seti 0 9 5
    r2 = r5 | 65536; // bori 5 65536 2
    r5 = 7571367; // seti 7571367 9 5
    r4 = r2 & 255; // bani 2 255 4
    r5 = r5 + r4; // addr 5 4 5
    r5 = r5 & 16777215; // bani 5 16777215 5
    r5 = r5 * 65899; // muli 5 65899 5
    r5 = r5 & 16777215; // bani 5 16777215 5
    r4 = (256 > r2); // gtir 256 2 4
    ip = r4 + ip; // addr 4 1 1
    ip = ip + 1; // addi 1 1 1
    ip = 27; // seti 27 1 1
    r4 = 0; // seti 0 2 4
    r3 = r4 + 1; // addi 4 1 3
    r3 = r3 * 256; // muli 3 256 3
    r3 = (r3 > r2); // gtrr 3 2 3
    ip = r3 + ip; // addr 3 1 1
    ip = ip + 1; // addi 1 1 1
    ip = 25; // seti 25 6 1
    r4 = r4 + 1; // addi 4 1 4
    ip = 17; // seti 17 8 1
    r2 = r4; // setr 4 6 2
    ip = 7; // seti 7 4 1
    r4 = (r5 == r0); // eqrr 5 0 4
    ip = r4 + ip; // addr 4 1 1
    ip = 5; // seti 5 5 1
}

void transpiledProgram_v2()
{
    unsigned r0 = 0, ip = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0;

    r5 = 123; // seti 123 0 5
dest0: r5 = 456 & r5; // bani 5 456 5
    r5 = (r5 == 72); // eqri 5 72 5
    ip = r5 + ip; // addr 5 1 1
    ip = 0; // seti 0 0 1 <-- end of instruction testing part
    r5 = 0; // seti 0 9 5
dest5: r2 = r5 | 65536; // bori 5 65536 2
    r5 = 7571367; // seti 7571367 9 5
dest7: r4 = r2 & 255; // bani 2 255 4
    r5 = r5 + r4; // addr 5 4 5
    r5 = r5 & 16777215; // bani 5 16777215 5
    r5 = r5 * 65899; // muli 5 65899 5
    r5 = r5 & 16777215; // bani 5 16777215 5
    r4 = (256 > r2); // gtir 256 2 4
    ip = r4 + ip; // addr 4 1 1
    ip = ip + 1; // addi 1 1 1
    ip = 27; // seti 27 1 1
    r4 = 0; // seti 0 2 4
dest17: r3 = r4 + 1; // addi 4 1 3
    r3 = r3 * 256; // muli 3 256 3
    r3 = (r3 > r2); // gtrr 3 2 3
    ip = r3 + ip; // addr 3 1 1
    ip = ip + 1; // addi 1 1 1
    ip = 25; // seti 25 6 1
    r4 = r4 + 1; // addi 4 1 4
    ip = 17; // seti 17 8 1
dest25: r2 = r4; // setr 4 6 2
    ip = 7; // seti 7 4 1
dest27: r4 = (r5 == r0); // eqrr 5 0 4
    ip = r4 + ip; // addr 4 1 1
    ip = 5; // seti 5 5 1
}

void transpiledProgram_v3()
{
    unsigned r0 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0;

    r5 = 0;
dest5: r2 = r5 | 65536;
    r5 = 7571367;
dest7: r4 = r2 & 255;
    r5 = r5 + r4;
    r5 = r5 & 16777215;
    r5 = r5 * 65899;
    r5 = r5 & 16777215;
    if (256 > r2)
        goto dest27;
    r4 = 0;
dest17: r3 = r4 + 1;
    r3 = r3 * 256;
    r3 = (r3 > r2);
    if (r3 == 1)
        goto dest25;
    r4 = r4 + 1;
    goto dest17;
dest25: r2 = r4;
    goto dest7;
dest27: r4 = (r5 == r0);
    if (r4 == 0)
        goto dest5;
}

void transpiledProgram_v4()
{
    unsigned r0 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0;

    while (true)
    {
        r2 = r5 | 65536;
        r5 = 7571367;
        while (true)
        {
            r4 = r2 & 255;
            r5 = r5 + r4;
            r5 = r5 & 16777215;
            r5 = r5 * 65899;
            r5 = r5 & 16777215;
            if (256 > r2)
            {
                break;
            }
            r4 = 0;
            while (true)
            {
                r3 = r4 + 1;
                r3 = r3 * 256;
                r3 = (r3 > r2);
                if (r3 == 1)
                    break;
                r4 = r4 + 1;
            }
            r2 = r4;
        }
        if (r5 == r0) // <-- This is the only place where r0 is used, and the program terminates here iff r5 == r0
        {
            break;
        }
    }
}

std::vector<unsigned> getTerminatingValuesOfFirstRegister()
{
    unsigned r2 = 0, r3 = 0, r4 = 0, r5 = 0;

    // Use a vector for simplicity due to a lack of LinkedHashMap in C++
    std::vector<unsigned> uniqueValuesOfRegister5InOrder;

    while (true)
    {
        r2 = r5 | 65536;
        r5 = 7571367;
        while (true)
        {
            r4 = r2 & 255;
            r5 = r5 + r4;
            r5 = r5 & 16777215;
            r5 = r5 * 65899;
            r5 = r5 & 16777215;
            if (256 > r2)
            {
                break;
            }
            r4 = 0;
            while (true)
            {
                r3 = r4 + 1;
                r3 = r3 * 256;
                r3 = (r3 > r2);
                if (r3 == 1)
                    break;
                r4 = r4 + 1;
            }
            r2 = r4;
        }

        // Capture all the values of r5 in order until a repetition is found
        // These are all values for r0 that eventually terminate the program
        auto findResult = std::find(uniqueValuesOfRegister5InOrder.cbegin(), uniqueValuesOfRegister5InOrder.cend(), r5);
        if (findResult != uniqueValuesOfRegister5InOrder.cend())
        {
            break;
        }
        uniqueValuesOfRegister5InOrder.push_back(r5);
    }

    return uniqueValuesOfRegister5InOrder;
}

}
}
}
