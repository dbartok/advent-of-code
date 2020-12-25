#include "Day25-ComboBreaker.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace AoC = AdventOfCode;

TEST_CLASS(Day25ComboBreaker)
{
public:

    TEST_METHOD(encryptionKeyForHandshake_SimpleTests)
    {
        Assert::AreEqual(14897079ll, AoC::encryptionKeyForHandshake(5764801ll, 17807724ll));
    }

};
