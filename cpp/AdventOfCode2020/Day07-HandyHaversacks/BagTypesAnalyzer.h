#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day07
{

using BagColor = std::string;
struct QuantifiedBag;
using QuantifiedBags = std::vector<QuantifiedBag>;
using BagColorToQuantifiedBags = std::unordered_map<BagColor, QuantifiedBags>;


struct QuantifiedBag
{
    BagColor color;
    int quantity;

    QuantifiedBag(BagColor color, int quantity);
};

class BagTypesAnalyzer
{
public:
    void addRelationship(const BagColor& containerBagColor, const BagColor& containedBagColor, int containedQuantity);

    int getNumBagColorsThatCanContainShinyGold() const;
    int getNumTotalBagsContainedInsideShinyGold() const;

private:
    BagColorToQuantifiedBags m_bagColorToContainerBags;
    BagColorToQuantifiedBags m_bagColorToContainedBags;

    std::vector<BagColor> getTopologicalOrder() const;
    void getReverseTopologicalOrderRecursive(std::vector<BagColor>& finishedOrder, std::unordered_set<BagColor>& visited, const BagColor& currentBagColor) const;
};

}
}
}
