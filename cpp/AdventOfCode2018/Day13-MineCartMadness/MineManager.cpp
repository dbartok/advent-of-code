#include "MineManager.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day13
{

using MineMapLine = std::vector<RailPieceSharedPtr>;
using MineMap = std::vector<MineMapLine>;

MineManager::MineManager(MineMap mineMap, std::list<MineCart> mineCarts)
    : m_mineMap{std::move(mineMap)}
    , m_mineCarts{std::move(mineCarts)}
{

}

Coordinates MineManager::coordinatesOfFirstCollision()
{
    while (true)
    {
        sortMineCarts();
        for (auto& mineCart : m_mineCarts)
        {
            mineCart.move();

            if (isThereCollision(mineCart.getCurrentPosition()))
            {
                return mineCart.getCurrentPosition();
            }

            reorientMineCart(mineCart);
        }
    }
}

Coordinates MineManager::coordinatesOfLastRemainingCart()
{
    while (m_mineCarts.size() > 1)
    {
        sortMineCarts();
        for (auto mineCartIter = m_mineCarts.begin(); mineCartIter != m_mineCarts.end();)
        {
            mineCartIter->move();

            if (isThereCollision(mineCartIter->getCurrentPosition()))
            {
                mineCartIter = eraseBothMineCartsWithSamePosition(mineCartIter);
            }
            else
            {
                reorientMineCart(*mineCartIter);
                ++mineCartIter;
            }
        }
    }

    return m_mineCarts.front().getCurrentPosition();
}

bool MineManager::isThereCollision(const Coordinates& position) const
{
    const auto numMineCartsAtPosition = std::count_if(m_mineCarts.cbegin(), m_mineCarts.cend(), [&position](const MineCart& mc) {return mc.getCurrentPosition() == position; });
    return numMineCartsAtPosition >= 2;
}

void MineManager::sortMineCarts()
{
    std::vector<MineCart> mineCartsVector{std::make_move_iterator(m_mineCarts.begin()), std::make_move_iterator(m_mineCarts.end())};

    std::sort(mineCartsVector.begin(), mineCartsVector.end(),
                [](const MineCart& lhs, const MineCart& rhs)
                {
                    return lhs.getCurrentPosition() < rhs.getCurrentPosition();
                });

    m_mineCarts.assign(std::make_move_iterator(mineCartsVector.begin()), std::make_move_iterator(mineCartsVector.end()));
}

std::list<MineCart>::iterator MineManager::eraseBothMineCartsWithSamePosition(std::list<MineCart>::iterator mineCartIter)
{
    std::list<MineCart>::iterator otherMineCartIter = m_mineCarts.begin();
    while (true)
    {
        if (mineCartIter != otherMineCartIter && otherMineCartIter->getCurrentPosition() == mineCartIter->getCurrentPosition())
        {
            break;
        }
        ++otherMineCartIter;
    }

    m_mineCarts.erase(otherMineCartIter);
    return m_mineCarts.erase(mineCartIter);
}

void MineManager::reorientMineCart(MineCart& mineCart)
{
    const auto& position = mineCart.getCurrentPosition();
    auto railPiece = m_mineMap[position.second][position.first];
    railPiece->applyOrientation(mineCart);
}

}
}
}
