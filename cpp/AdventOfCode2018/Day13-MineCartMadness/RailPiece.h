#pragma once

#include "MineCart.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day13
{

class RailPiece;
using RailPieceSharedPtr = std::shared_ptr<RailPiece>;

class RailPiece
{
public:
    virtual void applyOrientation(MineCart& mineCart) = 0;
};

class DeterministicOrientingRailPiece : public RailPiece
{
public:
    void applyOrientation(MineCart& mineCart) override;

protected:
    std::unordered_map<Orientation, Orientation> m_orientationMap;
};

class MainDiagonalRailPiece : public DeterministicOrientingRailPiece
{
public:
    MainDiagonalRailPiece();
};

class AntiDiagonalRailPiece : public DeterministicOrientingRailPiece
{
public:
    AntiDiagonalRailPiece();
};

class StraightRailPiece : public RailPiece
{
public:
    void applyOrientation(MineCart&) override;
};

class EmptyRailPiece : public RailPiece
{
public:
    void applyOrientation(MineCart&) override;
};

class IntersectionRailPiece : public RailPiece
{
public:
    void applyOrientation(MineCart& mineCart) override;
};

}
}
}
