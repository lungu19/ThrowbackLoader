#include "Uplay.h"

DLLEXPORT int UPLAY_INSTALLER_AreChunksInstalled()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_INSTALLER_GetChunkIdsFromTag()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPLAY_INSTALLER_GetChunks()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT const char* UPLAY_INSTALLER_GetLanguageUtf8()
{
    LOGGER_INFO(__FUNCTION__);
    return CONSTS::UPLAY::DEFAULT_GAME_LANGUAGE;
}

DLLEXPORT int UPLAY_INSTALLER_Init()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_INSTALLER_ReleaseChunkIdList()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_INSTALLER_UpdateInstallOrder()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}