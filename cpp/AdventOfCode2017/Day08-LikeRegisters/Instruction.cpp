#include "Instruction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day08
{

Instruction::Instruction(Operation operation, Condition condition)
    : m_operation{operation}
    , m_condition{condition}
{

}

void Instruction::execute(State& state) const
{
    if (m_condition.isTrue(state))
    {
        m_operation.execute(state);
    }
}

Instruction Instruction::fromString(const std::string& instructionString)
{
    std::vector<std::string> tokens;
    boost::split(tokens, instructionString, boost::is_any_of(" "));

    if (tokens.size() != 7)
    {
        throw std::runtime_error("Invalid number of tokens.");
    }

    if (tokens[3] != "if")
    {
        throw std::runtime_error("Mandatory 'if' token not found.");
    }

    std::string operationTargetRegisterName = std::move(tokens[0]);
    std::string operationName = std::move(tokens[1]);
    int operationArgument = std::stoi(tokens[2]);
    Operation operation{std::move(operationTargetRegisterName), std::move(operationName), std::move(operationArgument)};

    std::string conditionRegisterName = std::move(tokens[4]);
    std::string conditionSymbol = std::move(tokens[5]);
    int conditionArgument = std::stoi(tokens[6]);
    Condition condition{conditionRegisterName, conditionSymbol, conditionArgument};

    return Instruction{std::move(operation), std::move(condition)};
}

}
}
}
