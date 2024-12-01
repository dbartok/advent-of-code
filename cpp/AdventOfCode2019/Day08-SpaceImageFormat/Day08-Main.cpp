#include "Day08-SpaceImageFormat.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2019::Day08;

    std::fstream fileIn("input.txt");
    std::string encodedImage
    {
        (std::istreambuf_iterator<char>(fileIn)),
        (std::istreambuf_iterator<char>())
    };

    encodedImage.erase(std::remove(encodedImage.begin(), encodedImage.end(), '\n'), encodedImage.end());

    std::cout << "First part: " << CurrentDay::checksumOfLayerWithMostZeroes(encodedImage) << std::endl;
    std::cout << "Second part: " << std::endl << CurrentDay::decodeImage(encodedImage) << std::endl;
}
