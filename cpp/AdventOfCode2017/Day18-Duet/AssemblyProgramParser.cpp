#include "AssemblyProgramParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day18
{

AssemblyProgramParser::AssemblyProgramParser(std::vector<std::string> instructionStrings) noexcept
    : m_instructionStrings{std::move(instructionStrings)}
{

}

AssemblyProgram AssemblyProgramParser::createProgram() const
{
    std::vector<AssemblyInstruction::SharedPtr> instructions;

    for (const auto& instructionString : m_instructionStrings)
    {
        std::vector<std::string> tokens;
        boost::split(tokens, instructionString, boost::is_any_of(" "));

        if (tokens.empty())
        {
            throw std::runtime_error("No tokens in instruction.");
        }

        std::string instructionName = std::move(tokens[0]);
        std::vector<std::string> args{std::make_move_iterator(tokens.begin() + 1), std::make_move_iterator(tokens.end())};

        AssemblyInstruction::SharedPtr instruction = createInstruction(instructionName, args);
        if (!instruction)
        {
            throw std::runtime_error("Unable to parse instruction: " + instructionString);
        }

        instructions.push_back(std::move(instruction));
    }

    return AssemblyProgram{instructions};
}

AssemblyInstruction::SharedPtr AssemblyProgramParser::createCustomInstruction(const std::string&, const std::vector<std::string>&) const noexcept
{
    return nullptr;
}

bool AssemblyProgramParser::validateInstruction(const std::string & instructionName, const std::vector<std::string> & args) const
{
    if (instructionName == "set" || instructionName == "add" || instructionName == "mul" || instructionName == "mod" || instructionName == "jgz" || instructionName == "sub" ||instructionName == "jnz")
    {
        if (args.size() != 2)
        {
            return false;
        }
    }
    else
    {
        if (args.size() != 1)
        {
            return false;
        }
    }

    return true;
}

AssemblyInstruction::SharedPtr AssemblyProgramParser::createDefaultInstruction(const std::string& instructionName, const std::vector<std::string>& args) const
{
    if (instructionName == "set")
    {
        return std::make_shared<SetInstruction>(args[0], args[1]);
    }
    else if (instructionName == "add")
    {
        return std::make_shared<AddInstruction>(args[0], args[1]);
    }
    else if (instructionName == "mul")
    {
        return std::make_shared<MultiplyInstruction>(args[0], args[1]);
    }
    else if (instructionName == "mod")
    {
        return std::make_shared<ModuloInstruction>(args[0], args[1]);
    }
    else if (instructionName == "jgz")
    {
        return std::make_shared<JumpGreaterThanZeroInstruction>(args[0], args[1]);
    }
    else if (instructionName == "sub")
    {
        return std::make_shared<SubtractInstruction>(args[0], args[1]);
    }
    else if (instructionName == "jnz")
    {
        return std::make_shared<JumpNotZeroInstruction>(args[0], args[1]);
    }
    else
    {
        return nullptr;
    }
}

AssemblyInstruction::SharedPtr AssemblyProgramParser::createInstruction(const std::string& instructionName, const std::vector<std::string>& args) const
{
    if (!validateInstruction(instructionName, args))
    {
        return nullptr;
    }

    auto customInstruction = createCustomInstruction(instructionName, args);

    if (customInstruction)
    {
        return customInstruction;
    }

    return createDefaultInstruction(instructionName, args);
}

AssemblyInstruction::SharedPtr SoundProgramParser::createCustomInstruction(const std::string& instructionName, const std::vector<std::string>& args) const noexcept
{
    if (instructionName == "snd")
    {
        return std::make_shared<SoundInstruction>(args[0]);
    }
    else if (instructionName == "rcv")
    {
        return std::make_shared<RecoverInstruction>(args[0]);
    }
    else
    {
        return nullptr;
    }
}

AssemblyInstruction::SharedPtr MessageQueueProgramParser::createCustomInstruction(const std::string& instructionName, const std::vector<std::string>& args) const noexcept
{
    if (instructionName == "snd")
    {
        return std::make_shared<SendInstruction>(args[0]);
    }
    else if (instructionName == "rcv")
    {
        return std::make_shared<ReceiveInstruction>(args[0]);
    }
    else
    {
        return nullptr;
    }
}

}
}
}
