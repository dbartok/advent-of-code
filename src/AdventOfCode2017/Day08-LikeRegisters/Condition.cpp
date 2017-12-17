#include "Condition.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

BEGIN_LIBRARIES_DISABLE_WARNINGS
// Add library includes here
END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{

Condition::Condition(std::string registerName, std::string symbol, int argument)
    : m_registerName{std::move(registerName)}
    , m_symbol{std::move(symbol)}
    , m_argument{argument}
{

}

bool Condition::isTrue(const State& state) const
{
    int registerValue = state.registerValue(m_registerName);

    if (m_symbol == "==")
    {
        return registerValue == m_argument;
    }
    else if (m_symbol == "!=")
    {
        return registerValue != m_argument;
    }
    else if (m_symbol == ">")
    {
        return registerValue > m_argument;
    }
    else if (m_symbol == "<")
    {
        return registerValue < m_argument;
    }
    else if (m_symbol == "<=")
    {
        return registerValue <= m_argument;
    }
    else if (m_symbol == ">=")
    {
        return registerValue >= m_argument;
    }
    else
    {
        throw("Unknown condition symbol.");
    }
}

}
