#include "Uplay.h"

DLLEXPORT int UPLAY_USER_ClearGameSession()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_USER_ConsumeItem()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}
DLLEXPORT int UPLAY_USER_GetAccountId()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPLAY_USER_GetAccountIdUtf8()
{
    LOGGER_INFO(__FUNCTION__);
    return g_uplay_config.GetUserId().c_str();
}

DLLEXPORT int UPLAY_USER_GetCPUScore()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPLAY_USER_GetCdKeyUtf8()
{
    LOGGER_INFO(__FUNCTION__);
    return CONSTS::UPLAY::DEFAULT_CD_KEY;
}

DLLEXPORT int UPLAY_USER_GetCdKeys()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPLAY_USER_GetConsumableItems()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPLAY_USER_GetCredentials()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPLAY_USER_GetEmail()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPLAY_USER_GetEmailUtf8()
{
    LOGGER_INFO(__FUNCTION__);
    return CONSTS::UPLAY::DEFAULT_EMAIL;
}

DLLEXPORT int UPLAY_USER_GetGPUScore()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPLAY_USER_GetGPUScoreConfidenceLevel()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPLAY_USER_GetNameUtf8()
{
    LOGGER_INFO(__FUNCTION__);
    return g_uplay_config.GetUsername().c_str();
}

DLLEXPORT int UPLAY_USER_GetPassword()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPLAY_USER_GetPasswordUtf8()
{
    LOGGER_INFO(__FUNCTION__);
    return CONSTS::UPLAY::DEFAULT_PASSWORD;
}

DLLEXPORT int UPLAY_USER_GetProfile()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPLAY_USER_GetTicketUtf8()
{
    LOGGER_INFO(__FUNCTION__);
    return CONSTS::UPLAY::DEFAULT_TICKETID;
}

DLLEXPORT int UPLAY_USER_GetUsername()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPLAY_USER_GetUsernameUtf8()
{
    LOGGER_INFO(__FUNCTION__);
    return g_uplay_config.GetUsername().c_str();
}

DLLEXPORT int UPLAY_USER_IsConnected()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_USER_IsInOfflineMode()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_USER_IsOwned(int data)
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_USER_ReleaseCdKeyList()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_USER_ReleaseConsumeItemResult()
{
    LOGGER_INFO(__FUNCTION__);
    return 1;
}

DLLEXPORT int UPLAY_USER_ReleaseProfile()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPLAY_USER_SetGameSession()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}