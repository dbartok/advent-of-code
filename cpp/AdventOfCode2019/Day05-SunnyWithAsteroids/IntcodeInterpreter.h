#pragma once

#include "IntcodeInstruction.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day05
{

class ParameterCreator
{
public:
    ParameterCreator(IntcodeNumberType opcodeWithParameterModes, const IntcodeProgamState& state);

    IntcodeParameter getParam(size_t parameterPosition);

private:
    IntcodeNumberType m_opcodeWithParameterModes;
    const IntcodeProgamState& m_state;

    IntcodeParameterMode createParameterMode(size_t parameterPosition);
};

class IntcodeInterpreter
{
public:
    IntcodeInterpreter(std::vector<IntcodeNumberType> program);

    void execute();
    void step();

    void addInput(IntcodeNumberType input);
    bool isBlockedOnInput() const;
    const std::vector<IntcodeNumberType>& getOutputs() const;
    void clearOutputs();
    const IntcodeProgramExecutionState getExecutionState() const;

private:
    IntcodeProgamState m_state;

    IntcodeInstruction::SharedPtr createNextInstruction();
};

}
}
}
