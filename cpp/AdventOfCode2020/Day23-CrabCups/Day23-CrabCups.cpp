#include "Day23-CrabCups.h"

#include "CupMixer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <algorithm>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

size_t MANY_CUPS_NUMBER = 1'000'000;

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day23
{

std::vector<size_t> convertStringToDigitwiseVector(const std::string& str)
{
    std::vector<size_t> digitwiseVector;

    std::transform(str.cbegin(), str.cend(), std::back_inserter(digitwiseVector), [](char c)
                   {
                       return c - '0';
                   });

    return digitwiseVector;
}

std::string convertDigitwiseVectorToString(const std::vector<size_t>& digitwiseVector)
{
    std::string result;

    std::transform(digitwiseVector.cbegin(), digitwiseVector.cend(), std::back_inserter(result), [](size_t digit)
                   {
                       return digit + '0';
                   });

    return result;
}

void addPaddingToInitialCups(std::vector<Cup>& cups)
{
    const size_t numPaddingCupsRequired = MANY_CUPS_NUMBER - cups.size();
    std::vector<Cup> paddingCups(numPaddingCupsRequired);

    const size_t firstPaddingCup = cups.size() + 1;
    std::iota(paddingCups.begin(), paddingCups.end(), firstPaddingCup);

    cups.insert(cups.end(), std::make_move_iterator(paddingCups.cbegin()), std::make_move_iterator(paddingCups.cend()));
}

std::string cupLabelsStartingFromCupOne(const std::string& initialCupLabellingString, size_t numMixes)
{
    std::vector<Cup> initialCups = convertStringToDigitwiseVector(initialCupLabellingString);
    CupMixer cupMixer{std::move(initialCups)};
    cupMixer.mixRepeatedly(numMixes);
    std::vector<Cup> labelsOnCupsAfterCupOne = cupMixer.getLabelsOnCupsAfterCupOne();
    return convertDigitwiseVectorToString(labelsOnCupsAfterCupOne);
}

int64_t twoCupLabelsAfterCupOneMultipliedManyCups(const std::string& initialCupLabellingString, size_t numMixes)
{
    std::vector<Cup> initialCups = convertStringToDigitwiseVector(initialCupLabellingString);
    addPaddingToInitialCups(initialCups);
    CupMixer cupMixer{std::move(initialCups)};
    cupMixer.mixRepeatedly(numMixes);
    return cupMixer.getTwoCupLabelsAfterCupOneMultiplied();
}

}
}
}
