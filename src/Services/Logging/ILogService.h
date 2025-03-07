#pragma once
#include <string>
#include "src/Services/IService.h"

class ILogService : public IService
{
public:
	virtual ~ILogService() = default;

	/// @brief Output the desired message to the console
	/// @param msg String to be output
	virtual void Log(std::string msg) = 0;

	/// @brief Output the desired message to the console with a highlighted warning
	/// @param msg String to be output
	virtual void LogWarning(std::string msg) = 0;

	/// @brief Output the desired message to the console to denote a major error has occurred
	/// @param msg String to be output
	virtual void LogError(std::string msg) = 0;

	/// Returns the type index of the base interface.
	std::type_index getTypeIndex() const override
	{
		return std::type_index(typeid(ILogService));
	}
};