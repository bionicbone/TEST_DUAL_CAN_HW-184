# TEST_DUAL_CAN_HW-184
LOLIN32 ESP32 with 2 x HW-184 Can Bus Module

Requirement: MCP_CAN_lib-master-1.5.0 library
https://github.com/coryjfowler/MCP_CAN_lib

This is working, HS bus @ 500kb/s, MS Bus at 125kb/s. Both busses are sending one standard frame every ~4ms.

The HW-184 CAN Bus modules must be powered by 5v (I used a NANO powered by USB just to get thh 5v & GND pins in this test)

For the LOLIN32 connections

CAN0: GPIO19 to D0, GPIO23 to D1, GPIO18 to CLK, GPIO22 to CS, GPIO16 to INT

CAN1: GPIO19 to D0, GPIO23 to D1, GPIO18 to CLK, GPI17 to CS, GPIO3 to INT

CS and INT pins were just randomly chosen, I may need to do more research. i.e. GPIO2 caused firmware uploading issues

I did manage to add an Adafruit SD Card breakout, however I found that trying to log data at 1 frame every 4ms was impossible by a long margin, maybe I need to investigate further because SD Card would be much better than having to use the laptop to capture every log.

The CAN Bus write modules are currently set to send ID 145 & 146 every 4ms with an increamenting counter. Using this I was able to detect if any of the frames were lost. It was noted that at the popular 115200 USB baud rate the data was unreliably captured in the the Visual Studio COM window. 250000 baud currently solves the issue although I may find the car sends data faster than my one frame to process every 2ms.

Furthermore, it maybe necessary to write a VB code so that the data comes over without displaying in the Visual Studio COM window which causes a significant overhead and unnecessary when only wanting to log data. However, I am using the built in Visual Studio logging function from the Visual Studio COM window, therefore this is a live with for now. 

Testing:

![image](https://user-images.githubusercontent.com/7845867/153749063-f127f76e-d1a8-4db5-8971-6d85f0dc9111.png)

![image](https://user-images.githubusercontent.com/7845867/153749020-cd51ae38-fe67-422a-b763-e793f3d51d74.png)


Next Steps:

Calculating the Time Quantum on the MCP2515 then a 32Mhz Crystal would be better for the 500kb/s (2us bit time), while 8Mhz was best for the 125kb/s (8us bit time). Do bit registers need altering ? That said 8Mhz seems to work just fine so far in my bench testing above.

Check the captured data layout is compatible with a SavvyCan import type, I may need to alter slightly before I capture too much data

The Land Rover Freelander 2 anaylsis and play back app will need to be updated to detect the CAN0 and CAN1 bus info
