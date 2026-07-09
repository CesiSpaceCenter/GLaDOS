#include "cmd.h"

#include <bnp.h>
#include <log.h>
#include <freertos/FreeRTOS_ps.h>

void racer::cmd::task(void* arg) {
  UNUSED(arg);
  while (true) {
    bnp::sleep(100);
    if (bnp::log::mutex == NULL)
      continue;

    if (xSemaphoreTake(bnp::log::mutex, 100) == pdTRUE) {
      std::string input = "";
      while (Serial.available()) {
        char input_char = Serial.read();
        input += input_char;
      }

      xSemaphoreGive(bnp::log::mutex);

      if (!input.empty()) {
        int spaceIndex = input.find_last_of(' ');

        std::string actionStr;
        int value = 0;
        if (spaceIndex != -1 && std::isdigit(input.at(spaceIndex + 1))) {
          actionStr = input.substr(0, spaceIndex);
          std::string valueStr = input.substr(spaceIndex + 1);
          value = std::stoi(valueStr);
        } else {
          actionStr = input;
        }

        if (actionStr == "reset" || actionStr == "r") {
          bnp::reset();
        } else if (actionStr == "bootloader" || actionStr == "b") {
          bnp::jump_to_bootloader();
        } else if (actionStr == "servo on") {
          //servoPower.on();
        } else if (actionStr == "servo off") {
          //servoPower.off();
        } else if (actionStr == "cam on") {
          //cameraPower.on();
        } else if (actionStr == "cam off") {
          //cameraPower.off();
        } else if (actionStr == "servo set") {
          //servo_move(value);
        } else if (actionStr == "ps") {
          freertos_ps(Serial);
        } else {
          BNP_LOG("unknown command {}", actionStr);
        }
      }
    }
  }
}
