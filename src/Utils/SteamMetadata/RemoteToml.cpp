#include "RemoteToml.h"
#include "OSTPlatform/include/Http.h"
#include "Utils/Config/Config.h"
#include "Utils/Logging/Log.h"
#include "Utils/SteamMetadata/SteamDiagnostics.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string_view>
#include <vector>

namespace RemoteToml {

namespace {
    static std::vector<std::string> BuildUrlTemplates()
    {
        return Config::GetRemoteUrlTemplates();
    }
} // namespace

Result Fetch(const Request& request)
{
    namespace fs = std::filesystem;
    Result out;

    // 1. SHA-256 of the DLL.
    const auto hashStart = std::chrono::steady_clock::now();
    out.sha256 = SteamDiagnostics::Sha256Of(request.dllPath);
    const auto hashMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - hashStart).count();

    if (out.sha256.empty()) {
        LOG_WARN("RemoteToml({}/{}): Sha256OfFile failed for {} ({} ms)",
                 request.channel, request.component, request.dllPath, hashMs);
        return out;
    }
    LOG_INFO("RemoteToml({}/{}): sha256 = {} ({} ms)",
             request.channel, request.component, out.sha256, hashMs);

    // 2. Cache path & dir.
    fs::path steamRoot = fs::path(request.dllPath).parent_path();
    fs::path cacheDir  = steamRoot / "opensteamtool" / request.channel / request.component;
    fs::path cachePath = cacheDir / (out.sha256 + ".toml");
    const std::string cachePathText = cachePath.string();

    // 3. Remote HTTP downloads disabled: check local cache directly.
    if (fs::exists(cachePath)) {
        LOG_INFO("RemoteToml({}/{}): loading local cache {}",
                 request.channel, request.component, cachePathText);

        std::ifstream ifs(cachePath, std::ios::binary);
        if (ifs) {
            std::string buf((std::istreambuf_iterator<char>(ifs)),
                             std::istreambuf_iterator<char>());
            if (!buf.empty()) {
                out.body = std::move(buf);
                out.ok = true;
                out.fromCache = true;
                return out;
            }
        }
    }

    LOG_WARN("RemoteToml({}/{}): remote downloads disabled and local file not found: {}",
             request.channel, request.component, cachePathText);
    return out;
}

} // namespace RemoteToml
