#pragma once

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <Eigen/Core>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2017
{
namespace Day21
{

using DynamicBoolMatrix = Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>;

}
}
}
