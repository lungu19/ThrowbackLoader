#include "Uplay.h"

#include <fcntl.h>
#include <io.h>
#include <list>

#define EXTRA_SAVE_PADDING (32 + 8)

// file name + file_size are important
struct FileData
{
    char* file_name;   // note: NULL terminated
    uint32_t* unknown; // seemingly unused pointer to 4 bytes of zeroes
    uint32_t file_size;
    uint32_t padding;
    uint64_t last_modified; // unix timestamp in ms
};

struct FileList
{
    uint32_t number;
    uint32_t padding = 0;
    struct FileData** files;
};

DLLEXPORT int UPC_StorageFileClose(ContextData* context, unsigned in_handle)
{
    LOGGER_INFO(__FUNCTION__);
    return _close(in_handle);
}

DLLEXPORT int UPC_StorageFileDelete(ContextData* context, char* in_file_name_utf8)
{
    LOGGER_INFO(__FUNCTION__);

    if (std::filesystem::remove(get_saves_path(context->config->GetAppId()) / in_file_name_utf8))
    {
        return 0;
    }
    return -1;
}

DLLEXPORT int UPC_StorageFileListFree(ContextData* context, FileList* in_storage_file_list)
{
    LOGGER_INFO(__FUNCTION__);
    if (!in_storage_file_list)
    {
        return -0xd;
    }

    if (in_storage_file_list->number)
    {
        for (int i = 0; i < in_storage_file_list->number; ++i)
        {
            delete[] in_storage_file_list->files[i]->file_name;
            delete in_storage_file_list->files[i]->unknown;
            delete in_storage_file_list->files[i];
        }
    }

    delete[] in_storage_file_list->files;
    delete in_storage_file_list;
    return 0;
}

DLLEXPORT int UPC_StorageFileListGet(ContextData* context, FileList** out_storage_file_list)
{
    LOGGER_INFO(__FUNCTION__);
    if (!context || !out_storage_file_list)
    {
        return -0xd;
    }

    std::list<std::filesystem::directory_entry> list;
    for (const auto& file : std::filesystem::directory_iterator(get_saves_path(context->config->GetAppId())))
    {
        if (file.is_regular_file())
        {
            list.push_back(file);
        }
    }

    struct FileList* fl = new FileList();
    fl->number = list.size();
    fl->files = new FileData*[fl->number];
    unsigned index = 0;
    for (auto& file : list)
    {
        unsigned long file_size = std::filesystem::file_size(file);
        std::string file_name = file.path().filename().string();
        if (file_size < EXTRA_SAVE_PADDING)
        {
            --fl->number;
            continue;
        }

        FileData* f_data = new FileData();
        f_data->file_name = new char[file_name.size() + 1];
        file_name.copy(f_data->file_name, file_name.size());
        f_data->file_name[file_name.size()] = 0;
        f_data->unknown = new uint32_t;
        *f_data->unknown = 0;
        f_data->padding = 0;
        f_data->file_size = file_size - EXTRA_SAVE_PADDING;
        f_data->last_modified =
            std::chrono::duration_cast<std::chrono::milliseconds>(file.last_write_time().time_since_epoch()).count();
        fl->files[index] = f_data;
        ++index;
    }

    *out_storage_file_list = fl;
    return 0;
}

DLLEXPORT int UPC_StorageFileOpen(ContextData* context, char* in_file_name_utf8, unsigned in_flags, int* out_handle)
{
    LOGGER_INFO(__FUNCTION__);
    // inFlags 0x1 = read?
    // inFlags 0x2 = write?
    int oflag = _O_BINARY | _O_CREAT | _O_RDWR;
    if (in_flags == 0x2)
    {
        oflag |= _O_TRUNC;
    }

    const auto file_path = get_saves_path(context->config->GetAppId()) / in_file_name_utf8;
    // int file_handle = _open(file_path.string().c_str(), oflag, _S_IREAD | _S_IWRITE);

    int file_handle;
    (void)_sopen_s(&file_handle, file_path.string().c_str(), oflag, _SH_DENYNO, _S_IREAD | _S_IWRITE);

    *out_handle = file_handle;
    return 0;
}

DLLEXPORT int UPC_StorageFileRead(ContextData* context, int in_handle, int in_bytes_to_read,
                                  unsigned in_bytes_read_offset, void* out_data, int* out_bytes_read, void* in_callback,
                                  void* in_callback_data)
{
    LOGGER_INFO(__FUNCTION__);

    _lseek(in_handle, in_bytes_read_offset + EXTRA_SAVE_PADDING, SEEK_SET);
    int ret = _read(in_handle, out_data, in_bytes_to_read);
    int out = 0;
    if (ret >= 0)
    {
        *out_bytes_read = ret;
    }
    else
    {
        out = -1; // not sure if right error
    }

    context->callbacks.push(CallbackData(in_callback, in_callback_data, out));
    return 0x10000;
}

DLLEXPORT int UPC_StorageFileWrite(ContextData* context, int in_handle, void* in_data, int in_size, void* in_callback,
                                   void* in_callback_data)
{
    LOGGER_INFO(__FUNCTION__);

    char padding_data[EXTRA_SAVE_PADDING] = {};
    _write(in_handle, padding_data, sizeof(padding_data));
    int ret = _write(in_handle, in_data, in_size);

    int out = 0;
    if (ret < 0)
    {
        out = -1; // Not sure if right error
    }

    context->callbacks.push(CallbackData(in_callback, in_callback_data, out));
    return 0x10000;
}