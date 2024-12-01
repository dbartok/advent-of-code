#include "FuelProducer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <cmath>
#include <deque>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const char* FUEL = "FUEL";
const char* ORE = "ORE";
}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day14
{

FuelProducer::FuelProducer(std::vector<ChemicalReaction> reactions)
{
    for (auto& reaction : reactions)
    {
        m_chemicalNameToSourceReaction.emplace(reaction.output.name, std::move(reaction));
    }
}

void FuelProducer::produceFuel(long long amount)
{
    std::deque<QuantifiedChemical> workOrders;
    workOrders.push_back({FUEL, amount});

    while (!workOrders.empty())
    {
        QuantifiedChemical nextChemicalToProduce = workOrders.front();
        workOrders.pop_front();

        if (nextChemicalToProduce.name == ORE)
        {
            m_oreConsumed += nextChemicalToProduce.amount;
            continue;
        }

        std::vector<QuantifiedChemical> ingredients = calculateIngredients(nextChemicalToProduce);
        std::copy(std::make_move_iterator(ingredients.begin()), std::make_move_iterator(ingredients.end()), std::back_inserter(workOrders));
    }
}

long long FuelProducer::getOreConsumed() const
{
    return m_oreConsumed;
}

std::vector<QuantifiedChemical> FuelProducer::calculateIngredients(const QuantifiedChemical& chemicalToProduce)
{
    ChemicalReaction& sourceReaction = m_chemicalNameToSourceReaction.at(chemicalToProduce.name);

    std::vector<QuantifiedChemical> ingredients = sourceReaction.inputs;

    if (sourceReaction.currentResidueRemaining >= chemicalToProduce.amount)
    {
        sourceReaction.currentResidueRemaining -= chemicalToProduce.amount;
        return {};
    }

    long long amountToProduce = chemicalToProduce.amount - sourceReaction.currentResidueRemaining;
    long long numReactionsRequired = std::ceil(amountToProduce / static_cast<double>(sourceReaction.output.amount));
    sourceReaction.currentResidueRemaining = numReactionsRequired * sourceReaction.output.amount - amountToProduce;

    for (auto& ingredient : ingredients)
    {
        ingredient.amount *= numReactionsRequired;
    }

    return ingredients;
}

}
}
}
