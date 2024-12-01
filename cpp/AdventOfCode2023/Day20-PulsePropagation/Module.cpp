#include "Module.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day20
{

Module::Module(std::vector<std::string> outputModuleNames)
    : m_outputModuleNames{std::move(outputModuleNames)}
{

}

const std::vector<std::string>& Module::getOutputModuleNames() const
{
    return m_outputModuleNames;
}

const std::vector<std::string>& Module::getInputModuleNames() const
{
    return m_inputModuleNames;
}

void Module::addInputModule(const std::string& inputModuleName)
{
    m_inputModuleNames.push_back(inputModuleName);
}

Module::~Module()
{

}

boost::optional<PulseHeight> FlipFlopModule::processIncomingPulse(const std::string& sourceModuleName, PulseHeight height)
{
    if (height == PulseHeight::HIGH)
    {
        return boost::none;
    }
    else
    {
        if (m_isOn)
        {
            m_isOn = false;
            return PulseHeight::LOW;
        }
        else
        {
            m_isOn = true;
            return PulseHeight::HIGH;
        }
    }
}

void ConjunctionModule::addInputModule(const std::string& inputModuleName)
{
    Module::addInputModule(inputModuleName);
    m_inputModuleNameToMostRecentPulse.emplace(inputModuleName, PulseHeight::LOW);
}

boost::optional<PulseHeight> ConjunctionModule::processIncomingPulse(const std::string& sourceModuleName, PulseHeight height)
{
    m_inputModuleNameToMostRecentPulse.at(sourceModuleName) = height;

    if (std::all_of(m_inputModuleNameToMostRecentPulse.cbegin(), m_inputModuleNameToMostRecentPulse.cend(), [](const auto& inputModuleNameAndMostRecentPulse)
                    {
                        return inputModuleNameAndMostRecentPulse.second == PulseHeight::HIGH;
                    }))
    {
        return PulseHeight::LOW;
    }
    else
    {
        return PulseHeight::HIGH;
    }
}

void BroadcastModule::addInputModule(const std::string& inputModuleName)
{
    throw std::runtime_error("The broadcast module cannot accept inputs.");
}

boost::optional<PulseHeight> BroadcastModule::processIncomingPulse(const std::string& sourceModuleName, PulseHeight height)
{
    return height;
}

boost::optional<PulseHeight> OutputModule::processIncomingPulse(const std::string& sourceModuleName, PulseHeight height)
{
    return boost::none;
}

}
}
}
