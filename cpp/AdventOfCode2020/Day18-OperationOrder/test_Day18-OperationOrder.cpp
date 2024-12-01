#include "Day18-OperationOrder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day18;

TEST_CLASS(Day18OperationOrder)
{
public:

    TEST_METHOD(sumOfResultingValuesWithoutPrecedence_SimpleTests)
    {
        Assert::AreEqual(71ll, CurrentDay::sumOfResultingValuesWithoutPrecedence({"1 + 2 * 3 + 4 * 5 + 6"}));
        Assert::AreEqual(51ll, CurrentDay::sumOfResultingValuesWithoutPrecedence({"1 + (2 * 3) + (4 * (5 + 6))"}));
        Assert::AreEqual(26ll, CurrentDay::sumOfResultingValuesWithoutPrecedence({"2 * 3 + (4 * 5)"}));
        Assert::AreEqual(437ll, CurrentDay::sumOfResultingValuesWithoutPrecedence({"5 + (8 * 3 + 9 + 3 * 4 * 3)"}));
        Assert::AreEqual(12240ll, CurrentDay::sumOfResultingValuesWithoutPrecedence({"5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))"}));
        Assert::AreEqual(13632ll, CurrentDay::sumOfResultingValuesWithoutPrecedence({"((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2"}));
    }

    TEST_METHOD(sumOfResultingValuesWithPrecedence_SimpleTests)
    {
        Assert::AreEqual(231ll, CurrentDay::sumOfResultingValuesWithPrecedence({"1 + 2 * 3 + 4 * 5 + 6"}));
        Assert::AreEqual(51ll, CurrentDay::sumOfResultingValuesWithPrecedence({"1 + (2 * 3) + (4 * (5 + 6))"}));
        Assert::AreEqual(46ll, CurrentDay::sumOfResultingValuesWithPrecedence({"2 * 3 + (4 * 5)"}));
        Assert::AreEqual(1445ll, CurrentDay::sumOfResultingValuesWithPrecedence({"5 + (8 * 3 + 9 + 3 * 4 * 3)"}));
        Assert::AreEqual(669060ll, CurrentDay::sumOfResultingValuesWithPrecedence({"5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))"}));
        Assert::AreEqual(23340ll, CurrentDay::sumOfResultingValuesWithPrecedence({"((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2"}));
    }

};
