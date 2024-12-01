#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2018
{
namespace Day18
{

enum class Acre;
using LumberAreaRow = std::vector<Acre>;
using LumberArea = std::vector<LumberAreaRow>;

enum class Acre
{
    OPEN,
    TREE,
    LUMBERYARD,
};

class LumberLandscapeSimulator
{
public:
    LumberLandscapeSimulator(LumberArea initialArea);

    void run(unsigned numIterations);

    unsigned getResourceValue() const;

private:
    LumberArea m_lumberArea;
    size_t m_width;
    size_t m_height;

    std::vector<LumberArea> m_previousResults;

    void executeCycle();

    Acre getNewAcreAt(unsigned x, unsigned y) const;
    std::vector<Acre> getNeighborsAt(unsigned x, unsigned y) const;
    unsigned countAll(Acre acreToCount) const;
};

}
}
}
