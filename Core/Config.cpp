#include "Config.h"

#include "Logger.h"
#include "Utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#define TOML_EXCEPTIONS 0
#define TOML_HEADER_ONLY 0
#define TOML_IMPLEMENTATION
#include <toml++/toml.hpp>

static constexpr const char* DEFAULT_CONFIG_FILE = R"([general]
username = 'R6ThrowbackUser' # edit to change in-game username. Limit to 16 characters

[advanced]
custom_user_id = '' # used to override the default user id ("R6Throwback_" followed by the season name), leave blank to use the default setting. This setting controls the foldername in Documents\Rainbow Six - Siege)";

bool write_default_config_file(const std::filesystem::path& config_path)
{
    std::ofstream file(config_path);

    if (!file.is_open())
    {
        return false;
    }

    LOGGER_INFO("Writing default config");
    file << DEFAULT_CONFIG_FILE;

    return true;
}

void assign_if_value(std::string& var, const std::optional<std::string_view>& opt)
{
    if (opt.has_value() && !opt->empty())
    {
        var = *opt;
    }
}

void assign_if_value(bool& var, const std::optional<bool>& opt)
{
    {
        var = opt.value_or(var);
    }
}

void UplayConfig::Initialize()
{
    const auto config_path = std::filesystem::current_path() / CONSTS::DEFAULT_CONFIG_FILENAME;
    LOGGER_INFO("Config path: {}", config_path.string());

    if (!std::filesystem::exists(config_path))
    {
        LOGGER_WARNING("Config file not found");
        write_default_config_file(config_path);
        return;
    }

    const auto parse_result = toml::parse_file(config_path.string());
    if (!parse_result)
    {
        LOGGER_WARNING("Config file parsing failed with error:");
        std::cout << parse_result.error() << "\n";
        write_default_config_file(config_path);
        return;
    }

    const auto& toml_table = parse_result.table();
    {
        assign_if_value(m_Username, toml_table["general"]["username"].value<std::string_view>());
        assign_if_value(m_UserId, toml_table["advanced"]["custom_user_id"].value<std::string_view>());
    }
    m_UserId = get_user_id(m_UserId);

    LOGGER_INFO("username: {} - user_id: {}", m_Username, m_UserId);
}

bool SteamConfig::Initialize()
{
    if (!m_IsInit)
    {
        m_IsInit = true;
    }

    return m_IsInit;
}