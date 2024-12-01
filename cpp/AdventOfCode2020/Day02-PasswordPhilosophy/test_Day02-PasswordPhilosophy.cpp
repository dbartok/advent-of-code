#include "Day02-PasswordPhilosophy.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2020::Day02;

TEST_CLASS(Day02PasswordPhilosophy)
{
public:

    TEST_METHOD(numValidPasswordsWithRangePolicy_SimpleTests)
    {
        Assert::AreEqual(2, CurrentDay::numValidPasswordsWithRangePolicy(m_lines));
    }

    TEST_METHOD(numValidPasswordsWithPositionPolicy_SimpleTests)
    {
        Assert::AreEqual(1, CurrentDay::numValidPasswordsWithPositionPolicy(m_lines));
    }

private:
    std::vector<std::string> m_lines =
    {
        "1-3 a: abcde",
        "1-3 b: cdefg",
        "2-9 c: ccccccccc"
    };
};
