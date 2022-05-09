#ifndef _SLOGGER_H_
#define _SLOGGER_H_
#include "header.h"
#include <string>

#define DEBUG       spdlog::level::level_enum::debug
#define WARN        spdlog::level::level_enum::warn
#define INFO        spdlog::level::level_enum::info
#define ERR         spdlog::level::level_enum::err
#define TERMINAL    spdlog::level::level_enum::critical

#define LOG(level, msg, args...) spdlog::get("muti_logger")->log(level, msg, args)

namespace SLOG {
void Init(const std::string& filename, const spdlog::level::level_enum& level, const bool& mulThread);
};
#endif