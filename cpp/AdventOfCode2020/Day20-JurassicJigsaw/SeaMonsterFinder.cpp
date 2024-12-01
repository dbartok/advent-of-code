#include "SeaMonsterFinder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day20
{

SeaMonsterFinder::SeaMonsterFinder(std::vector<std::string> image)
    : m_originalImage{std::move(image)}
    , m_image{m_originalImage}
    , m_imageHeight{m_image.size()}
    , m_imageWidth{m_image.front().size()}
{

}

void SeaMonsterFinder::markSeaMonsterFields()
{
    for (size_t j = 0; j < m_imageHeight - m_seaMonsterPatternHeight + 1; ++j)
    {
        for (size_t i = 0; i < m_imageWidth - m_seaMonsterPatternWidth + 1; ++i)
        {
            if (isSeaMonsterStartingAt(i, j))
            {
                markSeaMonsterPatternStartingAt(i, j);
            }
        }
    }
}

int SeaMonsterFinder::getNumWaterFields() const
{
    return std::accumulate(m_image.cbegin(), m_image.cend(), 0, [](int outerAcc, const auto& row)
                            {
                                return outerAcc + std::accumulate(row.cbegin(), row.cend(), 0, [](int innerAcc, const auto& field)
                                                                    {
                                                                        return innerAcc + (field == '#');
                                                                    });
                            });
}

void SeaMonsterFinder::markSeaMonsterPatternStartingAt(size_t x, size_t y)
{
    for (size_t j = 0; j < m_seaMonsterPatternHeight; ++j)
    {
        for (size_t i = 0; i < m_seaMonsterPatternWidth; ++i)
        {
            const auto& seaMonsterPatternField = m_seaMonsterPattern.at(j).at(i);
            if (seaMonsterPatternField == '#')
            {
                m_image.at(y + j).at(x + i) = 'O';
            }
        }
    }
}

bool SeaMonsterFinder::isSeaMonsterStartingAt(size_t x, size_t y) const
{
    for (size_t j = 0; j < m_seaMonsterPatternHeight; ++j)
    {
        for (size_t i = 0; i < m_seaMonsterPatternWidth; ++i)
        {
            const auto& seaMonsterPatternField = m_seaMonsterPattern.at(j).at(i);
            if (seaMonsterPatternField == '#' && m_image.at(y + j).at(x + i) != '#')
            {
                return false;
            }
        }
    }

    return true;
}

}
}
}
