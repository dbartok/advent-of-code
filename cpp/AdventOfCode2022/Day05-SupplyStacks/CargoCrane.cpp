#include "CargoCrane.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day05
{

CargoCrane::CargoCrane(std::vector<CrateStack> crateStacks, std::vector<MoveInstruction> moveInstructions)
    : m_crateStacks{std::move(crateStacks)}
    , m_moveInstructions{std::move(moveInstructions)}
{

}

void CargoCrane::executeMoveInstructions()
{
    for (const auto& moveInstruction : m_moveInstructions)
    {
        executeMoveInstruction(moveInstruction);
    }
}

std::string CargoCrane::getCratesOnTopOfEachStack() const
{
    std::string cratesOnTopOfEachStack;

    for (const auto& crateStack : m_crateStacks)
    {
        cratesOnTopOfEachStack += crateStack.top();
    }

    return cratesOnTopOfEachStack;
}

void SingleCrateMovingCargoCrane::executeMoveInstruction(const MoveInstruction& moveInstruction)
{
    for (size_t iteration = 0; iteration < moveInstruction.quantity; ++iteration)
    {
        moveSingleCrate(moveInstruction.from_index, moveInstruction.to_index);
    }
}

void SingleCrateMovingCargoCrane::moveSingleCrate(size_t from_index, size_t to_index)
{
    const char crate = m_crateStacks.at(from_index).top();
    m_crateStacks.at(from_index).pop();
    m_crateStacks.at(to_index).push(crate);
}

void MultiCrateMovingCargoCrane::executeMoveInstruction(const MoveInstruction& moveInstruction)
{
    std::vector<char> cratesToMove;

    for (size_t iteration = 0; iteration < moveInstruction.quantity; ++iteration)
    {
        const char crate = m_crateStacks.at(moveInstruction.from_index).top();
        m_crateStacks.at(moveInstruction.from_index).pop();
        cratesToMove.push_back(crate);
    }

    std::reverse(cratesToMove.begin(), cratesToMove.end());

    for (size_t iteration = 0; iteration < moveInstruction.quantity; ++iteration)
    {
        const char crate = cratesToMove.at(iteration);
        m_crateStacks.at(moveInstruction.to_index).push(crate);
    }
}

}
}
}
