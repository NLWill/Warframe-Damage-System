#pragma once
#include <typeindex>

/// Base class for all services.
class IService
{
public:
	virtual ~IService() = default;

	/// Virtual function to get the base type index of the service.
	/// Should be overridden in each service interface to return the typeid
	/// of the base interface.
	virtual std::type_index getTypeIndex() const = 0;
};