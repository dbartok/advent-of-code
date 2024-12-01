#pragma once

#include "Node.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2021
{
namespace Day18
{

class SnailfishNumberParser
{
public:
    SnailfishNumberParser(std::string snailfishNumberString);

    Node::SharedPtr createRootNode();

private:
    std::string m_snailfishNumberString;

    size_t m_index = 0;
    Node* m_prevCreatedNode = nullptr;

    char getNextChar();
    void chainWithPrevCreatedNode(Node* node);
};

}
}
}
