#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"
#include <stack>
#include <sstream>
#include "src/Services/ServiceLocator.h"
#include "DatabaseManipulationFunctions.h"

/// @brief Convert database string format into a vector of strings
/// @return 
std::vector<std::string> DatabaseManipulationFunctions::ExtractArrayData(const std::string &data)
{
	if (!ContainsArray(data)){
		ServiceLocator::GetLogger().LogError("Data fed to ExtractArrayData is not wrapped by []");
		return {};
	}

	// Remove the [] around the array data and split by commas.
	std::vector<std::string> items = SplitCommaSeparatedVariables(data.substr(1, data.size() - 2));
	
	return items;
}

/// @brief Extract pairs of category labels and associated data strings from a {} wrapped string representation of a struct
/// @return 
std::vector<std::pair<std::string, std::string>> DatabaseManipulationFunctions::ExtractStructData(const std::string &data)
{
	if (!ContainsStruct(data)){
		ServiceLocator::GetLogger().LogError("Data fed to ExtractStructData is not wrapped by {}");
		return {};
	}
	// Remove the {} around the struct data
	return ExtractCategoryDataPairs(data.substr(1, data.length() -2));
}

std::vector<std::pair<std::string, std::string>> DatabaseManipulationFunctions::ExtractCategoryDataPairs(const std::string &data)
{
	auto lines = SplitCommaSeparatedVariables(data);

	std::vector<std::pair<std::string, std::string>> categoryDataList;

	for (std::string line : lines){
		categoryDataList.push_back(SplitDataEntry(line));
	}

	return categoryDataList;
}

/// @brief Separate a set of comma-separated data entries into strings of Category:Data
/// @return 
std::vector<std::string> DatabaseManipulationFunctions::SplitCommaSeparatedVariables(const std::string &data)
{
	std::vector<std::string> entries;

	std::string entry;
	std::stringstream ss(data);
	std::stack<char> depthTracker;

	if (!CheckMatchingBrackets(data))
	{
		ServiceLocator::GetLogger().LogError("Invalid data passed to SplitCommaSeparatedVariables: mismatching brackets in input data!");
		return {data};
	}

	while (ss)
	{
		bool completeDataEntry = false;
		while (!completeDataEntry)
		{
			std::string nextPartOfEntry;
			getline(ss, nextPartOfEntry, ',');
			entry += nextPartOfEntry;

			// ServiceLocator::GetLogger().Log("-----------");
			// ServiceLocator::GetLogger().Log(nextPartOfEntry);

			// Check if the next part of the entry is a complete section
			// If the entry contains mismatched { or [ or (, this will imply that the next line is also required. Repeat until all brackets have been matched
			for (char c : nextPartOfEntry)
			{

				switch (c)
				{
				case '[':
				case '(':
				case '{':
					depthTracker.push(c);
					break;
				case ']':
				case ')':
				case '}':
					if (depthTracker.size() == 0)
					{
						ServiceLocator::GetLogger().LogError("Error parsing data, mismatched brackets, depthTracker size = 0");
						return entries;
					}
					if (depthTracker.top() == '[' && c == ']')
					{
						depthTracker.pop();
					}
					else if (depthTracker.top() == '(' && c == ')')
					{
						depthTracker.pop();
					}
					else if (depthTracker.top() == '{' && c == '}')
					{
						depthTracker.pop();
					}
					else
					{
						ServiceLocator::GetLogger().LogError("Error parsing data, mismatched brackets");
						return entries;
					}
					break;
				default:
					break;
				}
			}

			if (depthTracker.size() == 0 || !ss)
			{
				completeDataEntry = true;
			}
			else
			{
				// if this is not a complete data entry, return the comma back as it will be required for processing later down the line
				// ServiceLocator::GetLogger().Log("Current State of depthTracker");
				// ServiceLocator::GetLogger().Log(std::to_string(depthTracker.size()));
				entry += ',';
			}
		}

		if (entry != "")
		{
			entries.push_back(entry);
			entry = "";
		}
	}

	if (depthTracker.size() > 0)
	{
		// Implies that there were mismatched brackets spanning over the whole string
		ServiceLocator::GetLogger().LogError("Error parsing data, mismatched brackets");
	}

	return entries;
}

