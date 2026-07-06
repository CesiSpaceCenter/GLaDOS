/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <Arduino.h>

#define ARCH_STM32

#define PIN_BEEPER $BEEPER_PIN
#define PIN_S1 $MOTOR1_PIN
#define PIN_S2 $MOTOR2_PIN
#define PIN_S3 $MOTOR3_PIN
#define PIN_S4 $MOTOR4_PIN
#define PIN_S5 $MOTOR5_PIN
#define PIN_S6 $MOTOR6_PIN
#define PIN_S7 $MOTOR7_PIN
#define PIN_S8 $MOTOR8_PIN
#define PIN_LED_STRIP $LED_STRIP_PIN
#define PIN_LED $LED0_PIN


#define UART1_ENABLE false
#define PIN_UART1_TX $UART1_TX_PIN
#define PIN_UART1_RX $UART1_RX_PIN

#define UART2_ENABLE false
#define PIN_UART2_TX $UART2_TX_PIN
#define PIN_UART2_RX $UART2_RX_PIN

#define UART3_ENABLE false
#define PIN_UART3_TX $UART3_TX_PIN
#define PIN_UART3_RX $UART3_RX_PIN

#define UART4_ENABLE false
#define PIN_UART4_TX $UART4_TX_PIN
#define PIN_UART4_RX $UART4_RX_PIN

#define UART5_ENABLE false
#define PIN_UART5_TX $UART5_TX_PIN
#define PIN_UART5_RX $UART5_RX_PIN

#define UART6_ENABLE false
#define PIN_UART6_TX $UART6_TX_PIN
#define PIN_UART6_RX $UART6_RX_PIN


#define I2C1_ENABLE false
#define PIN_I2C1_SCL $I2C1_SCL_PIN
#define PIN_I2C1_SDA $I2C1_SDA_PIN

#define I2C2_ENABLE false
#define PIN_I2C2_SCL $I2C2_SCL_PIN
#define PIN_I2C2_SDA $I2C2_SDA_PIN

#define I2C3_ENABLE false
#define PIN_I2C3_SCL $I2C3_SCL_PIN
#define PIN_I2C3_SDA $I2C3_SDA_PIN


#define SPI1_ENABLE false
#define PIN_SPI1_MISO $SPI1_SDI_PIN
#define PIN_SPI1_MOSI $SPI1_SDO_PIN
#define PIN_SPI1_SCK $SPI1_SCK_PIN

#define SPI2_ENABLE false
#define PIN_SPI2_MISO $SPI2_SDI_PIN
#define PIN_SPI2_MOSI $SPI2_SDO_PIN
#define PIN_SPI2_SCK $SPI2_SCK_PIN

#define SPI3_ENABLE false
#define PIN_SPI3_MISO $SPI3_SDI_PIN
#define PIN_SPI3_MOSI $SPI3_SDO_PIN
#define PIN_SPI3_SCK $SPI3_SCK_PIN


#define GYRO_SPI $GYRO_1_SPI_INSTANCE
#define PIN_GYRO_1_EXTI $GYRO_1_EXTI_PIN
#define PIN_GYRO_2_EXTI $GYRO_2_EXTI_PIN
#define PIN_GYRO_1_CS $GYRO_1_CS_PIN
#define PIN_GYRO_2_CS $GYRO_2_CS_PIN

#define FLASH_SPI $FLASH_SPI_INSTANCE
#define PIN_FLASH_CS $FLASH_CS_PIN
#define BAR_I2C_INSTANCE $BARO_I2C_INSTANCE

#define PIN_ADC_VBAT $ADC_VBAT_PIN
#define PIN_ADC_RSSI $ADC_RSSI_PIN
#define PIN_ADC_CURR $ADC_CURR_PIN

#define PIN_IO1 $PINIO1_PIN
#define PIN_IO3 $PINIO2_PIN
#define PIN_IO2 $PINIO3_PIN

#define GYRO_1_ALIGN $GYRO_1_ALIGN
#define GYRO_2_ALIGN $GYRO_2_ALIGN
