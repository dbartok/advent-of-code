#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/variant.hpp>

#include <vector>
#include <string>
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day16
{

class DanceMove
{
public:
    using SharedPtr = std::shared_ptr<DanceMove>;

    DanceMove() = default;

    DanceMove(const DanceMove&) = default;
    DanceMove(DanceMove&&) = default;
    DanceMove& operator=(const DanceMove&) = default;
    DanceMove& operator=(DanceMove&&) = default;
    virtual ~DanceMove() = default;

    virtual void execute(std::string& nameOrderString) const = 0;

    static SharedPtr sharedPtrFromString(const std::string& danceMoveString);
};

class SpinMove : public DanceMove
{
public:
    SpinMove(unsigned offset) noexcept;

    SpinMove(const SpinMove&) = default;
    SpinMove(SpinMove&&) = default;
    SpinMove& operator=(const SpinMove&) = default;
    SpinMove& operator=(SpinMove&&) = default;
    ~SpinMove() = default;

    void execute(std::string& nameOrderString) const override;

private:
    unsigned m_offset;
};

class ExchangeMove : public DanceMove
{
public:
    ExchangeMove(unsigned pos1, unsigned pos2) noexcept;

    ExchangeMove(const ExchangeMove&) = default;
    ExchangeMove(ExchangeMove&&) = default;
    ExchangeMove& operator=(const ExchangeMove&) = default;
    ExchangeMove& operator=(ExchangeMove&&) = default;
    ~ExchangeMove() = default;

    void execute(std::string& nameOrderString) const override;

private:
    unsigned m_pos1;
    unsigned m_pos2;
};

class PartnerMove : public DanceMove
{
public:
    PartnerMove(std::string name1, std::string name2) noexcept;

    PartnerMove(const PartnerMove&) = default;
    PartnerMove(PartnerMove&&) = default;
    PartnerMove& operator=(const PartnerMove&) = default;
    PartnerMove& operator=(PartnerMove&&) = default;
    ~PartnerMove() = default;

    void execute(std::string& nameOrderString) const override;

private:
    std::string m_name1;
    std::string m_name2;
};

}
}
}
