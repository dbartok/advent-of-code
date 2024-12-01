#include "IntcodeInterpreter.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day05
{

ParameterCreator::ParameterCreator(IntcodeNumberType opcodeWithParameterModes, const IntcodeProgamState& state)
    : m_opcodeWithParameterModes{opcodeWithParameterModes}
    , m_state{state}
{

}

IntcodeParameter ParameterCreator::getParam(size_t parameterPosition)
{
    const IntcodeNumberType value = m_state.program.at(m_state.instructionPointer + parameterPosition);
    const IntcodeParameterMode parameterMode = createParameterMode(parameterPosition);

    return IntcodeParameter{value, parameterMode};
}

IntcodeParameterMode ParameterCreator::createParameterMode(size_t parameterPosition)
{
    const int divisor = pow(10, parameterPosition + 1);

    const int modeNumber = (m_opcodeWithParameterModes / divisor) % 10;

    if (modeNumber == 0)
    {
        return IntcodeParameterMode::POSITION;
    }
    else if (modeNumber == 1)
    {
        return IntcodeParameterMode::IMMEDIATE;
    }
    else if (modeNumber == 2)
    {
        return IntcodeParameterMode::RELATIVE;
    }

    throw std::runtime_error("Invalid parameter mode: " + std::to_string(modeNumber));
}

IntcodeInterpreter::IntcodeInterpreter(std::vector<IntcodeNumberType> program)
    : m_state{std::move(program), {}, {}, IntcodeProgramExecutionState::RUNNING, 0, 0}
{

}

void IntcodeInterpreter::execute()
{
    do
    {
        step();
    } while (m_state.executionState == IntcodeProgramExecutionState::RUNNING);
}

void IntcodeInterpreter::step()
{
    if (m_state.executionState == IntcodeProgramExecutionState::WAITING_FOR_INPUT)
    {
        m_state.executionState = IntcodeProgramExecutionState::RUNNING;
    }

    IntcodeInstruction::SharedPtr nextInstruction = createNextInstruction();

    nextInstruction->execute(m_state);
    nextInstruction->moveInstructionPointer(m_state.instructionPointer);
}

void IntcodeInterpreter::addInput(IntcodeNumberType input)
{
    m_state.inputs.push_back(input);
}

bool IntcodeInterpreter::isBlockedOnInput() const
{
    return m_state.executionState == IntcodeProgramExecutionState::WAITING_FOR_INPUT && m_state.inputs.empty();
}

const std::vector<IntcodeNumberType>& IntcodeInterpreter::getOutputs() const
{
    return m_state.outputs;
}

void IntcodeInterpreter::clearOutputs()
{
    m_state.outputs.clear();
}

const IntcodeProgramExecutionState IntcodeInterpreter::getExecutionState() const
{
    return m_state.executionState;
}

IntcodeInstruction::SharedPtr IntcodeInterpreter::createNextInstruction()
{
    const IntcodeNumberType opcodeWithParameterModes = m_state.program.at(m_state.instructionPointer);
    const int opcode = opcodeWithParameterModes % 100;

    ParameterCreator creator{opcodeWithParameterModes, m_state};

    switch (opcode)
    {
        case 1:
            return std::make_shared<AddIntcodeInstruction>(creator.getParam(1), creator.getParam(2), creator.getParam(3));
        case 2:
            return std::make_shared<MultiplyIntcodeInstruction>(creator.getParam(1), creator.getParam(2), creator.getParam(3));
        case 3:
            return std::make_shared<InputIntcodeInstruction>(creator.getParam(1));
        case 4:
            return std::make_shared<OutputIntcodeInstruction>(creator.getParam(1));
        case 5:
            return std::make_shared<JumpIfTrueIntcodeInstruction>(creator.getParam(1), creator.getParam(2));
        case 6:
            return std::make_shared<JumpIfFalseIntcodeInstruction>(creator.getParam(1), creator.getParam(2));
        case 7:
            return std::make_shared<LessThanIntcodeInstruction>(creator.getParam(1), creator.getParam(2), creator.getParam(3));
        case 8:
            return std::make_shared<EqualsIntcodeInstruction>(creator.getParam(1), creator.getParam(2), creator.getParam(3));
        case 9:
            return std::make_shared<RelativeBaseOffsetInstruction>(creator.getParam(1));
        case 99:
            return std::make_shared<HaltIntcodeInstruction>();
    }

    throw std::runtime_error("Invalid opcode: " + std::to_string(opcode));
}

}
}
}
