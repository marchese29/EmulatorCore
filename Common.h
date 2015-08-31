//
// Created by Daniel Marchese on 8/29/15.
//

#ifndef EMULATORCORE_COMMON_H
#define EMULATORCORE_COMMON_H

#include <cstdint>
#include <cstdio>
#include <cstdarg>

#define Log(msg, ...) (log_msg(msg, ##__VA_ARGS__))

inline void log_msg(const char* const msg, ...) {
    static int count = 1;
    char szBuf[512];

    va_list args;
    va_start(args, msg);
    vsprintf(szBuf, msg, args);
    va_end(args);

    printf("%d: %s\n", count, szBuf);

    count++;
}

#endif //EMULATORCORE_COMMON_H
