#include "../Core/Core.h"

#pragma comment(linker, "/export:?GetDefaultArgsString@DefaultArgs@@YAPEBDXZ=GetDefaultArgsString")
DLLEXPORT char const* GetDefaultArgsString()
{
    return "/uplayproductid:635 /belaunch /nologo /windowtitle:\"Rainbow Six Siege: Operation Throwback\"";
}

BOOL APIENTRY DllMain(HMODULE handle_module, DWORD call_reason, LPVOID lp_reserved)
{
    return TRUE;
}
