#include "Day06-CustomCustoms.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day06;

TEST_CLASS(Day06CustomCustoms)
{
public:

    TEST_METHOD(sumAnyoneAnsweredYes_SimpleTests)
    {
        Assert::AreEqual(11, CurrentDay::sumAnyoneAnsweredYes(m_lines));
    }

    TEST_METHOD(sumEveryoneAnsweredYes_SimpleTests)
    {
        Assert::AreEqual(6, CurrentDay::sumEveryoneAnsweredYes(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "abc",
        "",
        "a",
        "b",
        "c",
        "",
        "ab",
        "ac",
        "",
        "a",
        "a",
        "a",
        "a",
        "",
        "b"
    };

};
