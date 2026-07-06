#include "bnp.h"
#include "hal/board.h"
#include <Arduino.h>

void bnp::panic(const char* message) {
    digitalWrite(PIN_LED, LOW);
    while (true) {
        if (Serial.available()) {
            bnp::reset();
        }
        Serial.println("---- PANIC ----");
        Serial.println(message);
        delay(1000);
    }
}

void bnp::reset() {
    NVIC_SystemReset();
}

void bnp::init() {
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);
    Serial.begin(9600);
    Serial.println("bnp init");
    bnp::i2c.init();
    bnp::spi.init();
    bnp::uart.init();
}

// from https://gist.github.com/gonzabrusco/fd47e89e4c6fb302fc54b83637a3a101

#define BOOTLOADER_ADDR 0x1FF00000
struct bootloader_vectable__t {
    uint32_t stack_pointer;
    void (*reset_handler)(void);
};
#define BOOTLOADER_VECTOR_TABLE	((struct bootloader_vectable__t *)BOOTLOADER_ADDR)
void bnp::jump_to_bootloader() {
    // Deinit HAL and Clocks
    HAL_DeInit();
    HAL_RCC_DeInit();

    // Disable all interrupts
    __disable_irq();

    // Disable Systick
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

    // Disable interrupts and clear pending ones
    for (size_t i = 0; i < sizeof(NVIC->ICER)/sizeof(NVIC->ICER[0]); i++) {
        NVIC->ICER[i]=0xFFFFFFFF;
        NVIC->ICPR[i]=0xFFFFFFFF;
    }

    // Re-enable interrupts
    __enable_irq();

    // Map Bootloader (system flash) memory to 0x00000000. This is STM32 family dependant.
    //__HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();

    // Set embedded bootloader vector table base offset
    WRITE_REG(SCB->VTOR, SCB_VTOR_TBLOFF_Msk & 0x00000000);

    // Switch to Main Stack Pointer (in case it was using the Process Stack Pointer)
    __set_CONTROL(0);

    // Instruction synchronization barrier
    __ISB();

    // Set Main Stack Pointer to the Bootloader defined value.
    __set_MSP(BOOTLOADER_VECTOR_TABLE->stack_pointer);

    __DSB(); // Data synchronization barrier
    __ISB(); // Instruction synchronization barrier

    // Jump to Bootloader Reset Handler
    BOOTLOADER_VECTOR_TABLE->reset_handler();

    // The next instructions will not be reached
    while (1){}
}

void bnp::sleep(long msecs) {
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        vTaskDelay((msecs * configTICK_RATE_HZ) / 1000L);
    } else {
        delay(msecs);
    }
}

void bnp::create_task(TaskFunction_t func, UBaseType_t priority, const char* name) {
    portBASE_TYPE s = xTaskCreate(func, name, configMINIMAL_STACK_SIZE, NULL, priority, NULL);
    if (s != pdPASS) bnp::panic(strcat((char*)"Could not init task ", name));
}
