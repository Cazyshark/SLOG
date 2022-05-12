#include "slogger.h"
#include <iostream>

int main() {
    SLOG::Init("logger", WARN, false);
    for (size_t i = 0; i < 1000000; i++) {
        LOG(WARN, "test mulit out");
    }
    return 0;
}