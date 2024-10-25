## JoybusOverUart
Arduino compatible, C++ library to Read/Write to Joybus protocol devices (N64, GameCube controllers) over UART in a non-blocking way (no bit bang).
Works with any UART capable of 1250000bps. Interrupts aren't blocked or used.

(Ab)uses Serial Port to emulate the OneWire-like protocol of Joybus, based on the work published by qwertymodo (http://www.qwertymodo.com/hardware-projects/n64/n64-controller).

![](https://raw.githubusercontent.com/GitMoDu/JoybusOverUart/master/media/gamecube_controller_demo.gif)

In order to wire this up, we need to tie the UART's Rx and Tx pins together using a Schottky diode, as shown here (https://github.com/dword1511/onewire-over-uart).
![](https://raw.githubusercontent.com/GitMoDu/JoybusOverUart/master/media/pp2od_rd.png)

Hardware required: serial port (uart) capable of 1250000 bps baud-rate.

## Supported Devices:
  * Nintendo 64 controller.
  * GameCube controller.

## Supported Platforms
 * STM32F1, STM32F4
 * RP2040

