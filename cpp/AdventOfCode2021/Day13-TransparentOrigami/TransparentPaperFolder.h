#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash.hpp>

#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day13
{

enum class Axis
{
    X,
    Y,
};

struct FoldInstruction
{
    Axis axis;
    int position;
};

using FoldInstructions = std::vector<FoldInstruction>;

using Coordinates = std::pair<int, int>;
using CoordinatesSet = std::unordered_set<Coordinates, boost::hash<Coordinates>>;

struct BoundingBox
{
    Coordinates offset;
    Coordinates size;
};

class TransparentPaperFolder
{
public:
    TransparentPaperFolder(CoordinatesSet dotCoordinatesSet, FoldInstructions foldInstructions);

    void foldOnce();
    void foldCompletely();

    unsigned getNumVisibleDots() const;
    std::string getSerializedMessage() const;

private:
    CoordinatesSet m_dotCoordinatesSet;
    FoldInstructions m_foldInstructions;

    size_t m_instructionIndex = 0;

    void foldBottomHalfUp(int yThreshold);
    void foldRightHalfLeft(int xThreshold);

    BoundingBox getBoundingBox() const;
};

}
}
}
