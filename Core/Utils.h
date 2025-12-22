#ifndef CORE_UTILS_H
#define CORE_UTILS_H

#include <filesystem>
#include <optional>
#include <span>
#include <string_view>

#include "Consts.h"

[[nodiscard]] std::filesystem::path get_saves_path(std::optional<int32_t> app_id = std::nullopt);
[[nodiscard]] std::string get_user_id(std::string& current_user_id);
void execute_streaminginstall_workaround();

#endif // CORE_UTILS_H