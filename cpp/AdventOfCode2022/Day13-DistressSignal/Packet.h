#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/optional.hpp>

#include <vector>
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day13
{

class Packet;
using PacketSharedPtr = std::shared_ptr<Packet>;
using Packets = std::vector<PacketSharedPtr>;

class Packet
{
public:
    virtual Packets getContainedPackets() const = 0;
    virtual boost::optional<int> getScalarValue() const = 0;

    virtual ~Packet()
    {

    }

private:
};


class ListPacket : public Packet
{
public:
    ListPacket(Packets containedPackets)
        : m_containedPackets{std::move(containedPackets)}
    {

    }

    Packets getContainedPackets() const override
    {
        return m_containedPackets;
    }

    boost::optional<int> getScalarValue() const override
    {
        return boost::none;
    }

private:
    Packets m_containedPackets;
};

class IntegerPacket : public Packet
{
public:
    IntegerPacket(int value)
        : m_value{value}
    {

    }

    Packets getContainedPackets() const override
    {
        throw std::runtime_error("Integer packets contain no further packets");
    }

    boost::optional<int> getScalarValue() const override
    {
        return m_value;
    }

private:
    int m_value;
};

}
}
}