/// @brief Split a category:data string and return a pair of form {category, data} 
/// @return 
std::pair<std::string, std::string> DatabaseManipulationFunctions::SplitDataEntry(const std::string &entry)
{
	std::string category, data;

	// The category and data are separated by the first colon that is not inside any quotation marks
	std::stack<char> depthTracker;

	for (int i = 0; i < entry.size(); i++)
	{
		char c = entry[i];
		switch (c)
		{
		case '"':
			if (depthTracker.size() > 0 && depthTracker.top() == '"')
			{
				depthTracker.pop();
			}
			else
			{
				depthTracker.push(c);
			}
			break;
		case ':':
			if (depthTracker.size() > 0)
			{
				continue;
			}
			else
			{
				// This is the correct colon and i = colon location
				category = entry.substr(0, i);
				data = entry.substr(i + 1);
				break;
			}
		default:
			break;
		}

		// Stop iterating over the entry once the colon has been found, otherwise the result may be overwritten by a colon later in the entry
		if (category != "")
		{
			break;
		}
	}

	return {category, data};
}

std::vector<std::string> DatabaseManipulationFunctions::SplitAndIndentEntries(const std::string &data, int baseIndentationDepth)
{
	if (!CheckMatchingBrackets(data)){
		return {};
	}

	auto lines = SplitCommaSeparatedVariables(data);
	int currentDepth = baseIndentationDepth;

	for (int h = 0; h < lines.size(); h++){
		std::string tabs = "";
		for (int i = 0; i < currentDepth; i++)
		{
			tabs += "    ";
		}
		
		lines[h] = tabs + lines[h];
		for (char c : lines[h]){
			if (c == '{'){
				currentDepth++;
			}
			else if (c == '}'){
				currentDepth--;
			}
		}
	}

	return lines;
}

std::string DatabaseManipulationFunctions::ParseString(const std::string &data)
{
	if (data.at(0) != '"' || data.at(data.size() - 1) != '"'){
		ServiceLocator::GetLogger().LogError("Data fed to ParseString is not in quotation marks");
		return data;
	}
	return data.substr(1, data.size() - 2);
}

bool DatabaseManipulationFunctions::ParseBool(const std::string &data)
{
	if (data == "1" || data == "True"){
		return true;
	}
	else if (data == "0" || data == "False"){
		return false;
	}
	else {
		ServiceLocator::GetLogger().LogError("Error parsing bool from input data: " + data);
	}
	return false;
}

bool DatabaseManipulationFunctions::ParseInt(const std::string &data)
{
	return std::stoi(data);
}

bool DatabaseManipulationFunctions::ParseFloat(const std::string &data)
{
	return std::stof(data);
}

bool DatabaseManipulationFunctions::CheckMatchingBrackets(const std::string &str)
{
	std::stack<char> depthTracker;

	for (char c : str)
	{
		switch (c)
		{
		case '[':
		case '(':
		case '{':
			depthTracker.push(c);
			break;
		case ']':
		case ')':
		case '}':
			if (depthTracker.size() == 0)
			{
				ServiceLocator::GetLogger().LogError("Error parsing data, mismatched brackets, depthTracker size = 0: excess character \'" + c + std::to_string('\''));
				return false;
			}

			if (depthTracker.top() == '[' && c == ']')
			{
				depthTracker.pop();
			}
			else if (depthTracker.top() == '(' && c == ')')
			{
				depthTracker.pop();
			}
			else if (depthTracker.top() == '{' && c == '}')
			{
				depthTracker.pop();
			}
			else
			{
				ServiceLocator::GetLogger().LogError("Error parsing data, mismatched brackets");
				return false;
			}
			break;
		default:
			break;
		}
	}

	if (depthTracker.size() > 0)
	{
		// Implies that there were mismatched brackets spanning over the whole string
		ServiceLocator::GetLogger().LogError("Error parsing data, mismatched brackets");
		return false;
	}

	return true;
}

bool DatabaseManipulationFunctions::ContainsArray(const std::string &str)
{
	if (str.at(0) == '[' && str.at(str.length() -1) == ']'){
		return true;
	}
	else return false;
}

bool DatabaseManipulationFunctions::ContainsStruct(const std::string &str)
{
	if (str.at(0) == '{' && str.at(str.length() -1) == '}'){
		return true;
	}
	else return false;
}
