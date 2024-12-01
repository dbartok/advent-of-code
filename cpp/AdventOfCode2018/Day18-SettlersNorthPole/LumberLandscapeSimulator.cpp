#include "LumberLandscapeSimulator.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day18
{

LumberLandscapeSimulator::LumberLandscapeSimulator(LumberArea initialArea)
    : m_lumberArea{std::move(initialArea)}
    , m_width{0}
    , m_height{m_lumberArea.size()}
{
    bool isRectangle = Utils::allElementsEqual(m_lumberArea.cbegin(), m_lumberArea.cend(), [](const LumberAreaRow& lhs, const LumberAreaRow& rhs)
                                                {
                                                    return lhs.size() == rhs.size();
                                                });

    if (!isRectangle)
    {
        throw std::runtime_error("Area needs to be a rectangle.");
    }

    if (m_height > 0)
    {
        m_width = m_lumberArea.front().size();
    }
}

void LumberLandscapeSimulator::run(unsigned numIterations)
{
    for (unsigned i = 0; i < numIterations; ++i)
    {
        m_previousResults.push_back(m_lumberArea);

        executeCycle();

        auto findResult = std::find(m_previousResults.cbegin(), m_previousResults.cend(), m_lumberArea);
        if (findResult != m_previousResults.cend())
        {
            unsigned cycleLength = std::distance(findResult, m_previousResults.cend());
            unsigned remainingIterations = numIterations - i - 1;
            unsigned resultPosInCycle = remainingIterations % cycleLength;
            auto finalPositionIter = findResult + resultPosInCycle;

            m_lumberArea = *finalPositionIter;
            break;
        }
    }
}

unsigned LumberLandscapeSimulator::getResourceValue() const
{
    return countAll(Acre::TREE) * countAll(Acre::LUMBERYARD);
}

void LumberLandscapeSimulator::executeCycle()
{
    LumberArea newLumberArea(m_height, LumberAreaRow{m_width, Acre::OPEN});

    for (unsigned j = 0; j < m_lumberArea.size(); ++j)
    {
        for (unsigned i = 0; i < m_lumberArea.size(); ++i)
        {
            newLumberArea[j][i] = getNewAcreAt(i, j);
        }
    }

    m_lumberArea = newLumberArea;
}

Acre LumberLandscapeSimulator::getNewAcreAt(unsigned x, unsigned y) const
{
    std::vector<Acre> neighbors = getNeighborsAt(x, y);
    unsigned treeCount = std::count(neighbors.cbegin(), neighbors.cend(), Acre::TREE);
    unsigned lumberyardCount = std::count(neighbors.cbegin(), neighbors.cend(), Acre::LUMBERYARD);

    Acre currentAcre = m_lumberArea[y][x];

    if (currentAcre == Acre::OPEN)
    {
        return treeCount >= 3 ? Acre::TREE : Acre::OPEN;
    }
    else if (currentAcre == Acre::TREE)
    {
        return lumberyardCount >= 3 ? Acre::LUMBERYARD : Acre::TREE;
    }
    else
    {
        return (treeCount > 0 && lumberyardCount > 0) ? Acre::LUMBERYARD : Acre::OPEN;
    }
}

std::vector<Acre> LumberLandscapeSimulator::getNeighborsAt(unsigned x, unsigned y) const
{
    std::vector<Acre> neighbors;

    unsigned iBegin = (x > 0) ? (x - 1) : 0;
    unsigned jBegin = (y > 0) ? (y - 1) : 0;

    unsigned iEnd = (x < m_width - 1) ? (x + 1) : (m_width - 1);
    unsigned jEnd = (y < m_height - 1) ? (y + 1) : (m_height - 1);

    for (int j = jBegin; j <= jEnd; ++j)
    {
        for (int i = iBegin; i <= iEnd; ++i)
        {
            if (i == x && j == y)
            {
                continue;
            }

            neighbors.push_back(m_lumberArea[j][i]);
        }
    }

    return neighbors;
}

unsigned LumberLandscapeSimulator::countAll(Acre acreToCount) const
{
    return std::accumulate(m_lumberArea.cbegin(), m_lumberArea.cend(), 0u, [acreToCount](unsigned acc, const LumberAreaRow& row)
                            {
                                return acc + std::count(row.cbegin(), row.cend(), acreToCount);
                            });
}

}
}
}
