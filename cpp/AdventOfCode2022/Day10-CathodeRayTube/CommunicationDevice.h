#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int REGISTER_STARTING_VALUE = 1;
const unsigned SCREEN_WIDTH = 40;
const unsigned SCREEN_HEIGHT = 6;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day10
{

struct Instruction
{
    int offset;
    unsigned duration;
};

class CommunicationDevice
{
public:
    CommunicationDevice(std::vector<Instruction> instructions);

    void runProgram();

    int getSumOfInterestingSignalStrengths() const;
    std::string getImageAppearingOnScreen() const;

private:
    std::vector<Instruction> m_instructions;

    int m_register;
    unsigned m_cycleCounter;
    std::vector<int> m_interestingSignalStrengths;
    std::vector<bool> m_screen;

    void runInstruction(const Instruction& instruction);
    void elapseCycle();
    void captureInterestingSignalStrength();
    void drawCurrentPixel();
};

}
}
}
