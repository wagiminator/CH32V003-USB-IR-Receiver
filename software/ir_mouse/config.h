// ===================================================================================
// User Configurations for IR Mouse Adapter
// ===================================================================================

#pragma once

// IR codes (NEC protocol)
#define IR_ADDR             0x1A      // IR device address
#define IR_CMD_UP           0x01      // IR command for mouse up
#define IR_CMD_RIGHT        0x02      // IR command for mouse right
#define IR_CMD_DOWN         0x03      // IR command for mouse down
#define IR_CMD_LEFT         0x04      // IR command for mouse left
#define IR_CMD_BTL          0x05      // IR command for left mouse button
#define IR_CMD_BTR          0x06      // IR command for right mouse button
#define IR_CMD_WUP          0x07      // IR command for mouse wheel up
#define IR_CMD_WDOWN        0x08      // IR command for mouse wheel down
#define IR_REPEAT           0xFE      // IR repeat code
#define IR_FAIL             0xFF      // IR fail code

// Mouse speed
#define IR_MOUSE_SPEED      10        // mouse pointer speed

// Pin definitions
#define PIN_IR              PC1       // pin connected to TSOP4838 IR receiver

// USB pin defines
#define USB_PORT            A         // [A,C,D] GPIO Port to use with D+, D- and DPU
#define USB_PIN_DP          1         // [0-4] GPIO Number for USB D+ Pin
#define USB_PIN_DM          2         // [0-4] GPIO Number for USB D- Pin

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA 

// USB device descriptor
#define USB_VENDOR_ID       0x1209    // VID
#define USB_PRODUCT_ID      0xc003    // PID
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)
#define USB_LANGUAGE        0x0409    // US English

// USB descriptor strings
#define MANUF_STR           "wagiminator"
#define PROD_STR            "IR Mouse"
#define SERIAL_STR          "CH32V003HID"

