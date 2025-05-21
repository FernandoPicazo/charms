#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

#define LOG_INFO(msg, ...) \
    do { \
        time_t now = time(NULL); \
        char time_str[20]; \
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now)); \
        fprintf(stderr, "[%s] [INFO] %s:%d: " msg "\n", time_str, __BASE_FILE__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#define LOG_ERROR(msg, ...) \
    do { \
        time_t now = time(NULL); \
        char time_str[20]; \
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now)); \
        fprintf(stderr, "[%s] [ERROR] %s:%d: " msg "\n", time_str, __BASE_FILE__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#define LOG_PERROR(msg, ...) \
    do { \
        time_t now = time(NULL); \
        char time_str[20]; \
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now)); \
        fprintf(stderr, "[%s] [PERROR] %s:%d: " msg "\n", time_str, __BASE_FILE__, __LINE__, ##__VA_ARGS__); \
        perror("    System error"); \
    } while (0)
    #endif // LOGGER_H