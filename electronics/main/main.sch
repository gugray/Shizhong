EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CustomParts:ATmega88V-10PU-Adapted U?
U 1 1 63D8B760
P 4400 3600
F 0 "U?" H 3950 5050 50  0000 C CNN
F 1 "ATmega88V-10PU" V 4500 4250 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4400 4500 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2545-8-bit-AVR-Microcontroller-ATmega48-88-168_Datasheet.pdf" H 4400 3600 50  0001 C CNN
	1    4400 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 63D8E0EA
P 1800 1700
F 0 "BT?" H 1918 1796 50  0000 L CNN
F 1 "3V Coin" H 1918 1705 50  0000 L CNN
F 2 "" V 1800 1760 50  0001 C CNN
F 3 "~" V 1800 1760 50  0001 C CNN
	1    1800 1700
	1    0    0    -1  
$EndComp
Text GLabel 1800 1500 1    50   Input ~ 0
VCC
Text GLabel 1800 1800 3    50   Input ~ 0
GND
Text GLabel 4350 1700 1    50   Input ~ 0
VCC
Text GLabel 4500 1700 1    50   Input ~ 0
VCC
$Comp
L Device:C C?
U 1 1 63D90A73
P 4650 1900
F 0 "C?" V 4550 2000 50  0000 C CNN
F 1 "0.1uF" V 4700 2050 50  0000 C CNN
F 2 "" H 4688 1750 50  0001 C CNN
F 3 "~" H 4650 1900 50  0001 C CNN
	1    4650 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 1700 4500 1900
Wire Wire Line
	4500 1900 4500 2100
Connection ~ 4500 1900
$Comp
L Device:C C?
U 1 1 63D918F1
P 4200 1900
F 0 "C?" V 4100 2000 50  0000 C CNN
F 1 "0.1uF" V 4250 2050 50  0000 C CNN
F 2 "" H 4238 1750 50  0001 C CNN
F 3 "~" H 4200 1900 50  0001 C CNN
	1    4200 1900
	0    -1   1    0   
$EndComp
Wire Wire Line
	4350 1700 4350 1900
Wire Wire Line
	4350 1900 4350 2100
Connection ~ 4350 1900
Text GLabel 4900 1900 2    50   Input ~ 0
GND
Text GLabel 3950 1900 0    50   Input ~ 0
GND
Wire Wire Line
	3950 1900 4050 1900
Wire Wire Line
	4800 1900 4900 1900
$Comp
L Device:R R?
U 1 1 63D92D6A
P 3350 2500
F 0 "R?" V 3450 2550 50  0000 C CNN
F 1 "10k" V 3250 2550 50  0000 C CNN
F 2 "" V 3280 2500 50  0001 C CNN
F 3 "~" H 3350 2500 50  0001 C CNN
	1    3350 2500
	0    -1   -1   0   
$EndComp
Text GLabel 3200 2500 0    50   Input ~ 0
VCC
Wire Wire Line
	3500 2500 3700 2500
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 63D952F1
P 1800 2600
F 0 "J?" H 1800 2850 50  0000 C CNN
F 1 "Programmer" V 1900 2600 50  0000 C CNN
F 2 "" H 1800 2600 50  0001 C CNN
F 3 "~" H 1800 2600 50  0001 C CNN
	1    1800 2600
	-1   0    0    -1  
$EndComp
Text GLabel 2000 2500 2    50   Input ~ 0
PIN-RST
Text GLabel 3600 2250 0    50   Input ~ 0
PIN-RST
Wire Wire Line
	3600 2250 3700 2250
Wire Wire Line
	3700 2250 3700 2500
Connection ~ 3700 2500
Wire Wire Line
	3700 2500 3800 2500
Text GLabel 5000 3700 2    50   Input ~ 0
PIN-MOSI
Text GLabel 2000 2800 2    50   Input ~ 0
PIN-MOSI
Text GLabel 2000 2700 2    50   Input ~ 0
PIN-MISO
Text GLabel 5000 3600 2    50   Input ~ 0
PIN-MISO
Text GLabel 5000 3500 2    50   Input ~ 0
PIN-SCK
Text GLabel 2000 2600 2    50   Input ~ 0
PIN-SCK
$Comp
L Device:Crystal_Small Y?
U 1 1 63D97EB5
P 3500 3450
F 0 "Y?" V 3500 3350 50  0000 R CNN
F 1 "32kHz" V 3300 3550 50  0000 R CNN
F 2 "" H 3500 3450 50  0001 C CNN
F 3 "~" H 3500 3450 50  0001 C CNN
	1    3500 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 3350 3800 3350
Wire Wire Line
	3800 3350 3800 3400
Wire Wire Line
	3500 3550 3800 3550
Wire Wire Line
	3800 3550 3800 3500
$Comp
L Device:C C?
U 1 1 63D990C6
P 3250 3350
F 0 "C?" V 3100 3500 50  0000 C CNN
F 1 "6pF" V 3200 3500 50  0000 C CNN
F 2 "" H 3288 3200 50  0001 C CNN
F 3 "~" H 3250 3350 50  0001 C CNN
	1    3250 3350
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 63D99A49
P 3250 3550
F 0 "C?" V 3400 3700 50  0000 C CNN
F 1 "6pF" V 3300 3700 50  0000 C CNN
F 2 "" H 3288 3400 50  0001 C CNN
F 3 "~" H 3250 3550 50  0001 C CNN
	1    3250 3550
	0    -1   1    0   
$EndComp
Wire Wire Line
	3100 3350 2850 3350
Wire Wire Line
	2850 3350 2850 3450
Wire Wire Line
	2850 3550 3100 3550
Wire Wire Line
	3400 3550 3500 3550
Connection ~ 3500 3550
Wire Wire Line
	3400 3350 3500 3350
Connection ~ 3500 3350
Wire Wire Line
	2850 3450 2800 3450
Connection ~ 2850 3450
Wire Wire Line
	2850 3450 2850 3550
Text GLabel 2800 3450 0    50   Input ~ 0
GND
Text GLabel 5000 2600 2    50   Input ~ 0
PIN-SDA
Text GLabel 5000 2500 2    50   Input ~ 0
PIN-SCL
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 63D9CE8B
P 6750 2500
F 0 "J?" H 6750 2750 50  0000 C CNN
F 1 "NEO-6M GPS" V 6850 2500 50  0000 C CNN
F 2 "" H 6750 2500 50  0001 C CNN
F 3 "~" H 6750 2500 50  0001 C CNN
	1    6750 2500
	1    0    0    -1  
$EndComp
Text Notes 7050 2700 2    50   ~ 0
VCC\nRX\nTX\nGND
Text GLabel 6550 2700 0    50   Input ~ 0
GND
Text GLabel 6550 2400 0    50   Input ~ 0
VCC
NoConn ~ 6550 2500
Text GLabel 3800 3150 0    50   Input ~ 0
PIN-PD4
Text GLabel 6550 2600 0    50   Input ~ 0
PIN-PD4
$EndSCHEMATC
