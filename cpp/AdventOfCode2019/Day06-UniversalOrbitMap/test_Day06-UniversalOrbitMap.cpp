#include "Day06-UniversalOrbitMap.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day06;

TEST_CLASS(Day06UniversalOrbitMap)
{
public:

    TEST_METHOD(totalNumberOfDirectAndIndirectOrbits_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "COM)B",
            "B)C",
            "C)D",
            "D)E",
            "E)F",
            "B)G",
            "G)H",
            "D)I",
            "E)J",
            "J)K",
            "K)L"
        };

        Assert::AreEqual(42u, CurrentDay::totalNumberOfDirectAndIndirectOrbits(lines));
    }

    TEST_METHOD(minimumNumberOfOrbitalTransfers_SimpleTests)
    {
        std::vector<std::string> lines =
        {
            "COM)B",
            "B)C",
            "C)D",
            "D)E",
            "E)F",
            "B)G",
            "G)H",
            "D)I",
            "E)J",
            "J)K",
            "K)L",
            "K)YOU",
            "I)SAN"
        };

        Assert::AreEqual(4u, CurrentDay::minimumNumberOfOrbitalTransfers(lines));
    }

};
