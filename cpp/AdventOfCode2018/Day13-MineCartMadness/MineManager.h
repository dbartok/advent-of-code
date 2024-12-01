#pragma once

#include "RailPiece.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day13
{

using MineMapLine = std::vector<RailPieceSharedPtr>;
using MineMap = std::vector<MineMapLine>;

class MineManager
{
public:
    MineManager(MineMap mineMap, std::list<MineCart> mineCarts);

    Coordinates coordinatesOfFirstCollision();
    Coordinates coordinatesOfLastRemainingCart();

private:
    MineMap m_mineMap;
    std::list<MineCart> m_mineCarts;

    bool isThereCollision(const Coordinates& position) const;
    void sortMineCarts();
    std::list<MineCart>::iterator eraseBothMineCartsWithSamePosition(std::list<MineCart>::iterator mineCartIter);
    void reorientMineCart(MineCart& mineCart);
};

}
}
}
