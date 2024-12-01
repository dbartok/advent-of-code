#include "CommunicationDevice.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned INTERESTING_SIGNAL_STRENGTH_OFFSET = 20;
const unsigned INTERESTING_SIGNAL_STRENGTH_MODULUS = 40;
const unsigned INTERESTING_SIGNAL_STRENGTH_COUNT = 6;
const char LIGHT_PIXEL = '#';
const char DARK_PIXEL = '.';

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day10
{

CommunicationDevice::CommunicationDevice(std::vector<Instruction> instructions)
    : m_instructions{std::move(instructions)}
    , m_register{REGISTER_STARTING_VALUE}
    , m_cycleCounter{0u}
    , m_screen(SCREEN_HEIGHT* SCREEN_WIDTH)
{

}

void CommunicationDevice::runProgram()
{
    for (const auto& instruction : m_instructions)
    {
        runInstruction(instruction);
    }
}

int CommunicationDevice::getSumOfInterestingSignalStrengths() const
{
    if (m_interestingSignalStrengths.size() < INTERESTING_SIGNAL_STRENGTH_COUNT)
    {
        throw std::runtime_error("There are too few interesting signals");
    }

    return std::accumulate(m_interestingSignalStrengths.cbegin(), m_interestingSignalStrengths.cbegin() + INTERESTING_SIGNAL_STRENGTH_COUNT, 0);
}

std::string CommunicationDevice::getImageAppearingOnScreen() const
{
    std::string output;

    for (size_t i = 0; i < m_screen.size(); ++i)
    {
        const char currentChar = m_screen.at(i) ? LIGHT_PIXEL : DARK_PIXEL;
        output += currentChar;
        if ((i + 1) % SCREEN_WIDTH == 0 && i != m_screen.size() - 1)
        {
            output += "\n";
        }
    }

    return output;
}

void CommunicationDevice::runInstruction(const Instruction& instruction)
{
    for (unsigned cycleToElapse = 0; cycleToElapse < instruction.duration; ++cycleToElapse)
    {
        elapseCycle();
    }

    m_register += instruction.offset;
}

void CommunicationDevice::elapseCycle()
{
    drawCurrentPixel();

    ++m_cycleCounter;

    captureInterestingSignalStrength();
}

void CommunicationDevice::captureInterestingSignalStrength()
{
    if (m_cycleCounter % INTERESTING_SIGNAL_STRENGTH_MODULUS == INTERESTING_SIGNAL_STRENGTH_OFFSET)
    {
        m_interestingSignalStrengths.push_back(m_cycleCounter * m_register);
    }
}

void CommunicationDevice::drawCurrentPixel()
{
    const int currentlyRenderedPixelPositionX = m_cycleCounter % SCREEN_WIDTH;
    const bool isCurrentPixelLit = std::abs(currentlyRenderedPixelPositionX - m_register) <= 1;

    m_screen.at(m_cycleCounter) = isCurrentPixelLit;
}

}
}
}
