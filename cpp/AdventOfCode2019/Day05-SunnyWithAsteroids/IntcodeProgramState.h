#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2019
{
namespace Day05
{

using IntcodeNumberType = long long;

enum class IntcodeProgramExecutionState
{
    RUNNING,
    WAITING_FOR_INPUT,
    TERMINATED,
};

template<class T>
class AutoGrowingOnOutOfBoundsVector
{
public:
    AutoGrowingOnOutOfBoundsVector(std::vector<T> vec)
        : m_innerVector{std::move(vec)}
    {

    }

    const T& at(size_t index) const
    {
        return m_innerVector.at(index);
    }

    T& at(size_t index)
    {
        if (index >= m_innerVector.size())
        {
            m_innerVector.resize(index + 1);
        }

        return m_innerVector.at(index);
    }

private:
    std::vector<T> m_innerVector;
};

struct IntcodeProgamState
{
    AutoGrowingOnOutOfBoundsVector<IntcodeNumberType> program;
    std::vector<IntcodeNumberType> inputs;

    std::vector<IntcodeNumberType> outputs;

    IntcodeProgramExecutionState executionState;
    size_t instructionPointer;
    IntcodeNumberType relativeBase;
};

}
}
}
