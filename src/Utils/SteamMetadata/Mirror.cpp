#include "Mirror.h"

#include "OSTPlatform/include/Http.h"
#include "Utils/Logging/Log.h"

#include <iterator>
#include <string>

namespace Mirror {

std::optional<std::string> Fetch(std::string_view relPath)
{
    LOG_INFO("Mirror: Remote fetching disabled");
    return std::nullopt;
}

} // namespace Mirror
