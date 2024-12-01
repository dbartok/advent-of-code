#include "TerminalOutputAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <numeric>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

int SMALL_DIRECTORY_SIZE_THRESOLD = 100'000;
int TOTAL_FILESYSTEM_SIZE = 70'000'000;
int FREE_SPACE_REQUIRED = 30'000'000;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day07
{

DirectoryNode::DirectoryNode(DirectoryNode* parent)
    : m_parent{parent}
{

}

std::vector<DirectoryNode*> DirectoryNode::getAllSubdirectoriesRecursively()
{
    std::vector<DirectoryNode*> subdirectoriesOutput;
    collectAllSubdirectoriesRecursively(subdirectoriesOutput);
    return subdirectoriesOutput;
}

DirectoryNode* DirectoryNode::subdirectoryAt(const std::string& subdirectoryName)
{
    return m_subdirectoryNameToSubdirectory.at(subdirectoryName).get();
}

void DirectoryNode::insertDirectory(const std::string& name)
{
    const auto parentNode = this;
    auto newDirectoryNode = std::make_shared<DirectoryNode>(parentNode);
    m_subdirectoryNameToSubdirectory.emplace(name, std::move(newDirectoryNode));
}

void DirectoryNode::insertFile(const std::string& _name, int size)
{
    m_fileSizes.push_back(size);
}

DirectoryNode* DirectoryNode::getParent() const
{
    return m_parent;
}

int DirectoryNode::getTotalSize() const
{
    const int totalSizeOfFiles = std::accumulate(m_fileSizes.cbegin(), m_fileSizes.cend(), 0);
    const int totalSizeOfDirectories = std::accumulate(m_subdirectoryNameToSubdirectory.cbegin(), m_subdirectoryNameToSubdirectory.cend(), 0, [](int acc, const auto& subdirectoryNameAndSubdirectory)
                                                        {
                                                            return acc + subdirectoryNameAndSubdirectory.second->getTotalSize();
                                                        });

    return totalSizeOfFiles + totalSizeOfDirectories;
}

void DirectoryNode::collectAllSubdirectoriesRecursively(std::vector<DirectoryNode*>& subdirectoriesOutput)
{
    subdirectoriesOutput.push_back(this);

    for (const auto& subdirectoryNameAndSubdirectory : m_subdirectoryNameToSubdirectory)
    {
        subdirectoryNameAndSubdirectory.second->collectAllSubdirectoriesRecursively(subdirectoriesOutput);
    }
}


TerminalOutputAnalyzer::TerminalOutputAnalyzer(std::vector<std::string> terminalOutputLines)
    : m_terminalOutputLines{std::move(terminalOutputLines)}
    , m_rootDirectoryNode{std::make_shared<DirectoryNode>()}
    , m_currentDirectoryNode{nullptr}
{

}

void TerminalOutputAnalyzer::reconstructFilesystem()
{
    for (const auto& outputLine : m_terminalOutputLines)
    {
        processOutputLine(outputLine);
    }
}

int TerminalOutputAnalyzer::getTotalSizeOfSmallDirectories() const
{
    std::vector<DirectoryNode*> allDirectories = m_rootDirectoryNode->getAllSubdirectoriesRecursively();

    return std::accumulate(allDirectories.cbegin(), allDirectories.cend(), 0, [](int acc, const auto directoryNodePtr)
                            {
                                const int totalSize = directoryNodePtr->getTotalSize();
                                if (totalSize <= SMALL_DIRECTORY_SIZE_THRESOLD)
                                {
                                    return acc + totalSize;
                                }

                                return acc;
                            });
}

int TerminalOutputAnalyzer::getSizeOfSmallestDirectoryToDelete() const
{
    const int rootDirectorySize = m_rootDirectoryNode->getTotalSize();
    const int currentFreeSpace = TOTAL_FILESYSTEM_SIZE - rootDirectorySize;
    const int minDirectorySizeToDelete = FREE_SPACE_REQUIRED - currentFreeSpace;

    std::vector<int> directorySizes = getAllDirectorySizes();

    std::sort(directorySizes.begin(), directorySizes.end());

    return *std::find_if(directorySizes.cbegin(), directorySizes.cend(), [minDirectorySizeToDelete](int directorySize)
                            {
                                return directorySize > minDirectorySizeToDelete;
                            });
}

void TerminalOutputAnalyzer::processOutputLine(const std::string& outputLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, outputLine, boost::is_any_of(" "));

    if (tokens.at(0) == "$")
    {
        if (tokens.at(1) == "cd")
        {
            processDirectoryChange(tokens.at(2));
        }
    }
    else
    {
        processItemInCurrentDirectory(tokens.at(0), tokens.at(1));
    }
}

void TerminalOutputAnalyzer::processDirectoryChange(const std::string& directoryName)
{
    if (directoryName == "/")
    {
        m_currentDirectoryNode = m_rootDirectoryNode.get();
    }
    else if (directoryName == "..")
    {
        m_currentDirectoryNode = m_currentDirectoryNode->getParent();
    }
    else
    {
        m_currentDirectoryNode = m_currentDirectoryNode->subdirectoryAt(directoryName);
    }
}

void TerminalOutputAnalyzer::processItemInCurrentDirectory(const std::string& metadata, const std::string& name)
{
    if (metadata == "dir")
    {
        m_currentDirectoryNode->insertDirectory(name);
    }
    else
    {
        const int size = std::stoi(metadata);
        m_currentDirectoryNode->insertFile(name, size);
    }
}

std::vector<int> TerminalOutputAnalyzer::getAllDirectorySizes() const
{
    std::vector<DirectoryNode*> allDirectories = m_rootDirectoryNode->getAllSubdirectoriesRecursively();

    std::vector<int> allDirectorySizes;
    std::transform(allDirectories.cbegin(), allDirectories.cend(), std::back_inserter(allDirectorySizes), [](const auto& directory)
                    {
                        return directory->getTotalSize();
                    });

    return allDirectorySizes;
}

}
}
}
