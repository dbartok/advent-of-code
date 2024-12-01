#pragma once

#include "State.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <functional>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day08
{

class Operation
{
public:
    Operation(std::string target, std::string name, int argument) noexcept;
    void execute(State& state) const;

private:
    std::string m_target;
    std::string m_name;
    int m_argument;
};

}
}
}
