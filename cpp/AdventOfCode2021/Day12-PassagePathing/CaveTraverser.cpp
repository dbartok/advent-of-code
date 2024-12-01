#include "CaveTraverser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

using AdventOfCode::Year2021::Day12::Cave;
Cave START_CAVE = "start";
Cave END_CAVE = "end";

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day12
{

CaveTraverser::CaveTraverser(const std::vector<CaveConnection>& connections)
{
    for (const auto& connection : connections)
    {
        m_caveConnectedCaves[connection.first].push_back(connection.second);
        m_caveConnectedCaves[connection.second].push_back(connection.first);
    }
}

void CaveTraverser::traverse()
{
    std::queue<Caves> openCavePathsFromStart;
    openCavePathsFromStart.push({START_CAVE});

    while (!openCavePathsFromStart.empty())
    {
        const Caves currentPath = openCavePathsFromStart.front();
        openCavePathsFromStart.pop();

        const Cave& lastCaveInCurrentPath = currentPath.back();
        const Caves& connectedCaves = m_caveConnectedCaves.at(lastCaveInCurrentPath);

        for (const auto& cave : connectedCaves)
        {
            if (cave == END_CAVE)
            {
                ++m_numPathsFromStartToEnd;
            }
            else if (canVisitCave(currentPath, cave))
            {
                auto currentPathExtended{currentPath};
                currentPathExtended.push_back(cave);
                openCavePathsFromStart.push(currentPathExtended);
            }
        }
    }
}

unsigned CaveTraverser::getNumPathsFromStartToEnd() const
{
    return m_numPathsFromStartToEnd;
}

CaveTraverser::~CaveTraverser()
{

}

bool CaveTraverser::isUppercaseCave(const Cave& cave)
{
    return std::all_of(cave.cbegin(), cave.cend(), [](const auto& c)
                        {
                            return std::isupper(c);
                        });
}

bool CaveTraverser::canVisitCave(const std::vector<Cave>& pathSoFar, const Cave& cave)
{
    if (isUppercaseCave(cave))
    {
        return true;
    }

    else
    {
        return canVisitLowercaseCave(pathSoFar, cave);
    }
}


bool CaveTraverserWithSingleVisitationLimitLowercase::canVisitLowercaseCave(const std::vector<Cave>& pathSoFar, const Cave& cave)
{
    return std::find(pathSoFar.cbegin(), pathSoFar.cend(), cave) == pathSoFar.cend();
}

bool CaveTraverserWithDoubleVisitationLimitForOneLowercase::canVisitLowercaseCave(const std::vector<Cave>& pathSoFar, const Cave& cave)
{
    if (cave == START_CAVE || cave == END_CAVE)
    {
        return false;
    }

    std::unordered_map<Cave, int> caveToNumOccurencesInPath = getLowerCaseCaveToNumOccurencesInPath(pathSoFar);
    const auto caveToNumOccurrencesIter = caveToNumOccurencesInPath.find(cave);
    const int caveCountInPath = caveToNumOccurrencesIter != caveToNumOccurencesInPath.cend() ? caveToNumOccurrencesIter->second : 0;

    if (caveCountInPath == 0)
    {
        return true;
    }
    else if (caveCountInPath == 1)
    {
        const int numLowercaseCavesDuplicatedAlreadyInPath = std::count_if(caveToNumOccurencesInPath.cbegin(), caveToNumOccurencesInPath.cend(), [](const auto& elem)
                                                                                {
                                                                                    return elem.second == 2;
                                                                                });
        return numLowercaseCavesDuplicatedAlreadyInPath == 0;
    }
    else
    {
        return false;
    }
}

std::unordered_map<Cave, int> CaveTraverserWithDoubleVisitationLimitForOneLowercase::getLowerCaseCaveToNumOccurencesInPath(const std::vector<Cave>& pathSoFar)
{
    std::unordered_map<Cave, int> caveToNumOccurencesInPath;

    for (const auto& cave : pathSoFar)
    {
        if (!isUppercaseCave(cave))
        {
            ++caveToNumOccurencesInPath[cave];
        }
    }

    return caveToNumOccurencesInPath;
}

}
}
}
