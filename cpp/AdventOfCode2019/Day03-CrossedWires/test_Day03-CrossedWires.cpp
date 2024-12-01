#include "Day03-CrossedWires.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day03;

TEST_CLASS(Day03CrossedWires)
{
public:

    TEST_METHOD(distanceToClosestIntersection_SimpleTests)
    {
        Assert::AreEqual(6, CurrentDay::distanceToClosestIntersection(testWireLines1));
        Assert::AreEqual(159, CurrentDay::distanceToClosestIntersection(testWireLines2));
        Assert::AreEqual(135, CurrentDay::distanceToClosestIntersection(testWireLines3));
    }

    TEST_METHOD(combinedWireStepsToClosestIntersection_SimpleTests)
    {
        Assert::AreEqual(30, CurrentDay::combinedWireStepsToClosestIntersection(testWireLines1));
        Assert::AreEqual(610, CurrentDay::combinedWireStepsToClosestIntersection(testWireLines2));
        Assert::AreEqual(410, CurrentDay::combinedWireStepsToClosestIntersection(testWireLines3));
    }

private:
    std::vector<std::string> testWireLines1{"R8,U5,L5,D3", "U7,R6,D4,L4"};
    std::vector<std::string> testWireLines2{"R75,D30,R83,U83,L12,D49,R71,U7,L72", "U62,R66,U55,R34,D71,R55,D58,R83"};
    std::vector<std::string> testWireLines3{"R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51", "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7"};
};
