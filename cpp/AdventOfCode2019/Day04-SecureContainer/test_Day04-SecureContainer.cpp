#include "Day04-SecureContainer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day04;

TEST_CLASS(Day04SecureContainer)
{
public:

    TEST_METHOD(numDifferentValidPasswordsSimple_SimpleTests)
    {
        Assert::AreEqual(1u, CurrentDay::numDifferentValidPasswordsSimple(111111, 111111));
        Assert::AreEqual(0u, CurrentDay::numDifferentValidPasswordsSimple(223450, 223450));
        Assert::AreEqual(0u, CurrentDay::numDifferentValidPasswordsSimple(123789, 123789));
        Assert::AreEqual(8u, CurrentDay::numDifferentValidPasswordsSimple(111121, 111132));
    }

    TEST_METHOD(numDifferentValidPasswordsLargerGroupIsNotMatching_SimpleTests)
    {
        Assert::AreEqual(1u, CurrentDay::numDifferentValidPasswordsLargerGroupIsNotMatching(112233, 112233));
        Assert::AreEqual(0u, CurrentDay::numDifferentValidPasswordsLargerGroupIsNotMatching(123444, 123444));
        Assert::AreEqual(1u, CurrentDay::numDifferentValidPasswordsLargerGroupIsNotMatching(111122, 111122));
        Assert::AreEqual(0u, CurrentDay::numDifferentValidPasswordsLargerGroupIsNotMatching(234448, 234448));
        Assert::AreEqual(1u, CurrentDay::numDifferentValidPasswordsLargerGroupIsNotMatching(234456, 234456));
        Assert::AreEqual(2u, CurrentDay::numDifferentValidPasswordsLargerGroupIsNotMatching(111121, 111134));
    }

};
