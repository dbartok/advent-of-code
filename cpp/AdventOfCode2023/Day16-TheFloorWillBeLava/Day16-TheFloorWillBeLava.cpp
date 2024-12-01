#include "Day16-TheFloorWillBeLava.h"

#include "ContraptionAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day16
{

std::vector<BeamHead> getInwardsPointingEdgeBeamHeads(const std::vector<std::string>& contraptionLines)
{
    std::vector<BeamHead> inwardsPointingEdgeBeamHeads;

    for (int i = 0; i < contraptionLines.front().size(); ++i)
    {
        inwardsPointingEdgeBeamHeads.emplace_back(Coordinates{i, 0}, DOWN);
    }

    for (int i = 0; i < contraptionLines.front().size(); ++i)
    {
        inwardsPointingEdgeBeamHeads.emplace_back(Coordinates{i, contraptionLines.size() - 1}, UP);
    }

    for (int j = 0; j < contraptionLines.size(); ++j)
    {
        inwardsPointingEdgeBeamHeads.emplace_back(Coordinates{0, j}, RIGHT);
    }

    for (int j = 0; j < contraptionLines.size(); ++j)
    {
        inwardsPointingEdgeBeamHeads.emplace_back(Coordinates{contraptionLines.front().size() - 1, j}, LEFT);
    }

    return inwardsPointingEdgeBeamHeads;
}

int numEnergizedTiles(const std::vector<std::string>& contraptionLines)
{
    ContraptionAnalyzer contraptionAnalyzer{contraptionLines};

    contraptionAnalyzer.shootBeamFrom({STARTING_POSITION, RIGHT});

    return contraptionAnalyzer.getNumEnergizedTiles();
}

int maxNumEnergizedTiles(const std::vector<std::string>& contraptionLines)
{
    std::vector<BeamHead> inwardsPointingEdgeBeamHeads = getInwardsPointingEdgeBeamHeads(contraptionLines);

    int maxNumEnergizedTiles = 0;

    for (const auto& beamHead : inwardsPointingEdgeBeamHeads)
    {
        ContraptionAnalyzer contraptionAnalyzer{contraptionLines};

        contraptionAnalyzer.shootBeamFrom(beamHead);

        maxNumEnergizedTiles = std::max(maxNumEnergizedTiles, contraptionAnalyzer.getNumEnergizedTiles());
    }

    return maxNumEnergizedTiles;
}

}
}
}