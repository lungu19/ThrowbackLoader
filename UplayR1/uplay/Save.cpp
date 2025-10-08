#include "Uplay.h"

#include "../../Core/Utils.h"

#include <fstream>

static constexpr const int SAVE_PADDING_SIZE = 0x228;

[[nodiscard]] std::optional<std::vector<std::filesystem::path>> get_save_files()
{
    std::error_code error_code;
    const auto iterator = std::filesystem::directory_iterator(get_saves_path(), error_code);

    if (error_code)
    {
        return std::nullopt;
    }

    std::vector<std::filesystem::path> save_files{};
    const auto savefile_extension = std::format(".{}", CONSTS::SAVE_FILE_EXTENSION);

    for (const auto& entry : iterator)
    {
        if (entry.is_regular_file() && entry.path().extension() == savefile_extension)
        {
            save_files.push_back(entry.path());
        }
    }

    return save_files;
}

[[nodiscard]] std::filesystem::path get_save_path(uint32_t handle)
{
    const auto saves_path = get_saves_path();
    const auto fileName = std::format("{}.{}", handle, CONSTS::SAVE_FILE_EXTENSION);
    return saves_path / fileName;
}

[[nodiscard]] std::optional<uint64_t> parse_save_handle(const std::filesystem::path& filepath)
{
    if (!filepath.has_extension())
    {
        return std::nullopt;
    }

    const auto stem = filepath.stem();
    if (stem.empty())
    {
        return std::nullopt;
    }

    const std::string stem_str = stem.string();

    uint64_t file_number = 0;
    const auto result = std::from_chars(stem_str.data(), stem_str.data() + stem_str.size(), file_number, 16);
    if (result.ec != std::errc{} || result.ptr != stem_str.data() + stem_str.size())
    {
        return std::nullopt;
    }

    return file_number;
}

std::optional<uint64_t> get_file_size(const std::filesystem::path& file_path)
{
    std::error_code error_code;
    const auto file_size = std::filesystem::file_size(file_path, error_code);

    if (error_code)
    {
        return std::nullopt;
    }

    return static_cast<uint64_t>(file_size);
}

DLLEXPORT int UPLAY_SAVE_GetSavegames(UplayList** out_games_list, UplayOverlapped* overlapped)
{
    LOGGER_INFO(__FUNCTION__);

    if (!out_games_list || !overlapped)
    {
        LOGGER_ERROR("Null pointer passed to the function");
        return 0;
    }

    const auto savefile_paths = get_save_files();

    if (!savefile_paths.has_value() || savefile_paths->size() == 0)
    {
        return 0;
    }

    std::vector<std::unique_ptr<FileList>> saves_found;
    for (const auto& save_path : savefile_paths.value())
    {
        const auto save_handle = parse_save_handle(save_path);
        if (!save_handle.has_value())
        {
            continue;
        }

        std::ifstream save_file(save_path, std::ios::binary | std::ios::ate);
        if (!save_file.is_open())
        {
            continue;
        }

        const auto file_size = static_cast<DWORD>(save_file.tellg());
        save_file.seekg(0x28, std::ios::beg);

        auto data_buffer = std::unique_ptr<char[]>(new (std::nothrow) char[0x200]);
        if (!data_buffer || !save_file.read(reinterpret_cast<char*>(data_buffer.get()), 0x200))
        {
            continue;
        }

        auto file_list_item = std::make_unique<FileList>();
        file_list_item->bufferstring = data_buffer.release();
        file_list_item->num = save_handle.value();
        file_list_item->pointer = file_size - SAVE_PADDING_SIZE;

        saves_found.push_back(std::move(file_list_item));
    }

    if (saves_found.empty())
    {
        return 0;
    }

    auto game_ptr_array = std::make_unique<FileList*[]>(saves_found.size());

    for (size_t i = 0; i < saves_found.size(); ++i)
    {
        game_ptr_array[i] = saves_found[i].release();
    }

    auto final_list = std::make_unique<UplayList>();
    final_list->count = saves_found.size();
    final_list->games = game_ptr_array.release();

    *out_games_list = final_list.release();
    return 1;
}

DLLEXPORT int UPLAY_SAVE_Remove(uint32_t in_handle, UplayOverlapped* overlapped)
{
    LOGGER_INFO("{} {}", __FUNCTION__, in_handle);

    if (!overlapped)
    {
        return 0;
    }

    const auto savePath = get_save_path(in_handle);
    if (!std::filesystem::remove(savePath))
    {
        LOGGER_ERROR("Failed to remove savefile");
        return 0;
    }

    overlapped->set_result();
    return 1;
}

