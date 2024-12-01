#include "Day22-SlamShuffle.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day22
{

ShuffleInstruction createShuffleInstruction(const std::vector<std::string>& tokens)
{
    ShuffleType type;
    int arg = 0;

    if (tokens.back() == "stack")
    {
        type = ShuffleType::DEAL_INTO_NEW_STACK;
    }
    else if (tokens.front() == "cut")
    {
        type = ShuffleType::CUT;
        arg = std::stoi(tokens.back());
    }
    else
    {
        type = ShuffleType::DEAL_WITH_INCREMENT;
        arg = std::stoi(tokens.back());
    }

    return ShuffleInstruction{type, arg};
}

std::vector<ShuffleInstruction> createShuffleInstructions(const std::vector<std::string>& shuffleInstructionLines)
{
    std::vector<ShuffleInstruction> shuffleInstructions;

    for (const auto& line : shuffleInstructionLines)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of(" "));

        ShuffleInstruction shuffleInstruction = createShuffleInstruction(tokens);

        shuffleInstructions.push_back(std::move(shuffleInstruction));
    }

    return shuffleInstructions;
}

std::vector<unsigned> cardsAfterShuffle(const std::vector<std::string>& shuffleInstructionLines, unsigned deckSize)
{
    std::vector<ShuffleInstruction> shuffleInstructions = createShuffleInstructions(shuffleInstructionLines);

    SlamShuffler shuffler{shuffleInstructions, deckSize, 1};

    return shuffler.getAllCardsAfterSingleIteration();
}

BigNumber cardAtPositionAfterMultipleShuffles(const std::vector<std::string>& shuffleInstructionLines, BigNumber deckSize, BigNumber numIterations, BigNumber position)
{
    std::vector<ShuffleInstruction> shuffleInstructions = createShuffleInstructions(shuffleInstructionLines);

    SlamShuffler shuffler{shuffleInstructions, deckSize, numIterations};

    return shuffler.getCardAtPosition(position);
}

}
}
}
