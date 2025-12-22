#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#ifdef _DEBUG

#include <chrono>
#include <format>
#include <iostream>

class Logger
{
    enum class LOG_LEVEL
    {
        NONE = -1,
        INFO,
        WARN,
        ERR
    };

  public:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    static Logger& Instance();
    void print_level(LOG_LEVEL level) const;
    void print_timestamp() const;

    template <typename Fmt, typename... Args> void print_formatted_message(Fmt&& fmt, Args&&... args) const
    {
        const auto formatted_message = std::format(fmt, std::forward<Args>(args)...);
        std::cout << formatted_message << "\n";
    }

    template <typename Fmt, typename... Args> void log(LOG_LEVEL level, Fmt&& fmt, Args&&... args) const
    {
        print_level(level);
        print_timestamp();

        if constexpr (sizeof...(Args) == 0)
        {
            std::cout << fmt.get() << "\n";
            return;
        }

        print_formatted_message(fmt, std::forward<Args>(args)...);
    }

  public:
    template <typename... Args> void info(std::format_string<Args...> fmt, Args&&... args) const
    {
        log(LOG_LEVEL::INFO, std::forward<decltype(fmt)>(fmt), std::forward<Args>(args)...);
    }

    template <typename... Args> void warn(std::format_string<Args...> fmt, Args&&... args) const
    {
        log(LOG_LEVEL::WARN, std::forward<decltype(fmt)>(fmt), std::forward<Args>(args)...);
    }

    template <typename... Args> void err(std::format_string<Args...> fmt, Args&&... args) const
    {
        log(LOG_LEVEL::ERR, std::forward<decltype(fmt)>(fmt), std::forward<Args>(args)...);
    }
};

template <typename... Args> void LOGGER_INFO(std::format_string<Args...> fmt, Args&&... args)
{
    Logger::Instance().info(fmt, std::forward<Args>(args)...);
}

template <typename... Args> void LOGGER_WARNING(std::format_string<Args...> fmt, Args&&... args)
{
    Logger::Instance().warn(fmt, std::forward<Args>(args)...);
}

template <typename... Args> void LOGGER_ERROR(std::format_string<Args...> fmt, Args&&... args)
{
    Logger::Instance().err(fmt, std::forward<Args>(args)...);
}

#else

#define LOGGER_INFO(...)
#define LOGGER_WARNING(...)
#define LOGGER_ERROR(...)

#endif

[[nodiscard]] bool handle_windows_calls(int reason);

#endif // CORE_LOGGER_H