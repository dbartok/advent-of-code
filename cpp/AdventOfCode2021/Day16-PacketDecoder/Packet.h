#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day16
{

class Packet
{
public:
    using SharedPtr = std::shared_ptr<Packet>;

    Packet(int64_t versionNumber);

    virtual int64_t getSumOfAllContainedVersionNumbers() const = 0;
    virtual int64_t evaluate() const = 0;

    virtual ~Packet();

protected:
    int64_t m_versionNumber;
};

class LiteralPacket : public Packet
{
public:
    LiteralPacket(int64_t versionNumber, int64_t literal);

    int64_t getSumOfAllContainedVersionNumbers() const override;
    int64_t evaluate() const override;

    virtual ~LiteralPacket();

private:
    int64_t m_literal;
};

class OperatorPacket : public Packet
{
public:
    OperatorPacket(int64_t versionNumber, std::vector<Packet::SharedPtr> containedPacketPtrs);

    int64_t getSumOfAllContainedVersionNumbers() const override;
    virtual int64_t evaluate() const = 0;

    virtual ~OperatorPacket();

protected:
    std::vector<Packet::SharedPtr> m_containedPacketPtrs;
};

class SumOperatorPacket : public OperatorPacket
{
public:
    using OperatorPacket::OperatorPacket;

    int64_t evaluate() const override;

    virtual ~SumOperatorPacket();
};

class ProductOperatorPacket : public OperatorPacket
{
public:
    using OperatorPacket::OperatorPacket;

    int64_t evaluate() const override;

    virtual ~ProductOperatorPacket();
};

class MinimumOperatorPacket : public OperatorPacket
{
public:
    using OperatorPacket::OperatorPacket;

    int64_t evaluate() const override;

    virtual ~MinimumOperatorPacket();
};

class MaximumOperatorPacket : public OperatorPacket
{
public:
    using OperatorPacket::OperatorPacket;

    int64_t evaluate() const override;

    virtual ~MaximumOperatorPacket();
};

class TwoOperandOperatorPacket : public OperatorPacket
{
public:
    using OperatorPacket::OperatorPacket;

    int64_t evaluate() const override;
    virtual int64_t evaluateForTwoOperands(int64_t lhs, int64_t rhs) const = 0;

    virtual ~TwoOperandOperatorPacket();
};

class GreaterThanOperatorPacket : public TwoOperandOperatorPacket
{
public:
    using TwoOperandOperatorPacket::TwoOperandOperatorPacket;

    int64_t evaluateForTwoOperands(int64_t lhs, int64_t rhs) const override;

    virtual ~GreaterThanOperatorPacket();
};

class LessThanOperatorPacket : public TwoOperandOperatorPacket
{
public:
    using TwoOperandOperatorPacket::TwoOperandOperatorPacket;

    int64_t evaluateForTwoOperands(int64_t lhs, int64_t rhs) const override;

    virtual ~LessThanOperatorPacket();
};

class EqualToOperatorPacket : public TwoOperandOperatorPacket
{
public:
    using TwoOperandOperatorPacket::TwoOperandOperatorPacket;

    int64_t evaluateForTwoOperands(int64_t lhs, int64_t rhs) const override;

    virtual ~EqualToOperatorPacket();
};

}
}
}
