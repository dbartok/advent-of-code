#pragma once

#include "AssemblyProgram.h"
#include "AssemblyInstruction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day18
{

class AssemblyProgramParser
{
public:
    AssemblyProgramParser(std::vector<std::string> instructionStrings) noexcept;

    AssemblyProgramParser(const AssemblyProgramParser&) = default;
    AssemblyProgramParser(AssemblyProgramParser&&) = default;
    AssemblyProgramParser& operator=(const AssemblyProgramParser&) = default;
    AssemblyProgramParser& operator=(AssemblyProgramParser&&) = default;
    virtual ~AssemblyProgramParser() = default;

    AssemblyProgram createProgram() const;

protected:
    virtual AssemblyInstruction::SharedPtr createCustomInstruction(const std::string& instructionName, const std::vector<std::string>& args) const noexcept;

private:
    std::vector<std::string> m_instructionStrings;

    bool validateInstruction(const std::string& instructionName, const std::vector<std::string>& args) const;
    AssemblyInstruction::SharedPtr createDefaultInstruction(const std::string& instructionName, const std::vector<std::string>& args) const;
    AssemblyInstruction::SharedPtr createInstruction(const std::string& instructionName, const std::vector<std::string>& args) const;
};

class SoundProgramParser : public AssemblyProgramParser
{
public:
    using AssemblyProgramParser::AssemblyProgramParser;
    SoundProgramParser() = delete;

    SoundProgramParser(const SoundProgramParser&) = default;
    SoundProgramParser(SoundProgramParser&&) = default;
    SoundProgramParser& operator=(const SoundProgramParser&) = default;
    SoundProgramParser& operator=(SoundProgramParser&&) = default;
    ~SoundProgramParser() = default;

protected:
    AssemblyInstruction::SharedPtr createCustomInstruction(const std::string& instructionName, const std::vector<std::string>& args) const noexcept override;
};

class MessageQueueProgramParser : public AssemblyProgramParser
{
public:
    using AssemblyProgramParser::AssemblyProgramParser;
    MessageQueueProgramParser() = delete;

    MessageQueueProgramParser(const MessageQueueProgramParser&) = default;
    MessageQueueProgramParser(MessageQueueProgramParser&&) = default;
    MessageQueueProgramParser& operator=(const MessageQueueProgramParser&) = default;
    MessageQueueProgramParser& operator=(MessageQueueProgramParser&&) = default;
    ~MessageQueueProgramParser() = default;

protected:
    AssemblyInstruction::SharedPtr createCustomInstruction(const std::string& instructionName, const std::vector<std::string>& args) const noexcept override;
};

}
}
}
