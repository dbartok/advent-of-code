#include "Day07-RecursiveCircus.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2017::Day07;

TEST_CLASS(Day07RecursiveCircus)
{
public:

    TEST_METHOD(nameOfBottomProgram_SimpleTests)
    {
        Assert::AreEqual(std::string("tknk"), CurrentDay::nameOfBottomProgram(m_nodeDescriptors));
    }

    TEST_METHOD(correctWeightOfWrongWeightProgram_SimpleTests)
    {
        Assert::AreEqual(60, CurrentDay::correctWeightOfWrongWeight(m_nodeDescriptors));
    }

private:
    std::vector<CurrentDay::NodeDescriptor> m_nodeDescriptors =
    {
        {"pbga", 66, {}},
        {"xhth", 57, {}},
        {"ebii", 61, {}},
        {"havc", 66, {}},
        {"ktlj", 57, {}},
        {"fwft", 72, {"ktlj", "cntj", "xhth"}},
        {"qoyq", 66, {}},
        {"padx", 45, {"pbga", "havc", "qoyq"}},
        {"tknk", 41, {"ugml", "padx", "fwft"}},
        {"jptl", 61, {}},
        {"ugml", 68, {"gyxo", "ebii", "jptl"}},
        {"gyxo", 61, {}},
        {"cntj", 57, {}}
    };

};
