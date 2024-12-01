#include "Operation.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day08
{

Operation::Operation(std::string target, std::string name, int argument) noexcept
    : m_target{std::move(target)}
    , m_name{std::move(name)}
    , m_argument{argument}
{

}

void Operation::execute(State& state) const
{
    if (m_name == "inc")
    {
        state.addToRegister(m_target, m_argument);
    }
    else if (m_name == "dec")
    {
        state.substractFromRegister(m_target, m_argument);
    }
    else
    {
        throw std::runtime_error("Unknown operation name.");
    }
}

}
}
}
