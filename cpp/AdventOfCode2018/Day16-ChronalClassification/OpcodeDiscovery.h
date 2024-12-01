#pragma once

#include "InstructionEvaluator.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day16
{

using OpcodeToOpcodeStrings = std::unordered_map<unsigned, OpcodeStringSet>;

struct CapturedSample
{
    Registers before;
    Instruction instruction;
    Registers after;

    CapturedSample(Registers before, Instruction instruction, Registers after)
        : before{std::move(before)}
        , instruction{std::move(instruction)}
        , after{std::move(after)}

    {

    }
};

class OpcodeDiscovery
{
public:
    OpcodeDiscovery(std::vector<CapturedSample> capturedSamples);

    void discover();

    unsigned getNumSamplesBehaveMoreThanThreeOpcodes() const;
    OpcodeToOpcodeString getOpcodeToOpcodeString() const;

private:
    std::vector<CapturedSample> m_capturedSamples;

    OpcodeToOpcodeStrings m_opcodeToPossibleOpcodeStringsAmbiguous;
    OpcodeToOpcodeString m_opcodeToOpcodeStringUnambiguous;
    unsigned m_numSamplesBehaveMoreThanThreeOpcodes = 0;

    OpcodeStringSet getPossibleOpcodeStringsForSample(const CapturedSample& sample);

    void processOpcodeDiscovery(unsigned opcode, const OpcodeStringSet& constrainedOpcodeStrings);

    void disambiguatePossibleOpcodes();
    std::vector<unsigned> getNewlyDisambiguatedOpcodes() const;
    void moveOpcodesToUnambiguous(const std::vector<unsigned>& newlyDisambiguatedOpcodes);
    void removeOpcodeStringsFromPossibilities(const std::vector<unsigned>& newlyDisambiguatedOpcodes);
};

}
}
}
