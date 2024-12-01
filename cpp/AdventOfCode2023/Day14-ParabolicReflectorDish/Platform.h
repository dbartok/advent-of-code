#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/dense>

#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day14
{

using Matrix = Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic>;

class Platform
{
public:
    Platform(Matrix matrix);

    void slideNorth();
    void executeSpinCycles(unsigned numSpinsToExecute);

    int getTotalLoadOnNorthSupportBeams() const;

private:
    Matrix m_matrix;
    std::vector<Matrix> m_seenMatrices;

    void executeSpinCycle();
    void rotateRight();

    int getNewYCoordinateForRoundRockAt(int x, int y) const;
};

}
}
}
