#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stack>
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day05
{

struct MoveInstruction
{
    size_t from_index;
    size_t to_index;
    size_t quantity;
};


using CrateStack = std::stack<char>;

class CargoCrane
{
public:
    CargoCrane(std::vector<CrateStack> crateStacks, std::vector<MoveInstruction> moveInstructions);

    void executeMoveInstructions();

    std::string getCratesOnTopOfEachStack() const;

protected:
    std::vector<CrateStack> m_crateStacks;
    std::vector<MoveInstruction> m_moveInstructions;

    virtual void executeMoveInstruction(const MoveInstruction& moveInstruction) = 0;
};

class SingleCrateMovingCargoCrane : public CargoCrane
{
public:
    using CargoCrane::CargoCrane;

protected:
    void executeMoveInstruction(const MoveInstruction& moveInstruction) override;

private:
    void moveSingleCrate(size_t from_index, size_t to_index);
};

class MultiCrateMovingCargoCrane : public CargoCrane
{
public:
    using CargoCrane::CargoCrane;

protected:
    void executeMoveInstruction(const MoveInstruction& moveInstruction) override;
};

}
}
}
