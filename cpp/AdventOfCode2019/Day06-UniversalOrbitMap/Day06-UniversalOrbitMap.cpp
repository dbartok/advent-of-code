#include "Day06-UniversalOrbitMap.h"

#include "OrbitMap.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day06
{

OrbitMap parseOrbitMap(const std::vector<std::string>& orbitLines, EdgeType edgeType)
{
    OrbitMap orbitMap;

    for (const auto& line : orbitLines)
    {
        std::vector<std::string> fromNodeIDAndToNodeID;
        Utils::splitStringIntoTypedVector(line, fromNodeIDAndToNodeID, ')');

        if (fromNodeIDAndToNodeID.size() != 2)
        {
            throw std::runtime_error("Invalid line: " + line);
        }

        orbitMap.addEdge(fromNodeIDAndToNodeID.front(), fromNodeIDAndToNodeID.back(), edgeType);
    }

    return orbitMap;
}

unsigned totalNumberOfDirectAndIndirectOrbits(const std::vector<std::string>& orbitLines)
{
    OrbitMap orbitMap = parseOrbitMap(orbitLines, EdgeType::DIRECTED);

    return orbitMap.getNumTransitiveOrbits();
}

unsigned minimumNumberOfOrbitalTransfers(const std::vector<std::string>& orbitLines)
{
    OrbitMap orbitMap = parseOrbitMap(orbitLines, EdgeType::UNDIRECTED);

    return orbitMap.getDistanceBetweenStartAndGoal() - 2;
}

}
}
}
