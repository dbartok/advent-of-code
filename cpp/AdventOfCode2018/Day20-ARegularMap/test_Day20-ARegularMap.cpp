#include "Day20-ARegularMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day20;

TEST_CLASS(Day20ARegularMap)
{
public:

    TEST_METHOD(distanceToFarthestRoom_SimpleTests)
    {
        Assert::AreEqual(3u, CurrentDay::distanceToFarthestRoom("^WNE$"));
        Assert::AreEqual(10u, CurrentDay::distanceToFarthestRoom("^ENWWW(NEEE|SSE(EE|N))$"));
        Assert::AreEqual(18u, CurrentDay::distanceToFarthestRoom("^ENNWSWW(NEWS|)SSSEEN(WNSE|)EE(SWEN|)NNN$"));
        Assert::AreEqual(23u, CurrentDay::distanceToFarthestRoom("^ESSWWN(E|NNENN(EESS(WNSE|)SSS|WWWSSSSE(SW|NNNE)))$"));
        Assert::AreEqual(31u, CurrentDay::distanceToFarthestRoom("^WSSEESWWWNW(S|NENNEEEENN(ESSSSW(NWSW|SSEN)|WSWWN(E|WWS(E|SS))))$"));
    }

    TEST_METHOD(numRoomsWithLargeDistance_SimpleTests)
    {
        Assert::AreEqual(2u, CurrentDay::numRoomsWithLargeDistance("^WNE$", 2));
        Assert::AreEqual(1u, CurrentDay::numRoomsWithLargeDistance("^WNE$", 3));
    }

};
