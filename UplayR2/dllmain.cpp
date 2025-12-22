#include "../Core/Core.h"
#include "uplay/Uplay.h"

DLLEXPORT const char* Throwbackloader_GetVersion()
{
    return get_version_string();
}

BOOL APIENTRY DllMain(HMODULE handle_module, DWORD call_reason, LPVOID lp_reserved)
{
    const auto result = handle_windows_calls(call_reason);
    execute_streaminginstall_workaround();
    return result;
}
