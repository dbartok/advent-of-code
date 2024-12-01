#include "Day16-PacketDecoder.h"

#include "BitsTransmissionDecoder.h"
#include "Packet.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <sstream>
#include <bitset>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day16
{

std::string convertHexCharToBinaryString(char hexChar)
{
    int decimal = std::stoi(std::string{hexChar}, nullptr, 16);
    const std::bitset<4> binary(decimal);
    std::ostringstream oss;
    oss << binary;
    return oss.str();
}

std::string convertHexStringToBinaryString(const std::string& hexString)
{
    std::string binaryString;

    for (const char hexChar : hexString)
    {
        std::string binaryStringPiece = convertHexCharToBinaryString(hexChar);
        binaryString += binaryStringPiece;
    }

    return binaryString;
}

int64_t sumOfAllVersionNumbersInPackets(const std::string& transmissionString)
{
    std::string binaryTransmissionString = convertHexStringToBinaryString(transmissionString);
    BitsTransmissionDecoder decoder{std::move(binaryTransmissionString)};
    Packet::SharedPtr packet = decoder.decodePacket();

    return packet->getSumOfAllContainedVersionNumbers();
}

int64_t evaluateExpression(const std::string& transmissionString)
{
    std::string binaryTransmissionString = convertHexStringToBinaryString(transmissionString);
    BitsTransmissionDecoder decoder{std::move(binaryTransmissionString)};
    Packet::SharedPtr packet = decoder.decodePacket();

    return packet->evaluate();
}

}
}
}