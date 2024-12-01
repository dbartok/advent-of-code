#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day20
{

class SeaMonsterFinder
{
public:
    SeaMonsterFinder(std::vector<std::string> image);

    void markSeaMonsterFields();

    int getNumWaterFields() const;

private:
    const std::vector<std::string> m_originalImage;
    std::vector<std::string> m_image;
    size_t m_imageHeight;
    size_t m_imageWidth;

    const std::vector<std::string> m_seaMonsterPattern =
    {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };
    const size_t m_seaMonsterPatternHeight = m_seaMonsterPattern.size();
    const size_t m_seaMonsterPatternWidth = m_seaMonsterPattern.front().size();

    void markSeaMonsterPatternStartingAt(size_t x, size_t y);

    bool isSeaMonsterStartingAt(size_t x, size_t y) const;
};

}
}
}
