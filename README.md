# TEST_DUAL_CAN_HW-184
LOLIN32 ESP32 with 2 x HW-184 Can Bus Module

This appears to be working, but more testing required as I only used one Can bus writer and swapped to each indivdual HW-184 for testing the code. Also both were set to 500kb/s bus speed.

The HW-184 CAN Bus modules must be powered by 5v (I used a NANO powered by USB just to get thh 5v & GND pins in this test)

For the LOLIN32 connections

CAN0: GPIO19 to D0, GPIO23 to D1, GPIO18 to CLK, GPIO22 to CS, GPIO16 to INT

CAN1: GPIO19 to D0, GPIO23 to D1, GPIO18 to CLK, GPI17 to CS, GPIO3 to INT

CS and INT pins were just randomly chosen, I may need to do more research. i.e. GPIO2 caused firmware uploading issues

I did manage to add an Adafruit SD Card breakout, however I found that trying to log data at 1 frame every 4ms was impossible by a long margin, maybe I need to investigate further because SD Card would be much better than having to use the laptop to capture every log.

The CAN Bus write module is currently set to send ID 145 every 4ms with an increamenting counter. Using this I was able to detect if any of the frames were lost. It was noted that at the popular 115200 USB baud rate the data was unreliably captured in the the Visual Studio COM window. 250000 baud currently solves the issue although once both buss are running then this may need to be increased further.

Furthermore, it maybe necessary to write a VB code so that the data comes over without displaying in the Visual Studio COM window which causes a significant overhead and unnecessary when only wanting to log data. However, I am using the built in Visual Studio logging function from the Visual Studio COM window, therefore this is a live with for now. 

Next Steps:

CAN0 remains at 500kb/s, but CAN1 has been changed to 125kb/s.

Build another CAN Sender running at 125kb/s sending a frame every 4ms and attach both to make sure the ESP32

Check the ESP32 keep up using the single SPI interface, essenially we will double the frames on the bus to one every 2ms.

Check the captured data layout is compatible with a SavvyCan import type, I may need to alter slightly before I capture too much data

The Land Rover Freelander 2 anaylsis and play back app will need to be updated to detect the CAN0 and CAN1 bus info
