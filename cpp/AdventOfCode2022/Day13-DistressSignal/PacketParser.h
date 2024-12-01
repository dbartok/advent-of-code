#pragma once

#include "Packet.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day13
{

class PacketParser
{
public:
    PacketParser(std::string packetString);

    void parse();

    PacketSharedPtr getRootPacket() const;

private:
    std::string m_packetString;
    std::vector<std::string> m_tokens;
    size_t m_currentTokenIndex = 0;

    PacketSharedPtr m_rootPacket = nullptr;

    Packets parseContainedPackets();
    std::string getNextToken();
};


}
}
}
