#include "../Core/Core.h"
#include "uplay/Uplay.h"

BOOL APIENTRY DllMain(HMODULE handle_module, DWORD call_reason, LPVOID lp_reserved)
{
    return (handle_windows_calls(call_reason));
}
