#include "Day03-GearRatios.h"

#include "SchematicAnalyzer.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2023
{
namespace Day03
{

int sumOfAllPartNumbers(const std::vector<std::string>& schematicLines)
{
    SchematicAnalyzer schematicAnalyzer = SchematicAnalyzer{schematicLines};

    return schematicAnalyzer.getSumOfAllPartNumbers();
}

int sumOfAllGearRatios(const std::vector<std::string>& schematicLines)
{
    SchematicAnalyzer schematicAnalyzer = SchematicAnalyzer{schematicLines};

    return schematicAnalyzer.getSumOfAllGearRatios();
}

}
}
}