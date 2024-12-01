#include "Day03-SpiralMemory.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day03;

TEST_CLASS(Day03SpiralMemory)
{
public:

    TEST_METHOD(stepsToCarryBack_SimpleTests)
    {
        Assert::AreEqual(0u, CurrentDay::stepsToCarryBack(1u));
        Assert::AreEqual(3u, CurrentDay::stepsToCarryBack(12u));
        Assert::AreEqual(2u, CurrentDay::stepsToCarryBack(23u));
        Assert::AreEqual(31u, CurrentDay::stepsToCarryBack(1024u));
    }

    TEST_METHOD(stepsToCarryBack_LocationOnCorner)
    {
        Assert::AreEqual(2u, CurrentDay::stepsToCarryBack(9u));
        Assert::AreEqual(4u, CurrentDay::stepsToCarryBack(25u));
    }

    TEST_METHOD(stressTestFirstValueGreaterThan_SimpleTests)
    {
        Assert::AreEqual(4u, CurrentDay::stressTestFirstValueGreaterThan(2u));
        Assert::AreEqual(26u, CurrentDay::stressTestFirstValueGreaterThan(25u));
        Assert::AreEqual(304u, CurrentDay::stressTestFirstValueGreaterThan(147u));
        Assert::AreEqual(806u, CurrentDay::stressTestFirstValueGreaterThan(747u));
    }
};
