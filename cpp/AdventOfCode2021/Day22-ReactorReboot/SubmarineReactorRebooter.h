#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <vector>
#include <map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day22
{

using CubeState = bool;
using Interval = std::pair<int, int>;

struct RebootStep
{
    CubeState state;
    std::vector<Interval> intervalDimensions;

    bool isInitializationStep() const;
};

struct Node
{
public:
    void insertRebootStep(const RebootStep& rebootStep);

    uint64_t getNumCubesOn() const;

private:
    std::map<int, Node> m_intervals;
    boost::optional<CubeState> m_state;

    void splitAt(int threshold);
    std::vector<Node*> getNodesInRange(const Interval& interval);

    uint64_t getNumCubesOnRecursive(uint64_t multiplyingFactor) const;
};

class SubmarineReactorRebooter
{
public:

    SubmarineReactorRebooter(std::vector<RebootStep> rebootSteps);

    void executeRebootInitializationProcedure();
    void executeRebootFullRebootProcedure();

    uint64_t getNumCubesOn() const;

private:
    std::vector<RebootStep> m_rebootSteps;

    Node m_rootNode;

    void executeRebootStep(const RebootStep& rebootStep);
};


}
}
}
