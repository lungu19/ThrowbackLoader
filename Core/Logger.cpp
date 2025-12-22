#include "Core.h"
#include "Logger.h"
#include <Windows.h>

#ifdef _DEBUG
Logger& Logger::Instance()
{
    static Logger instance;
    return instance;
}

void Logger::print_level(LOG_LEVEL level) const
{
    switch (level)
    {
    case LOG_LEVEL::ERR:
        std::cout << "[ERROR]";
        return;
    case LOG_LEVEL::WARN:
        std::cout << "[WARNING]";
        return;
    case LOG_LEVEL::INFO:
        std::cout << "[INFO]";
        return;
    case LOG_LEVEL::NONE:
    default:
        return;
    }
}

void Logger::print_timestamp() const
{
    const auto time_point = std::chrono::system_clock::now();
    const auto formatted_timestamp = std::format(" [{:%Y-%m-%d %H:%M:%S}] ", time_point);
    std::cout << formatted_timestamp;
}
#endif

void create_console()
{
#ifdef _DEBUG
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    SetConsoleTitleA("ThrowbackLoader");
    SetLayeredWindowAttributes(GetConsoleWindow(), 0, 200, 2);
#endif
}

void free_console()
{
#ifdef _DEBUG
    fclose(stdout);
    FreeConsole();
#endif
}

bool handle_windows_calls(int reason)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        create_console();
        LOGGER_INFO("ThrowbackLoader version {}", Throwbackloader_GetVersion());
        return TRUE;
    }

    if (reason == DLL_PROCESS_DETACH)
    {
        free_console();
        return TRUE;
    }
    return FALSE;
}