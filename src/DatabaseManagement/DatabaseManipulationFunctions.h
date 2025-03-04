#pragma once
#include <vector>
#include <string>

class DatabaseManipulationFunctions{
public:
// Mid-Level functionality
static std::vector<std::string> ExtractArrayData(const std::string &data);
static std::vector<std::pair<std::string, std::string>> ExtractStructData(const std::string &data);
static std::vector<std::pair<std::string, std::string>> ExtractCategoryDataPairs(const std::string &data);

static std::vector<std::string> SplitCommaSeparatedVariables(const std::string &data);
static std::pair<std::string, std::string> SplitDataEntry(const std::string &entry);


// Low-level data manipulation functionality
static std::vector<std::string> SplitAndIndentEntries(const std::string &data, unsigned int baseIndentationDepth = 0);
static std::string ParseString(const std::string &data);
static bool ParseBool(const std::string &data);
static bool ParseInt(const std::string &data);
static bool ParseFloat(const std::string &data);

private:
static bool CheckMatchingBrackets(const std::string &str);
static bool ContainsArray(const std::string &str);
static bool ContainsStruct(const std::string &str);
};