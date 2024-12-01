#include "Day20-GrovePositioningSystem.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day20;

TEST_CLASS(Day20GrovePositioningSystem)
{
public:

    TEST_METHOD(sumOfGroveCoordinates_SimpleTests)
    {
        Assert::AreEqual(3ll, CurrentDay::sumOfGroveCoordinates(m_lines));
    }

    TEST_METHOD(sumOfGroveCoordinatesWithDecryptionRoutine_SimpleTests)
    {
        Assert::AreEqual(1623178306ll, CurrentDay::sumOfGroveCoordinatesWithDecryptionRoutine(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "1",
        "2",
        "-3",
        "3",
        "-2",
        "0",
        "4"
    };
};
