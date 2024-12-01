#pragma once

#include <AdventOfCode2019/Day05-SunnyWithAsteroids/IntcodeInterpreter.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day23
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;
using AdventOfCode::Year2019::Day05::IntcodeInterpreter;

struct IntcodePacket
{
    size_t destination;
    IntcodeNumberType messageOne;
    IntcodeNumberType messageTwo;
};

class IntcodeComputerNetwork
{
public:
    IntcodeComputerNetwork(const std::vector<IntcodeNumberType>& program);

    void runUntilFirstNatPacket();
    void runUntilFirstDuplicateNatPacket();

    IntcodeNumberType getSecondPartOfNatPacket() const;

private:
    std::vector<IntcodeInterpreter> m_interpreters;

    boost::optional<IntcodePacket> m_natPacket;
    boost::optional<IntcodePacket> m_previouslyDeliveredNatPacket;

    unsigned m_numStepsSincePacketSent = 0;

    void stepAllComputers();
    void processOutgoingPacket(const std::vector<IntcodeNumberType>& outputs);
    void deliverPacket(const IntcodePacket& packet);
    bool isSystemIdle() const;
};


}
}
}
