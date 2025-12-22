#include "Uplay.h"

DLLEXPORT int UPC_StoreCheckout()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT bool UPC_StoreIsEnabled()
{
    LOGGER_INFO(__FUNCTION__);
    return false;
}

DLLEXPORT int UPC_StoreIsEnabled_Extended(ContextData* context, bool* out_enabled)
{
    LOGGER_INFO(__FUNCTION__);

    if (!context || !out_enabled)
    {
        return -2;
    }

    *out_enabled = false;
    return 0;
}

DLLEXPORT int UPC_StoreLanguageSet()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_StorePartnerGet()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_StorePartnerGet_Extended()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_StoreProductDetailsShow()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_StoreProductListFree()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_StoreProductListGet()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}

DLLEXPORT int UPC_StoreProductsShow()
{
    LOGGER_INFO(__FUNCTION__);
    return 0;
}