#ifndef UPLAY_R1_H
#define UPLAY_R1_H

#include "../../Core/Core.h"

inline UplayConfig g_uplay_config;

struct UplayOverlapped
{
    void* Result;
    int IsOperationCompleted;
    int Reserved;

    void set_zeroes()
    {
        std::memset(this, NULL, sizeof(UplayOverlapped));
    };
    void set_result()
    {
        IsOperationCompleted = 1;
        Reserved = 0;
    };
    void set_result(void* outResult)
    {
        Result = outResult;
        IsOperationCompleted = 1;
    };
};

struct FileList
{
    DWORD num;
    char* bufferstring;
    DWORD pointer;
};

struct UplayList
{
    ULONG_PTR count;
    FileList** games;
};

DLLEXPORT int UPLAY_ClearGameSession();
DLLEXPORT int UPLAY_GetLastError();
DLLEXPORT int UPLAY_GetNextEvent();
DLLEXPORT int UPLAY_GetOverlappedOperationResult(UplayOverlapped* overlapped, int* outResult);
DLLEXPORT int UPLAY_HasOverlappedOperationCompleted(UplayOverlapped* overlapped);
DLLEXPORT int UPLAY_Init();
DLLEXPORT int UPLAY_METADATA_ClearContinuousTag();
DLLEXPORT int UPLAY_METADATA_SetContinuousTag();
DLLEXPORT int UPLAY_METADATA_SetSingleEventTag();
DLLEXPORT int UPLAY_PeekNextEvent();
DLLEXPORT int UPLAY_PRESENCE_SetPresence();
DLLEXPORT int UPLAY_PRODUCT_GetProductList();
DLLEXPORT int UPLAY_PRODUCT_ReleaseProductList();
DLLEXPORT int UPLAY_Quit();
DLLEXPORT int UPLAY_Release();
DLLEXPORT int UPLAY_SetGameSession();
DLLEXPORT int UPLAY_SetLanguage(const char* language);
DLLEXPORT int UPLAY_Start();
DLLEXPORT int UPLAY_StartCN();
DLLEXPORT int UPLAY_Startup();
DLLEXPORT int UPLAY_Update();

// Achievements
DLLEXPORT int UPLAY_ACH_EarnAchievement();
DLLEXPORT int UPLAY_ACH_GetAchievementImage();
DLLEXPORT int UPLAY_ACH_GetAchievements();
DLLEXPORT int UPLAY_ACH_ReleaseAchievementImage();
DLLEXPORT int UPLAY_ACH_ReleaseAchievementList();
DLLEXPORT int UPLAY_ACH_Write();

// Avatar
DLLEXPORT int UPLAY_AVATAR_Get();
DLLEXPORT int UPLAY_AVATAR_GetAvatarIdForCurrentUser();
DLLEXPORT int UPLAY_AVATAR_GetBitmap();
DLLEXPORT int UPLAY_AVATAR_Release();

// Chat
DLLEXPORT int UPLAY_CHAT_GetHistory();
DLLEXPORT int UPLAY_CHAT_Init();
DLLEXPORT int UPLAY_CHAT_ReleaseHistoryList();
DLLEXPORT int UPLAY_CHAT_SendMessage();
DLLEXPORT int UPLAY_CHAT_SentMessagesRead();

// Friends
DLLEXPORT int UPLAY_FRIENDS_AddPlayedWith();
DLLEXPORT int UPLAY_FRIENDS_AddToBlackList();
DLLEXPORT int UPLAY_FRIENDS_DisableFriendMenuItem();
DLLEXPORT int UPLAY_FRIENDS_EnableFriendMenuItem();
DLLEXPORT int UPLAY_FRIENDS_GetFriendList();
DLLEXPORT int UPLAY_FRIENDS_Init();
DLLEXPORT int UPLAY_FRIENDS_InviteToGame();
DLLEXPORT int UPLAY_FRIENDS_IsBlackListed();
DLLEXPORT int UPLAY_FRIENDS_IsFriend();
DLLEXPORT int UPLAY_FRIENDS_RemoveFriendship();
DLLEXPORT int UPLAY_FRIENDS_RemoveFromBlackList();
DLLEXPORT int UPLAY_FRIENDS_RequestFriendship();
DLLEXPORT int UPLAY_FRIENDS_RespondToGameInvite();
DLLEXPORT int UPLAY_FRIENDS_ShowFriendSelectionUI();
DLLEXPORT int UPLAY_FRIENDS_ShowInviteFriendsToGameUI();

// Installer
DLLEXPORT int UPLAY_INSTALLER_AreChunksInstalled();
DLLEXPORT int UPLAY_INSTALLER_GetChunkIdsFromTag();
DLLEXPORT int UPLAY_INSTALLER_GetChunks();
DLLEXPORT const char* UPLAY_INSTALLER_GetLanguageUtf8();
DLLEXPORT int UPLAY_INSTALLER_Init();
DLLEXPORT int UPLAY_INSTALLER_ReleaseChunkIdList();
DLLEXPORT int UPLAY_INSTALLER_UpdateInstallOrder();

// Options
DLLEXPORT int UPLAY_OPTIONS_Apply();
DLLEXPORT int UPLAY_OPTIONS_Close();
DLLEXPORT int UPLAY_OPTIONS_Enumerate();
DLLEXPORT int UPLAY_OPTIONS_Get();
DLLEXPORT int UPLAY_OPTIONS_Open();
DLLEXPORT int UPLAY_OPTIONS_ReleaseKeyValueList();
DLLEXPORT int UPLAY_OPTIONS_SetInGameState();

