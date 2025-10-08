#ifndef UPLAY_R2_H
#define UPLAY_R2_H

#include "../../Core/Core.h"
#include <queue>

inline UplayConfig g_uplay_config;

struct CallbackData
{
    CallbackData(void* fn, void* context_data, unsigned long arg)
    {
        this->callback = (void (*)(unsigned long, void*))fn;
        this->context_data = context_data;
        this->arg1 = arg;
    }

    void (*callback)(unsigned long, void*);
    unsigned long arg1;
    void* context_data;
};

struct ContextData
{
    bool initialized;
    std::queue<CallbackData> callbacks;
    UplayConfig* config;
};

struct ChunkList;

struct Product;
struct ProductList;

struct FileData;
struct FileList;

DLLEXPORT const char* UPC_ErrorToString(int param_1);
DLLEXPORT int UPC_ApplicationIdGet(ContextData* context, const char** out_app_id);
DLLEXPORT int UPC_AvatarFree();
DLLEXPORT int UPC_AvatarGet();
DLLEXPORT int UPC_BlacklistAdd();
DLLEXPORT int UPC_BlacklistHas();
DLLEXPORT int UPC_BlacklistHas_Extended();
DLLEXPORT void UPC_Cancel();
DLLEXPORT ContextData* UPC_ContextCreate();
DLLEXPORT int UPC_ContextFree(ContextData* context);
DLLEXPORT int UPC_CPUScoreGet(ContextData* context, unsigned int* out_score);
DLLEXPORT const char* UPC_EmailGet();
DLLEXPORT int UPC_EmailGet_Extended(ContextData* context, const char** out_email);
DLLEXPORT int UPC_EventNextPeek();
DLLEXPORT int UPC_EventNextPoll();
DLLEXPORT int UPC_EventRegisterHandler();
DLLEXPORT int UPC_GPUScoreGet(ContextData* context, unsigned* out_score, float* out_confidence_level);
DLLEXPORT const char* UPC_IdGet(ContextData* context);
DLLEXPORT int UPC_IdGet_Extended(ContextData* context, const char** out_id);
DLLEXPORT int UPC_Init(unsigned in_version, int appid);
DLLEXPORT const char* UPC_InstallLanguageGet();
DLLEXPORT int UPC_InstallLanguageGet_Extended(ContextData* context, const char** out_install_language);
DLLEXPORT int UPC_LaunchApp();
DLLEXPORT const char* UPC_NameGet(ContextData* context);
DLLEXPORT int UPC_NameGet_Extended(ContextData* context, const char** out_name);
DLLEXPORT int UPC_RichPresenceSet();
DLLEXPORT int UPC_RichPresenceSet_Extended();
DLLEXPORT int UPC_ShowBrowserUrl();
DLLEXPORT const char* UPC_TicketGet();
DLLEXPORT int UPC_TicketGet_Extended(ContextData* context, const char** out_ticket);
DLLEXPORT void UPC_Uninit();
DLLEXPORT int UPC_Update(ContextData* context);
DLLEXPORT int UPC_UserFree();
DLLEXPORT int UPC_UserGet();
DLLEXPORT int UPC_UserPlayedWithAdd();
DLLEXPORT int UPC_UserPlayedWithAdd_Extended();

// Achievement
DLLEXPORT int UPC_AchievementImageFree();
DLLEXPORT int UPC_AchievementImageGet();
DLLEXPORT int UPC_AchievementListFree();
DLLEXPORT int UPC_AchievementListGet(ContextData* context, void* in_opt_user_id_utf8, unsigned in_filter,
                                     void* out_achievement_list, void* in_callback, void* in_callback_data);
DLLEXPORT int UPC_AchievementUnlock();

// Friend
DLLEXPORT int UPC_FriendAdd();
DLLEXPORT int UPC_FriendCheck();
DLLEXPORT int UPC_FriendCheck_Extended();
DLLEXPORT int UPC_FriendListFree();
DLLEXPORT int UPC_FriendListGet();
DLLEXPORT int UPC_FriendRemove();

