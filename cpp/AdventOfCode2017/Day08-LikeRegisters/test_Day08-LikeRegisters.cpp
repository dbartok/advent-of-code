#include "Day08-LikeRegisters.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day08;

TEST_CLASS(Day08LikeRegisters)
{
public:

    TEST_METHOD(largestRegisterAfterCompletion_SimpleTests)
    {
        Assert::AreEqual(1, CurrentDay::largestRegisterAfterCompletion(m_instructions));
    }

    TEST_METHOD(largestRegisterDuringExecution_SimpleTests)
    {
        Assert::AreEqual(10, CurrentDay::largestRegisterDuringExecution(m_instructions));
    }

private:
    std::vector<CurrentDay::Instruction> m_instructions =
    {
        {{"b", "inc",   5}, {"a", ">",   1}},
        {{"a", "inc",   1}, {"b", "<",   5}},
        {{"c", "dec", -10}, {"a", ">=",  1}},
        {{"c", "inc", -20}, {"c", "==", 10}}
    };
};
