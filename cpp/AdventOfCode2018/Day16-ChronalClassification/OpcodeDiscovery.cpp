#include "OpcodeDiscovery.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day16
{

OpcodeDiscovery::OpcodeDiscovery(std::vector<CapturedSample> capturedSamples)
    : m_capturedSamples{std::move(capturedSamples)}
    , m_opcodeToPossibleOpcodeStringsAmbiguous{}
{

}

void OpcodeDiscovery::discover()
{
    for (const auto& capturedSample : m_capturedSamples)
    {
        auto possibleOpcodeStrings = getPossibleOpcodeStringsForSample(capturedSample);

        processOpcodeDiscovery(capturedSample.instruction.opcode, possibleOpcodeStrings);
    }

    disambiguatePossibleOpcodes();
}

unsigned OpcodeDiscovery::getNumSamplesBehaveMoreThanThreeOpcodes() const
{
    return m_numSamplesBehaveMoreThanThreeOpcodes;
}

OpcodeToOpcodeString OpcodeDiscovery::getOpcodeToOpcodeString() const
{
    return m_opcodeToOpcodeStringUnambiguous;
}

OpcodeStringSet OpcodeDiscovery::getPossibleOpcodeStringsForSample(const CapturedSample& sample)
{
    InstructionEvaluator instructionEvaluator{sample.instruction, sample.before};
    OpcodeStringSet allOpcodeStrings = instructionEvaluator.getAllOpcodeStrings();

    OpcodeStringSet possibleOpcodeStrings;

    for (const auto& opcodeString : allOpcodeStrings)
    {
        const Registers actualAfter = instructionEvaluator.evaluateAs(opcodeString);

        if (sample.after == actualAfter)
        {
            possibleOpcodeStrings.insert(opcodeString);
        }
    }

    return possibleOpcodeStrings;
}

void OpcodeDiscovery::processOpcodeDiscovery(unsigned opcode, const OpcodeStringSet& constrainedOpcodeStrings)
{
    if (constrainedOpcodeStrings.size() >= 3)
    {
        ++m_numSamplesBehaveMoreThanThreeOpcodes;
    }

    auto findResult = m_opcodeToPossibleOpcodeStringsAmbiguous.find(opcode);
    if (findResult == m_opcodeToPossibleOpcodeStringsAmbiguous.end())
    {
        m_opcodeToPossibleOpcodeStringsAmbiguous.emplace(opcode, constrainedOpcodeStrings);
    }
    else
    {
        auto& currentPossibleOpcodeStrings = findResult->second;

        OpcodeStringSet intersection;
        set_intersection(currentPossibleOpcodeStrings.cbegin(), currentPossibleOpcodeStrings.cend(),
                            constrainedOpcodeStrings.cbegin(), constrainedOpcodeStrings.cend(),
                            std::inserter(intersection, intersection.begin()));

        currentPossibleOpcodeStrings = intersection;
    }
}

void OpcodeDiscovery::disambiguatePossibleOpcodes()
{
    while (!m_opcodeToPossibleOpcodeStringsAmbiguous.empty())
    {
        std::vector<unsigned> newlyDisambiguatedOpcodes = getNewlyDisambiguatedOpcodes();

        if (newlyDisambiguatedOpcodes.empty())
        {
            throw std::runtime_error("Failed to disambiguate possible opcodes.");
        }

        moveOpcodesToUnambiguous(newlyDisambiguatedOpcodes);

        removeOpcodeStringsFromPossibilities(newlyDisambiguatedOpcodes);
    }
}

std::vector<unsigned> OpcodeDiscovery::getNewlyDisambiguatedOpcodes() const
{
    std::vector<unsigned> newlyDisambiguatedOpcodes;

    for (const auto& elem : m_opcodeToPossibleOpcodeStringsAmbiguous)
    {
        unsigned opcode = elem.first;
        const OpcodeStringSet& possibleOpcodeStrings = elem.second;

        if (possibleOpcodeStrings.size() == 1)
        {
            newlyDisambiguatedOpcodes.emplace_back(opcode);
        }
    }

    return newlyDisambiguatedOpcodes;
}

void OpcodeDiscovery::moveOpcodesToUnambiguous(const std::vector<unsigned>& newlyDisambiguatedOpcodes)
{
    for (const auto& opcode : newlyDisambiguatedOpcodes)
    {
        auto findResult = m_opcodeToPossibleOpcodeStringsAmbiguous.find(opcode);

        const auto& possibleOpcodeStrings = findResult->second;
        m_opcodeToOpcodeStringUnambiguous.emplace(opcode, *possibleOpcodeStrings.cbegin());

        m_opcodeToPossibleOpcodeStringsAmbiguous.erase(findResult);
    }
}

void OpcodeDiscovery::removeOpcodeStringsFromPossibilities(const std::vector<unsigned>& newlyDisambiguatedOpcodes)
{
    for (const auto& opcode : newlyDisambiguatedOpcodes)
    {
        std::string opcodeSring = m_opcodeToOpcodeStringUnambiguous.at(opcode);
        for (auto& elem : m_opcodeToPossibleOpcodeStringsAmbiguous)
        {
            OpcodeStringSet& possibleOpcodeStrings = elem.second;
            possibleOpcodeStrings.erase(opcodeSring);
        }
    }
}

}
}
}
