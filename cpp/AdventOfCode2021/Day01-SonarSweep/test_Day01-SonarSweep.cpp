#include "Day01-SonarSweep.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2021::Day01;

TEST_CLASS(Day01SonarSweep)
{
public:

    TEST_METHOD(numDepthMeasurementIncreases_SimpleTests)
    {
        Assert::AreEqual(7u, CurrentDay::numDepthMeasurementIncreases(m_depthMeasurements));
    }

    TEST_METHOD(numDepthMeasurementIncreasesWithRollingWindow_SimpleTests)
    {
        Assert::AreEqual(5u, CurrentDay::numDepthMeasurementIncreasesWithRollingWindow(m_depthMeasurements));
    }

private:
    std::vector<unsigned> m_depthMeasurements{199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
};
