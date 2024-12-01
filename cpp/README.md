# Advent of Code: C++ solutions

This folder contains solutions to the Advent of Code puzzles between 2017 and 2023 in C++.

## Libraries

Some solutions use one or more of the following libraries:  
- [boost](http://www.boost.org/)  
- [eigen3](http://eigen.tuxfamily.org/)  

An easy way to install these locally is with [vcpkg](https://github.com/Microsoft/vcpkg):  
`vcpkg install <library name>:<platform>`  
e.g., `vcpkg install boost:x86-windows` or `vcpkg install eigen3:x64-windows`

## Visual Studio Project Template

In order to easily create a new VS project for each day's programming puzzle, you can use the project template from the "Visual Studio Project Template" folder. These projects can then be collected in a VS solution.

The template was most recently tested with Visual Studio 2022.

The template contains a set of placeholder files, and three configurations:
- The Debug and Release configurations are standard, and are used to run the application.
- The Test configuration is used for running the unit tests.

All three of these configurations are supported for both x86 and x64 platforms.

To use the template:
1. Go into the AdventOfCode folder and add the contents to a zip file called `AdventOfCode.zip`.
2. Move `AdventOfCode.zip` to the root VS ProjectTemplates directory, its default path is:
`C:\Users\<Your username>\Documents\Visual Studio <Your VS version>\Templates\ProjectTemplates`.
3. Create a new project from VS, using the new "AdventOfCode" template that is now available to select.
4. Copy the contents of the "Starting files" folder to the root of the newly created project.
5. At this point, you should be able to open the placeholder files in the newly created project from inside VS:
`DayXX-PuzzleName.h`, `DayXX-PuzzleName.cpp`, `DayXX-Main.cpp` and `test_DayXX-PuzzleName.cpp`
6. The Debug and Release configurations in the new project should build and run.
7. Both of the placeholder unit tests should be discovered and passing when the tests are run from VS in the Test configuration.
8. Make sure to rename the files in VS to correspond to the given day's puzzle.
9. Use the TODOs in the code as guidance on how to use the skeleton files.

## Visual Studio settings
In order to keep the coding style consistent, the Visual Studio C++ Text Editor settings used throughout the repository can be imported to Visual Studio from `Settings\TextEditorCPP.vssettings`.  
[Trailing Whitespace Visualizer](https://marketplace.visualstudio.com/items?itemName=MadsKristensen.TrailingWhitespaceVisualizer) is recommended with the "Remove on save" option enabled to make sure no trailing whitespaces are present in the files.

## Warnings & Code Analysis
All warnings are enabled (/Wall) along with extensive Code Analysis (Microsoft All Rules and also Core C++ Check).

## Ignoring warnings in libraries

The standard library and other libraries produce several externally unfixable warnings when compiled with /Wall. We are also not interested in the Code Analysis warning messages for libraries.
Unfortunately, there is currently no easy way in VS to disable warning messages for all external libraries.

Therefore, whenever a header from an external library is included, the include should be surrounded with disable warning directives to reduce the number of warnings.

There are some convenience macros available for this in `Common/DisableLibraryWarningsMacros.h`.  
For the includes surrounded by these macros, the following warnings will be disabled:  
- Externally unfixable warnings.
- All Code Analysis warnings originating from the Microsoft All Rules analysis.
- All Core C++ Check warnings.

Example usage:  

```cpp
#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/functional/hash/hash.hpp>
#include <boost/algorithm/string.hpp>

#include <vector>
#include <string>
END_LIBRARIES_DISABLE_WARNINGS
```
