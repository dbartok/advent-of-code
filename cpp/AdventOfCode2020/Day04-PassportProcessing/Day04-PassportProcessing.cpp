#include "Day04-PassportProcessing.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <boost/algorithm/string.hpp>

#include <unordered_map>
#include <array>
#include <regex>
__END_LIBRARIES_DISABLE_WARNINGS

namespace AdventOfCode
{
namespace Year2020
{
namespace Day04
{

using PassportData = std::unordered_map<std::string, std::string>;

const std::array<std::string, 7> REQUIRED_FIELDS =
{
    "byr",
    "iyr",
    "eyr",
    "hgt",
    "hcl",
    "ecl",
    "pid",
};

bool isValidPassportData(const PassportData& passportData)
{
    for (const auto& requiredField : REQUIRED_FIELDS)
    {
        if (passportData.find(requiredField) == passportData.cend())
        {
            return false;
        }
    }

    return true;
}

bool isAllDigits(const std::string& value)
{
    return std::all_of(value.cbegin(), value.cend(), [](char c) {return std::isdigit(c); });
}

bool isNumberBetween(const std::string& value, int lowerBound, int upperBound)
{
    if (!isAllDigits(value))
    {
        return false;
    }

    int valueInt = std::stoi(value);
    return valueInt >= lowerBound && valueInt <= upperBound;
}

bool isYearBetween(const std::string& value, int lowerBound, int upperBound)
{
    if (value.size() != 4)
    {
        return false;
    }

    return isNumberBetween(value, lowerBound, upperBound);
}

bool isValidBirthYear(const std::string& value)
{
    return isYearBetween(value, 1920, 2002);
}

bool isValidIssueYear(const std::string& value)
{
    return isYearBetween(value, 2010, 2020);
}

bool isValidExpirationYear(const std::string& value)
{
    return isYearBetween(value, 2020, 2030);
}

bool isValidHeight(const std::string& value)
{
    if (value.size() < 3)
    {
        return false;
    }

    std::string unit = value.substr(value.size() - 2);
    std::string scalar = value.substr(0, value.size() - 2);
    if (unit == "cm")
    {
        return isNumberBetween(scalar, 150, 193);
    }
    else if (unit == "in")
    {
        return isNumberBetween(scalar, 59, 76);
    }
    else
    {
        return false;
    }
}

bool isValidHairColor(const std::string& value)
{
    const std::regex hexColorRegex("#[a-f0-9]{6}");
    return std::regex_match(value, hexColorRegex);
}

bool isValidEyeColor(const std::string& value)
{
    const std::regex eyeColorRegex("(amb|blu|brn|gry|grn|hzl|oth)");
    return std::regex_match(value, eyeColorRegex);
}

bool isValidPassportID(const std::string& value)
{
    const std::regex passportIDRegex("[0-9]{9}");
    return std::regex_match(value, passportIDRegex);
}

bool isValidKeyValuePair(const std::pair<std::string, std::string>& keyValuePair)
{
    const std::string& key = keyValuePair.first;
    const std::string& value = keyValuePair.second;

    if (key == "byr")
    {
        return isValidBirthYear(value);
    }
    if (key == "iyr")
    {
        return isValidIssueYear(value);
    }
    if (key == "eyr")
    {
        return isValidExpirationYear(value);
    }
    if (key == "hgt")
    {
        return isValidHeight(value);
    }
    if (key == "hcl")
    {
        return isValidHairColor(value);
    }
    if (key == "ecl")
    {
        return isValidEyeColor(value);
    }
    if (key == "pid")
    {
        return isValidPassportID(value);
    }
    if (key == "cid")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isValidPassportDataStrict(const PassportData& passportData)
{
    if (!isValidPassportData(passportData))
    {
        return false;
    }

    for (const auto& keyValuePair : passportData)
    {
        if (!isValidKeyValuePair(keyValuePair))
        {
            return false;
        }
    }

    return true;
}


std::vector<std::string> transformBatchFileLinesToSingleLines(const std::vector<std::string>& batchFileLines)
{
    std::vector<std::string> singleLines;
    std::vector<std::string> currentLineParts;
    for (const auto& batchFileLine : batchFileLines)
    {
        if (batchFileLine == "")
        {
            singleLines.push_back(boost::algorithm::join(currentLineParts, " "));
            currentLineParts = {};
            continue;
        }

        currentLineParts.push_back(batchFileLine);
    }

    singleLines.push_back(boost::algorithm::join(currentLineParts, " "));

    return singleLines;
}

PassportData parsePassportData(const std::string& singleLine)
{
    PassportData passportData;

    std::vector<std::string> keyValuePairs;
    boost::split(keyValuePairs, singleLine, boost::is_any_of(" "));

    for (const auto& keyValuePair : keyValuePairs)
    {
        std::vector<std::string> keyValuePairTokens;
        boost::split(keyValuePairTokens, keyValuePair, boost::is_any_of(":"));

        passportData.emplace(std::move(keyValuePairTokens.at(0)), std::move(keyValuePairTokens.at(1)));
    }

    return passportData;
}

std::vector<PassportData> parseAllPassportData(const std::vector<std::string>& batchFileLines)
{
    std::vector<PassportData> allPassportData;
    std::vector<std::string> singleLines = transformBatchFileLinesToSingleLines(batchFileLines);

    for (const auto& singleLine : singleLines)
    {
        PassportData passportData = parsePassportData(singleLine);
        allPassportData.push_back(std::move(passportData));
    }

    return allPassportData;
}

int numValidPassports(const std::vector<std::string>& batchFileLines)
{
    std::vector<PassportData> allPassportData = parseAllPassportData(batchFileLines);
    return std::count_if(allPassportData.cbegin(), allPassportData.cend(), [](const auto& passportData)
                         {
                             return isValidPassportData(passportData);
                         });
}

int numValidPassportsStrict(const std::vector<std::string>& batchFileLines)
{
    std::vector<PassportData> allPassportData = parseAllPassportData(batchFileLines);
    return std::count_if(allPassportData.cbegin(), allPassportData.cend(), [](const auto& passportData)
                         {
                             return isValidPassportDataStrict(passportData);
                         });
}

}
}
}
