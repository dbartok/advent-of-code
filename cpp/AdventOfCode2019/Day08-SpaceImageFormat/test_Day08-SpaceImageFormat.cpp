#include "Day08-SpaceImageFormat.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2019::Day08;

TEST_CLASS(Day08SpaceImageFormat)
{
public:

    TEST_METHOD(checksumOfLayerWithMostZeroes_SimpleTests)
    {
        Assert::AreEqual(1u, CurrentDay::checksumOfLayerWithMostZeroes("123456789012", 3u, 2u));
        Assert::AreEqual(6u, CurrentDay::checksumOfLayerWithMostZeroes("003456011212", 3u, 2u));
    }

    TEST_METHOD(decodeImage_SimpleTests)
    {
        Assert::AreEqual(std::string{" .\n. \n"}, CurrentDay::decodeImage("0222112222120000", 2u, 2u));
    }

};
