#include "Day09-SensorBoost.h"

#include <AdventOfCodeCommon/UnittestExtraDefinitions.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day09;

TEST_CLASS(Day09SensorBoost)
{
public:

    TEST_METHOD(boostKeycodeProduced_SimpleTests)
    {
        Assert::AreEqual(1219070632396864ll, CurrentDay::boostKeycodeProduced({1102, 34915192, 34915192, 7, 4, 7, 99, 0}, 1).front());
        Assert::AreEqual(1125899906842624ll, CurrentDay::boostKeycodeProduced({104, 1125899906842624, 99}, 1).front());

        std::vector<CurrentDay::IntcodeNumberType> quineInput{109, 1, 204, -1, 1001, 100, 1, 100, 1008, 100, 16, 101, 1006, 101, 0, 99};
        Assert::AreEqual(quineInput, CurrentDay::boostKeycodeProduced(quineInput, 1));
    }

};
