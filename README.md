# GLaDOS - RACER embedded software (ACU & SCU)

This repo contains the embedded source code for the **RACER** experimental student rocket, 

## Avionics architecture overview

As told by the CSpace specification rules, the avionics hardware is split in two:

1. **"Experiment" (ACU - Attitude Control Unit) :** 
   Manages the active roll control, telemetry, camera power, screen.
2. **Sequencer (SCU - Sequence Control Unit) :** 
   Manages the rocket's vital functions: global states, timer, parachute deployment.

Those systems are electrically isolated, the only communication is for the SCU to tell its state to the ACU via an optocoupler.

## Tech stack

- **Hardware :** The two systems are based on STM32 FPV drone flight controllers (currently [Flywoo Goku F722 Pro V2](https://flywoo.net/products/goku-f722-pro-v2-30x30-flight-controller), but can theorically be swapped for any equivalent FC).
- **Software :** C++ using the Arduino Framework, using FreeRTOS for multi-tasking.
- **Dev environment :** VSCode or VSCodium, with clangd or Microsoft C/C++ tools with PlatformIO

## Project structure

```text
├── include/
│   ├── acu/bnp_config.h  # ACU-specific config
│   ├── scu/bnp_config.h  # SCU-specific config
│   └── boards/           # Hardware board pinout configurations and generation script
│
├── lib/
│   └── bnp/              # General purpose library (tools like  logging, error handling, etc.)
│       ├── freertos/     # FreeRTOS abstraction functions (task creations, process management)
│       └── hal/          # Hardware abstraction (I/O digital/analog, PWM, UART, SPI, I2C)
│
├── src/                  # Main program
│   ├── ahrs/             # Vehicle attitude estimation
│   ├── blackbox/         # Logs & data serialization and storage on flash chip
│   ├── cmd/              # Command line interface (via Serial) for debug
│   ├── led/              # LEDs control depending on the vehicle state
│   ├── optocom/          # Physical communication link between ACU and SCU
│   ├── screen/           # OLED screen management of the ACU
│   ├── sensors/          # Sensors (barometer, IMU, GNSS, etc)
│   ├── servo/            # Servo control (roll and parachute deployment system)
│   ├── tm/               # Telemetry
│   ├── state.h           # Vehicle global state machine, shared between ACU & SCU
│   └── main.cpp, acu.h, scu.h  # Entry points, main programs
```
