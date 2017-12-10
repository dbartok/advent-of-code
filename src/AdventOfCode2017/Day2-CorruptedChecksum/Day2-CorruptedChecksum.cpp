#include "Day2-CorruptedChecksum.h"
#include "../../Common/Utils.h"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

namespace AdventOfCode
{

unsigned checkSumDiffSmallestLargest(const RowsOfNumbers& rows)
{
    unsigned checkSum = 0;

    for (const auto& row : rows)
    {
        if (row.empty())
        {
            continue;
        }

        unsigned maxElement = *std::max_element(row.begin(), row.end());
        unsigned minElement = *std::min_element(row.begin(), row.end());
        checkSum += (maxElement - minElement);
    }

    return checkSum;
}

unsigned sumEvenlyDivisbleValues(const RowsOfNumbers& rows)
{
    unsigned sum = 0;

    for (const auto& row : rows)
    {
        for (size_t i = 0; i < row.size(); i++)
        {
            for (size_t j = i + 1; j < row.size(); j++)
            {
                unsigned dividend = std::max(row[i], row[j]);
                unsigned divisor = std::min(row[i], row[j]);

                if (dividend % divisor == 0)
                {
                    sum += dividend / divisor;
                    break;
                }
            }
        }
    }

    return sum;
}

}


int main()
{
    namespace AoC = AdventOfCode;

    std::fstream fileIn("input.txt");
    AoC::RowsOfNumbers inputRows;

    std::string lineBuffer;
    while (std::getline(fileIn, lineBuffer))
    {
        AoC::RowOfNumbers row;
        AoC::Utils::splitStringIntoTypedVector(lineBuffer, row);
        inputRows.push_back(std::move(row));
    }

    std::cout << "First part: " << AoC::checkSumDiffSmallestLargest(inputRows) << std::endl;
    std::cout << "Second part: " << AoC::sumEvenlyDivisbleValues(inputRows) << std::endl;
}
