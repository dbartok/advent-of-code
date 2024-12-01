#pragma once

#include "FlowRateOptimizer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day16
{

struct ValveRoom
{
    std::string name;
    int flowRate;
    std::vector<std::string> connectedRoomNames;

};

class ValveNetworkSimplifier
{
public:
    ValveNetworkSimplifier(std::vector<ValveRoom> valveRooms);

    void buildCostMatrix();

    CostMatrix getCostMatrix() const;
    std::unordered_map<size_t, int> getRoomIndexToFlowRate() const;

private:
    std::unordered_map<std::string, ValveRoom> m_roomNameToRoom;

    std::unordered_map<std::string, size_t> m_roomNameToCostMatrixIndex;
    CostMatrix m_costMatrix;

    void allocateCostMatrixIndices();

    void buildCostMatrixRow(const std::string& startRoomName);
};

}
}
}
