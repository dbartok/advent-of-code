#include "Day16-ChronalClassification.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2018::Day16;

TEST_CLASS(Day16ChronalClassification)

public:

    TEST_METHOD(numSamplesBehaveMoreThanThreeOpcodes_SimpleTests)
    {
        std::vector<std::string> opcodeManualLines =
        {
            "Before: [3, 2, 1, 1]",
            "9 2 1 2",
            "After:  [3, 2, 2, 1]",
            "",
            "",
        };

        Assert::AreEqual(1u, CurrentDay::numSamplesBehaveMoreThanThreeOpcodes(opcodeManualLines));
    }

};
