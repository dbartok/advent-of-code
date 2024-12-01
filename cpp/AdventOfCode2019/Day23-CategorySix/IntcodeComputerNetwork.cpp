#include "IntcodeComputerNetwork.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
unsigned NUM_COMPUTERS = 50;
AdventOfCode::Year2019::Day05::IntcodeNumberType DEFAULT_INPUT = -1;
size_t NAT_ADDRESS = 255;
unsigned IDLE_THRESHOLD_NUM_STEPS = 10000;
}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day23
{

IntcodeComputerNetwork::IntcodeComputerNetwork(const std::vector<IntcodeNumberType>& program)
{
    for (size_t i = 0; i < NUM_COMPUTERS; ++i)
    {
        IntcodeInterpreter interpreter{program};
        interpreter.addInput(i);
        m_interpreters.push_back(std::move(interpreter));
    }
}

void IntcodeComputerNetwork::runUntilFirstNatPacket()
{
    while (!m_natPacket.has_value())
    {
        stepAllComputers();
    }
}

void IntcodeComputerNetwork::runUntilFirstDuplicateNatPacket()
{
    while (true)
    {
        stepAllComputers();

        if (isSystemIdle())
        {
            assert(m_natPacket.has_value());
            deliverPacket(*m_natPacket);

            if (m_previouslyDeliveredNatPacket.has_value() &&
                m_natPacket->messageTwo == m_previouslyDeliveredNatPacket->messageTwo)
            {
                break;
            }

            m_previouslyDeliveredNatPacket = m_natPacket;
        }
    }
}

IntcodeNumberType IntcodeComputerNetwork::getSecondPartOfNatPacket() const
{
    assert(m_natPacket.has_value());
    return m_natPacket->messageTwo;
}

void IntcodeComputerNetwork::stepAllComputers()
{
    ++m_numStepsSincePacketSent;
    for (auto& interpreter : m_interpreters)
    {
        if (interpreter.isBlockedOnInput())
        {
            interpreter.addInput(DEFAULT_INPUT);
        }

        interpreter.step();

        if (interpreter.getOutputs().size() == 3)
        {
            processOutgoingPacket(interpreter.getOutputs());
            interpreter.clearOutputs();
            m_numStepsSincePacketSent = 0;
        }
    }
}

void IntcodeComputerNetwork::processOutgoingPacket(const std::vector<IntcodeNumberType>& outputs)
{
    size_t destination = outputs.at(0);
    IntcodeNumberType messageOne = outputs.at(1);
    IntcodeNumberType messageTwo = outputs.at(2);

    IntcodePacket packet{destination, messageOne, messageTwo};

    if (destination == NAT_ADDRESS)
    {
        packet.destination = 0;
        m_natPacket = packet;
    }
    else
    {
        deliverPacket(packet);
    }
}

void IntcodeComputerNetwork::deliverPacket(const IntcodePacket& packet)
{
    m_interpreters.at(packet.destination).addInput(packet.messageOne);
    m_interpreters.at(packet.destination).addInput(packet.messageTwo);
    m_numStepsSincePacketSent = 0;
}

bool IntcodeComputerNetwork::isSystemIdle() const
{
    return m_numStepsSincePacketSent > IDLE_THRESHOLD_NUM_STEPS;
}

}
}
}
