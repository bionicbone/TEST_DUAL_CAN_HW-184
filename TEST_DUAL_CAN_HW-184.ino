/*
 Name:		TEST_DUAL_CAN_HW_184.ino
 Created:	2/7/2022 4:13:10 PM
 Author:	Micro
*/

// CAN Receive Example
//

#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string
unsigned long timer0 = micros();
unsigned long timer1 = micros();

#define CAN0_INT 16                             // Set INT to pin 16
MCP_CAN CAN0(5);                               // Set CS to pin 10

// Add 2nd Can Module
#define CAN1_INT 3                              // Set INT to pin 2
MCP_CAN CAN1(17);                               // Set CS to pin 10


void setup()
{
  Serial.begin(250000);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("CAN0: MCP2515 Initialized Successfully!");
  else
    Serial.println("CAN0: Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input

  // Add 2nd Can Module
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN1.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("CAN1: MCP2515 Initialized Successfully!");
  else
    Serial.println("CAN1: Error Initializing MCP2515...");

  CAN1.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN1_INT, INPUT);                            // Configuring pin for /INT input
  
  //SPI.setClockDivider(SPI_CLOCK_DIV4);         // Set SPI to run at 4MHz (8MHz / 2 = 4 MHz)
                                                  //SPI_CLOCK_DIV2 would be used for 8MHz (16MHz / 2 = 8 MHz)

  
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
  if (!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    Serial.println(micros() - timer0);

    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)

    if ((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "CAN0: Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "CAN0: Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

    Serial.print(msgString);

    if ((rxId & 0x40000000) == 0x40000000) {    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    }
    else {
      for (byte i = 0; i < len; i++) {
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }

    Serial.println();

    timer0 = micros();
  }


  // Add 2nd Can Module
  if (!digitalRead(CAN1_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    Serial.println(micros() - timer1);

    CAN1.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)

    if ((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "CAN1: Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "CAN1: Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

    Serial.print(msgString);

    if ((rxId & 0x40000000) == 0x40000000) {    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    }
    else {
      for (byte i = 0; i < len; i++) {
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }

 
    Serial.println();

    timer1 = micros();
  }

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/