// InstallChunks
DLLEXPORT int UPC_InstallChunkListFree(ContextData* context, ChunkList* chunk_list);
DLLEXPORT int UPC_InstallChunkListGet(ContextData* context, ChunkList** out_chunk_list);
DLLEXPORT int UPC_InstallChunksOrderUpdate();
DLLEXPORT int UPC_InstallChunksOrderUpdate_Extended();
DLLEXPORT int UPC_InstallChunksPresenceCheck();

// Multiplayer
DLLEXPORT int UPC_MultiplayerInvite();
DLLEXPORT int UPC_MultiplayerInviteAnswer();
DLLEXPORT int UPC_MultiplayerSessionClear();
DLLEXPORT int UPC_MultiplayerSessionClear_Extended();
DLLEXPORT int UPC_MultiplayerSessionFree();
DLLEXPORT int UPC_MultiplayerSessionGet();
DLLEXPORT int UPC_MultiplayerSessionSet();
DLLEXPORT int UPC_MultiplayerSessionSet_Extended();

// Overlay
DLLEXPORT int UPC_OverlayBrowserUrlShow();
DLLEXPORT int UPC_OverlayFriendInvitationShow();
DLLEXPORT int UPC_OverlayFriendInvitationShow_Extended();
DLLEXPORT int UPC_OverlayFriendSelectionFree();
DLLEXPORT int UPC_OverlayFriendSelectionShow();
DLLEXPORT int UPC_OverlayMicroAppShow();
DLLEXPORT int UPC_OverlayNotificationShow();
DLLEXPORT int UPC_OverlayNotificationShow_Extended();
DLLEXPORT int UPC_OverlayShow();

// Product
DLLEXPORT int UPC_ProductConsume();
DLLEXPORT int UPC_ProductConsumeSignatureFree();
DLLEXPORT int UPC_ProductListFree(ContextData* context, ProductList* in_product_list);
DLLEXPORT int UPC_ProductListGet(ContextData* context, char* in_opt_user_id_utf8, unsigned in_filter,
                                 ProductList** out_product_list, void* in_callback, void* in_callback_data);

// StorageFile
DLLEXPORT int UPC_StorageFileClose(ContextData* context, unsigned in_handle);
DLLEXPORT int UPC_StorageFileDelete(ContextData* context, char* in_file_name_utf8);
DLLEXPORT int UPC_StorageFileListFree(ContextData* context, FileList* in_storage_file_list);
DLLEXPORT int UPC_StorageFileListGet(ContextData* context, FileList** out_storage_file_list);
DLLEXPORT int UPC_StorageFileOpen(ContextData* context, char* in_file_name_utf8, unsigned in_flags, int* out_handle);
DLLEXPORT int UPC_StorageFileRead(ContextData* context, int in_handle, int in_bytes_to_read,
                                  unsigned in_bytes_read_offset, void* out_data, int* out_bytes_read, void* in_callback,
                                  void* in_callback_data);
DLLEXPORT int UPC_StorageFileWrite(ContextData* context, int in_handle, void* in_data, int in_size, void* in_callback,
                                   void* in_callback_data);

// Store
DLLEXPORT int UPC_StoreCheckout();
DLLEXPORT bool UPC_StoreIsEnabled();
DLLEXPORT int UPC_StoreIsEnabled_Extended(ContextData* context, bool* out_enabled);
DLLEXPORT int UPC_StoreLanguageSet();
DLLEXPORT int UPC_StorePartnerGet();
DLLEXPORT int UPC_StorePartnerGet_Extended();
DLLEXPORT int UPC_StoreProductDetailsShow();
DLLEXPORT int UPC_StoreProductListFree();
DLLEXPORT int UPC_StoreProductListGet();
DLLEXPORT int UPC_StoreProductsShow();

#endif // UPLAY_R2_H