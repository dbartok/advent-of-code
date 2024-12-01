#include "BagTypesAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
#include <cassert>
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day07
{

const BagColor SHINY_GOLD = "shiny gold";

QuantifiedBag::QuantifiedBag(BagColor color, int quantity)
    : color{std::move(color)}
    , quantity{quantity}
{

}

void BagTypesAnalyzer::addRelationship(const BagColor& containerBagColor, const BagColor& containedBagColor, int containedQuantity)
{
    m_bagColorToContainerBags[containedBagColor].emplace_back(std::move(containerBagColor), containedQuantity);
    m_bagColorToContainedBags[containerBagColor].emplace_back(std::move(containedBagColor), containedQuantity);
}

int BagTypesAnalyzer::getNumBagColorsThatCanContainShinyGold() const
{
    std::queue<BagColor> queue;
    queue.push(SHINY_GOLD);

    std::unordered_set<BagColor> visited;
    visited.insert(SHINY_GOLD);

    while (!queue.empty())
    {
        BagColor currentColor = queue.front();
        queue.pop();

        const auto containerBagsIter = m_bagColorToContainerBags.find(currentColor);
        if (containerBagsIter == m_bagColorToContainerBags.cend())
        {
            continue;
        }

        for (const auto& containerBag : containerBagsIter->second)
        {
            bool wasInserted = visited.insert(containerBag.color).second;
            if (wasInserted)
            {
                queue.push(containerBag.color);
            }
        }
    }

    return visited.size() - 1;
}

int BagTypesAnalyzer::getNumTotalBagsContainedInsideShinyGold() const
{
    std::unordered_map<BagColor, int> bagColorToTotalQuantity;
    bagColorToTotalQuantity[SHINY_GOLD] = 1;

    std::vector<BagColor> topologicalOrder = getTopologicalOrder();

    for (const auto& currentBagColor : topologicalOrder)
    {
        const auto containedBagsIter = m_bagColorToContainedBags.find(currentBagColor);
        if (containedBagsIter == m_bagColorToContainedBags.cend())
        {
            continue;
        }

        int currentBagTotalQuantity = bagColorToTotalQuantity.at(currentBagColor);

        for (const auto& containedBag : containedBagsIter->second)
        {
            bagColorToTotalQuantity[containedBag.color] += (currentBagTotalQuantity * containedBag.quantity);
        }
    }


    int numTotalBags = std::accumulate(bagColorToTotalQuantity.cbegin(), bagColorToTotalQuantity.cend(), 0, [](int acc, const auto& element)
                                        {
                                            return acc + element.second;
                                        });
    return numTotalBags - 1;
}

std::vector<BagColor> BagTypesAnalyzer::getTopologicalOrder() const
{
    std::vector<BagColor> finishedOrder;
    std::unordered_set<BagColor> visited;
    visited.insert(SHINY_GOLD);

    getReverseTopologicalOrderRecursive(finishedOrder, visited, SHINY_GOLD);

    std::reverse(finishedOrder.begin(), finishedOrder.end());
    assert(finishedOrder.front() == SHINY_GOLD);

    return finishedOrder;
}

void BagTypesAnalyzer::getReverseTopologicalOrderRecursive(std::vector<BagColor>& finishedOrder, std::unordered_set<BagColor>& visited, const BagColor& currentBagColor) const
{
    const auto containedBagsIter = m_bagColorToContainedBags.find(currentBagColor);
    if (containedBagsIter != m_bagColorToContainedBags.cend())
    {
        for (const auto& containedBag : containedBagsIter->second)
        {
            bool wasInserted = visited.insert(containedBag.color).second;
            if (wasInserted)
            {
                getReverseTopologicalOrderRecursive(finishedOrder, visited, containedBag.color);
            }
        }
    }

    finishedOrder.push_back(currentBagColor);
}

}
}
}
