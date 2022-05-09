#include "slogger.h"
#include <thread>

namespace SLOG {

void Init(const std::string& filename, const spdlog::level::level_enum& level, const bool& mulThread) {
    std::int8_t thread_num = std::max(std::thread::hardware_concurrency(), (unsigned int) 1);
    spdlog::init_thread_pool(1024 * 1024 * 64, mulThread ? thread_num : 1);
    
    //auto console_out = std::make_shared<spdlog::sinks::stdout_color_sink_mt> ();

    auto file_warn = std::make_shared<spdlog::sinks::basic_file_sink_mt> (filename + "_warn.log");
    file_warn->set_level(spdlog::level::warn);

    auto file_debug = std::make_shared<spdlog::sinks::basic_file_sink_mt> (filename + "_debug.log");
    file_debug->set_level(spdlog::level::debug);

    auto file_err = std::make_shared<spdlog::sinks::basic_file_sink_mt> (filename + "_err.log");
    file_err->set_level(spdlog::level::err);

    auto file_info = std::make_shared<spdlog::sinks::basic_file_sink_mt> (filename + "_info.log");
    file_info->set_level(spdlog::level::info);
    std::vector<spdlog::sink_ptr> sinks {file_info, file_err, file_warn, file_debug};
    auto logger = std::make_shared<spdlog::async_logger> ("muti_logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    logger->set_level(level);
    logger->set_pattern("[%Y-%m-%d %H:%M:%S:%e] [thread %t] [%l]%v");
    spdlog::register_logger(logger);
}


};