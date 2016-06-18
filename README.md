# halfDulpexSerial
This project can help make a stm32f10x board as an alternative to USB2Dynamixel to some degree. 

## Background
Dynamixel AX-12/18 servos are good acutator for robots. The communication :
>Command Signal : Digital Packet
Protocol Type : Half duplex Asynchronous Serial Communication (8bit,1stop,No Parity)
Link (Physical) : TTL Level Multi Drop (daisy chain type Connector)

More at link [http://support.robotis.com/en/product/dynamixel/ax_series/ax-18f.htm](http://support.robotis.com/en/product/dynamixel/ax_series/ax-18f.htm)

## Problem
1. The servo use single line half dulpex serial to communicate but we usually have two lines full dulpex serial which means we need the bridge.
2. The servo has high default baud rate (1000000=1Mbps). Although it is changeable it's usually not easy to find usb2serial chip and software to communicate with it.

## Solution
This project uses tm32f10x as the bridge. Stm3210x its supports the half dulpex mode usart and its usart support up to 4.5Mbps baud rate(USART1).

servo <---single line----> usart1_stm32f10x <---DMA--->usart2_stm32f10x <----double line -----> serial_port

You can set the baudrate at init function ar `APP\app.c`:

```c
BSP_USART_Init ( 115200 );
BSP_SERVO_Init ( 1000000 );
```