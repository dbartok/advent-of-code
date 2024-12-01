#include "DanceMove.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/lexical_cast.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day16
{

DanceMove::SharedPtr DanceMove::sharedPtrFromString(const std::string& danceMoveString)
{
    if (danceMoveString.empty())
    {
        throw std::runtime_error("Move string is empty.");
    }

    const char moveID = danceMoveString.front();
    const std::string argsString = danceMoveString.substr(1);

    if (moveID == 's')
    {
        unsigned offset = boost::lexical_cast<unsigned>(argsString);

        return std::make_shared<SpinMove>(offset);
    }
    else if (moveID == 'x')
    {
        std::vector<unsigned> args;
        Utils::splitStringIntoTypedVector(argsString, args, '/');
        if (args.size() != 2)
        {
            throw std::runtime_error("Two arguments expected for Exchange move.");
        }

        return std::make_shared<ExchangeMove>(args[0], args[1]);
    }
    else if (moveID == 'p')
    {
        std::vector<std::string> args;
        Utils::splitStringIntoTypedVector(argsString, args, '/');
        if (args.size() != 2)
        {
            throw std::runtime_error("Two arguments expected for Partner move.");
        }

        return std::make_shared<PartnerMove>(args[0], args[1]);
    }
    else
    {
        throw std::runtime_error("Unknown move identifier.");
    }
}


SpinMove::SpinMove(unsigned offset) noexcept
    : m_offset{offset}
{

}

void SpinMove::execute(std::string& nameOrderString) const
{
    if (nameOrderString.empty())
    {
        return;
    }

    auto namesInOrderOriginal{nameOrderString};

    for (size_t i = 0; i < nameOrderString.size(); ++i)
    {
        nameOrderString[(i + m_offset) % nameOrderString.size()] = namesInOrderOriginal[i];
    }
}


ExchangeMove::ExchangeMove(unsigned pos1, unsigned pos2) noexcept
    : m_pos1{pos1}
    , m_pos2{pos2}
{

}

void ExchangeMove::execute(std::string& nameOrderString) const
{
    if (nameOrderString.size() < std::max(m_pos1, m_pos2))
    {
        throw std::runtime_error("Too few elements.");
    }

    std::swap(nameOrderString[m_pos1], nameOrderString[m_pos2]);
}


PartnerMove::PartnerMove(std::string name1, std::string name2) noexcept
    : m_name1{std::move(name1)}
    , m_name2{std::move(name2)}
{

}

void PartnerMove::execute(std::string& nameOrderString) const
{
    const size_t name1Pos = nameOrderString.find(m_name1);
    const size_t name2Pos = nameOrderString.find(m_name2);

    if (name1Pos == std::string::npos || name2Pos == std::string::npos)
    {
        throw std::runtime_error("Both named elements need to be present.");
    }

    std::swap(nameOrderString[name1Pos], nameOrderString[name2Pos]);
}

}
}
}
