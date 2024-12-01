#include "ArcadeCabinet.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const int LEFT_INPUT = -1;
const int NEUTRAL_INPUT = 0;
const int RIGHT_INPUT = 1;
}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day13
{

using AdventOfCode::Year2019::Day05::IntcodeNumberType;
using AdventOfCode::Year2019::Day05::IntcodeProgramExecutionState;

ArcadeCabinet::ArcadeCabinet(IntcodeInterpreter interpreter)
    : m_interpreter{std::move(interpreter)}
    , m_score{0}
{

}

void ArcadeCabinet::play()
{
    while (m_interpreter.getExecutionState() != IntcodeProgramExecutionState::TERMINATED)
    {
        m_interpreter.execute();

        const auto& outputs = m_interpreter.getOutputs();
        updateDisplay(outputs);

        m_interpreter.addInput(getNextInput());
        m_interpreter.clearOutputs();
    }
}

unsigned ArcadeCabinet::getNumBlockTiles() const
{
    return std::count_if(m_coordinatesToTileID.cbegin(), m_coordinatesToTileID.cend(), [](const auto& coordinatesAndTileID)
                            {
                                return coordinatesAndTileID.second == TileID::BLOCK;
                            });
}

int ArcadeCabinet::getScore() const
{
    return m_score;
}

void ArcadeCabinet::updateDisplay(const std::vector<IntcodeNumberType>& outputs)
{
    assert(outputs.size() % 3 == 0);
    for (size_t i = 0; i < outputs.size(); i += 3)
    {
        int xCoord = outputs.at(i);
        int yCoord = outputs.at(i + 1);
        int value = outputs.at(i + 2);

        if (xCoord == -1)
        {
            m_score = value;
            continue;
        }

        updatePixel({xCoord, yCoord}, value);
    }
}

void ArcadeCabinet::updatePixel(const Coordinates& coordinates, IntcodeNumberType value)
{
    TileID tileID = static_cast<TileID>(value);
    if (tileID == TileID::BALL)
    {
        m_ballPos = coordinates;
    }
    else if (tileID == TileID::PADDLE)
    {
        m_paddlePos = coordinates;
    }

    m_coordinatesToTileID[coordinates] = tileID;
}

int ArcadeCabinet::getNextInput() const
{
    if (m_paddlePos.first < m_ballPos.first)
    {
        return RIGHT_INPUT;
    }
    else if (m_paddlePos.first > m_ballPos.first)
    {
        return LEFT_INPUT;
    }
    else
    {
        return NEUTRAL_INPUT;
    }
}

}
}
}
