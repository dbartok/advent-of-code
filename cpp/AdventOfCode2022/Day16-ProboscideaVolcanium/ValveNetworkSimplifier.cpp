#include "ValveNetworkSimplifier.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char* START_ROOM_NAME = "AA";

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day16
{

ValveNetworkSimplifier::ValveNetworkSimplifier(std::vector<ValveRoom> valveRooms)
{
    for (auto& room : valveRooms)
    {
        m_roomNameToRoom.emplace(room.name, std::move(room));
    }
}

void ValveNetworkSimplifier::buildCostMatrix()
{
    allocateCostMatrixIndices();

    const size_t numRooms = m_roomNameToRoom.size();

    m_costMatrix = CostMatrix(numRooms, CostMatrixRow(numRooms));

    for (const auto& roomNameAndRoom : m_roomNameToRoom)
    {
        buildCostMatrixRow(roomNameAndRoom.first);
    }
}

CostMatrix ValveNetworkSimplifier::getCostMatrix() const
{
    return m_costMatrix;
}

std::unordered_map<size_t, int> ValveNetworkSimplifier::getRoomIndexToFlowRate() const
{
    std::unordered_map<size_t, int> roomIndexToFlowRate;

    for (const auto& roomNameAndRoom : m_roomNameToRoom)
    {
        const size_t roomIndex = m_roomNameToCostMatrixIndex.at(roomNameAndRoom.first);
        roomIndexToFlowRate.emplace(roomIndex, roomNameAndRoom.second.flowRate);
    }

    return roomIndexToFlowRate;
}

void ValveNetworkSimplifier::allocateCostMatrixIndices()
{
    m_roomNameToCostMatrixIndex.emplace(START_ROOM_NAME, START_ROOM_INDEX);

    size_t currentIndex = 1;

    for (const auto& roomNameAndRoom : m_roomNameToRoom)
    {
        const bool wasInserted = m_roomNameToCostMatrixIndex.emplace(roomNameAndRoom.first, currentIndex).second;
        if (wasInserted)
        {
            ++currentIndex;
        }
    }
}

void ValveNetworkSimplifier::buildCostMatrixRow(const std::string& startRoomName)
{
    const size_t startRoomIndex = m_roomNameToCostMatrixIndex.at(startRoomName);

    std::queue<std::string> roomNamesBfsQueue;
    roomNamesBfsQueue.push(startRoomName);

    while (!roomNamesBfsQueue.empty())
    {
        std::string currentRoomName = roomNamesBfsQueue.front();
        roomNamesBfsQueue.pop();

        const auto& currentRoom = m_roomNameToRoom.at(currentRoomName);
        const size_t currentRoomIndex = m_roomNameToCostMatrixIndex.at(currentRoomName);
        const int currentRoomCost = m_costMatrix.at(startRoomIndex).at(currentRoomIndex);

        for (const auto& connectedRoomName : currentRoom.connectedRoomNames)
        {
            const size_t connectedRoomIndex = m_roomNameToCostMatrixIndex.at(connectedRoomName);

            if (startRoomIndex != connectedRoomIndex && m_costMatrix.at(startRoomIndex).at(connectedRoomIndex) == 0)
            {
                m_costMatrix.at(startRoomIndex).at(connectedRoomIndex) = currentRoomCost + 1;
                roomNamesBfsQueue.push(connectedRoomName);
            }
        }
    }
}

}
}
}
