#pragma once

#include "Module.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day20
{

struct Pulse
{
    std::string sourceModuleName;
    std::string destinationModuleName;
    PulseHeight height;

    Pulse(std::string sourceModuleName, std::string destinationModuleName, PulseHeight height)
        : sourceModuleName{std::move(sourceModuleName)}
        , destinationModuleName{std::move(destinationModuleName)}
        , height{std::move(height)}
    {

    }
};

class PulseProcessor
{
public:
    PulseProcessor(ModuleNameToModuleSharedPtr moduleNameToModuleSharedPtr);

    void processRepeatedButtonPresses(unsigned numButtonPresses);
    void processUntilLowPulseDeliveredToRx();

    int getNumLowAndHighPulsesMultipliedTogether() const;
    int64_t getNumButtonPresses() const;

private:
    ModuleNameToModuleSharedPtr m_moduleNameToModuleSharedPtr;

    int m_numLowPulses = 0;
    int m_numHighPulses = 0;
    int64_t m_numButtonPresses = 0;

    std::string m_finalConjunctionModuleName;
    std::unordered_map<std::string, int> m_finalConjunctionInputModuleNameToPeriod;

    void processSingleButtonPress();
    void saveFinalConjuctionInputPeriodIfNeeded(const Pulse& currentPulse);
};

}
}
}
