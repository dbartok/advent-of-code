#include "PulseProcessor.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/math/common_factor_rt.hpp>

#include <numeric>
#include <queue>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day20
{

PulseProcessor::PulseProcessor(ModuleNameToModuleSharedPtr moduleNameToModuleSharedPtr)
    : m_moduleNameToModuleSharedPtr{std::move(moduleNameToModuleSharedPtr)}
{
    const auto rxModuleNameToModuleSharedPtrIter = m_moduleNameToModuleSharedPtr.find("rx");

    if (rxModuleNameToModuleSharedPtrIter == m_moduleNameToModuleSharedPtr.cend())
    {
        return;
    }

    m_finalConjunctionModuleName = rxModuleNameToModuleSharedPtrIter->second->getInputModuleNames().front();
    const ModuleSharedPtr& finalConjunctionModuleSharedPtr = m_moduleNameToModuleSharedPtr.at(m_finalConjunctionModuleName);

    for (const auto& finalConjunctionInputModuleName : finalConjunctionModuleSharedPtr->getInputModuleNames())
    {
        m_finalConjunctionInputModuleNameToPeriod.emplace(finalConjunctionInputModuleName, 0);
    }
}

void PulseProcessor::processRepeatedButtonPresses(unsigned numButtonPresses)
{
    for (int i = 0; i < numButtonPresses; ++i)
    {
        processSingleButtonPress();
    }
}

void PulseProcessor::processUntilLowPulseDeliveredToRx()
{
    while (!std::all_of(m_finalConjunctionInputModuleNameToPeriod.cbegin(), m_finalConjunctionInputModuleNameToPeriod.cend(), [](const auto& finalConjunctionInputModuleNameAndPeriod)
                        {
                            return finalConjunctionInputModuleNameAndPeriod.second != 0;
                        }))
    {
        processSingleButtonPress();
    }

    m_numButtonPresses = std::accumulate(m_finalConjunctionInputModuleNameToPeriod.cbegin(), m_finalConjunctionInputModuleNameToPeriod.cend(), 1ll, [](int64_t acc, const auto& finalConjunctionInputModuleNameAndPeriod)
                                            {
                                                return boost::math::lcm(acc, static_cast<int64_t>(finalConjunctionInputModuleNameAndPeriod.second));
                                            });
}

int PulseProcessor::getNumLowAndHighPulsesMultipliedTogether() const
{
    return m_numLowPulses * m_numHighPulses;
}

int64_t PulseProcessor::getNumButtonPresses() const
{
    return m_numButtonPresses;
}

void PulseProcessor::processSingleButtonPress()
{
    ++m_numButtonPresses;

    std::queue<Pulse> signalQueue;
    signalQueue.emplace("button", "broadcaster", PulseHeight::LOW);

    while (!signalQueue.empty())
    {
        Pulse currentPulse = signalQueue.front();
        signalQueue.pop();

        saveFinalConjuctionInputPeriodIfNeeded(currentPulse);

        if (currentPulse.height == PulseHeight::LOW)
        {
            ++m_numLowPulses;
        }
        else
        {
            ++m_numHighPulses;
        }

        auto destinationModuleSharedPtr = m_moduleNameToModuleSharedPtr.at(currentPulse.destinationModuleName);
        boost::optional<PulseHeight> outgoingPulseHeight = destinationModuleSharedPtr->processIncomingPulse(currentPulse.sourceModuleName, currentPulse.height);

        if (!outgoingPulseHeight)
        {
            continue;
        }

        for (const auto& newSignalOutputModuleName : destinationModuleSharedPtr->getOutputModuleNames())
        {
            signalQueue.emplace(currentPulse.destinationModuleName, newSignalOutputModuleName, outgoingPulseHeight.get());
        }
    }
}

void PulseProcessor::saveFinalConjuctionInputPeriodIfNeeded(const Pulse& currentPulse)
{
    if (currentPulse.destinationModuleName != m_finalConjunctionModuleName || currentPulse.height != PulseHeight::HIGH)
    {
        return;
    }

    auto finalConjunctionInputModuleNameAndPeriodIter = m_finalConjunctionInputModuleNameToPeriod.find(currentPulse.sourceModuleName);
    if (finalConjunctionInputModuleNameAndPeriodIter != m_finalConjunctionInputModuleNameToPeriod.cend() && finalConjunctionInputModuleNameAndPeriodIter->second == 0)
    {
        finalConjunctionInputModuleNameAndPeriodIter->second = m_numButtonPresses;
    }
}

}
}
}
