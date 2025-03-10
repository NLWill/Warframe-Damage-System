#include "src/DatabaseManagement/DatabaseRetrievalFunctions.h"
#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"
#include <fstream>
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"

#define DEBUG_DATABASE_RETRIEVAL_FUNCTIONS true

std::string DatabaseRetrievalFunctions::GetModData(std::string modName)
{
	std::string filePath = FindFilePath(modName, SearchType::Mod);
	return GetDataFromDatabase(filePath);
}

std::string DatabaseRetrievalFunctions::GetWeaponData(std::string weaponName)
{
	std::string filePath = FindFilePath(weaponName, SearchType::Weapon);
	return GetDataFromDatabase(filePath);
}

std::string DatabaseRetrievalFunctions::GetTargetData(std::string targetName)
{
	std::string filePath = FindFilePath(targetName, SearchType::Target);
	return GetDataFromDatabase(filePath);
}

std::string DatabaseRetrievalFunctions::FindFilePath(std::string name, SearchType searchType)
{
	std::string filePathListToSearch;
	switch (searchType)
	{
	case SearchType::Mod:
		filePathListToSearch = "data/Mod File Paths.txt";
		break;
	case SearchType::Weapon:
		filePathListToSearch = "data/Weapon File Paths.txt";
		break;
	case SearchType::Target:
		filePathListToSearch = "data/Target File Paths.txt";
		break;
	default:
		std::__throw_invalid_argument("Unhandled search type in FindFilePath");
		break;
	}

#if DEBUG_DATABASE_RETRIEVAL_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Consulting the file path list " + filePathListToSearch);
#endif
	std::ifstream inputStream(filePathListToSearch);

	if (!inputStream)
	{
		ServiceLocator::GetService<ILogService>()->LogError("Failed to open file path list");
		std::string errorMsg = "Unable to open file path " + filePathListToSearch;
		std::__throw_invalid_argument(errorMsg.c_str());
	}

	// Iterate over the entries in the file path list until the name of the entry matches the name of the desired item
	std::string line;
	while (std::getline(inputStream, line))
	{
		auto itemNamePathPair = DatabaseManipulationFunctions::SplitDataEntry(line);
		auto itemName = DatabaseManipulationFunctions::ParseString(itemNamePathPair.first);
		if (itemName == name)
		{
#if DEBUG_DATABASE_RETRIEVAL_FUNCTIONS
			ServiceLocator::GetService<ILogService>()->Log("Found the corresponding file path");
#endif
			// All the file paths are taken from the original game, but the files are all contained within the data/ folder, so prepend this to the file path
			// Also append .txt as file extension as this is how they are stored currently
			return "data" + DatabaseManipulationFunctions::ParseString(itemNamePathPair.second) + ".txt";
		}
	}
	std::string errorMsg = "Failed to find path to " + name + " in file path list";
	std::__throw_invalid_argument(errorMsg.c_str());
}

std::string DatabaseRetrievalFunctions::GetDataFromDatabase(std::string filePath)
{
#if DEBUG_DATABASE_RETRIEVAL_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("File path = " + filePath);
#endif

	// Open the provided file path and save all data into a string
	std::ifstream inputStream(filePath);

	if (!inputStream)
	{
		ServiceLocator::GetService<ILogService>()->LogError("Failed to open file path: " + filePath);
		std::string errorMsg = "Unable to open file path " + filePath;
		std::__throw_invalid_argument(errorMsg.c_str());
	}

	std::string databaseData;
	std::string line;
	while (std::getline(inputStream, line))
	{
		databaseData += line;
	}

#if DEBUG_DATABASE_RETRIEVAL_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Obtained database data");
	ServiceLocator::GetService<ILogService>()->Log(databaseData);
#endif

	return databaseData;
}
