#include "State.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day08
{

const State::RegisterValueToNameMap& State::getRegisterValueToNameMap() const noexcept
{
    return m_registerValueToNameMap;
}

void State::addToRegister(const std::string& registerName, int addend)
{
    int& registerValue = m_registerValueToNameMap[registerName];
    registerValue += addend;

    m_globalMaxValueOfRegisters = std::max(m_globalMaxValueOfRegisters, registerValue);
}

void State::substractFromRegister(const std::string& registerName, int subtrahend)
{
    int& registerValue = m_registerValueToNameMap[registerName];
    registerValue -= subtrahend;

    m_globalMaxValueOfRegisters = std::max(m_globalMaxValueOfRegisters, registerValue);
}

int State::registerValue(const std::string& registerName) const
{
    auto foundIter = m_registerValueToNameMap.find(registerName);
    if (foundIter == m_registerValueToNameMap.end())
    {
        return 0;
    }

    return foundIter->second;
}

int State::getGlobalMaxValueOfRegisters() const noexcept
{
    return m_globalMaxValueOfRegisters;
}

}
}
}
