#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day20
{

class Module;
using ModuleSharedPtr = std::shared_ptr<Module>;
using ModuleNameToModuleSharedPtr = std::unordered_map<std::string, ModuleSharedPtr>;

enum class PulseHeight
{
    LOW = 0,
    HIGH = 1,
};

class Module
{
public:
    Module(std::vector<std::string> outputModuleNames);

    const std::vector<std::string>& getOutputModuleNames() const;
    const std::vector<std::string>& getInputModuleNames() const;

    virtual void addInputModule(const std::string& inputModuleName);
    virtual boost::optional<PulseHeight> processIncomingPulse(const std::string& sourceModuleName, PulseHeight height) = 0;

    virtual ~Module();

private:
    std::vector<std::string> m_inputModuleNames;
    std::vector<std::string> m_outputModuleNames;
};


class FlipFlopModule : public Module
{
public:
    using Module::Module;

    boost::optional<PulseHeight> processIncomingPulse(const std::string& sourceModuleName, PulseHeight height) override;

private:
    bool m_isOn = false;
};

class ConjunctionModule : public Module
{
public:
    using Module::Module;

    void addInputModule(const std::string& inputModuleName) override;

    boost::optional<PulseHeight> processIncomingPulse(const std::string& sourceModuleName, PulseHeight height) override;

private:
    std::unordered_map<std::string, PulseHeight> m_inputModuleNameToMostRecentPulse;
};

class BroadcastModule : public Module
{
public:
    using Module::Module;

    void addInputModule(const std::string& inputModuleName) override;

    boost::optional<PulseHeight> processIncomingPulse(const std::string& sourceModuleName, PulseHeight height) override;
};

class OutputModule : public Module
{
public:
    using Module::Module;

    boost::optional<PulseHeight> processIncomingPulse(const std::string& sourceModuleName, PulseHeight height) override;
};

}
}
}
