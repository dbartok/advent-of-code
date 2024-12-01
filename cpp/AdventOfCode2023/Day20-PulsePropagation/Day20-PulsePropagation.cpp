#include "Day20-PulsePropagation.h"

#include "Module.h"
#include "PulseProcessor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const unsigned NUM_BUTTON_PRESSES_PART_ONE = 1000;

}

namespace AdventOfCode
{
namespace Year2023
{
namespace Day20
{

ModuleSharedPtr createModuleSharedPtr(std::vector<std::string> outputModuleNames, char op)
{
    switch (op)
    {
        case '%':
            return std::make_shared<FlipFlopModule>(outputModuleNames);
        case '&':
            return std::make_shared<ConjunctionModule>(outputModuleNames);
        case 'b':
            return std::make_shared<BroadcastModule>(outputModuleNames);
        default:
            throw std::runtime_error("Invalid operator: " + std::string{op});
    }
}


std::pair<std::string, ModuleSharedPtr> parseModuleLine(const std::string& moduleLine)
{
    std::vector<std::string> moduleLineTokens;
    boost::split(moduleLineTokens, moduleLine, boost::is_any_of("->"), boost::token_compress_on);

    std::string outputNamesToken = moduleLineTokens.at(1);
    boost::trim(outputNamesToken);
    std::vector<std::string> outputNames;
    boost::split(outputNames, outputNamesToken, boost::is_any_of(", "), boost::token_compress_on);

    std::string name = moduleLineTokens.at(0);
    boost::trim(name);
    if (!isalpha(name.front()))
    {
        name = name.substr(1, name.size() - 1);
    }

    ModuleSharedPtr moduleSharedPtr = createModuleSharedPtr(std::move(outputNames), moduleLine.front());

    return {std::move(name), std::move(moduleSharedPtr)};
}

PulseProcessor parseModuleLines(const std::vector<std::string>& moduleLines)
{
    ModuleNameToModuleSharedPtr moduleNameToModuleSharedPtr;

    for (const auto& moduleLine : moduleLines)
    {
        std::pair<std::string, ModuleSharedPtr> moduleNameAndModuleSharedPtr = parseModuleLine(moduleLine);
        moduleNameToModuleSharedPtr.insert(std::move(moduleNameAndModuleSharedPtr));
    }

    // Add inputs
    for (const auto& moduleNameAndModuleSharedPtr : moduleNameToModuleSharedPtr)
    {
        const std::string& moduleName = moduleNameAndModuleSharedPtr.first;
        const ModuleSharedPtr& moduleSharedPtr = moduleNameAndModuleSharedPtr.second;

        for (const auto& outputModuleName : moduleSharedPtr->getOutputModuleNames())
        {
            auto moduleNameAndModuleSharedPtrIter = moduleNameToModuleSharedPtr.find(outputModuleName);

            // Found an output-only module
            if (moduleNameAndModuleSharedPtrIter == moduleNameToModuleSharedPtr.cend())
            {
                moduleNameAndModuleSharedPtrIter = moduleNameToModuleSharedPtr.emplace(outputModuleName, std::make_shared<OutputModule>(std::vector<std::string>{})).first;
            }

            moduleNameAndModuleSharedPtrIter->second->addInputModule(moduleName);
        }
    }

    return {moduleNameToModuleSharedPtr};
}


int numLowAndHighPulsesMultipliedTogether(const std::vector<std::string>& moduleLines)
{
    PulseProcessor pulseProcessor = parseModuleLines(moduleLines);

    pulseProcessor.processRepeatedButtonPresses(NUM_BUTTON_PRESSES_PART_ONE);

    return pulseProcessor.getNumLowAndHighPulsesMultipliedTogether();
}

int64_t fewestNumButtonPressesToDeliverLowPulseToRx(const std::vector<std::string>& moduleLines)
{
    PulseProcessor pulseProcessor = parseModuleLines(moduleLines);

    pulseProcessor.processUntilLowPulseDeliveredToRx();

    return pulseProcessor.getNumButtonPresses();
}

}
}
}