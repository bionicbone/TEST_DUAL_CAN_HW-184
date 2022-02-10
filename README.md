# TEST_DUAL_CAN_HW-184
LOLIN32 ESP32 with 2 x HW-184 Can Bus Modules

This appears to be working, but more testing required as I only used one Can bus writer and connected to each indivdual HW-184. Also both were set to 500kb/s bus speed.

The HW-184 CAN Bus modules must be powered by 5v (I used a NANO powered by USB just to get thh 5v & GND pins in this test)

For the LOLIN32 connections

CAN0: GPIO19 to D0, GPIO23 to D1, GPIO18 to CLK, GPIO5 to CS, GPIO2 to INT

CAN1: GPIO19 to D0, GPIO23 to D1, GPIO18 to CLK, GPI17 to CS, GPIO3 to INT

For CAN1 the CS and INT pins were just randomly chosen, I may need to do more research.
