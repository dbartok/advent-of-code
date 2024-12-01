#include "Day14-SpaceStoichiometry.h"

#include "FuelProducer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const long long TOTAL_ORE_AVAILABLE = 1'000'000'000'000;
}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day14
{

QuantifiedChemical createQuantifiedChemical(std::string quantifiedChemicalString)
{
    boost::trim(quantifiedChemicalString);

    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, quantifiedChemicalString, boost::is_any_of(", "), boost::token_compress_on);

    if (tokens.size() != 2)
    {
        throw std::runtime_error("Invalid quantified chemical: " + quantifiedChemicalString);
    }

    int amount = std::stoi(tokens.front());

    return QuantifiedChemical{std::move(tokens.back()), amount};
}

std::vector<QuantifiedChemical> createInputs(const std::string& inputString)
{
    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, inputString, boost::is_any_of(","));

    std::vector<QuantifiedChemical> quantifiedChemicals;
    for (const auto& quantifiedChemicalString : tokens)
    {
        QuantifiedChemical quantifiedChemical = createQuantifiedChemical(quantifiedChemicalString);
        quantifiedChemicals.push_back(std::move(quantifiedChemical));
    }

    return quantifiedChemicals;
}

ChemicalReaction createChemicalReaction(const std::string& reactionLine)
{
    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, reactionLine, boost::is_any_of("=>"), boost::token_compress_on);

    if (tokens.size() != 2)
    {
        throw std::runtime_error("Invalid line: " + reactionLine);
    }

    std::vector<QuantifiedChemical> inputs = createInputs(tokens.front());
    QuantifiedChemical output = createQuantifiedChemical(tokens.back());

    return ChemicalReaction{std::move(inputs), std::move(output), 0};
}

std::vector<ChemicalReaction> createChemicalReactions(const std::vector<std::string>& reactionLines)
{
    std::vector<ChemicalReaction> chemicalReactions;

    for (const auto& line : reactionLines)
    {
        ChemicalReaction chemicalReaction = createChemicalReaction(line);
        chemicalReactions.push_back(std::move(chemicalReaction));
    }

    return chemicalReactions;
}

long long minOreRequiredToProduceFuel(const std::vector<std::string>& reactionLines)
{
    std::vector<ChemicalReaction> chemicalReactions = createChemicalReactions(reactionLines);

    FuelProducer producer{std::move(chemicalReactions)};

    producer.produceFuel(1);

    return producer.getOreConsumed();
}

long long maxProducableFuel(const std::vector<std::string>& reactionLines)
{
    std::vector<ChemicalReaction> chemicalReactions = createChemicalReactions(reactionLines);

    long long lowerBoundInclusive = 1;
    long long upperBoundExclusive = TOTAL_ORE_AVAILABLE;
    while (upperBoundExclusive - lowerBoundInclusive > 1)
    {
        FuelProducer producer{chemicalReactions};

        long long mid = (lowerBoundInclusive + upperBoundExclusive) / 2;
        producer.produceFuel(mid);
        if (producer.getOreConsumed() <= TOTAL_ORE_AVAILABLE)
        {
            lowerBoundInclusive = mid;
        }
        else
        {
            upperBoundExclusive = mid;
        }
    }

    return lowerBoundInclusive;
}

}
}
}
