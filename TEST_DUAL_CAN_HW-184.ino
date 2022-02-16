/*
 Name:		TEST_DUAL_CAN_HW_184.ino
 Created:	2/7/2022 4:13:10 PM
 Author:	Micro
*/

// CAN Receive Example
// Uses the MCP_CAN_lib-master-1.5.0 library
// https://github.com/coryjfowler/MCP_CAN_lib

#include <mcp_can.h>
#include <SPI.h>



unsigned long upTimer = millis();

#define CAN0_INT 16                             // Set INT to pin 16
MCP_CAN CAN0(22);                               // Set CS to pin 10

// Add 2nd Can Module
#define CAN1_INT 3                              // Set INT to pin 2
MCP_CAN CAN1(17);                               // Set CS to pin 10


void setup()
{
  // Serial needs to be at least this speed otherwise line will be dropped
  Serial.begin(250000);
  Serial.println("Dual Can Bus Logger, 500kb/s & 125kb/s...");
  
  // Initialize MCP2515 running at 8MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("CAN0: MCP2515 Initialized Successfully!");
  else
    Serial.println("CAN0: Error Initializing MCP2515...");
    CAN0.setMode(MCP_NORMAL);                              // Set operation mode to normal so the MCP2515 sends acks to received data.
      pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input

  // Add 2nd Can Module
  
  // Initialize MCP2515 running at 8MHz with a baudrate of 125kb/s and the masks and filters disabled.
  if (CAN1.begin(MCP_ANY, CAN_125KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("CAN1: MCP2515 Initialized Successfully!");
  else
    Serial.println("CAN1: Error Initializing MCP2515...");
  CAN1.setMode(MCP_NORMAL);                               // Set operation mode to normal so the MCP2515 sends acks to received data.
  pinMode(CAN1_INT, INPUT);                               // Configuring pin for /INT input
  
  //SPI.setClockDivider(SPI_CLOCK_DIV4);         // Set SPI to run at 4MHz (8MHz / 2 = 4 MHz)
                                                 //SPI_CLOCK_DIV2 would be used for 8MHz (16MHz / 2 = 8 MHz)
}

void loop()
{
  if (!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    readCan(CAN0, 0);
  }

  // Add 2nd Can Module
  if (!digitalRead(CAN1_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    readCan(CAN1, 1);
  }
}


void readCan(MCP_CAN myCan, uint8_t MCP2515number) {
  //Serial.println(micros() - timer1);

  long unsigned int rxId;
  unsigned char len = 0;
  unsigned char rxBuf[8];
  char msgString[128];                            // Array to store serial string
  myCan.readMsgBuf(&rxId, &len, rxBuf);      // Read data: rxId = Frame ID, len = data length, buf = data byte(s)

  if ((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
    sprintf(msgString, "CAN%1d: Extended ID: 0x%.8lX  DLC: %1d  Data:", MCP2515number, (rxId & 0x1FFFFFFF), len);
  else
    //sprintf(msgString, "CAN%1d: Standard ID: 0x%.3lX       DLC: %1d  Data:", MCP2515number, rxId, len);
    sprintf(msgString, "%.8d,%1d,%.3lX,0,0,%1d",millis()-upTimer , MCP2515number, rxId, len);

  Serial.print(msgString);

  if ((rxId & 0x40000000) == 0x40000000) {    // Determine if message is a remote request frame.
    sprintf(msgString, " REMOTE REQUEST FRAME");
    Serial.print(msgString);
  }
  else {
    for (byte i = 0; i < len; i++) {
      sprintf(msgString, ",%.2X", rxBuf[i]);
      Serial.print(msgString);
    }
  }


  Serial.println();

  //timer1 = micros();
}

