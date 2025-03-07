#include "src/Services/ServiceLocator.h"

std::map<std::type_index, std::shared_ptr<IService>> ServiceLocator::services;
std::mutex ServiceLocator::mutex;