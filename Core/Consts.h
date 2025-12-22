#ifndef CORE_CONSTS_H
#define CORE_CONSTS_H

#define TO_STR_HELPER(x) #x
#define TO_STR(x) TO_STR_HELPER(x)

namespace CONSTS
{
static constexpr const char* SAVE_FILE_EXTENSION = "sav";
static constexpr const char* SAVE_FILES_FOLDER = "ThrowbackLoaderSaves";
static constexpr const char* DEFAULT_CONFIG_FILENAME = "ThrowbackLoader.toml";

static constexpr const char* DEFAULT_USERNAME = "R6ThrowbackUser";
namespace UPLAY
{
static constexpr const char* DEFAULT_CD_KEY = "1111-2222-3333-4444";
static constexpr const char* DEFAULT_EMAIL = "user@throwback.tb";
static constexpr const char* DEFAULT_PASSWORD = "password";
static constexpr const char* DEFAULT_TICKETID = ""; // empty ticket is required to appear offline in R2
static constexpr const char* DEFAULT_GAME_LANGUAGE = "en-US";
static constexpr const char* DEFAULT_GAME_ID = "R6ThrowbackGameId";
} // namespace UPLAY

namespace STEAM
{
static constexpr int SIEGE_STEAM_ID = 359550;
} // namespace STEAM

} // namespace CONSTS

#endif // CORE_CONSTS_H