#include "Day08-TreetopTreeHouse.h"

#include "TreeHeightmapAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day08
{

MatrixRow parseHeightmapLine(const std::string& heightmapLine)
{
    MatrixRow heightmapMatrixRow(heightmapLine.size());

    for (size_t colIndex = 0; colIndex < heightmapLine.size(); ++colIndex)
    {
        heightmapMatrixRow[colIndex] = heightmapLine.at(colIndex) - '0';
    }

    return heightmapMatrixRow;
}

Matrix parseHeightmapLines(const std::vector<std::string>& heightmapLines)
{
    const size_t height = heightmapLines.size();
    const size_t width = heightmapLines.at(0).size();

    Matrix heightmap(height, width);

    for (size_t rowIndex = 0; rowIndex < heightmapLines.size(); ++rowIndex)
    {
        MatrixRow heightmapMatrixRow = parseHeightmapLine(heightmapLines.at(rowIndex));
        heightmap.row(rowIndex) = heightmapMatrixRow;
    }

    return heightmap;
}

int numTreesVisibleFromOutsideTheGrid(const std::vector<std::string>& heightmapLines)
{
    Matrix heightmapMatrix = parseHeightmapLines(heightmapLines);

    TreeHeightmapAnalyzer treeHeightmapAnalyzer{std::move(heightmapMatrix)};

    return treeHeightmapAnalyzer.getNumTreesVisibleFromOutsideTheGrid();
}

int highestPossibleScenicScore(const std::vector<std::string>& heightmapLines)
{
    Matrix heightmapMatrix = parseHeightmapLines(heightmapLines);

    TreeHeightmapAnalyzer treeHeightmapAnalyzer{std::move(heightmapMatrix)};

    return treeHeightmapAnalyzer.getHighestPossibleScenicScore();
}

}
}
}