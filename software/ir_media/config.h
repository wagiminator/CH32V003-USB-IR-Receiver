// ===================================================================================
// User Configurations for IR Multimedia Control
// ===================================================================================

#pragma once

// IR codes (NEC protocol)
#define IR_ADDR             0x1A      // IR device address
#define IR_CMD_VOL_UP       0x01      // IR command for volume up
#define IR_CMD_VOL_DOWN     0x03      // IR command for volume down
#define IR_CMD_VOL_MUTE     0x0C      // IR command for volume mute/unmute
#define IR_CMD_PLAY         0x05      // IR command for media play
#define IR_CMD_PAUSE        0x06      // IR command for media pause
#define IR_CMD_STOP         0x07      // IR command for media stop
#define IR_CMD_RECORD       0x08      // IR command for media record
#define IR_CMD_NEXT         0x09      // IR command for media next
#define IR_CMD_PREV         0x0A      // IR command for media previous
#define IR_CMD_FORWARD      0x02      // IR command for media forward
#define IR_CMD_REWIND       0x04      // IR command for media rewind
#define IR_CMD_EJECT        0x0B      // IR command for media eject
#define IR_REPEAT           0xFE      // IR repeat code
#define IR_FAIL             0xFF      // IR fail code

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
#define PROD_STR            "IR Media Control"
#define SERIAL_STR          "CH32V003HID"

