#include "Packet.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <numeric>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day16
{

Packet::Packet(int64_t versionNumber)
    : m_versionNumber{versionNumber}
{

}

Packet::~Packet()
{

}

LiteralPacket::LiteralPacket(int64_t versionNumber, int64_t literal)
    : Packet{versionNumber}
    , m_literal{literal}
{

}

int64_t LiteralPacket::getSumOfAllContainedVersionNumbers() const
{
    return m_versionNumber;
}

int64_t LiteralPacket::evaluate() const
{
    return m_literal;
}

LiteralPacket::~LiteralPacket()
{

}

OperatorPacket::OperatorPacket(int64_t versionNumber, std::vector<Packet::SharedPtr> containedPacketPtrs)
    : Packet{versionNumber}
    , m_containedPacketPtrs{std::move(containedPacketPtrs)}
{

}

int64_t OperatorPacket::getSumOfAllContainedVersionNumbers() const
{
    return std::accumulate(m_containedPacketPtrs.cbegin(), m_containedPacketPtrs.cend(), m_versionNumber, [](const auto& acc, const auto& packetPtr)
                            {
                                return acc + packetPtr->getSumOfAllContainedVersionNumbers();
                            });
}

OperatorPacket::~OperatorPacket()
{

}

int64_t SumOperatorPacket::evaluate() const
{
    return std::accumulate(m_containedPacketPtrs.cbegin(), m_containedPacketPtrs.cend(), 0ll, [](const auto& acc, const auto& packetPtr)
                            {
                                return acc + packetPtr->evaluate();
                            });
}

SumOperatorPacket::~SumOperatorPacket()
{

}


int64_t ProductOperatorPacket::evaluate() const
{
    return std::accumulate(m_containedPacketPtrs.cbegin(), m_containedPacketPtrs.cend(), 1ll, [](const auto& acc, const auto& packetPtr)
                            {
                                return acc * packetPtr->evaluate();
                            });
}

ProductOperatorPacket::~ProductOperatorPacket()
{

}

int64_t MinimumOperatorPacket::evaluate() const
{
    return std::accumulate(m_containedPacketPtrs.cbegin(), m_containedPacketPtrs.cend(), std::numeric_limits<int64_t>::max(), [](const auto& acc, const auto& packetPtr)
                            {
                                return std::min(acc, packetPtr->evaluate());
                            });
}

MinimumOperatorPacket::~MinimumOperatorPacket()
{

}


int64_t MaximumOperatorPacket::evaluate() const
{
    return std::accumulate(m_containedPacketPtrs.cbegin(), m_containedPacketPtrs.cend(), std::numeric_limits<int64_t>::min(), [](const auto& acc, const auto& packetPtr)
                            {
                                return std::max(acc, packetPtr->evaluate());
                            });
}

MaximumOperatorPacket::~MaximumOperatorPacket()
{

}

int64_t TwoOperandOperatorPacket::evaluate() const
{
    if (m_containedPacketPtrs.size() != 2)
    {
        throw std::runtime_error("A two operand operator must have exactly two operands");
    }

    const auto& lhsPacketPtr = m_containedPacketPtrs.at(0);
    const auto& rhsPacketPtr = m_containedPacketPtrs.at(1);

    return evaluateForTwoOperands(lhsPacketPtr->evaluate(), rhsPacketPtr->evaluate());
}

TwoOperandOperatorPacket::~TwoOperandOperatorPacket()
{

}

int64_t GreaterThanOperatorPacket::evaluateForTwoOperands(int64_t lhs, int64_t rhs) const
{
    return lhs > rhs;
}

GreaterThanOperatorPacket::~GreaterThanOperatorPacket()
{

}

int64_t LessThanOperatorPacket::evaluateForTwoOperands(int64_t lhs, int64_t rhs) const
{
    return lhs < rhs;
}

LessThanOperatorPacket::~LessThanOperatorPacket()
{

}

int64_t EqualToOperatorPacket::evaluateForTwoOperands(int64_t lhs, int64_t rhs) const
{
    return lhs == rhs;
}

EqualToOperatorPacket::~EqualToOperatorPacket()
{

}

}
}
}
