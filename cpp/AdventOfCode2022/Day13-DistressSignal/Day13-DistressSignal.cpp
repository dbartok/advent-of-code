#include "Day13-DistressSignal.h"

#include "Packet.h"
#include "PacketParser.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char* firstDividerPacketString = "[[2]]";
const char* secondDividerPacketString = "[[6]]";

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day13
{

using PacketPairTextSection = std::vector<std::string>;
using PacketPair = std::pair<PacketSharedPtr, PacketSharedPtr>;
using PacketPairs = std::vector<PacketPair>;

PacketSharedPtr parsePacketString(const std::string& packetLine)
{
    PacketParser packetParser(packetLine);
    packetParser.parse();
    return packetParser.getRootPacket();
}

PacketPair parsePacketPairTextSection(const PacketPairTextSection& packetPairTextSection)
{
    PacketSharedPtr firstPacket = parsePacketString(packetPairTextSection.at(0));
    PacketSharedPtr secondPacket = parsePacketString(packetPairTextSection.at(1));

    return PacketPair{std::move(firstPacket), std::move(secondPacket)};
}

PacketPairs parseDistressSignalLines(const std::vector<std::string>& distressSignalLines)
{
    std::vector<PacketPairTextSection> packetPairTextSections;
    boost::split(packetPairTextSections, distressSignalLines, [](const auto& elem) { return elem.empty(); });

    PacketPairs packetPairs;

    for (const auto& packetPairTextSection : packetPairTextSections)
    {
        PacketPair packetPair = parsePacketPairTextSection(packetPairTextSection);
        packetPairs.push_back(std::move(packetPair));
    }

    return packetPairs;
}

PacketSharedPtr wrapInListPacket(const PacketSharedPtr& packet)
{
    return std::make_shared<ListPacket>(std::vector<PacketSharedPtr>{packet});
}

boost::optional<bool> arePacketsInOrder(const PacketSharedPtr& firstPacket, const PacketSharedPtr& secondPacket)
{
    Packets subpacketsInFirstPacket = firstPacket->getContainedPackets();
    Packets subpacketsInSecondPacket = secondPacket->getContainedPackets();

    for (size_t packetIndex = 0; ; ++packetIndex)
    {
        if (packetIndex == subpacketsInFirstPacket.size() && packetIndex == subpacketsInSecondPacket.size())
        {
            return boost::none;
        }

        if (packetIndex == subpacketsInFirstPacket.size())
        {
            return true;
        }

        if (packetIndex == subpacketsInSecondPacket.size())
        {
            return false;
        }

        PacketSharedPtr firstSubpacket = subpacketsInFirstPacket.at(packetIndex);
        PacketSharedPtr secondSubpacket = subpacketsInSecondPacket.at(packetIndex);

        const boost::optional<int> firstSubpacketScalarValue = firstSubpacket->getScalarValue();
        const boost::optional<int> secondSubpacketScalarValue = secondSubpacket->getScalarValue();

        if (firstSubpacketScalarValue && secondSubpacketScalarValue)
        {
            if (firstSubpacketScalarValue.value() != secondSubpacketScalarValue.value())
            {
                return firstSubpacketScalarValue.value() < secondSubpacketScalarValue.value();
            }
        }
        // At least one list packet
        else
        {
            if (firstSubpacketScalarValue)
            {
                firstSubpacket = wrapInListPacket(firstSubpacket);
            }

            if (secondSubpacketScalarValue)
            {
                secondSubpacket = wrapInListPacket(secondSubpacket);
            }

            const boost::optional<bool> orderResult = arePacketsInOrder(firstSubpacket, secondSubpacket);
            if (orderResult.has_value())
            {
                return orderResult;
            }
        }
    }
}

Packets flattenPacketPairs(const PacketPairs& packetPairs)
{
    Packets packets;

    for (const auto& packetPair : packetPairs)
    {
        packets.push_back(packetPair.first);
        packets.push_back(packetPair.second);
    }

    return packets;
}

int sumOfIndicesOfPairsInRightOrder(const std::vector<std::string>& distressSignalLines)
{
    PacketPairs packetPairs = parseDistressSignalLines(distressSignalLines);

    int sum = 0;

    for (size_t i = 0; i < packetPairs.size(); ++i)
    {
        const boost::optional<bool> orderResult = arePacketsInOrder(packetPairs.at(i).first, packetPairs.at(i).second);
        if (orderResult.get_value_or(true))
        {
            sum += (i + 1);
        }
    }

    return sum;
}

int decoderKeyForDistressSignal(const std::vector<std::string>& distressSignalLines)
{
    PacketPairs packetPairs = parseDistressSignalLines(distressSignalLines);
    Packets packets = flattenPacketPairs(packetPairs);

    PacketSharedPtr firstDividerPacket = parsePacketString(firstDividerPacketString);
    packets.push_back(firstDividerPacket);

    PacketSharedPtr secondDividerPacket = parsePacketString(secondDividerPacketString);
    packets.push_back(secondDividerPacket);

    std::sort(packets.begin(), packets.end(), [](const auto& lhs, const auto& rhs)
              {
                  const boost::optional<bool> orderResult = arePacketsInOrder(lhs, rhs);
                  return orderResult.get_value_or(true);
              });

    int decoderKey = 1;

    for (size_t i = 0; i < packets.size(); ++i)
    {
        if (packets.at(i) == firstDividerPacket || packets.at(i) == secondDividerPacket)
        {
            decoderKey *= (i + 1);
        }
    }

    return decoderKey;
}

}
}
}