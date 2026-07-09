#ifndef BNP_UART_H
#define BNP_UART_H

#include <HardwareSerial.h>

namespace bnp {
    const int num_uart_buses = 6;
    /*#if UART1_ENABLE
    exter, HardwareSerial uart1;
    #endif

    #if UART2_ENABLE
    extern HardwareSerial uart2;
    #endif

    #if UART3_ENABLE
    extern HardwareSerial uart3;
    #endif

    #if UART4_ENABLE
    extern HardwareSerial uart4;
    #endif

    #if UART5_ENABLE
    extern HardwareSerial uart5;
    #endif

    #if UART6_ENABLE
    extern HardwareSerial uart6;
    #endif*/
    #if UART1_ENABLE
    inline HardwareSerial uart1(PIN_UART1_TX, PIN_UART1_RX);
    #endif

    #if UART2_ENABLE
    inline HardwareSerial uart2(PIN_UART2_TX, PIN_UART2_RX);
    #endif

    #if UART3_ENABLE
    inline HardwareSerial uart3(PIN_UART3_TX, PIN_UART3_RX);
    #endif

    #if UART4_ENABLE
    inline HardwareSerial uart4(PIN_UART4_TX, PIN_UART4_RX);
    #endif

    #if UART5_ENABLE
    inline HardwareSerial uart5(PIN_UART5_TX, PIN_UART5_RX);
    #endif

    #if UART6_ENABLE
    inline HardwareSerial uart6(PIN_UART6_TX, PIN_UART6_RX);
    #endif

    class UARTManager {
    public:
        void init();
        HardwareSerial* operator[](int index);

    private:
        HardwareSerial* uart_instances[num_uart_buses] = {
            #if UART1_ENABLE
            &uart1,
            #else
            nullptr,
            #endif

            #if UART2_ENABLE
            &uart2,
            #else
            nullptr,
            #endif

            #if UART3_ENABLE
            &uart3,
            #else
            nullptr,
            #endif

            #if UART4_ENABLE
            &uart4,
            #else
            nullptr,
            #endif

            #if UART5_ENABLE
            &uart5,
            #else
            nullptr,
            #endif

            #if UART6_ENABLE
            &uart6,
            #else
            nullptr,
            #endif
        };
    };
};

#endif
