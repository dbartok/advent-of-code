#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day18
{

class ExpressionNode
{
public:
    using SharedPtr = std::shared_ptr<ExpressionNode>;

    virtual ~ExpressionNode();

    virtual int64_t evaluate() const = 0;
};

class TwoOperandNode : public ExpressionNode
{
public:
    TwoOperandNode(ExpressionNode::SharedPtr leftOperand, ExpressionNode::SharedPtr rightOperand);

protected:
    ExpressionNode::SharedPtr m_leftOperand;
    ExpressionNode::SharedPtr m_rightOperand;
};

class AdditionNode : public TwoOperandNode
{
public:
    using TwoOperandNode::TwoOperandNode;

    int64_t evaluate() const override;
};

class MultiplicationNode : public TwoOperandNode
{
public:
    using TwoOperandNode::TwoOperandNode;

    int64_t evaluate() const override;
};

class NumberNode : public ExpressionNode
{
public:
    NumberNode(int64_t number);

    int64_t evaluate() const override;

private:
    int64_t m_number;
};

}
}
}
