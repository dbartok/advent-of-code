#include "Day25-ComboBreaker.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2020::Day25;

    std::fstream fileIn("input.txt");

    int cardPublicKey;
    fileIn >> cardPublicKey;

    int doorPublicKey;
    fileIn >> doorPublicKey;

    std::cout << "First part: " << CurrentDay::encryptionKeyForHandshake(cardPublicKey, doorPublicKey) << std::endl;
}
