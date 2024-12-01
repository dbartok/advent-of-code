#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
size_t DEFAULT_WIDTH = 25;
size_t DEFAULT_HEIGHT = 6;
}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day08
{

unsigned checksumOfLayerWithMostZeroes(const std::string& encodedImage, size_t width = DEFAULT_WIDTH, size_t height = DEFAULT_HEIGHT);
std::string decodeImage(const std::string& encodedImage, size_t width = DEFAULT_WIDTH, size_t height = DEFAULT_HEIGHT);

}
}
}
