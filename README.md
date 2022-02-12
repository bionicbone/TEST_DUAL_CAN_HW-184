# TEST_DUAL_CAN_HW-184
LOLIN32 ESP32 with 2 x HW-184 Can Bus Module

This appears to be working, but more testing required as I only used one Can bus writer and connected to each indivdual HW-184. Also both were set to 500kb/s bus speed.

The HW-184 CAN Bus modules must be powered by 5v (I used a NANO powered by USB just to get thh 5v & GND pins in this test)

For the LOLIN32 connections

CAN0: GPIO19 to D0, GPIO23 to D1, GPIO18 to CLK, GPIO22 to CS, GPIO16 to INT

CAN1: GPIO19 to D0, GPIO23 to D1, GPIO18 to CLK, GPI17 to CS, GPIO3 to INT

For CAN1 the CS and INT pins were just randomly chosen, I may need to do more research.

I did manage to add an Adafruit SD Card breakout, however I found that trying to log data at 1 frame every 4ms was impossible by a long margin, maybe I need to investigate further.

It should be noted the the USB serial needs to be capable of at least 250kb/s (250000b/s), otherwise data will be lost when using the Visual Studio COM window. It maybe necessary to write a VB code so that the data comes over without displaying in the scroll window which causes a significant overhead and unnecessary when only wanting to log data. For the time being I am using the built in Visual Studio logging function from the COM window. 

Next Steps:

CAN0 remains at 500kb/s, but CAN1 has been changed to 125kb/s.

Build another CAN Sender running at 125kb/s sending a frame every 4ms and attach both to make sure the ESP32

Check the ESP32 keep up using the single SPI interface, essenially we will double the frames on the bus to one every 2ms.
