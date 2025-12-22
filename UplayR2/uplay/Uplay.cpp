#include "Uplay.h"

DLLEXPORT const char* UPC_ErrorToString(int error)
{
    LOGGER_INFO(__FUNCTION__);

    switch (error)
    {
    case -1:
        return "Declined";
    case -2:
        return "Invalid arguments";
    case -3:
        return "Uninitialized subsystem";
    case -4:
        return "Communication error";
    case -5:
        return "Memory error";
    case -6:
        return "Not found";
    case -7:
        return "End of file";
    case -9:
        return "Unauthorized action";
    case -10:
        return "Internal error";
    case -0xb:
        return "Operation aborted";
    case -0xd:
        return "Failed precondition";
    case -0xe:
        return "Unavailable";
    default:
        return "Unknown error";
    }
}

DLLEXPORT int UPC_ApplicationIdGet(ContextData* context, const char** out_app_id)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_app_id)
    {
        return -2;
    }

    *out_app_id = CONSTS::UPLAY::DEFAULT_GAME_ID;
    return 0;
}

DLLEXPORT int UPC_AvatarFree()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_AvatarGet()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_BlacklistAdd()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_BlacklistHas()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_BlacklistHas_Extended()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT void UPC_Cancel()
{
    LOGGER_INFO(__FUNCTION__);
}

DLLEXPORT ContextData* UPC_ContextCreate()
{
    LOGGER_INFO(__FUNCTION__);
    auto data = new ContextData();
    data->config = &g_uplay_config;
    return data;
}

DLLEXPORT int UPC_ContextFree(ContextData* context)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context)
    {
        return -2;
    }

    delete context;
    return 0;
}

DLLEXPORT int UPC_CPUScoreGet(ContextData* context, unsigned int* out_score)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_score)
    {
        return -2;
    }

    *out_score = 0x1000;
    return 0;
}

DLLEXPORT const char* UPC_EmailGet()
{
    LOGGER_INFO(__FUNCTION__);
    return CONSTS::UPLAY::DEFAULT_EMAIL;
}

DLLEXPORT int UPC_EmailGet_Extended(ContextData* context, const char** out_email)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_email)
    {
        return -2;
    }

    *out_email = CONSTS::UPLAY::DEFAULT_EMAIL;
    return 0;
}

DLLEXPORT int UPC_EventNextPeek()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_EventNextPoll()
{
#ifdef ENABLE_VERY_VERBOSE_LOGGING
    LOGGER_INFO(__FUNCTION__);
#endif
    return -6;
}

DLLEXPORT int UPC_EventRegisterHandler()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_GPUScoreGet(ContextData* context, unsigned* out_score, float* out_confidence_level)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_score || !out_confidence_level)
    {
        return -2;
    }

    *out_score = 0x1000;
    *out_confidence_level = 1.0;
    return 0;
}

DLLEXPORT const char* UPC_IdGet(ContextData* context)
{
    LOGGER_INFO(__FUNCTION__);
    return context->config->GetUserId().c_str();
}

DLLEXPORT int UPC_IdGet_Extended(ContextData* context, const char** out_id)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_id)
    {
        return -2;
    }

    *out_id = context->config->GetUserId().c_str();
    return 0;
}

DLLEXPORT int UPC_Init(unsigned in_version, int appid)
{
    LOGGER_INFO(__FUNCTION__);
    g_uplay_config.Initialize();
    g_uplay_config.SetAppId(appid);
    return 0;
}

DLLEXPORT const char* UPC_InstallLanguageGet()
{
    LOGGER_INFO(__FUNCTION__);
    return CONSTS::UPLAY::DEFAULT_GAME_LANGUAGE;
}

DLLEXPORT int UPC_InstallLanguageGet_Extended(ContextData* context, const char** out_install_language)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_install_language)
    {
        return -2;
    }

    *out_install_language = CONSTS::UPLAY::DEFAULT_GAME_LANGUAGE;
    return 0;
}

DLLEXPORT int UPC_LaunchApp()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPC_NameGet(ContextData* context)
{
    LOGGER_INFO(__FUNCTION__);

    return context->config->GetUsername().c_str();
}

DLLEXPORT int UPC_NameGet_Extended(ContextData* context, const char** out_name)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_name)
    {
        return -2;
    }

    *out_name = context->config->GetUsername().c_str();
    return 0;
}

DLLEXPORT int UPC_RichPresenceSet()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_RichPresenceSet_Extended()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_ShowBrowserUrl()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT const char* UPC_TicketGet()
{
    LOGGER_INFO(__FUNCTION__);
    return CONSTS::UPLAY::DEFAULT_TICKETID;
}

DLLEXPORT int UPC_TicketGet_Extended(ContextData* context, const char** out_ticket)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_ticket)
    {
        return -2;
    }

    *out_ticket = CONSTS::UPLAY::DEFAULT_TICKETID;
    return 0;
}

DLLEXPORT void UPC_Uninit()
{
    LOGGER_INFO(__FUNCTION__);
}

DLLEXPORT int UPC_Update(ContextData* context)
{
#ifdef ENABLE_VERY_VERBOSE_LOGGING
    LOGGER_INFO(__FUNCTION__);
#endif
    while (!context->callbacks.empty())
    {
        auto cb = context->callbacks.front();
        cb.callback(cb.arg1, cb.context_data);
        context->callbacks.pop();
    }

    return 0;
}

DLLEXPORT int UPC_UserFree()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_UserGet()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_UserPlayedWithAdd()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_UserPlayedWithAdd_Extended()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}