// Overlay
DLLEXPORT int UPLAY_OVERLAY_SetShopUrl();
DLLEXPORT int UPLAY_OVERLAY_Show();
DLLEXPORT int UPLAY_OVERLAY_ShowBrowserUrl();
DLLEXPORT int UPLAY_OVERLAY_ShowFacebookAuthentication();
DLLEXPORT int UPLAY_OVERLAY_ShowMicroApp();
DLLEXPORT int UPLAY_OVERLAY_ShowNotification();
DLLEXPORT int UPLAY_OVERLAY_ShowShopUrl();

// Party
DLLEXPORT int UPLAY_PARTY_DisablePartyMemberMenuItem();
DLLEXPORT int UPLAY_PARTY_EnablePartyMemberMenuItem();
DLLEXPORT int UPLAY_PARTY_GetFullMemberList();
DLLEXPORT int UPLAY_PARTY_GetId();
DLLEXPORT int UPLAY_PARTY_GetInGameMemberList();
DLLEXPORT int UPLAY_PARTY_Init();
DLLEXPORT int UPLAY_PARTY_InvitePartyToGame();
DLLEXPORT int UPLAY_PARTY_InviteToParty();
DLLEXPORT int UPLAY_PARTY_IsInParty();
DLLEXPORT int UPLAY_PARTY_IsPartyLeader();
DLLEXPORT int UPLAY_PARTY_PromoteToLeader();
DLLEXPORT int UPLAY_PARTY_RespondToGameInvite();
DLLEXPORT int UPLAY_PARTY_SetGuest();
DLLEXPORT int UPLAY_PARTY_SetUserData();
DLLEXPORT int UPLAY_PARTY_ShowGameInviteOverlayUI();

// Saves

DLLEXPORT int UPLAY_SAVE_GetSavegames(UplayList** out_games_list, UplayOverlapped* overlapped);
DLLEXPORT int UPLAY_SAVE_Remove(uint32_t in_handle, UplayOverlapped* overlapped);
DLLEXPORT int UPLAY_SAVE_SetName();
DLLEXPORT int UPLAY_SAVE_Open(uint32_t in_handle, uint32_t in_flags, uint32_t* out_handle, UplayOverlapped* overlapped);
DLLEXPORT int UPLAY_SAVE_Close(uint32_t in_handle);
DLLEXPORT int UPLAY_SAVE_Read(uint32_t in_handle, uint32_t in_bytes_to_read, uint32_t in_bytes_read_offset,
                              uint8_t** out_data, uint32_t* out_bytes_read, UplayOverlapped* overlapped);
DLLEXPORT int UPLAY_SAVE_Write(uint32_t in_handle, uint32_t in_size, char** in_data, UplayOverlapped* overlapped);
DLLEXPORT int UPLAY_SAVE_ReleaseGameList(UplayList* games_list);

// Store
DLLEXPORT int UPLAY_STORE_Checkout();
DLLEXPORT int UPLAY_STORE_GetPartner();
DLLEXPORT int UPLAY_STORE_GetProducts();
DLLEXPORT int UPLAY_STORE_IsEnabled();
DLLEXPORT int UPLAY_STORE_ReleaseProductsList();
DLLEXPORT int UPLAY_STORE_ShowProductDetails();
DLLEXPORT int UPLAY_STORE_ShowProducts();

// User
DLLEXPORT int UPLAY_USER_ClearGameSession();
DLLEXPORT int UPLAY_USER_ConsumeItem();
DLLEXPORT int UPLAY_USER_GetAccountId();
DLLEXPORT const char* UPLAY_USER_GetAccountIdUtf8();
DLLEXPORT int UPLAY_USER_GetCdKeys();
DLLEXPORT const char* UPLAY_USER_GetCdKeyUtf8();
DLLEXPORT int UPLAY_USER_GetConsumableItems();
DLLEXPORT int UPLAY_USER_GetCPUScore();
DLLEXPORT int UPLAY_USER_GetCredentials();
DLLEXPORT int UPLAY_USER_GetEmail();
DLLEXPORT const char* UPLAY_USER_GetEmailUtf8();
DLLEXPORT int UPLAY_USER_GetGPUScore();
DLLEXPORT int UPLAY_USER_GetGPUScoreConfidenceLevel();
DLLEXPORT const char* UPLAY_USER_GetNameUtf8();
DLLEXPORT int UPLAY_USER_GetPassword();
DLLEXPORT const char* UPLAY_USER_GetPasswordUtf8();
DLLEXPORT int UPLAY_USER_GetProfile();
DLLEXPORT const char* UPLAY_USER_GetTicketUtf8();
DLLEXPORT int UPLAY_USER_GetUsername();
DLLEXPORT const char* UPLAY_USER_GetUsernameUtf8();
DLLEXPORT int UPLAY_USER_IsConnected();
DLLEXPORT int UPLAY_USER_IsInOfflineMode();
DLLEXPORT int UPLAY_USER_IsOwned(int data);
DLLEXPORT int UPLAY_USER_ReleaseCdKeyList();
DLLEXPORT int UPLAY_USER_ReleaseConsumeItemResult();
DLLEXPORT int UPLAY_USER_ReleaseProfile();
DLLEXPORT int UPLAY_USER_SetGameSession();

// Win
DLLEXPORT int UPLAY_WIN_GetActions();
DLLEXPORT int UPLAY_WIN_GetRewards();
DLLEXPORT int UPLAY_WIN_GetUnitBalance();
DLLEXPORT int UPLAY_WIN_RefreshActions();
DLLEXPORT int UPLAY_WIN_ReleaseActionList();
DLLEXPORT int UPLAY_WIN_ReleaseRewardList();
DLLEXPORT int UPLAY_WIN_SetActionsCompleted();

#endif // UPLAY_R1_H