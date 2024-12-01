#pragma once

#include "Packet.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <vector>
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day16
{

enum class PacketTypeID
{
    SUM = 0,
    PRODUCT = 1,
    MINIMUM = 2,
    MAXIMUM = 3,
    LITERAL = 4,
    GREATER_THAN = 5,
    LESS_THAN = 6,
    EQUAL_TO = 7,
};

class BitsTransmissionDecoder
{
public:
    BitsTransmissionDecoder(std::string binaryTransmissionString);

    Packet::SharedPtr decodePacket();

private:
    std::string m_binaryTransmissionString;
    size_t m_currentIndex = 0;

    int64_t decodeVersionNumber();
    int64_t decodeTypeID();
    int64_t decodeLiteralPacketBody();
    std::vector<Packet::SharedPtr> decodeOperatorPacketContents();
    std::vector<Packet::SharedPtr> decodeTotalLengthOperatorPacketContents();
    std::vector<Packet::SharedPtr> decodeNumSubpacketsOperatorPacketContents();
    int64_t decodeNextNBits(size_t n);

    Packet::SharedPtr createOperatorPacket(PacketTypeID typeID, int64_t versionNumber, std::vector<Packet::SharedPtr> containedPacketPtrs) const;
};

}
}
}
