#include "Day25-HaltingProblem.h"

#include "TuringMachine.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <cassert>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day25
{

StateModifier createStateModifierFromLines(const std::vector<std::string>& stateModifierLines)
{
    assert(stateModifierLines.size() == 3);

    // Parse written value
    std::vector<std::string> tokens;
    boost::split(tokens, stateModifierLines[0], boost::is_any_of(" "), boost::token_compress_on);

    if (tokens.size() != 4)
    {
        throw std::runtime_error("Invalid new written value.");
    }

    const bool writtenValue = std::stoi(tokens[3]);

    // Parse cursor offset
    boost::split(tokens, stateModifierLines[1], boost::is_any_of(" "), boost::token_compress_on);

    if (tokens.size() != 6)
    {
        throw std::runtime_error("Invalid cursor offset.");
    }

    int cursorOffset{};
    if (tokens[5] == "left")
    {
        cursorOffset = -1;
    }
    else if (tokens[5] == "right")
    {
        cursorOffset = 1;
    }
    else
    {
        throw std::runtime_error("Invalid cursor direction.");
    }

    // Parse next state
    boost::split(tokens, stateModifierLines[2], boost::is_any_of(" "), boost::token_compress_on);

    if (tokens.size() != 4 || tokens[3].size() != 1)
    {
        throw std::runtime_error("Invalid next state.");
    }

    const StateIDType nextStateID = tokens[3].front();

    return StateModifier{writtenValue, cursorOffset, nextStateID};
}

TuringMachine::TransitionMap createTransitionMapFromLines(const std::vector<std::string>& transitionMapLines)
{
    if (transitionMapLines.size() % 10 != 0)
    {
        throw std::runtime_error("Invalid number of lines.");
    }

    TuringMachine::TransitionMap transitionMap;

    for (unsigned i = 0; i < transitionMapLines.size(); i+=10)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, transitionMapLines[i + 1], boost::is_any_of(" "));

        if (tokens.size() != 3 || tokens[2].size() == 0)
        {
            throw std::runtime_error("Invalid state transition headline.");
        }

        StateIDType stateID = tokens[2].front();

        StateModifier valueFalseModifier = createStateModifierFromLines({transitionMapLines.cbegin() + i + 3, transitionMapLines.cbegin() + i + 6});
        StateModifier valueTrueModifier = createStateModifierFromLines({transitionMapLines.cbegin() + i + 7, transitionMapLines.cbegin() + i + 10});

        StateTransition stateTransition{std::move(valueFalseModifier), std::move(valueTrueModifier)};

        transitionMap.emplace(stateID, std::move(stateTransition));
    }

    return transitionMap;
}

TuringMachine createTuringMachineFromLines(std::vector<std::string> turingMachineLines)
{
    if (turingMachineLines.size() < 2)
    {
        throw std::runtime_error("Not enough lines.");
    }

    std::for_each(turingMachineLines.begin(), turingMachineLines.end(), [](auto& line)
                  {
                      boost::trim_if(line, boost::is_any_of("-. "));
                  });

    // Parse initial state
    std::vector<std::string> tokens;
    boost::split(tokens, turingMachineLines[0], boost::is_any_of(" "), boost::token_compress_on);

    if (tokens.size() != 4 || tokens[3].size() != 1)
    {
        throw std::runtime_error("Invalid initial state.");
    }

    const StateIDType startingStateID = tokens[3].front();

    // Parse number of iterations
    boost::split(tokens, turingMachineLines[1], boost::is_any_of(" "), boost::token_compress_on);

    if (tokens.size() != 7)
    {
        throw std::runtime_error("Invalid number of iterations.");
    }

    const unsigned numIterations = boost::lexical_cast<unsigned>(tokens[5]);

    // Parse state transition map
    TuringMachine::TransitionMap stateIDToTransition = createTransitionMapFromLines({turingMachineLines.cbegin() + 2, turingMachineLines.cend()});

    return TuringMachine{stateIDToTransition, startingStateID, numIterations};
}

unsigned diagnosticChecksum(const std::vector<std::string>& turingMachineLines)
{
    TuringMachine turingMachine = createTuringMachineFromLines(turingMachineLines);
    turingMachine.run();
    return turingMachine.getChecksum();
}

}
}
}
