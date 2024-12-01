#include "Day05-AlchemicalReaction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day05;

TEST_CLASS(Day05AlchemicalReaction)
{
public:

    TEST_METHOD(getReducedPolymerString_SimpleTests)
    {
        Assert::AreEqual(std::string{""}.length(), CurrentDay::getReducedPolymerLength("aA"));
        Assert::AreEqual(std::string{""}.length(), CurrentDay::getReducedPolymerLength("abBA"));
        Assert::AreEqual(std::string{"abAB"}.length(), CurrentDay::getReducedPolymerLength("abAB"));
        Assert::AreEqual(std::string{"aabAAB"}.length(), CurrentDay::getReducedPolymerLength("aabAAB"));
        Assert::AreEqual(std::string{"dabCBAcaDA"}.length(), CurrentDay::getReducedPolymerLength("dabAcCaCBAcCcaDA"));
    }


    TEST_METHOD(getShortestLengthRemoveOneUnit_SimpleTests)
    {
        Assert::AreEqual(4u, CurrentDay::getOneUnitRemovedShortestReducedLength("dabAcCaCBAcCcaDA"));
    }

};
