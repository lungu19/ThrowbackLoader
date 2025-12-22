#include "Core.h"

#define STRINGIFY_DETAIL(x) #x
#define STRINGIFY(x) STRINGIFY_DETAIL(x)

constexpr bool version_has_metadata()
{
    return !std::string_view(TB_LOADER_METADATA).empty();
}

[[nodiscard]] const char* get_version_string()
{
    if constexpr (version_has_metadata())
    {
        static const char versionString[] = STRINGIFY(TB_LOADER_MAJOR) "." STRINGIFY(TB_LOADER_MINOR) "." STRINGIFY(
            TB_LOADER_PATCH) "-" TB_LOADER_METADATA;
        return versionString;
    }

    static const char versionString[] =
        STRINGIFY(TB_LOADER_MAJOR) "." STRINGIFY(TB_LOADER_MINOR) "." STRINGIFY(TB_LOADER_PATCH);
    return versionString;
}