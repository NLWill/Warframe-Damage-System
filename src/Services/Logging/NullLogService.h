#include "src/Services/Logging/LoggerServiceBase.h"

class NullLogger : public Logger{
	public:
	NullLogger() {}
	~NullLogger() {}
	virtual void Log(string msg) {}
	virtual void LogWarning(string msg) {}
	virtual void LogError(string msg) {}
};