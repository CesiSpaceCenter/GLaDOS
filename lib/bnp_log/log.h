#ifndef BNP_LOG_H
#define BNP_LOG_H

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <semphr.h>
#include <fmt.h>
#include <string>

namespace bnp::log {
    inline SemaphoreHandle_t mutex;
    void init();

    template <typename... Args>
    void log(const char *filename, const char *function, int line, const char *format, Args &&...args) {
        if (bnp::log::mutex == NULL) return;

        if (xSemaphoreTake(bnp::log::mutex, 100) == pdTRUE) {
            std::string header = fmt::format(
                "t+{:.2f} {}:{}:{}\t>> ", millis() / 1000.0, filename, function, line);
            Serial.print(header.c_str());

            std::string body = fmt::format(format, std::forward<Args>(args)...);
            Serial.println(body.c_str());

            xSemaphoreGive(bnp::log::mutex);
        }
    }
}

#define BNP_LOG(format, ...) bnp::log::log(__FILE_NAME__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__)

#endif

