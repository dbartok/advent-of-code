#include "Day16-FlawedFrequencyTransmission.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day16;

TEST_CLASS(Day16FlawedFrequencyTransmission)
{
public:

    TEST_METHOD(firstEightDigitsOfFinalOutput_SimpleTests)
    {
        Assert::AreEqual(std::string{"24176176"}, CurrentDay::firstEightDigitsOfFinalOutput("80871224585914546619083218645595"));
        Assert::AreEqual(std::string{"73745418"}, CurrentDay::firstEightDigitsOfFinalOutput("19617804207202209144916044189917"));
        Assert::AreEqual(std::string{"52432133"}, CurrentDay::firstEightDigitsOfFinalOutput("69317163492948606335995924319873"));
    }

    TEST_METHOD(messageInFinalOutputForRealSignal_SimpleTests)
    {
        Assert::AreEqual(std::string{"84462026"}, CurrentDay::messageInFinalOutputForRealSignal("03036732577212944063491565474664"));
        Assert::AreEqual(std::string{"78725270"}, CurrentDay::messageInFinalOutputForRealSignal("02935109699940807407585447034323"));
        Assert::AreEqual(std::string{"53553731"}, CurrentDay::messageInFinalOutputForRealSignal("03081770884921959731165446850517"));
    }

};
