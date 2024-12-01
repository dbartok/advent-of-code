#include "Day01-InverseCaptcha.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day01;

TEST_CLASS(Day01InverseCaptcha)
{
public:

    TEST_METHOD(sumOfDigitsMatchNextDigit_SimpleTests)
    {
        Assert::AreEqual(3u, CurrentDay::sumOfDigitsMatchNextDigit("1122"));
        Assert::AreEqual(4u, CurrentDay::sumOfDigitsMatchNextDigit("1111"));
        Assert::AreEqual(0u, CurrentDay::sumOfDigitsMatchNextDigit("1234"));
        Assert::AreEqual(9u, CurrentDay::sumOfDigitsMatchNextDigit("91212129"));
    }

    TEST_METHOD(sumOfDigitsMatchHalfwayRoundDigit_SimpleTests)
    {
        Assert::AreEqual(6u, CurrentDay::sumOfDigitsMatchHalfwayRoundDigit("1212"));
        Assert::AreEqual(0u, CurrentDay::sumOfDigitsMatchHalfwayRoundDigit("1221"));
        Assert::AreEqual(4u, CurrentDay::sumOfDigitsMatchHalfwayRoundDigit("123425"));
        Assert::AreEqual(12u, CurrentDay::sumOfDigitsMatchHalfwayRoundDigit("123123"));
        Assert::AreEqual(4u, CurrentDay::sumOfDigitsMatchHalfwayRoundDigit("12131415"));
    }

};
