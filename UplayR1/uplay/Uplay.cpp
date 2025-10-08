#include "Uplay.h"

DLLEXPORT int UPLAY_ClearGameSession()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPLAY_GetLastError()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPLAY_GetNextEvent()
{
#ifdef ENABLE_VERY_VERBOSE_LOGGING
    LOGGER_INFO(__FUNCTION__);
#endif
    return 0;
}

DLLEXPORT int UPLAY_GetOverlappedOperationResult(UplayOverlapped* overlapped, int* outResult)
{
    LOGGER_INFO(__FUNCTION__);
    if (overlapped && overlapped->IsOperationCompleted)
    {
        *outResult = overlapped->Reserved;
        return 1;
    }

    return 0;
}

DLLEXPORT int UPLAY_HasOverlappedOperationCompleted(UplayOverlapped* overlapped)
{
#ifdef ENABLE_VERY_VERBOSE_LOGGING
    LOGGER_INFO(__FUNCTION__);
#endif

    return overlapped->IsOperationCompleted;
}

DLLEXPORT int UPLAY_Init()
{
    LOGGER_INFO(__FUNCTION__);
    g_uplay_config.Initialize();
    return 1;
}

DLLEXPORT int UPLAY_PeekNextEvent()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_Quit()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_Release()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_SetGameSession()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_Update()
{
#ifdef ENABLE_VERY_VERBOSE_LOGGING
    LOGGER_INFO(__FUNCTION__);
#endif
    return 1;
}

DLLEXPORT int UPLAY_SetLanguage(const char* language)
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_Start()
{
    LOGGER_INFO(__FUNCTION__);
    UPLAY_Init();
    return 0;
}
DLLEXPORT int UPLAY_StartCN()
{
    LOGGER_INFO(__FUNCTION__);
    return UPLAY_Start();
}
DLLEXPORT int UPLAY_Startup()
{
    LOGGER_INFO(__FUNCTION__);
    return UPLAY_Start();
}

DLLEXPORT int UPLAY_METADATA_ClearContinuousTag()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_METADATA_SetContinuousTag()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_METADATA_SetSingleEventTag()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_PRODUCT_GetProductList()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_PRODUCT_ReleaseProductList()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}