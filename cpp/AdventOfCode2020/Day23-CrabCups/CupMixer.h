#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day23
{

using Cup = size_t;

struct list {};
struct hash {};

using CupLinkedHashSet = boost::multi_index_container<
    Cup,
    boost::multi_index::indexed_by<
        boost::multi_index::sequenced<
            boost::multi_index::tag<list>
        >,
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<hash>,
            boost::multi_index::identity<Cup>
        >
    >
>;

class CupMixer
{
public:
    CupMixer(const std::vector<Cup>& initialCups);

    void mixRepeatedly(size_t numMixes);

    std::vector<Cup> getLabelsOnCupsAfterCupOne() const;
    int64_t getTwoCupLabelsAfterCupOneMultiplied() const;

private:
    CupLinkedHashSet m_cups;
    Cup m_currentCup;
    const Cup m_highestCup;

    void mix();
    std::vector<Cup> pickUpCups();
    void putDownCups(const std::vector<Cup>& cupsPickedUp, Cup destinationCup);
    void updateCurrentCup();

    Cup getDestinationCup() const;
    std::vector<Cup> getCupsNextToCup(Cup cup, size_t numCupsToSelect) const;
    CupLinkedHashSet::const_iterator getListIteratorForCup(Cup cup) const;
    void advanceCupIterCircularly(CupLinkedHashSet::const_iterator& cupIter) const;
};

}
}
}
