#include "Day15-LensLibrary.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2023::Day15;

TEST_CLASS(Day15LensLibrary)
{
public:

    TEST_METHOD(sumOfHashResults_SimpleTests)
    {
        Assert::AreEqual(1320, CurrentDay::sumOfHashResults(m_initializationSequenceString));
    }

    TEST_METHOD(focusingPowerOfLensConfiguration_SimpleTests)
    {
        Assert::AreEqual(145, CurrentDay::focusingPowerOfLensConfiguration(m_initializationSequenceString));
    }

private:
    std::string m_initializationSequenceString = "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7";

};