DLLEXPORT int UPLAY_SAVE_SetName()
{
    LOGGER_INFO(__FUNCTION__);

    return 0;
}

DLLEXPORT int UPLAY_SAVE_Open(uint32_t in_handle, uint32_t in_flags, uint32_t* out_handle, UplayOverlapped* overlapped)
{
    LOGGER_INFO("{} {} {}", __FUNCTION__, in_handle, in_flags);

    if (!out_handle || !overlapped)
    {
        LOGGER_ERROR("One or more null pointer passed to the function");
        return -1;
    }

    *out_handle = in_handle;

    overlapped->set_zeroes();
    overlapped->set_result(&out_handle);
    return 1;
}

DLLEXPORT int UPLAY_SAVE_Close(uint32_t in_handle)
{
    LOGGER_INFO("{} {}", __FUNCTION__, in_handle);

    return 1;
}

DLLEXPORT int UPLAY_SAVE_Read(uint32_t in_handle, uint32_t in_bytes_to_read, uint32_t in_bytes_read_offset,
                              uint8_t** out_data, uint32_t* out_bytes_read, UplayOverlapped* overlapped)
{
    LOGGER_INFO("{} {} {} {}", __FUNCTION__, in_handle, in_bytes_to_read, in_bytes_read_offset);

    if (!out_data || !*out_data || !out_bytes_read || !overlapped)
    {
        LOGGER_ERROR("One or more null pointer passed to the function");
        return 0;
    }

    overlapped->set_zeroes();

    const auto file_path = get_save_path(in_handle);
    uint64_t file_size = 0;
    std::vector<uint8_t> file_data;

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open())
    {
        return 0;
    }

    file_size = get_file_size(file_path).value_or(-1);
    if (file_size < 0)
    {
        return 0;
    }

    file_data = std::vector<uint8_t>(file_size);
    file.seekg(0, std::ios::beg);
    if (!file.read(reinterpret_cast<char*>(file_data.data()), file_size))
    {
        return 0;
    }

    if (static_cast<uint64_t>(file_size) < SAVE_PADDING_SIZE)
    {
        return 0;
    }

    const size_t available_bytes = file_size - SAVE_PADDING_SIZE;
    const size_t bytes_to_copy = std::min(static_cast<size_t>(in_bytes_to_read), available_bytes);

    if (bytes_to_copy > 0)
    {
        std::memcpy(*out_data + in_bytes_read_offset, file_data.data() + SAVE_PADDING_SIZE, bytes_to_copy);
    }

    *out_bytes_read = static_cast<uint32_t>(file_size);
    overlapped->set_result(static_cast<void*>(*out_data));
    return 1;
}

DLLEXPORT int UPLAY_SAVE_Write(uint32_t in_handle, uint32_t in_size, char** in_data, UplayOverlapped* overlapped)
{
    LOGGER_INFO("{} {} {}", __FUNCTION__, in_handle, in_size);

    if (!in_data || !overlapped)
    {
        LOGGER_ERROR("One or more null pointer passed to the function");
        return 0;
    }

    overlapped->set_zeroes();

    const auto FilePath = get_save_path(in_handle);

    const size_t TotalSize = SAVE_PADDING_SIZE + in_size;
    std::vector<uint8_t> output_buffer(TotalSize, 0);

    const uint8_t* source_data = reinterpret_cast<const uint8_t*>(*in_data);
    std::copy(source_data, source_data + in_size, output_buffer.begin() + SAVE_PADDING_SIZE);

    std::fstream saveFile(FilePath, std::ios::binary | std::ios::out);
    if (!saveFile.is_open())
    {
        return 0;
    }

    saveFile.write(reinterpret_cast<const char*>(output_buffer.data()), TotalSize);
    if (saveFile.fail())
    {
        return 0;
    }

    overlapped->set_result(&in_data);
    return 1;
}

DLLEXPORT int UPLAY_SAVE_ReleaseGameList(UplayList* games_list)
{
    LOGGER_INFO(__FUNCTION__);

    if (!games_list)
    {
        LOGGER_ERROR("Null pointer passed to the function");
        return 0;
    }

    for (size_t i = 0; i < games_list->count; ++i)
    {
        if (games_list->games[i])
        {
            delete[] games_list->games[i]->bufferstring;
            delete games_list->games[i];
        }
    }

    delete[] games_list->games;
    delete games_list;
    return 1;
}