#include "RailPiece.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day13
{

void DeterministicOrientingRailPiece::applyOrientation(MineCart& mineCart)
{
    const Orientation currentOrientation = mineCart.getCurrentOrientation();

    const Orientation nextOrientation = m_orientationMap.at(currentOrientation);

    mineCart.setCurrentOrientation(nextOrientation);
}

MainDiagonalRailPiece::MainDiagonalRailPiece()
{
    m_orientationMap =
    {
        {Orientation::LEFT, Orientation::UP},
        {Orientation::UP, Orientation::LEFT},
        {Orientation::RIGHT, Orientation::DOWN},
        {Orientation::DOWN, Orientation::RIGHT}
    };
}

AntiDiagonalRailPiece::AntiDiagonalRailPiece()
{
    m_orientationMap =
    {
        {Orientation::LEFT, Orientation::DOWN},
        {Orientation::DOWN, Orientation::LEFT},
        {Orientation::RIGHT, Orientation::UP},
        {Orientation::UP, Orientation::RIGHT}
    };
}

void StraightRailPiece::applyOrientation(MineCart&)
{

}

void EmptyRailPiece::applyOrientation(MineCart&)
{
    throw std::runtime_error("Empty rail piece attempted to be used.");
}

void IntersectionRailPiece::applyOrientation(MineCart& mineCart)
{
    mineCart.turnToNextOrientation();
}

}
}
}
