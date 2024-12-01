#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
#include <unordered_map>
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const char* ROOT_NODE_NAME = "root";
const char* HUMAN_NODE_NAME = "humn";

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day21
{

class MonkeyNode;
using MonkeyNodeSharedPtr = std::shared_ptr<MonkeyNode>;

class MonkeyNode
{
public:
    MonkeyNode(std::string name)
        : m_name{std::move(name)}
        , m_parentNode{nullptr}
        , m_isAncestorOfHumanNode{false}
    {

    }

    virtual void setOperandNodes(MonkeyNodeSharedPtr leftOperandNode, MonkeyNodeSharedPtr rightOperandNode) = 0;
    virtual void forceEvaluateTo(int64_t expectedValue) = 0;
    virtual MonkeyNodeSharedPtr getLeftOperandNode() const = 0;
    virtual MonkeyNodeSharedPtr getRightOperandNode() const = 0;
    virtual int64_t evaluate() const = 0;

    void setParentNode(MonkeyNode* parentNode)
    {
        m_parentNode = parentNode;
    }

    void setIsAncestorOfHumanNode(bool isAncestorOfHumanNode)
    {
        m_isAncestorOfHumanNode = isAncestorOfHumanNode;
    }

    MonkeyNode* getParentNode() const
    {
        return m_parentNode;
    }

    bool getIsAncestorOfHumanNode() const
    {
        return m_isAncestorOfHumanNode;
    }

protected:
    std::string m_name;
    MonkeyNode* m_parentNode;
    bool m_isAncestorOfHumanNode;
};

class IntegerNode : public MonkeyNode
{
public:
    IntegerNode(std::string name, int64_t value)
        : MonkeyNode{std::move(name)}
        , m_value(value)
    {

    }

    void setOperandNodes(MonkeyNodeSharedPtr leftOperandNode, MonkeyNodeSharedPtr rightOperandNode) override
    {
        throw std::runtime_error("Cannot set operands on an integer node");
    }

    void forceEvaluateTo(int64_t expectedValue) override
    {
        if (m_name != HUMAN_NODE_NAME)
        {
            throw std::runtime_error("Cannot force evaluation for a non-human integer node");
        }

        m_value = expectedValue;
    }

    MonkeyNodeSharedPtr getLeftOperandNode() const override
    {
        throw std::runtime_error("Cannot get operands on an integer node");
    }

    MonkeyNodeSharedPtr getRightOperandNode() const override
    {
        throw std::runtime_error("Cannot get operands on an integer node");
    }

    int64_t evaluate() const override
    {
        return m_value;
    }

private:
    int64_t m_value;
};

class TwoOperandNode : public MonkeyNode
{
public:
    using MonkeyNode::MonkeyNode;

    virtual int64_t getLeftOperandValueForExpectedResult(int64_t expectedValue, int64_t rightOperandValue) const = 0;
    virtual int64_t getRightOperandValueForExpectedResult(int64_t expectedValue, int64_t leftOperandValue) const = 0;

    void forceEvaluateTo(int64_t expectedValue) override
    {
        if (m_leftOperandNode->getIsAncestorOfHumanNode() && m_rightOperandNode->getIsAncestorOfHumanNode())
        {
            throw std::runtime_error("Ambiguous evaluation: too many human nodes");
        }
        else if (m_leftOperandNode->getIsAncestorOfHumanNode())
        {
            const int64_t rightOperandValue = m_rightOperandNode->evaluate();
            const int64_t leftOperandExpectedValue = getLeftOperandValueForExpectedResult(expectedValue, rightOperandValue);
            m_leftOperandNode->forceEvaluateTo(leftOperandExpectedValue);
        }
        else if (m_rightOperandNode->getIsAncestorOfHumanNode())
        {
            const int64_t leftOperandValue = m_leftOperandNode->evaluate();
            const int64_t rightOperandExpectedValue = getRightOperandValueForExpectedResult(expectedValue, leftOperandValue);
            m_rightOperandNode->forceEvaluateTo(rightOperandExpectedValue);
        }
        else
        {
            throw std::runtime_error("Ambiguous evaluation: no human nodes");
        }
    }

    void setOperandNodes(MonkeyNodeSharedPtr leftOperandNode, MonkeyNodeSharedPtr rightOperandNode) override
    {
        m_leftOperandNode = std::move(leftOperandNode);
        m_rightOperandNode = std::move(rightOperandNode);
    }

    MonkeyNodeSharedPtr getLeftOperandNode() const override
    {
        return m_leftOperandNode;
    }

    MonkeyNodeSharedPtr getRightOperandNode() const override
    {
        return m_rightOperandNode;
    }

protected:
    MonkeyNodeSharedPtr m_leftOperandNode = nullptr;
    MonkeyNodeSharedPtr m_rightOperandNode = nullptr;
};

class AdditionNode : public TwoOperandNode
{
public:
    using TwoOperandNode::TwoOperandNode;

    int64_t getLeftOperandValueForExpectedResult(int64_t expectedValue, int64_t rightOperandValue) const override
    {
        return expectedValue - rightOperandValue;
    }

    int64_t getRightOperandValueForExpectedResult(int64_t expectedValue, int64_t leftOperandValue) const override
    {
        return expectedValue - leftOperandValue;
    }

    int64_t evaluate() const override
    {
        return m_leftOperandNode->evaluate() + m_rightOperandNode->evaluate();
    }
};

class SubtractionNode : public TwoOperandNode
{
public:
    using TwoOperandNode::TwoOperandNode;

    int64_t evaluate() const override
    {
        return m_leftOperandNode->evaluate() - m_rightOperandNode->evaluate();
    }

    int64_t getLeftOperandValueForExpectedResult(int64_t expectedValue, int64_t rightOperandValue) const override
    {
        return expectedValue + rightOperandValue;
    }

    int64_t getRightOperandValueForExpectedResult(int64_t expectedValue, int64_t leftOperandValue) const override
    {
        return leftOperandValue - expectedValue;
    }
};

class MultiplicationNode : public TwoOperandNode
{
public:
    using TwoOperandNode::TwoOperandNode;

    int64_t evaluate() const override
    {
        return m_leftOperandNode->evaluate() * m_rightOperandNode->evaluate();
    }

    int64_t getLeftOperandValueForExpectedResult(int64_t expectedValue, int64_t rightOperandValue) const override
    {
        return expectedValue / rightOperandValue;
    }

    int64_t getRightOperandValueForExpectedResult(int64_t expectedValue, int64_t leftOperandValue) const override
    {
        return expectedValue / leftOperandValue;
    }
};

class DivisionNode : public TwoOperandNode
{
public:
    using TwoOperandNode::TwoOperandNode;

    int64_t evaluate() const override
    {
        return m_leftOperandNode->evaluate() / m_rightOperandNode->evaluate();
    }

    int64_t getLeftOperandValueForExpectedResult(int64_t expectedValue, int64_t rightOperandValue) const override
    {
        return expectedValue * rightOperandValue;
    }

    int64_t getRightOperandValueForExpectedResult(int64_t expectedValue, int64_t leftOperandValue) const override
    {
        return leftOperandValue / expectedValue;
    }
};

class MonkeyParser
{
public:
    MonkeyParser(const std::vector<std::string>& monkeyLines);

    void parse();

    MonkeyNodeSharedPtr getRootNode() const;
    MonkeyNodeSharedPtr getHumanNode() const;

private:
    using Tokens = std::vector<std::string>;

    std::vector<Tokens> m_allMonkeyTokens;

    std::unordered_map<std::string, MonkeyNodeSharedPtr> m_monkeyNameToNode;

    void createAllNodes();
    void setAllChildrenNodes();
    void populateHumanPath();
    void createAndStoreNode(const Tokens& monkeyTokens);
    void setChildrenNodes(const Tokens& monkeyTokens);

    static MonkeyNodeSharedPtr createNode(const Tokens& monkeyTokens);
    static const std::string& getName(const Tokens& monkeyTokens);
    static bool isOperator(const Tokens& monkeyTokens);
};

}
}
}
