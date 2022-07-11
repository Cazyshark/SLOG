#include <AiLogger.h>
#include <string>

int main() {
    AiLogger *log = AiLogger::getLogger();
    log->Init("test", "./", "debug");
    LOG_ERR(12, 123, "test log {}", "123123");
    return 0;
}
