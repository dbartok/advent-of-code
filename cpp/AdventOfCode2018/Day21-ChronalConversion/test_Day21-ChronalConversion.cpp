#include "Day21-ChronalConversion.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day21;

TEST_CLASS(Day21ChronalConversion)
{
public:

    // Same as the real puzzle, because the solution had to be hand optimized for a specific input
    TEST_METHOD(lowestValueForFirstRegisterFewestInstructions_SimpleTests)
    {
        Assert::AreEqual(10846352u, CurrentDay::lowestValueForFirstRegisterFewestInstructions());
    }

    // Same as the real puzzle, because the solution had to be hand optimized for a specific input
    TEST_METHOD(lowestValueForFirstRegisterMostInstructions_SimpleTests)
    {
        Assert::AreEqual(5244670u, CurrentDay::lowestValueForFirstRegisterMostInstructions());
    }

};
