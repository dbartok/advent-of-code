#include "Day07-RecursiveCircus.h"

#include "WeightedTree.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <string>
#include <algorithm>
#include <unordered_set>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day07
{

std::string nameOfBottomProgram(const std::vector<NodeDescriptor>& nodeDescriptors)
{
    std::vector<std::string> allNodeNames;
    std::transform(nodeDescriptors.begin(), nodeDescriptors.end(), std::back_inserter(allNodeNames),
                   [](const NodeDescriptor& nd)
                   {
                       return nd.name;
                   });

    std::vector<std::string> allChildrenNames;
    std::for_each(nodeDescriptors.begin(), nodeDescriptors.end(), [&allChildrenNames](const NodeDescriptor& nd)
                  {
                      allChildrenNames.insert(allChildrenNames.end(), nd.childrenNames.begin(), nd.childrenNames.end());
                  });

    // Calculate set difference between allNodeNames and allChildrenNames
    // Because the elements are not already sorted, using unordered_set + find() is more effective than sorting and using std::set_difference
    std::unordered_set<std::string> allChildrenNamesSet(allChildrenNames.begin(), allChildrenNames.end());

    std::vector<std::string> nodesThatAreNotChildren;
    std::copy_if(allNodeNames.begin(), allNodeNames.end(), std::back_inserter(nodesThatAreNotChildren),
                 [&allChildrenNamesSet](const std::string& name)
                 {
                     return allChildrenNamesSet.find(name) == allChildrenNamesSet.end();
                 });

    if (nodesThatAreNotChildren.size() != 1)
    {
        throw std::runtime_error("There are either 0 or more than 1 bottom programs.");
    }

    return nodesThatAreNotChildren.front();
}

int correctWeightOfWrongWeight(const std::vector<NodeDescriptor>& nodeDescriptors)
{
    WeightedTree weightedTree = WeightedTree::fromNodeDescriptors(nodeDescriptors);
    return weightedTree.getCorrectWeightForSingleWrongWeight();
}

}
}
}
