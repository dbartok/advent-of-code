#include "Day16-ProboscideaVolcanium.h"

#include "ValveNetworkSimplifier.h"
#include "FlowRateOptimizer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int AVAILABLE_TIME_FIRST_PART = 30;
const int AVAILABLE_TIME_SECOND_PART = 26;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day16
{

ValveRoom parseValveRoomLine(const std::string& valveRoomLine)
{
    const std::regex valveRoomLineRegex(R"(Valve ([A-Z]+) has flow rate=([0-9]+); tunnels? leads? to valves? ([A-Z,\s]+))");
    std::smatch valveRoomLineMatch;

    std::regex_match(valveRoomLine, valveRoomLineMatch, valveRoomLineRegex);

    std::string name = valveRoomLineMatch[1];
    const int flowRate = std::stoi(valveRoomLineMatch[2]);

    std::vector<std::string> connectedRoomNames;
    boost::split(connectedRoomNames, std::string{valveRoomLineMatch[3]}, boost::is_any_of(" ,"), boost::token_compress_on);

    return ValveRoom{std::move(name), flowRate, std::move(connectedRoomNames)};
}

std::vector<ValveRoom> parseValveRoomLines(const std::vector<std::string>& valveRoomLines)
{
    std::vector<ValveRoom> valveRooms;

    for (const auto& valveRoomLine : valveRoomLines)
    {
        ValveRoom valveRoom = parseValveRoomLine(valveRoomLine);
        valveRooms.push_back(std::move(valveRoom));
    }

    return valveRooms;
}

FlowRateOptimizer createFlowRateOptimizer(const std::vector<std::string>& valveRoomLines, int availableTime)
{
    std::vector<ValveRoom> valveRooms = parseValveRoomLines(valveRoomLines);

    ValveNetworkSimplifier valveNetworkSimplifier{std::move(valveRooms)};
    valveNetworkSimplifier.buildCostMatrix();

    CostMatrix costMatrix = valveNetworkSimplifier.getCostMatrix();
    std::unordered_map<size_t, int> roomIndexToFlowRate = valveNetworkSimplifier.getRoomIndexToFlowRate();

    FlowRateOptimizer flowRateOptimizer{std::move(costMatrix), std::move(roomIndexToFlowRate), availableTime};
    return flowRateOptimizer;
}

int mostPressureThatCanBeReleased(const std::vector<std::string>& valveRoomLines)
{
    FlowRateOptimizer flowRateOptimizer = createFlowRateOptimizer(valveRoomLines, AVAILABLE_TIME_FIRST_PART);

    flowRateOptimizer.createAllStates();

    return flowRateOptimizer.getMaxPressureReleasedWithOneWorker();
}

int mostPressureThatCanBeReleasedWorkingWithElephant(const std::vector<std::string>& valveRoomLines)
{
    FlowRateOptimizer flowRateOptimizer = createFlowRateOptimizer(valveRoomLines, AVAILABLE_TIME_SECOND_PART);
    
    flowRateOptimizer.createAllStates();

    return flowRateOptimizer.getMaxPressureReleasedWithTwoWorkers();
}

}
}
}