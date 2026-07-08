#include "uart.h"
#include "bnp.h"
#include "log.h"
#include <fmt.h>

void bnp::UARTManager::init() {
    // UARTs will be initialized by user code/libraries

    BNP_LOG(
        "enabled UART buses: {}{}{}{}{}{}",
        (UART1_ENABLE ? "UART1 ": ""), (UART2_ENABLE ? "UART2 ": ""), (UART3_ENABLE ? "UART3 ": ""),
        (UART4_ENABLE ? "UART4 ": ""), (UART5_ENABLE ? "UART5 ": ""), (UART6_ENABLE ? "UART6 ": "")
    );
}

HardwareSerial* bnp::UARTManager::operator[](int index) {
    if (index < 1 || index > bnp::num_uart_buses) {
        bnp::panic(fmt::format("UART bus index out of range {}", index));
        return nullptr;
    }
    HardwareSerial* instance = this->uart_instances[index-1];
    if (instance == nullptr) {
        bnp::panic(fmt::format("tried to use invalid UART bus {}", index));
        return nullptr;
    }
    return instance;
}
