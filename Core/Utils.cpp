#include "Consts.h"
#include "Utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <Windows.h>

#include <ctre.hpp>

std::filesystem::path get_saves_path(std::optional<int32_t> app_id)
{
    auto saves_path = std::filesystem::current_path() / std::filesystem::path(CONSTS::SAVE_FILES_FOLDER);
    if (app_id.has_value())
    {
        saves_path /= std::to_string(app_id.value());
    }

    if (!std::filesystem::exists(saves_path))
    {
        std::filesystem::create_directories(saves_path);
    }
    return saves_path;
}

[[nodiscard]] std::string get_user_id(std::string& current_user_id)
{
    if (!current_user_id.empty())
    {
        return current_user_id;
    }

    const auto current_path = std::filesystem::current_path();
    const auto current_folder = current_path.filename().string();

    if (!ctre::match<R"(^Y\d+S\d+_.+$)">(current_folder)) // check if folder name is in the classic YxSx_SeasonName
    {
        return "R6Throwback_Unknown";
    }

    return std::format("R6Throwback_{}", current_folder);
}