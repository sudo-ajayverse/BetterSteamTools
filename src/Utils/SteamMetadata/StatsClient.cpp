#include "StatsClient.h"

#include "OSTPlatform/include/Http.h"
#include "OSTPlatform/include/Numbers.h"
#include "Utils/Config/Config.h"
#include "Utils/Logging/Log.h"

#include <cctype>
#include <cstdio>
#include <mutex>
#include <string_view>
#include <unordered_map>

namespace StatsClient {
namespace {

    std::mutex g_mutex;
    std::unordered_map<AppId_t, uint64_t> g_cache;

    bool ParseSteamId(std::string_view body, uint64_t* outSteamId) {
        const auto parsed = OSTPlatform::Numbers::ParseUInt64(body);
        if (!parsed || *parsed == 0) return false;
        *outSteamId = *parsed;
        return true;
    }

} // namespace

bool FetchStatSteamId(AppId_t appId, uint64_t* outSteamId) {
    if (!outSteamId || appId == k_uAppIdInvalid) return false;

    LOG_ACHIEVEMENT_DEBUG("Stats SteamID remote API disabled for appid={}", appId);
    return false;
}

} // namespace StatsClient
