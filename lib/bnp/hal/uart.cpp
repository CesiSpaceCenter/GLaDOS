#include "uart.h"
#include "bnp.h"

/*#if UART1_ENABLE
inline HardwareSerial bnp::uart1(PIN_UART1_TX, PIN_UART1_RX);
#endif

#if UART2_ENABLE
inline HardwareSerial bnp::uart2(PIN_UART2_TX, PIN_UART2_RX);
#endif

#if UART3_ENABLE
inline HardwareSerial bnp::uart3(PIN_UART3_TX, PIN_UART3_RX);
#endif

#if UART4_ENABLE
inline HardwareSerial bnp::uart4(PIN_UART4_TX, PIN_UART4_RX);
#endif

#if UART5_ENABLE
inline HardwareSerial bnp::uart5(PIN_UART5_TX, PIN_UART5_RX);
#endif

#if UART6_ENABLE
inline HardwareSerial bnp::uart6(PIN_UART6_TX, PIN_UART6_RX);
#endif*/

void bnp::UARTManager::init() {
    // UARTs will be initialized by user code/libraries

    Serial.print("uart: enabled UART buses: ");

    #if UART1_ENABLE
    Serial.print("UART1 ");
    #endif

    #if UART2_ENABLE
    Serial.print("UART2 ");
    #endif
    
    #if UART3_ENABLE
    Serial.print("UART3 ");
    #endif

    #if UART4_ENABLE
    Serial.print("UART4 ");
    #endif

    #if UART5_ENABLE
    Serial.print("UART5 ");
    #endif

    #if UART6_ENABLE
    Serial.print("UART6 ");
    #endif

    Serial.println("");
}

HardwareSerial* bnp::UARTManager::operator[](int index) {
    if (index < 1 || index > bnp::num_uart_buses) {
        String error_msg = "UART bus index out of range " + String(index);
        bnp::panic(error_msg.c_str());
        return nullptr;
    }
    HardwareSerial* instance = this->uart_instances[index-1];
    if (instance == nullptr) {
        String error_msg = "tried to use invalid UART bus " + String(index);
        bnp::panic(error_msg.c_str());
        return nullptr;
    }
    return instance;
}