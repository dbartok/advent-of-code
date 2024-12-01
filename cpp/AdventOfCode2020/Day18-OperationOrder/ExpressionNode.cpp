#include "ExpressionNode.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day18
{

ExpressionNode::~ExpressionNode()
{

}

TwoOperandNode::TwoOperandNode(ExpressionNode::SharedPtr leftOperand, ExpressionNode::SharedPtr rightOperand)
    : m_leftOperand{std::move(leftOperand)}
    , m_rightOperand{std::move(rightOperand)}
{

}

int64_t AdditionNode::evaluate() const
{
    return m_leftOperand->evaluate() + m_rightOperand->evaluate();
}

int64_t MultiplicationNode::evaluate() const
{
    return m_leftOperand->evaluate() * m_rightOperand->evaluate();
}

NumberNode::NumberNode(int64_t number)
    :m_number{number}
{

}

int64_t NumberNode::evaluate() const
{
    return m_number;
}

}
}
}
