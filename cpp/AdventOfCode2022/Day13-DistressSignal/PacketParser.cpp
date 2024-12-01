#include "PacketParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <algorithm>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day13
{

PacketParser::PacketParser(std::string packetString)
    : m_packetString{std::move(packetString)}
{
    std::string numberTokenBuffer;
    for (auto c : m_packetString)
    {
        if (isdigit(c))
        {
            numberTokenBuffer += c;
        }
        else
        {
            if (!numberTokenBuffer.empty())
            {
                m_tokens.push_back(std::move(numberTokenBuffer));
                numberTokenBuffer.clear();
            }
            if (c != ',')
            {
                m_tokens.push_back(std::string{c});
            }
        }
    }
}

void PacketParser::parse()
{
    // Skip outermost brackets because the root packet is precreated already
    getNextToken();

    Packets containedPackets = parseContainedPackets();
    m_rootPacket = std::make_shared<ListPacket>(std::move(containedPackets));
}

PacketSharedPtr PacketParser::getRootPacket() const
{
    return m_rootPacket;
}

Packets PacketParser::parseContainedPackets()
{
    Packets containedPackets;

    while (true)
    {
        std::string token = getNextToken();

        if (std::all_of(token.cbegin(), token.cend(), isdigit))
        {
            PacketSharedPtr packet = std::make_shared<IntegerPacket>(std::stoi(token));

            containedPackets.push_back(std::move(packet));
        }
        else if (token == "[")
        {
            Packets containedSubpackets = parseContainedPackets();
            PacketSharedPtr packet = std::make_shared<ListPacket>(std::move(containedSubpackets));

            containedPackets.push_back(std::move(packet));
        }
        else if (token == "]")
        {
            break;
        }
    }

    return containedPackets;
}

std::string PacketParser::getNextToken()
{
    return m_tokens.at(m_currentTokenIndex++);
}

}
}
}
