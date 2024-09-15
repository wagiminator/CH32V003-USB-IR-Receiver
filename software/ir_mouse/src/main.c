// ===================================================================================
// Project:   CH32V003 IR Mouse Adapter
// Version:   v1.0
// Year:      2024
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Converts an IR remote control into a USB mouse.
//
// References:
// -----------
// - CNLohr ch32v003fun: https://github.com/cnlohr/ch32v003fun
// - CNLohr rv003usb:    https://github.com/cnlohr/rv003usb
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Make sure GCC toolchain (gcc-riscv64-unknown-elf, newlib) and Python3 with
//   rvprog (via pip) are installed. In addition, Linux requires access rights to
//   WCH-LinkE programmer.
// - Edit config.h according to your needs.
// - Connect the WCH-LinkE programmer to the MCU board.
// - Run 'make flash'.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID mouse.
// - Use your NEC-compatible IR remote as a mouse.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include <config.h>                           // user configurations
#include <system.h>                           // system functions
#include <gpio.h>                             // GPIO functions
#include <usb_mouse.h>                        // USB HID mouse functions

// ===================================================================================
// IR Receiver Implementation (NEC Protocol)
// ===================================================================================

// IR receiver definitions and macros
#define IR_init()       PIN_input_PU(PIN_IR)  // pullup on IR pin
#define IR_available()  (!PIN_read(PIN_IR))   // return true if IR line is low

// IR wait for signal change and measure duration
uint8_t IR_waitChange(uint8_t timeout) {
  uint8_t pinState = PIN_read(PIN_IR);        // get current signal state
  uint8_t dur = 0;                            // variable for measuring duration
  while(PIN_read(PIN_IR) == pinState) {       // measure length of signal
    if(dur++ > timeout) return 0;             // exit if timeout
    DLY_us(100);                              // count every 100us
  }
  return dur;                                 // return time in 100us
}

// IR read data byte
uint8_t IR_readByte(void) {
  uint8_t result;
  uint8_t dur;
  for(uint8_t i=8; i; i--) {                  // 8 bits
    result >>= 1;                             // LSB first
    if(IR_waitChange(11) < 3) return IR_FAIL; // exit if wrong burst length
    dur = IR_waitChange(21);                  // measure length of pause
    if(dur <  3) return IR_FAIL;              // exit if wrong pause length
    if(dur > 11) result |= 0x80;              // bit "0" or "1" depends on pause duration
  }
  return result;                              // return received byte
}

// IR read data according to NEC protocol
uint8_t IR_read(void) {
  uint16_t addr;                              // variable for received address
  if(!IR_available())        return IR_FAIL;  // exit if no signal
  if(!IR_waitChange(100))    return IR_FAIL;  // exit if wrong start burst length

  uint8_t pause = IR_waitChange(55);          // get pause length
  if(pause < 19)             return IR_FAIL;  // exit if wrong start pause length
  if(pause < 35) {                            // repeat code?
    if(IR_waitChange(11) < 3) return IR_FAIL; // wrong repeat end mark
    return IR_REPEAT;                         // return IR repeat
  }

  uint8_t addr1 = IR_readByte();              // get first  address byte
  uint8_t addr2 = IR_readByte();              // get second address byte
  uint8_t cmd1  = IR_readByte();              // get first  command byte
  uint8_t cmd2  = IR_readByte();              // get second command byte

  if(IR_waitChange(11) < 3)  return IR_FAIL;  // exit if wrong final burst length
  if((cmd1 + cmd2) < 255)    return IR_FAIL;  // exit if command bytes are not inverse
  if((addr1 + addr2) == 255) addr = addr1;    // check if it's extended NEC-protocol ...
  else addr = ((uint16_t)addr2 << 8) | addr1; // ... and get the correct address
  if(addr != IR_ADDR)        return IR_FAIL;  // wrong address
  return cmd1;                                // return command code
}

// ===================================================================================
// Main Function
// ===================================================================================
int main(void) {
  // Variables
  uint8_t lastcommand = IR_FAIL;              // last received command

  // Setup
  IR_init();                                  // init IR receiver
  DLY_ms(1);                                  // wait a bit for USB
  MOUSE_init();                               // init USB HID mouse

  // Loop
  while(1) {
    if(IR_available()) {                      // IR signal coming in?
      uint8_t command = IR_read();            // get received command
      if(command == IR_REPEAT)                // repeat command?
        command = lastcommand;                // -> use last command
      lastcommand = command;                  // store last command

      switch(command) {                       // send key according to command
        case IR_CMD_LEFT:   MOUSE_move(-IR_MOUSE_SPEED, 0); break;
        case IR_CMD_RIGHT:  MOUSE_move( IR_MOUSE_SPEED, 0); break;
        case IR_CMD_UP:     MOUSE_move(0, -IR_MOUSE_SPEED); break;
        case IR_CMD_DOWN:   MOUSE_move(0,  IR_MOUSE_SPEED); break;
        case IR_CMD_WUP:    MOUSE_wheel_up(); break;
        case IR_CMD_WDOWN:  MOUSE_wheel_down(); break;
        case IR_CMD_BTL:    MOUSE_press(MOUSE_BUTTON_LEFT);
                            DLY_ms(10);
                            MOUSE_release(MOUSE_BUTTON_LEFT);
                            lastcommand = IR_FAIL;
                            break;
        case IR_CMD_BTR:    MOUSE_press(MOUSE_BUTTON_RIGHT);
                            DLY_ms(10);
                            MOUSE_release(MOUSE_BUTTON_RIGHT);
                            lastcommand = IR_FAIL;
                            break;
        default:            break;
      }
    }
  }
}
