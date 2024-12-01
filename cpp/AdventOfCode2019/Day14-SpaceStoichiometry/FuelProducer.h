#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day14
{

struct QuantifiedChemical
{
    std::string name;
    long long amount;
};

struct ChemicalReaction
{
    std::vector<QuantifiedChemical> inputs;
    QuantifiedChemical output;
    long long currentResidueRemaining;
};

using ChemicalNameToSourceReaction = std::unordered_map<std::string, ChemicalReaction>;

class FuelProducer
{
public:
    FuelProducer(std::vector<ChemicalReaction> reactions);

    void produceFuel(long long amount);

    long long getOreConsumed() const;

private:
    ChemicalNameToSourceReaction m_chemicalNameToSourceReaction;

    long long m_oreConsumed = 0;

    std::vector<QuantifiedChemical> calculateIngredients(const QuantifiedChemical& chemicalToProduce);
};

}
}
}
