#include "Day15-DuelingGenerators.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day15;

TEST_CLASS(Day15DuelingGenerators)
{
public:

    TEST_METHOD(judgeFinalCountNoCriteria_SimpleTests)
    {
        Assert::AreEqual(588u, CurrentDay::judgeFinalCountNoCriteria(m_generatorAStart, m_generatorBStart));
    }

    TEST_METHOD(judgeFinalCountWithCriteria_SimpleTests)
    {
        Assert::AreEqual(309u, CurrentDay::judgeFinalCountWithCriteria(m_generatorAStart, m_generatorBStart));
    }

private:
    const unsigned m_generatorAStart = 65;
    const unsigned m_generatorBStart = 8921;
};
