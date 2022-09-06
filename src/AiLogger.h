#ifndef AILOGGER_H
#define AILOGGER_H
#include <string>
#include <memory>
#include "header.h"

#define OFF_LOG     0
#define ERR         1
#define WARN        2
#define INFO        3
#define DEBUG       4
#define CRITICAL    5

enum LOG_LEVEL {
    off  = OFF_LOG,
    err  = ERR,
    warn = WARN,
    info = INFO,
    debug = DEBUG,
    critiacal = CRITICAL
};

class AiLogger {
public:
    ~AiLogger();
    static AiLogger* getLogger() {
        if (log_ptr == nullptr) {
            log_ptr = new AiLogger();
        }
        return log_ptr;
    }

    void Init(std::string &logname, std::string &logpath, std::string &loglevel);

    void Init(std::string &&logname, std::string &&logpath, std::string &&loglevel);

    bool setLevel(std::string &level);

    bool isOff();

    bool isErrEnable();

    bool isWarnEnable();

    bool isInfoEnable();

    bool isDebugEnable();

    bool isCriticalEnable();

    template<typename... Args>
    void error(spdlog::source_loc &loc, std::uint64_t &errorcode, std::string &traceid, std::string &msg, Args &...args);

    template<typename... Args>
    void error(spdlog::source_loc &&loc, std::uint64_t &&errorcode, std::string &&traceid, std::string &&msg, Args &...args);

    template<typename... Args>
    void warn(spdlog::source_loc &loc, std::string &traceid, std::string &msg, Args &...args);

    template<typename... Args>
    void warn(spdlog::source_loc &&loc, std::string &&traceid, std::string &&msg, Args &...args);

    template<typename... Args>
    void info(spdlog::source_loc& loc, std::string &traceid, std::string &msg,  Args &...args);

    template<typename... Args>
    void info(spdlog::source_loc &&loc, std::string &&traceid, std::string &&msg, Args &...args);

    template<typename... Args>
    void debug(spdlog::source_loc &loc, std::string &traceid, std::string &msg,  Args &...args);

    template<typename... Args>
    void debug(spdlog::source_loc &&loc, std::string &&traceid, std::string &&msg, Args &...args);

    template<typename... Args>
    void critical(spdlog::source_loc &loc, std::string &traceid, std::string &msg,  Args &...args);

    template<typename... Args>
    void critical(spdlog::source_loc &&loc, std::string &&traceid, std::string &&msg, Args &...args);

private:
    AiLogger();
    AiLogger(AiLogger&)=delete;
    AiLogger& operator=(const AiLogger)=delete;

    void setErr();

    void setWarn();

    void setInfo();

    void setDebug();

    void setCritical();

    std::string to_json(std::string& json);

    std::string _logbasepath;

    LOG_LEVEL _level;
    
    static  AiLogger* log_ptr;
};


template<typename... Args>
void AiLogger::error(spdlog::source_loc& loc, std::uint64_t &errorcode, std::string &traceid, std::string &msg, Args &...args) {
    if(!isErrEnable()) {
        return;
    }
    std::string message = traceid + ":[AiLogger][" + std::to_string(errorcode) + "] " + to_json(msg);
    spdlog::get("err_log")->log(loc, spdlog::level::err, message, args...);
}

template<typename... Args>
void AiLogger::error(spdlog::source_loc &&loc, std::uint64_t &&errorcode, std::string &&traceid, std::string &&msg, Args &...args) {
    AiLogger::error(loc, errorcode, traceid, msg, args...);
}

template<typename... Args>
void AiLogger::warn(spdlog::source_loc& loc, std::string &traceid, std::string &msg, Args &...args) {
    if(!isWarnEnable()) {
        return;
    }
    std::string message = traceid + ":[AiLogger]" + to_json(msg);
    spdlog::get("warn_log")->log(loc, spdlog::level::warn, message, args...);
}

template<typename... Args>
void AiLogger::warn(spdlog::source_loc &&loc, std::string &&traceid, std::string &&msg, Args &...args) {
    AiLogger::warn(loc, traceid, msg, args...);
}

template<typename... Args>
void AiLogger::info(spdlog::source_loc& loc, std::string &traceid, std::string &msg,  Args &...args) {
    if(!isInfoEnable()) {
        return;
    }
    std::string message = traceid + ":[AiLogger]" + to_json(msg);
    spdlog::get("info_log")->log(loc, spdlog::level::info, message, args...);
}

template<typename... Args>
void AiLogger::info(spdlog::source_loc &&loc, std::string &&traceid, std::string &&msg, Args &...args) {
    AiLogger::info(loc, traceid, msg, args...);
}

template<typename... Args>
void AiLogger::debug(spdlog::source_loc& loc, std::string &traceid, std::string &msg,  Args &...args) {
    if(!isDebugEnable()) {
        return;
    }
    std::string message = traceid + ":[AiLogger]" + to_json(msg);
    spdlog::get("debug_log")->log(loc, spdlog::level::debug, message, args...);
}

template<typename... Args>
void AiLogger::debug(spdlog::source_loc &&loc, std::string &&traceid, std::string &&msg, Args &...args) {
    AiLogger::debug(loc, traceid, msg, args...);
}


template<typename... Args>
void AiLogger::critical(spdlog::source_loc& loc, std::string &traceid, std::string &msg,  Args &...args) {
    if(!isCriticalEnable()) {
        return;
    }
    std::string message = traceid + ":[AiLogger]" + to_json(msg);
    spdlog::get("critical_log")->log(loc, spdlog::level::critical, message, args...);
}

template<typename... Args>
void AiLogger::critical(spdlog::source_loc &&loc, std::string &&traceid, std::string &&msg, Args &...args) {
    AiLogger::critical(loc, traceid, msg, args...);
}

#define TRACE spdlog::source_loc(__FILE__, __LINE__, SPDLOG_FUNCTION)
#define LOG_ERR(errcode, traceid, msg, args...) \
    AiLogger::getLogger()->error(TRACE, errcode, traceid, msg, ##args)
#define LOG_WARN(traceid, msg, args...) \
    AiLogger::getLogger()->warn(TRACE, traceid, msg, ##args)
#define LOG_INFO(traceid, msg, args...) \
    AiLogger::getLogger()->info(TRACE, traceid, msg, ##args)
#define LOG_DEBUG(traceid, msg, args...) \
    AiLogger::getLogger()->debug(TRACE, traceid, msg, ##args)
#define LOG_CRI(traceid, msg, args...) \
    AiLogger::getLogger()->critical(TRACE, traceid, msg, ##args)

#endif