#include "Day07-NoSpaceLeftOnDevice.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include "CppUnitTest.h"
__END_LIBRARIES_DISABLE_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CurrentDay = AdventOfCode::Year2022::Day07;

TEST_CLASS(Day07NoSpaceLeftOnDevice)
{
public:

    TEST_METHOD(totalSizeOfSmallDirectories_SimpleTests)
    {
        Assert::AreEqual(95437, CurrentDay::totalSizeOfSmallDirectories(m_lines));
    }

    TEST_METHOD(sizeOfSmallestDirectoryToDelete_SimpleTests)
    {
        Assert::AreEqual(24933642, CurrentDay::sizeOfSmallestDirectoryToDelete(m_lines));
    }

private:
    const std::vector<std::string> m_lines =
    {
        "$ cd /",
        "$ ls",
        "dir a",
        "14848514 b.txt",
        "8504156 c.dat",
        "dir d",
        "$ cd a",
        "$ ls",
        "dir e",
        "29116 f",
        "2557 g",
        "62596 h.lst",
        "$ cd e",
        "$ ls",
        "584 i",
        "$ cd ..",
        "$ cd ..",
        "$ cd d",
        "$ ls",
        "4060174 j",
        "8033020 d.log",
        "5626152 d.ext",
        "7214296 k"
    };
};
