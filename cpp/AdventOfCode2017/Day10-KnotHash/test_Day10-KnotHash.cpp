#include "Day10-KnotHash.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day10;

TEST_CLASS(Day10KnotHash)
{
public:

    TEST_METHOD(firstTwoMultipliedAfterKnotting_SimpleTests)
    {
        std::vector<unsigned> lengths = {3, 4, 1, 5};
        Assert::AreEqual(12u, CurrentDay::firstTwoMultipliedAfterKnotting(5, lengths));
    }

    TEST_METHOD(firstTwoMultipliedAfterKnotting_0Length_NoElementsAreMoved)
    {
        std::vector<unsigned> lengths = {3, 0, 2};
        Assert::AreEqual(4u, CurrentDay::firstTwoMultipliedAfterKnotting(5, lengths));
    }

    TEST_METHOD(knotHashDenseString_SimpleTests)
    {
        Assert::AreEqual(std::string("a2582a3a0e66e6e86e3812dcb672a272"), CurrentDay::knotHashDenseString(""));
        Assert::AreEqual(std::string("33efeb34ea91902bb2f59c9920caa6cd"), CurrentDay::knotHashDenseString("AoC 2017"));
        Assert::AreEqual(std::string("3efbe78a8d82f29979031a4aa0b16a9d"), CurrentDay::knotHashDenseString("1,2,3"));
        Assert::AreEqual(std::string("63960835bcdc130f0b66d7ff4f6a5a8e"), CurrentDay::knotHashDenseString("1,2,4"));
    }

};
