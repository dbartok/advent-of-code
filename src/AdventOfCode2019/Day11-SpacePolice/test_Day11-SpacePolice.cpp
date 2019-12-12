#include "Day11-SpacePolice.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace AoC = AdventOfCode;

TEST_CLASS(Day11SpacePolice)
{
public:

    TEST_METHOD(numPanelsPaintedAtLeastOnce_SimpleTests)
    {
        AoC::IntcodeNumberType mem = 1000; // Some high memory address
        Assert::AreEqual(1u, AoC::numPanelsPaintedAtLeastOnce(
            {
                3, mem, 104, 1, 104, 0, 99
            }
        ));
    }

    TEST_METHOD(registrationIdentifier_SimpleTests)
    {
        AoC::IntcodeNumberType mem = 1000; // Some high memory address
        Assert::AreEqual(std::string{"."}, AoC::registrationIdentifier(
            {
                3, mem, 104, 1, 104, 0, 99
            }
        ));
    }

};
