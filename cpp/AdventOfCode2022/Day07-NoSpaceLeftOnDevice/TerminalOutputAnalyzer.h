#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <memory>
#include <unordered_map>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2022
{
namespace Day07
{

class DirectoryNode
{
public:
    using SharedPtr = std::shared_ptr<DirectoryNode>;

    DirectoryNode(DirectoryNode* parent = nullptr);

    std::vector<DirectoryNode*> getAllSubdirectoriesRecursively();
    DirectoryNode* subdirectoryAt(const std::string& subdirectoryName);
    void insertDirectory(const std::string& name);
    void insertFile(const std::string& _name, int size);

    DirectoryNode* getParent() const;
    int getTotalSize() const;

private:
    DirectoryNode* m_parent;
    std::unordered_map<std::string, DirectoryNode::SharedPtr> m_subdirectoryNameToSubdirectory;
    std::vector<int> m_fileSizes;

    void collectAllSubdirectoriesRecursively(std::vector<DirectoryNode*>& subdirectoriesOutput);
};


class TerminalOutputAnalyzer
{
public:
    TerminalOutputAnalyzer(std::vector<std::string> terminalOutputLines);

    void reconstructFilesystem();

    int getTotalSizeOfSmallDirectories() const;
    int getSizeOfSmallestDirectoryToDelete() const;

private:
    std::vector<std::string> m_terminalOutputLines;

    DirectoryNode::SharedPtr m_rootDirectoryNode;
    DirectoryNode* m_currentDirectoryNode;

    void processOutputLine(const std::string& outputLine);
    void processDirectoryChange(const std::string& directoryName);
    void processItemInCurrentDirectory(const std::string& metadata, const std::string& name);

    std::vector<int> getAllDirectorySizes() const;
};

}
}
}
