#include "Day24-LobbyLayout.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

#include "HexTileFlipper.h"

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
    unsigned NUM_DAYS_TO_SIMULATE = 100;
}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day24
{

int numTilesWithBlackSideUpInInitialState(const std::vector<std::string>& tilePathLines)
{
    HexTileFlipper hexTileFlipper{tilePathLines};
    hexTileFlipper.setupInitialState();
    return hexTileFlipper.getNumBlackTiles();
}

int numTilesWithBlackSideUpAfterMultipleDays(const std::vector<std::string>& tilePathLines)
{
    HexTileFlipper hexTileFlipper{tilePathLines};
    hexTileFlipper.setupInitialState();
    hexTileFlipper.simulateMultipleDays(NUM_DAYS_TO_SIMULATE);
    return hexTileFlipper.getNumBlackTiles();
}

}
}
}
