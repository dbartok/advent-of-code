#include "BitsTransmissionDecoder.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
#include <cmath>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

size_t VERSION_NUMBER_NUM_BITS = 3;
size_t TYPE_ID_NUM_BITS = 3;
size_t LITERAL_CHUNK_NUM_BITS = 4;
size_t OPERATOR_PACKET_TOTAL_LENGTH_NUM_BITS = 15;
size_t OPERATOR_PACKET_NUM_SUBPACKETS_NUM_BITS = 11;

}

namespace AdventOfCode
{
namespace Year2021
{
namespace Day16
{

BitsTransmissionDecoder::BitsTransmissionDecoder(std::string binaryTransmissionString)
    : m_binaryTransmissionString{std::move(binaryTransmissionString)}
{

}

Packet::SharedPtr BitsTransmissionDecoder::decodePacket()
{
    const int64_t versionNumber = decodeVersionNumber();
    const int64_t typeID = decodeTypeID();

    Packet::SharedPtr packet;
    if (typeID == static_cast<int>(PacketTypeID::LITERAL))
    {
        const int64_t literal = decodeLiteralPacketBody();
        return std::make_shared<LiteralPacket>(versionNumber, literal);
    }
    else
    {
        std::vector<Packet::SharedPtr> containedPacketPtrs = decodeOperatorPacketContents();
        return createOperatorPacket(static_cast<PacketTypeID>(typeID), versionNumber, std::move(containedPacketPtrs));
    }
}

int64_t BitsTransmissionDecoder::decodeVersionNumber()
{
    return decodeNextNBits(VERSION_NUMBER_NUM_BITS);
}

int64_t BitsTransmissionDecoder::decodeTypeID()
{
    return decodeNextNBits(TYPE_ID_NUM_BITS);
}

int64_t BitsTransmissionDecoder::decodeLiteralPacketBody()
{
    int64_t literal = 0;
    bool areThereChunksRemaining = true;
    while (areThereChunksRemaining)
    {
        areThereChunksRemaining = decodeNextNBits(1);

        const int multiplicationFactor = std::pow(2, LITERAL_CHUNK_NUM_BITS);
        literal *= multiplicationFactor;

        const int literalChunk = decodeNextNBits(LITERAL_CHUNK_NUM_BITS);
        literal += literalChunk;
    }

    return literal;
}

std::vector<Packet::SharedPtr> BitsTransmissionDecoder::decodeOperatorPacketContents()
{
    const int64_t lengthTypeID = decodeNextNBits(1);

    if (lengthTypeID == 0)
    {
        return decodeTotalLengthOperatorPacketContents();
    }
    else
    {
        return decodeNumSubpacketsOperatorPacketContents();
    }
}

std::vector<Packet::SharedPtr> BitsTransmissionDecoder::decodeTotalLengthOperatorPacketContents()
{
    std::vector<Packet::SharedPtr> packets;
    const int64_t totalLengthInBits = decodeNextNBits(OPERATOR_PACKET_TOTAL_LENGTH_NUM_BITS);
    const size_t startIndex = m_currentIndex;

    while (m_currentIndex - startIndex < totalLengthInBits)
    {
        Packet::SharedPtr packet = decodePacket();
        packets.push_back(std::move(packet));
    }

    return packets;
}

std::vector<Packet::SharedPtr> BitsTransmissionDecoder::decodeNumSubpacketsOperatorPacketContents()
{
    std::vector<Packet::SharedPtr> packets;
    const int64_t numSubpackets = decodeNextNBits(OPERATOR_PACKET_NUM_SUBPACKETS_NUM_BITS);

    for (int64_t i = 0; i < numSubpackets; ++i)
    {
        Packet::SharedPtr packet = decodePacket();
        packets.push_back(std::move(packet));
    }

    return packets;
}

int64_t BitsTransmissionDecoder::decodeNextNBits(size_t n)
{
    std::string nextNBitsString = m_binaryTransmissionString.substr(m_currentIndex, n);
    m_currentIndex += n;
    return std::stoi(nextNBitsString, nullptr, 2);
}

Packet::SharedPtr BitsTransmissionDecoder::createOperatorPacket(PacketTypeID typeID, int64_t versionNumber, std::vector<Packet::SharedPtr> containedPacketPtrs) const
{
    switch (typeID)
    {
        case PacketTypeID::SUM:
            return std::make_shared<SumOperatorPacket>(versionNumber, std::move(containedPacketPtrs));
        case PacketTypeID::PRODUCT:
            return std::make_shared<ProductOperatorPacket>(versionNumber, std::move(containedPacketPtrs));
        case PacketTypeID::MINIMUM:
            return std::make_shared<MinimumOperatorPacket>(versionNumber, std::move(containedPacketPtrs));
        case PacketTypeID::MAXIMUM:
            return std::make_shared<MaximumOperatorPacket>(versionNumber, std::move(containedPacketPtrs));
        case PacketTypeID::GREATER_THAN:
            return std::make_shared<GreaterThanOperatorPacket>(versionNumber, std::move(containedPacketPtrs));
        case PacketTypeID::LESS_THAN:
            return std::make_shared<LessThanOperatorPacket>(versionNumber, std::move(containedPacketPtrs));
        case PacketTypeID::EQUAL_TO:
            return std::make_shared<EqualToOperatorPacket>(versionNumber, std::move(containedPacketPtrs));
        default:
            throw std::runtime_error("Unknown packet type ID: " + std::to_string(static_cast<int>(typeID)));
    }
}

}
}
}
