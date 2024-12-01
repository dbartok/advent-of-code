#include "Day25-Cryostasis.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day25;

TEST_CLASS(Day25Cryostasis)
{
public:

    TEST_METHOD(passwordForMainAirlock_SimpleTests)
    {
        CurrentDay::IntcodeNumberType mem = 1000; // Some high memory address
        std::vector<CurrentDay::IntcodeNumberType> testProgram;

        // Read input multiple times
        for(int i = 0; i < 23; ++i)
        {
            testProgram.push_back(3);
            testProgram.push_back(mem);
        }

        std::vector<CurrentDay::IntcodeNumberType> programEnd{104, '1', 104, '2', 104, '3', 104, '4', 99};

        testProgram.insert(testProgram.end(), programEnd.cbegin(), programEnd.cend());

        Assert::AreEqual(std::string{"1234"}, CurrentDay::passwordForMainAirlock(testProgram));
    }

};
