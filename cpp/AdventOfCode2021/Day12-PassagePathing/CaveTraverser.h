#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day12
{

using Cave = std::string;
using CaveConnection = std::pair<Cave, Cave>;
using Caves = std::vector<Cave>;

class CaveTraverser
{
public:
    CaveTraverser(const std::vector<CaveConnection>& connections);

    void traverse();

    unsigned getNumPathsFromStartToEnd() const;

    virtual ~CaveTraverser();

protected:
    virtual bool canVisitLowercaseCave(const std::vector<Cave>& pathSoFar, const Cave& cave) = 0;

    static bool isUppercaseCave(const Cave& cave);

private:
    std::unordered_map<Cave, Caves> m_caveConnectedCaves;

    unsigned m_numPathsFromStartToEnd = 0;

    bool canVisitCave(const std::vector<Cave>& pathSoFar, const Cave& cave);
};

class CaveTraverserWithSingleVisitationLimitLowercase : public CaveTraverser
{
public:
    using CaveTraverser::CaveTraverser;

protected:
    bool canVisitLowercaseCave(const std::vector<Cave>& pathSoFar, const Cave& cave) override;
};

class CaveTraverserWithDoubleVisitationLimitForOneLowercase : public CaveTraverser
{
public:
    using CaveTraverser::CaveTraverser;

protected:
    bool canVisitLowercaseCave(const std::vector<Cave>& pathSoFar, const Cave& cave) override;

private:
    static std::unordered_map<Cave, int> getLowerCaseCaveToNumOccurencesInPath(const std::vector<Cave>& pathSoFar);
};

}
}
}
