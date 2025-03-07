#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <typeindex>
#include <type_traits>

#include "src/Services/IService.h"

class ServiceLocator
{
public:
	/// Registers a service with the service locator.
	/// @tparam T The service implementation type.
	/// @param service Shared pointer to the service instance.
	template <typename T>
	static void RegisterService(std::shared_ptr<T> service)
	{
		static_assert(std::is_base_of<IService, T>::value, "T must inherit from IService");
		std::lock_guard<std::mutex> lock(mutex);
		std::type_index typeIndex = service->getTypeIndex(); // Use base class type index
		if (services.contains(typeIndex))
		{
			throw std::runtime_error("Service already registered");
		}
		services[typeIndex] = service;
	}

	/// Unregisters a service from the service locator.
	/// @tparam T The base service type.
	template <typename T>
	static void UnregisterService()
	{
		std::lock_guard<std::mutex> lock(mutex);
		std::type_index typeIndex = std::type_index(typeid(T));
		if (!services.contains(typeIndex))
		{
			throw std::runtime_error("Service not registered");
		}
		services.erase(typeIndex);
	}

	/// Gets a service from the service locator.
	/// @tparam T The base service type.
	/// @return Shared pointer to the requested service instance.
	template <typename T>
	static std::shared_ptr<T> GetService()
	{
		std::lock_guard<std::mutex> lock(mutex);
		std::type_index typeIndex = std::type_index(typeid(T));
		auto it = services.find(typeIndex);
		if (it == services.end())
		{
			throw std::runtime_error("Service not found");
		}
		return std::static_pointer_cast<T>(it->second);
	}

	/// @brief Checks whether a service is regisered for the given interface
	/// @tparam T The base service type
	/// @return Returns true if a service is registered which uses the provided interface
	template <typename T>
	static bool IsServiceRegistered()
	{
		std::lock_guard<std::mutex> lock(mutex);
		std::type_index typeIndex = std::type_index(typeid(T));
		if (services.contains(typeIndex))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	static std::map<std::type_index, std::shared_ptr<IService>> services;
	static std::mutex mutex;
};