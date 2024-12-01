#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
#include <array>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day15
{

class InitializationSequenceAnalyzer
{
public:
    InitializationSequenceAnalyzer(std::vector<std::string> initializationSequence);

    void executeSequence();

    int getSumOfInitializationSequenceHashes() const;
    int getFocusingPower() const;

private:
    struct Lens
    {
        std::string label;
        int focalLength;

        Lens(std::string label, int focalLength)
            : label{std::move(label)}
            , focalLength(focalLength)
        {

        }
    };

    using Box = std::vector<Lens>;
    using Boxes = std::array<Box, 256>;

    std::vector<std::string> m_initializationSequence;

    Boxes m_boxes;

    void executeInstruction(const std::string& instruction);
    void executeRemoval(const std::string& instruction);
    void executeUpsertion(const std::string& instruction);

    static int getHashValue(const std::string& str);
};

}
}
}
