#include "CupMixer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

size_t NUM_CUPS_TO_PICK_UP = 3;

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day23
{

CupMixer::CupMixer(const std::vector<Cup>& initialCups)
    : m_cups{initialCups.cbegin(), initialCups.cend()}
    , m_currentCup{m_cups.front()}
    , m_highestCup{m_cups.size()}
{

}

void CupMixer::mixRepeatedly(size_t numMixes)
{
    for (size_t i = 0; i < numMixes; ++i)
    {
        mix();
    }
}

std::vector<Cup> CupMixer::getLabelsOnCupsAfterCupOne() const
{
    return getCupsNextToCup(1, m_cups.size() - 1);
}

int64_t CupMixer::getTwoCupLabelsAfterCupOneMultiplied() const
{
    std::vector<Cup> twoCupsAfterCupOne = getCupsNextToCup(1, 2);
    return static_cast<int64_t>(twoCupsAfterCupOne.front())* twoCupsAfterCupOne.back();
}

void CupMixer::mix()
{
    std::vector<Cup> cupsPickedUp = pickUpCups();
    const Cup destinationCup = getDestinationCup();
    putDownCups(cupsPickedUp, destinationCup);
    updateCurrentCup();
}

std::vector<Cup> CupMixer::pickUpCups()
{
    const std::vector<Cup> cupsToBePickedUp = getCupsNextToCup(m_currentCup, NUM_CUPS_TO_PICK_UP);

    for (const auto& cup : cupsToBePickedUp)
    {
        m_cups.get<hash>().erase(cup);
    }

    return cupsToBePickedUp;
}

void CupMixer::putDownCups(const std::vector<Cup>& cupsPickedUp, Cup destinationCup)
{
    const auto destinationCupListIter = getListIteratorForCup(destinationCup);
    m_cups.insert(std::next(destinationCupListIter), cupsPickedUp.cbegin(), cupsPickedUp.cend());
}

void CupMixer::updateCurrentCup()
{
    auto currentCupIter = getListIteratorForCup(m_currentCup);
    advanceCupIterCircularly(currentCupIter);
    m_currentCup = *currentCupIter;
}

Cup CupMixer::getDestinationCup() const
{
    Cup destinationCup = m_currentCup;

    while (true)
    {
        destinationCup = (destinationCup == 1) ? m_highestCup : destinationCup - 1;
        const auto destinationCupIter = m_cups.get<hash>().find(destinationCup);
        if (destinationCupIter != m_cups.get<hash>().cend())
        {
            return *destinationCupIter;
        }
    }
}

std::vector<Cup> CupMixer::getCupsNextToCup(Cup cup, size_t numCupsToSelect) const
{
    auto cupIter = getListIteratorForCup(cup);
    std::vector<Cup> selectedCups;

    for (size_t offset = 1; offset <= numCupsToSelect; ++offset)
    {
        advanceCupIterCircularly(cupIter);
        selectedCups.push_back(*cupIter);
    }

    return selectedCups;
}

CupLinkedHashSet::const_iterator CupMixer::getListIteratorForCup(Cup cup) const
{
    const auto cupHashIter = m_cups.get<hash>().find(cup);
    return m_cups.project<list>(cupHashIter);
}

void CupMixer::advanceCupIterCircularly(CupLinkedHashSet::const_iterator& cupIter) const
{
    cupIter = (std::next(cupIter) == m_cups.cend()) ? m_cups.cbegin() : std::next(cupIter);
}

}
}
}
