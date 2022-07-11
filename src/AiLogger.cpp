#include <iostream>
#include "header.h"
#include "AiLogger.h"

//init static ptr
AiLogger* AiLogger::log_ptr(nullptr);

void AiLogger::Init(std::string &logname, std::string &logpath, std::string &loglevel) {
    try {
        this->_logbasepath = logpath + '/' + logname;
        setLevel(loglevel);
        spdlog::init_thread_pool(1024 * 1024 * 64, 10);
        if(isErrEnable())       setErr();
        if(isWarnEnable())      setWarn();
        if(isInfoEnable())      setInfo();
        if(isDebugEnable())     setDebug();
        if(isCriticalEnable())  setCritical();
    } catch(const spdlog::spdlog_ex &e) {
        std::cout << "AiLogger Init Failed : "  << e.what() << std::endl;
    }
}

void AiLogger::Init(std::string &&logname, std::string &&logpath, std::string &&loglevel) {
    Init(logname, logpath, loglevel);
}

bool AiLogger::setLevel(std::string &level) {
    if(level.compare("err") == 0) {
        this->_level = LOG_LEVEL::err;
        return true;
    }else if(level.compare("warn") == 0) {
        this->_level = LOG_LEVEL::warn;
        return true;
    }else if(level.compare("info") == 0) {
        this->_level = LOG_LEVEL::info;
        return true;
    }else if(level.compare("debug") == 0) {
        this->_level = LOG_LEVEL::debug;
        return true;
    }else if(level.compare("critical") == 0){
        this->_level = LOG_LEVEL::critiacal;
        return true;
    }
    return false;
}

bool AiLogger::isOff() {
    return this->_level >= OFF_LOG;
}

bool AiLogger::isErrEnable() {
    return this->_level >= ERR;
}

bool AiLogger::isWarnEnable() {
    return this->_level >= WARN;
}

bool AiLogger::isInfoEnable() {
    return this->_level >= INFO;
}

bool AiLogger::isDebugEnable() {
    return this->_level >= DEBUG;
}

bool AiLogger::isCriticalEnable() {
    return this->_level >= CRITICAL;
}

AiLogger::AiLogger(){
}

void AiLogger::setErr() {
    std::string logname = this->_logbasepath + "_err.log";
    auto err_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt> (logname);
    auto err_log = std::make_shared<spdlog::async_logger> ("err_log", err_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    err_log->set_level(spdlog::level::level_enum::err);
    err_log->set_pattern("%Y-%m-%d %H:%M:%S.%e %t %l %s[%#]-%v");
    err_log->should_backtrace();
    err_log->enable_backtrace(50);
    spdlog::register_logger(err_log);
}

void AiLogger::setWarn() {
    std::string logname = this->_logbasepath + "_warn.log";
    auto warn_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt> (logname);
    auto warn_log = std::make_shared<spdlog::async_logger> ("warn_log", warn_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    warn_log->set_level(spdlog::level::level_enum::warn);
    warn_log->set_pattern("%Y-%m-%d %H:%M:%S.%e %t %l %s[%#]-%v");
    warn_log->should_backtrace();
    warn_log->enable_backtrace(50);
    spdlog::register_logger(warn_log);
}

void AiLogger::setInfo() {
    std::string logname = this->_logbasepath + "_info.log";
    auto info_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt> (logname);
    auto info_log = std::make_shared<spdlog::async_logger> ("info_log", info_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    info_log->set_level(spdlog::level::level_enum::info);
    info_log->set_pattern("%Y-%m-%d %H:%M:%S.%e %t %l %s[%#]-%v");
    info_log->should_backtrace();
    info_log->enable_backtrace(50);
    spdlog::register_logger(info_log);
}

void AiLogger::setDebug() {
    std::string logname = this->_logbasepath + "_debug.log";
    auto debug_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt> (logname);
    auto debug_log = std::make_shared<spdlog::async_logger> ("debug_log", debug_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    debug_log->set_level(spdlog::level::level_enum::debug);
    debug_log->set_pattern("%Y-%m-%d %H:%M:%S.%e %t %l %s[%#]-%v");
    debug_log->should_backtrace();
    debug_log->enable_backtrace(50);
    spdlog::register_logger(debug_log);
}

void AiLogger::setCritical() {
    std::string logname = this->_logbasepath + "_critical.log";
    auto cri_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt> (logname);
    auto cri_log = std::make_shared<spdlog::async_logger> ("cri_log", cri_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    cri_log->set_level(spdlog::level::level_enum::critical);
    cri_log->set_pattern("%Y-%m-%d %H:%M:%S.%e %t %l %s[%#]-%v");
    cri_log->should_backtrace();
    cri_log->enable_backtrace(50);
    spdlog::register_logger(cri_log);
}

std::string AiLogger::to_json(std::string& json) {
    std::string result = "{{\"message\":\"" + json + "\", \"exception\": \"\"}}";
    return result;
}