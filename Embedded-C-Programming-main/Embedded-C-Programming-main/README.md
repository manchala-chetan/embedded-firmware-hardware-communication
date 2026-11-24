# Embedded C Programming — STM32F411 Bare-Metal Firmware & Host-Side C Exercises

[![Language](https://img.shields.io/badge/Language-C-00599C?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![MCU](https://img.shields.io/badge/MCU-STM32F411CEU6-03234B?logo=stmicroelectronics&logoColor=white)](https://www.st.com/en/microcontrollers-microprocessors/stm32f411ce.html)
[![Core](https://img.shields.io/badge/Core-ARM%20Cortex--M4-informational)](https://developer.arm.com/Processors/Cortex-M4)
[![IDE](https://img.shields.io/badge/IDE-STM32CubeIDE-blue)](https://www.st.com/en/development-tools/stm32cubeide.html)
[![Style](https://img.shields.io/badge/Programming-Bare--Metal%20%2F%20Register--Level-critical)]()
[![License](https://img.shields.io/badge/License-MIT-green.svg)](#license)

A structured, ground-up collection of **C programming exercises** and **STM32F411CEU6 (ARM Cortex‑M4) firmware projects**, built without any HAL/vendor abstraction layer. The goal of this repository is to demonstrate a solid, first-principles understanding of the C language and of how software talks directly to microcontroller hardware — from a single `while(1)` LED blink to structured, register-mapped, macro-driven peripheral drivers.

This repository is part of my preparation and portfolio for an **Embedded Software Engineering internship**, and is organized to make the underlying engineering progression (not just "the code that works") visible to a reviewer.

---

## Table of Contents

- [Why This Repository Exists](#why-this-repository-exists)
- [Repository Structure](#repository-structure)
- [Part 1 — `target/`: Bare-Metal STM32F411 Firmware](#part-1--target-bare-metal-stm32f411-firmware)
  - [Hardware & Toolchain](#hardware--toolchain)
  - [Design Philosophy: Registers Before HAL](#design-philosophy-registers-before-hal)
  - [Firmware Projects](#firmware-projects)
  - [Anatomy of a `target/` Project](#anatomy-of-a-target-project)
  - [Building & Flashing](#building--flashing)
- [Part 2 — `host/`: C Language Fundamentals](#part-2--host-c-language-fundamentals)
  - [Host Exercises](#host-exercises)
- [Skills Demonstrated](#skills-demonstrated)
- [Roadmap](#roadmap)
- [Getting Started](#getting-started)
- [Author](#author)
- [License](#license)

---

## Why This Repository Exists

Most introductory embedded portfolios rely on `HAL_GPIO_WritePin()` and vendor-generated boilerplate, which can hide whether an author actually understands **what happens between C code and silicon**. This repository takes the opposite approach:

- Every peripheral is driven by **directly dereferencing memory-mapped register addresses** taken from the STM32F411 reference manual (RM0383) — no `stm32f4xx_hal.h`.
- The same handful of GPIO/RCC registers are revisited multiple times across projects, each time with a **more disciplined abstraction** (raw pointers → bit-shifted masks → packed bit-field structs → named macros), mirroring how real embedded codebases evolve from a proof-of-concept into maintainable driver code.
- A parallel `host/` track builds the underlying **C fundamentals** (pointers, bitwise operators, structs/unions, the preprocessor) that the firmware code depends on, using plain GCC/STM32CubeIDE C projects that run on a PC instead of a microcontroller.

---

## Repository Structure

```
Embedded-C-Programming/
├── target/                          # STM32F411CEU6 bare-metal firmware (ARM Cortex-M4)
│   ├── 004_led_on/                  # Register-level GPIO output, clock enable
│   ├── 005_led_toggle/              # + software delay loop, blinking LED
│   ├── 006_GPIO_Button_LED/         # + GPIO input, pull-up config, polling
│   ├── 010_led_toggle_bitfields/    # Refactor: registers modeled as C bit-field structs
│   ├── 011_keypad_interfacing/      # 4x4 matrix keypad scan + semihosted printf
│   └── 013_led_toggle_with_macros/  # Refactor: address/constant macros, header split
│
├── host/                            # PC-side C fundamentals (STM32CubeIDE / GCC, no target hardware)
│   ├── bitwiseOperators/            # Bit set/clear/toggle exercises
│   ├── conditions/                  # if/else control-flow exercises
│   ├── definePreProcessor/          # #define, macro exercises
│   ├── floatNumbers/                # Floating-point arithmetic exercises
│   ├── loops/                       # for / while loop exercises
│   ├── strings/                     # C-string handling
│   ├── struct & union/              # struct, pointer-to-struct, union bit extraction
│   ├── studentsManagement/          # CRUD console app (arrays of structs, input validation)
│   └── geometricAreaCalculator/     # switch/case + multi-file (.c/.h) organization
│
└── .gitignore
```

Each leaf folder is a **self-contained STM32CubeIDE (Eclipse CDT) project**, complete with its own `.project` / `.cproject` metadata, so any single exercise can be imported and built in isolation.

---

## Part 1 — `target/`: Bare-Metal STM32F411 Firmware

### Hardware & Toolchain

| Component | Detail |
|---|---|
| **MCU** | STM32F411CEU6 — ARM Cortex‑M4F, 100 MHz, 512 KB Flash, 128 KB SRAM (commonly found on the "Black Pill" development board) |
| **IDE / Build system** | STM32CubeIDE (Eclipse CDT + `arm-none-eabi-gcc` toolchain, Makefile-based build under the hood) |
| **Debug interface** | SWD, via ST-Link (per-project `*.launch` / `*.cfg` OpenOCD debug configurations) |
| **Runtime** | Auto-generated CMSIS startup assembly (`startup_stm32f411ceux.s`) + Newlib syscall stubs (`syscalls.c`, `sysmem.c`) — no HAL, no CMSIS peripheral driver layer |
| **I/O for early debugging** | ARM semihosting (`initialise_monitor_handles()` + `printf`) used before any UART driver exists |

### Design Philosophy: Registers Before HAL

Every firmware project in `target/` manipulates peripherals by writing to their **absolute memory-mapped addresses**, exactly as documented in the STM32F4 reference manual:

```c
volatile uint32_t *const pClkCtrlReg  = (uint32_t*) 0x40023830; // RCC_AHB1ENR
volatile uint32_t *const pPortCModeReg = (uint32_t*) 0x40020800; // GPIOC_MODER
volatile uint32_t *const pPortCOutReg  = (uint32_t*) 0x40020814; // GPIOC_ODR

*pClkCtrlReg   |= (1 << 2);        // enable GPIOC clock (AHB1ENR bit 2)
*pPortCModeReg &= ~(3 << 26);      // clear MODER13[1:0]
*pPortCModeReg |=  (1 << 26);      // set PC13 as general-purpose output
```

This intentionally exposes the exact sequence every HAL call hides underneath: **enable the peripheral clock → configure the pin mode → drive the data register** — and forces correct use of `volatile` to prevent the compiler from optimizing away hardware-facing reads/writes.

### Firmware Projects

| # | Project | What It Adds | Concepts Demonstrated |
|---|---|---|---|
| 004 | [`004_led_on`](target/004_led_on) | Turns the on-board LED (PC13) on via direct register writes | RCC clock gating, GPIO mode configuration, active-low output logic |
| 005 | [`005_led_toggle`](target/005_led_toggle) | Blinks the LED using a software (busy-wait) delay | Custom `SWDelay()`, `while(1)` firmware main loop pattern |
| 006 | [`006_GPIO_Button_LED`](target/006_GPIO_Button_LED) | Reads a push-button on PA0 and drives the LED accordingly | GPIO input mode, internal pull-up configuration, polling-based input |
| 010 | [`010_led_toggle_bitfields`](target/010_led_toggle_bitfields) | Re-implements 005 by overlaying **C bit-field structs** (`RCC_AHB1ENR_t`, `GPIOx_MODE_t`, `GPIOx_ODR_t`) onto the peripheral addresses instead of raw shift/mask operations | Register modeling with `struct { uint32_t field : n; }`, readable field-level register access — the same pattern CMSIS device headers use internally |
| 011 | [`011_keypad_interfacing`](target/011_keypad_interfacing) | Scans a 4×4 matrix keypad (rows as outputs, columns as inputs) and reports the pressed key over semihosted `printf` | Multi-pin GPIO configuration, row/column matrix scanning algorithm, software debouncing via delay, mapping raw scan results to characters |
| 013 | [`013_led_toggle_with_macros`](target/013_led_toggle_with_macros) | Re-implements 010 with all magic numbers replaced by named macros in a dedicated header | `#define`-based register address aliases, separation of hardware definitions (`main.h`) from application logic (`main.c`), foundation of a minimal peripheral-driver style |

> **Progression at a glance:** `004`→`006` establish raw register access; `010`→`013` show the same hardware being wrapped in increasingly maintainable abstractions (bit-fields, then macros) — the natural first step toward writing a real peripheral driver layer.

### Anatomy of a `target/` Project

```
004_led_on/
├── .project / .cproject          # STM32CubeIDE / Eclipse CDT project definition
├── .settings/                    # Toolchain, indexer, and SFR-view settings
├── STM32F411CEUX_FLASH.ld        # Linker script — code/data placed in Flash, .bss/.data in RAM
├── STM32F411CEUX_RAM.ld          # Alternate linker script — full RAM execution (for debugging)
├── Startup/
│   └── startup_stm32f411ceux.s   # Vector table, Reset_Handler, .data/.bss init, branch to main()
├── Src/
│   ├── main.c                    # Application entry point / register-level logic
│   ├── syscalls.c                # Newlib syscall stubs (needed for printf via semihosting)
│   └── sysmem.c                  # Minimal heap (_sbrk) implementation
└── *.launch / *.cfg              # ST-Link/OpenOCD debug launch configuration
```

Understanding and being able to read this project layout — vector table → reset handler → C runtime init → `main()` — reflects the same boot sequence knowledge expected when bringing up firmware on any Cortex‑M part.

### Building & Flashing

1. Install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (bundles the `arm-none-eabi-gcc` toolchain, OpenOCD, and ST-Link drivers).
2. `File → Import → Existing Projects into Workspace`, and select the desired folder under `target/` (e.g. `target/006_GPIO_Button_LED`).
3. Connect an STM32F411-based board (e.g. WeAct "Black Pill") via ST-Link/SWD.
4. Build (`Ctrl+B`) and flash/debug (`F11`) using the included `*.launch` configuration.

Command-line equivalent (headless build), once the toolchain is on `PATH`:

```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft \
  -T STM32F411CEUX_FLASH.ld -nostartfiles \
  Startup/startup_stm32f411ceux.s Src/main.c Src/syscalls.c Src/sysmem.c \
  -o firmware.elf
```

---

## Part 2 — `host/`: C Language Fundamentals

Before (and alongside) writing firmware, this repository builds the C fundamentals that embedded work depends on — compiled and run as ordinary console applications on a PC (still via STM32CubeIDE's generic C/C++ project template), so logic can be verified independent of any hardware.

### Host Exercises

| Category | Projects | Focus |
|---|---|---|
| **Bitwise Operators** | `bitSettingExercise`, `bitClearingExercise`, `bitwiseExercise`, `oddOrEvenWithBitwise` | Setting/clearing/testing individual bits — the exact operations later reused on hardware registers |
| **Control Flow** | `conditions/ifExercise_2`, `ifExercise_3` | Nested conditionals and branching logic |
| **Loops** | `forLoop_EvenNumbers`, `forLoopNumberPyramid`, `whileLoop_EvenNumbers` | `for`/`while` iteration, nested loops, pattern generation |
| **Switch / Multi-file Design** | `geometricAreaCalculator` | `switch/case` dispatch; splits logic across `areaCalculator.c` / `.h` — first exposure to header/implementation separation |
| **Floating Point** | `floatCharge`, `floatPrice` | Floating-point arithmetic and formatted output |
| **Preprocessor** | `definePreProcessor` | `#define` constants and function-like macros |
| **Strings** | `strings` | C-string (char array) manipulation |
| **Structs & Unions** | `structExercise`, `structPointer`, `unionBitExtraction` | `struct` definitions, pointer-to-struct member access, using `union` to reinterpret raw bytes/bits — directly applicable to register-overlay techniques used in `target/010` |
| **Applied Project** | `studentsManagement` | A console CRUD application: an array of `Student_t` structs with add/remove/list operations, input validation (`scanf` return-code checking, buffer clearing on bad input), and safe fixed-size buffers — the largest and most complete host-side program in the repository |

---

## Skills Demonstrated

| Area | Evidence in this Repository |
|---|---|
| **C language fundamentals** | Pointers, structs, unions, bit-fields, the preprocessor, fixed-width types (`stdint.h`) — `host/` |
| **Register-level / bare-metal programming** | Direct memory-mapped I/O, `volatile` correctness, RCC clock gating, GPIO MODER/ODR/PUPDR configuration — `target/` |
| **ARM Cortex-M fundamentals** | Vector table & startup code, linker scripts (Flash vs. RAM placement), stack/heap layout | 
| **Peripheral interfacing** | Digital input (push-button, debounced matrix keypad), digital output (LED), row/column scanning algorithms |
| **Code evolution / maintainability** | Same peripherals re-implemented across raw pointers → bit-field structs → named macros, reflecting how firmware is refactored toward a driver-style architecture |
| **Toolchain fluency** | STM32CubeIDE project structure, `arm-none-eabi-gcc`, OpenOCD/ST-Link debug configuration, ARM semihosting for early-stage `printf` debugging |
| **Defensive programming** | Input validation and buffer-clearing on malformed `scanf` input in `studentsManagement` |

---

## Roadmap

Planned additions as this portfolio continues to grow:

- [ ] Timer-based delay (SysTick / TIM peripheral) to replace busy-wait `SWDelay()`
- [ ] UART driver (polling, then interrupt-driven) to replace semihosting
- [ ] Interrupt-driven GPIO (EXTI) button handling
- [ ] A minimal reusable GPIO driver header (building on the `013` macro/bit-field pattern)
- [ ] Basic unit tests for `host/` logic exercises

---

## Getting Started

```bash
git clone https://github.com/ShayanSaed/Embedded-C-Programming.git
cd Embedded-C-Programming
```

- To explore **firmware**: open any folder under `target/` in STM32CubeIDE and flash it to an STM32F411-based board.
- To explore **C fundamentals**: open any folder under `host/` in STM32CubeIDE (or compile directly with `gcc main.c -o app`) and run it locally — no hardware required.

---

## Author

**Shayan Saed**
GitHub: [@ShayanSaed](https://github.com/ShayanSaed)

This repository is maintained as a hands-on learning log and portfolio piece while pursuing an **Embedded Software Engineering internship**. Feedback, issues, and suggestions are welcome.

---

## License

This project is licensed under the [MIT License](LICENSE) — feel free to use these exercises as a learning reference.
