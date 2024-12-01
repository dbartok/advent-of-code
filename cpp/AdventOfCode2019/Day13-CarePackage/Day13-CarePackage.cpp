#include "Day13-CarePackage.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{
const int ENOUGH_QUARTERS_TO_PLAY = 2;
}

namespace AdventOfCode
{
namespace Year2019
{
namespace Day13
{

unsigned numBlockTilesWhenGameExits(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    IntcodeInterpreter interpreter{intcodeProgram};

    ArcadeCabinet arcadeCabinet{std::move(interpreter)};

    arcadeCabinet.play();

    return arcadeCabinet.getNumBlockTiles();
}

unsigned scoreAfterLastBlockBroken(const std::vector<IntcodeNumberType>& intcodeProgram)
{
    auto playableProgram{intcodeProgram};
    playableProgram.at(0) = ENOUGH_QUARTERS_TO_PLAY;
    IntcodeInterpreter interpreter{std::move(playableProgram)};

    ArcadeCabinet arcadeCabinet{std::move(interpreter)};

    arcadeCabinet.play();

    return arcadeCabinet.getScore();
}

}
}
}
