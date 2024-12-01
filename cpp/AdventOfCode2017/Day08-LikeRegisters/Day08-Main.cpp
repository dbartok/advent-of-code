#include "Day08-LikeRegisters.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
__END_LIBRARIES_DISABLE_WARNINGS

int main()
{
    namespace CurrentDay = AdventOfCode::Year2017::Day08;

    std::fstream fileIn("input.txt");
    std::vector<CurrentDay::Instruction> inputInsructions;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        CurrentDay::Instruction inputInstruction = CurrentDay::Instruction::fromString(lineBuffer);
        inputInsructions.push_back(std::move(inputInstruction));
    }

    std::cout << "First part: " << CurrentDay::largestRegisterAfterCompletion(inputInsructions) << std::endl;
    std::cout << "Second part: " << CurrentDay::largestRegisterDuringExecution(inputInsructions) << std::endl;
}
