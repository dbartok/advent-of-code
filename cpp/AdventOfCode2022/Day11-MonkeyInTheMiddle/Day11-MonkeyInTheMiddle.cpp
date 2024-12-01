#include "Day11-MonkeyInTheMiddle.h"

#include "MonkeyGroupSimulator.h"

#include <AdventOfCodeCommon/Utils.h>

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

const int WORRY_LEVEL_DIVISOR_FIRST_PART = 3;
const int WORRY_LEVEL_DIVISOR_SECOND_PART = 1;
const unsigned NUM_ROUNDS_TO_SIMULATE_FIRST_PART = 20;
const unsigned NUM_ROUNDS_TO_SIMULATE_SECOND_PART = 10'000;

}

namespace AdventOfCode
{
namespace Year2022
{
namespace Day11
{

using MonkeyDescriptionTextSection = std::vector<std::string>;

std::vector<int> parseStartingItemsLine(const std::string& startingItemsLine)
{
    const std::regex startingItemsLineRegex(R"(\s+Starting items: ([0-9,\s]+))");
    std::smatch startingItemsLineMatch;

    std::regex_match(startingItemsLine, startingItemsLineMatch, startingItemsLineRegex);

    const std::string startingItemsString = startingItemsLineMatch[1];

    std::vector<int> startingItems;
    Utils::splitStringIntoTypedVector(startingItemsString, startingItems, ',');

    return startingItems;
}

Operation::SharedPtr parseOperationLine(const std::string& operationLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, operationLine, boost::is_any_of(" "));

    const std::string operatorString = *(tokens.cend() - 2);
    const std::string secondOperandString = *(tokens.cend() - 1);

    if (secondOperandString == "old")
    {
        return std::make_shared<Square>();
    }

    const int secondOperand = std::stoi(secondOperandString);

    if (operatorString == "+")
    {
        return std::make_shared<Addition>(secondOperand);
    }
    else
    {
        return std::make_shared<Multiplication>(secondOperand);
    }
}

int parseTestModulusLine(const std::string& testModulusLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, testModulusLine, boost::is_any_of(" "));

    return std::stoi(tokens.back());
}

unsigned parseTestTargetLine(const std::string& testTargetLine)
{
    std::vector<std::string> tokens;
    boost::split(tokens, testTargetLine, boost::is_any_of(" "));

    return boost::lexical_cast<unsigned>(tokens.back());
}

Monkey parseMonkeyDescriptionTextSection(const MonkeyDescriptionTextSection& monkeyDescriptionTextSection)
{
    std::vector<int> startingItems = parseStartingItemsLine(monkeyDescriptionTextSection.at(1));
    Operation::SharedPtr operation = parseOperationLine(monkeyDescriptionTextSection.at(2));
    const int testModulus = parseTestModulusLine(monkeyDescriptionTextSection.at(3));
    const unsigned testTrueTarget = parseTestTargetLine(monkeyDescriptionTextSection.at(4));
    const unsigned testFalseTarget = parseTestTargetLine(monkeyDescriptionTextSection.at(5));

    return Monkey{std::move(startingItems), std::move(operation), testModulus, testTrueTarget, testFalseTarget};
}

std::vector<Monkey> parseMonkeyDescriptionLines(const std::vector<std::string>& monkeyDescriptionLines)
{
    std::vector<MonkeyDescriptionTextSection> monkeyDescriptionTextSections;
    boost::split(monkeyDescriptionTextSections, monkeyDescriptionLines, [](const auto& elem) {return elem.empty(); });

    std::vector<Monkey> monkeys;

    for (const auto& monkeyDescriptionTextSection : monkeyDescriptionTextSections)
    {
        Monkey monkey = parseMonkeyDescriptionTextSection(monkeyDescriptionTextSection);
        monkeys.push_back(std::move(monkey));
    }

    return monkeys;
}

int64_t levelOfMonkeyBusiness(const std::vector<std::string>& monkeyDescriptionLines)
{
    std::vector<Monkey> monkeys = parseMonkeyDescriptionLines(monkeyDescriptionLines);

    MonkeyGroupSimulator monkeyGroupSimulator{monkeys, WORRY_LEVEL_DIVISOR_FIRST_PART};

    monkeyGroupSimulator.simulate(NUM_ROUNDS_TO_SIMULATE_FIRST_PART);

    return monkeyGroupSimulator.getLevelOfMonkeyBusiness();
}

int64_t levelOfMonkeyBusinessWithRidiculousWorryLevels(const std::vector<std::string>& monkeyDescriptionLines)
{
    std::vector<Monkey> monkeys = parseMonkeyDescriptionLines(monkeyDescriptionLines);

    MonkeyGroupSimulator monkeyGroupSimulator{monkeys, WORRY_LEVEL_DIVISOR_SECOND_PART};

    monkeyGroupSimulator.simulate(NUM_ROUNDS_TO_SIMULATE_SECOND_PART);

    return monkeyGroupSimulator.getLevelOfMonkeyBusiness();
}

}
}
}