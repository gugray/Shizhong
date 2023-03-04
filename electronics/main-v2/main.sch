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
L CustomParts:ATmega88V-10PU-Adapted U1
U 1 1 63D8B760
P 4400 3600
F 0 "U1" H 3950 5050 50  0000 C CNN
F 1 "ATmega88V-10PU" V 4500 4250 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4400 4500 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2545-8-bit-AVR-Microcontroller-ATmega48-88-168_Datasheet.pdf" H 4400 3600 50  0001 C CNN
	1    4400 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 63D8E0EA
P 1800 1700
F 0 "BT1" H 1918 1796 50  0000 L CNN
F 1 "3V Coin" H 1918 1705 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_3002_1x2032" V 1800 1760 50  0001 C CNN
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
$Comp
L Device:R R1
U 1 1 63D92D6A
P 3350 2500
F 0 "R1" V 3450 2550 50  0000 C CNN
F 1 "10k" V 3250 2550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3280 2500 50  0001 C CNN
F 3 "~" H 3350 2500 50  0001 C CNN
	1    3350 2500
	0    -1   -1   0   
$EndComp
Text GLabel 3200 2500 0    50   Input ~ 0
VCC
Wire Wire Line
	3500 2500 3700 2500
Text GLabel 3600 2250 0    50   Input ~ 0
PIN-RST
Wire Wire Line
	3600 2250 3700 2250
Wire Wire Line
	3700 2250 3700 2500
Connection ~ 3700 2500
Wire Wire Line
	3700 2500 3800 2500
Text GLabel 1950 3500 2    50   Input ~ 0
PIN-MISO
Text GLabel 5000 3500 2    50   Input ~ 0
PIN-SCK
Text GLabel 1950 3600 2    50   Input ~ 0
PIN-SCK
$Comp
L Device:Crystal_Small Y1
U 1 1 63D97EB5
P 3500 3450
F 0 "Y1" V 3500 3350 50  0000 R CNN
F 1 "32kHz" V 3300 3550 50  0000 R CNN
F 2 "Crystal:Crystal_C38-LF_D3.0mm_L8.0mm_Horizontal" H 3500 3450 50  0001 C CNN
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
L Device:C C1
U 1 1 63D990C6
P 3250 3350
F 0 "C1" V 3100 3500 50  0000 C CNN
F 1 "6pF" V 3200 3500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" H 3288 3200 50  0001 C CNN
F 3 "~" H 3250 3350 50  0001 C CNN
	1    3250 3350
	0    -1   1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 63D99A49
P 3250 3550
F 0 "C2" V 3400 3700 50  0000 C CNN
F 1 "6pF" V 3300 3700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" H 3288 3400 50  0001 C CNN
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
L Connector_Generic:Conn_01x06 J1
U 1 1 64037738
P 1750 3400
F 0 "J1" H 1668 3817 50  0000 C CNN
F 1 "Port" V 1850 3550 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1750 3400 50  0001 C CNN
F 3 "~" H 1750 3400 50  0001 C CNN
	1    1750 3400
	-1   0    0    -1  
$EndComp
Text GLabel 1950 3400 2    50   Input ~ 0
PIN-MOSI
Text GLabel 1950 3700 2    50   Input ~ 0
PIN-RST
Text GLabel 1950 3200 2    50   Input ~ 0
GND
Text GLabel 1950 3300 2    50   Input ~ 0
VCC
Text GLabel 3800 2750 0    50   Input ~ 0
PIN-DQ
Wire Wire Line
	4350 1700 4350 2100
NoConn ~ 4500 2100
Connection ~ 4100 5450
Wire Wire Line
	4000 5450 4100 5450
Text GLabel 4000 5450 0    50   Input ~ 0
PIN-DQ
Wire Wire Line
	4100 5450 4300 5450
Wire Wire Line
	4100 5050 4100 5450
Wire Wire Line
	4200 5050 4100 5050
Wire Wire Line
	4600 5050 4600 5150
Connection ~ 4600 5050
Wire Wire Line
	4500 5050 4600 5050
Wire Wire Line
	4600 4950 4600 5050
$Comp
L Device:R R2
U 1 1 6405E32E
P 4350 5050
F 0 "R2" V 4450 5100 50  0000 C CNN
F 1 "5k" V 4250 5100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4280 5050 50  0001 C CNN
F 3 "~" H 4350 5050 50  0001 C CNN
	1    4350 5050
	0    -1   -1   0   
$EndComp
Text GLabel 4600 5750 3    50   Input ~ 0
GND
$Comp
L Sensor_Temperature:DS18B20 U2
U 1 1 6405CC84
P 4600 5450
F 0 "U2" H 4500 5750 50  0000 R CNN
F 1 "DS18B20" H 4500 5150 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 3600 5200 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 4450 5700 50  0001 C CNN
	1    4600 5450
	-1   0    0    -1  
$EndComp
Text GLabel 5000 3600 2    50   Input ~ 0
PIN-MISO
Text GLabel 5000 3700 2    50   Input ~ 0
PIN-MOSI
Text GLabel 5000 3000 2    50   Input ~ 0
PIN-BTN-MODE
Text GLabel 5000 2800 2    50   Input ~ 0
PIN-BTN-MINUS
Text GLabel 5000 2700 2    50   Input ~ 0
PIN-BTN-PLUS
Text GLabel 1550 4900 1    50   Input ~ 0
PIN-BTN-MODE
$Comp
L Switch:SW_Push SW2
U 1 1 6406A5EF
P 2150 5100
F 0 "SW2" V 2104 5248 50  0000 L CNN
F 1 "SW_Push" V 2195 5248 50  0000 L CNN
F 2 "Connector:PushButton5mm" H 2150 5300 50  0001 C CNN
F 3 "~" H 2150 5300 50  0001 C CNN
	1    2150 5100
	0    1    1    0   
$EndComp
Text GLabel 2150 4900 1    50   Input ~ 0
PIN-BTN-MINUS
$Comp
L Switch:SW_Push SW3
U 1 1 6406B3AA
P 2750 5100
F 0 "SW3" V 2704 5248 50  0000 L CNN
F 1 "SW_Push" V 2795 5248 50  0000 L CNN
F 2 "Connector:PushButton5mm" H 2750 5300 50  0001 C CNN
F 3 "~" H 2750 5300 50  0001 C CNN
	1    2750 5100
	0    1    1    0   
$EndComp
Text GLabel 2750 4900 1    50   Input ~ 0
PIN-BTN-PLUS
$Comp
L Switch:SW_Push SW1
U 1 1 6406336A
P 1550 5100
F 0 "SW1" V 1504 5248 50  0000 L CNN
F 1 "SW_Push" V 1595 5248 50  0000 L CNN
F 2 "Connector:PushButton5mm" H 1550 5300 50  0001 C CNN
F 3 "~" H 1550 5300 50  0001 C CNN
	1    1550 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 5300 2150 5300
Connection ~ 1550 5300
Wire Wire Line
	1550 5300 1400 5300
Connection ~ 2150 5300
Wire Wire Line
	2150 5300 1550 5300
Text GLabel 1400 5300 0    50   Input ~ 0
GND
NoConn ~ 3800 2850
NoConn ~ 3800 2950
NoConn ~ 3800 3050
NoConn ~ 3800 3150
NoConn ~ 3800 3700
NoConn ~ 3800 3800
NoConn ~ 3800 3900
NoConn ~ 3800 4100
NoConn ~ 4500 4500
NoConn ~ 5000 4000
NoConn ~ 5000 3250
NoConn ~ 5000 2900
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6407BF3C
P 1300 1500
F 0 "#FLG0101" H 1300 1575 50  0001 C CNN
F 1 "PWR_FLAG" H 1300 1673 50  0000 C CNN
F 2 "" H 1300 1500 50  0001 C CNN
F 3 "~" H 1300 1500 50  0001 C CNN
	1    1300 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1500 1800 1500
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6407CF41
P 1300 1800
F 0 "#FLG0102" H 1300 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 1300 1973 50  0000 C CNN
F 2 "" H 1300 1800 50  0001 C CNN
F 3 "~" H 1300 1800 50  0001 C CNN
	1    1300 1800
	1    0    0    1   
$EndComp
Wire Wire Line
	1800 1800 1300 1800
$Comp
L Device:LED D1
U 1 1 6409ED50
P 5600 4250
F 0 "D1" V 5639 4132 50  0000 R CNN
F 1 "LED" V 5548 4132 50  0000 R CNN
F 2 "LED_THT:LED_D2.0mm_W4.0mm_H2.8mm_FlatTop" H 5600 4250 50  0001 C CNN
F 3 "~" H 5600 4250 50  0001 C CNN
	1    5600 4250
	0    -1   -1   0   
$EndComp
Text GLabel 5600 4400 3    50   Input ~ 0
GND
$Comp
L Device:R R3
U 1 1 6409FDC2
P 5250 4100
F 0 "R3" V 5350 4150 50  0000 C CNN
F 1 "1k" V 5150 4150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5180 4100 50  0001 C CNN
F 3 "~" H 5250 4100 50  0001 C CNN
	1    5250 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5000 4100 5100 4100
Wire Wire Line
	5400 4100 5600 4100
Text GLabel 4350 4500 3    50   Input ~ 0
GND
$Comp
L CustomParts:BU9796AMUV-E2 U3
U 1 1 64043B37
P 8400 3200
F 0 "U3" H 8400 4265 50  0000 C CNN
F 1 "BU9796AMUV-E2" H 8400 4174 50  0000 C CNN
F 2 "Package_DFN_QFN:VQFN-24-1EP_4x4mm_P0.5mm_EP2.45x2.45mm" H 9100 4150 50  0001 C CNN
F 3 "" H 9100 4150 50  0001 C CNN
	1    8400 3200
	1    0    0    -1  
$EndComp
$Comp
L CustomParts:LCD16 LCD2
U 1 1 64045D3A
P 9900 3550
F 0 "LCD2" H 10017 2235 50  0000 C CNN
F 1 "LCD16" H 10017 2326 50  0000 C CNN
F 2 "Connector:LCD16-TN6" H 9450 3950 50  0001 C CNN
F 3 "" H 9450 3950 50  0001 C CNN
	1    9900 3550
	1    0    0    1   
$EndComp
Wire Wire Line
	9300 4000 9800 4000
Wire Wire Line
	9300 3900 9800 3900
Wire Wire Line
	9300 3800 9800 3800
Wire Wire Line
	9300 3700 9800 3700
Wire Wire Line
	9300 3600 9800 3600
Wire Wire Line
	9800 3500 9300 3500
Wire Wire Line
	9300 3400 9800 3400
Wire Wire Line
	9800 3300 9300 3300
Wire Wire Line
	9300 3200 9800 3200
Wire Wire Line
	9300 3100 9800 3100
Wire Wire Line
	9800 3000 9300 3000
Wire Wire Line
	9300 2900 9800 2900
Wire Wire Line
	9800 2800 9300 2800
Wire Wire Line
	9300 2700 9800 2700
Wire Wire Line
	9800 2600 9300 2600
Wire Wire Line
	9300 2500 9800 2500
Text GLabel 7500 2500 0    50   Input ~ 0
GND
Text GLabel 6850 2650 0    50   Input ~ 0
PIN-SCL
Text GLabel 6850 2900 0    50   Input ~ 0
PIN-SDA
Wire Wire Line
	7500 3000 7400 3000
Wire Wire Line
	7400 3000 7400 3100
Wire Wire Line
	7400 3100 7500 3100
Wire Wire Line
	7400 3100 7300 3100
Connection ~ 7400 3100
Text GLabel 7300 3100 0    50   Input ~ 0
GND
Wire Wire Line
	7400 3100 7400 3400
Wire Wire Line
	7400 3400 7500 3400
Text GLabel 7050 3650 0    50   Input ~ 0
VCC
$Comp
L Device:C C3
U 1 1 6405C403
P 7200 3800
F 0 "C3" H 7315 3846 50  0000 L CNN
F 1 "C" H 7315 3755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7238 3650 50  0001 C CNN
F 3 "~" H 7200 3800 50  0001 C CNN
	1    7200 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3650 7200 3650
Connection ~ 7200 3650
Wire Wire Line
	7200 3650 7500 3650
Wire Wire Line
	7500 3900 7400 3900
Wire Wire Line
	7400 3900 7400 3950
Wire Wire Line
	7400 3950 7200 3950
Wire Wire Line
	7200 3950 7050 3950
Connection ~ 7200 3950
Text GLabel 7050 3950 0    50   Input ~ 0
GND
$Comp
L Device:R R4
U 1 1 64063FAE
P 7000 2650
F 0 "R4" V 7100 2700 50  0000 C CNN
F 1 "10k" V 6900 2700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6930 2650 50  0001 C CNN
F 3 "~" H 7000 2650 50  0001 C CNN
	1    7000 2650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 640687D7
P 7000 2900
F 0 "R5" V 7100 2950 50  0000 C CNN
F 1 "10k" V 6900 2950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6930 2900 50  0001 C CNN
F 3 "~" H 7000 2900 50  0001 C CNN
	1    7000 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7150 2650 7500 2650
Wire Wire Line
	7500 2650 7500 2700
Wire Wire Line
	7150 2900 7500 2900
Wire Wire Line
	7500 2900 7500 2800
NoConn ~ 7500 4000
Text GLabel 4600 4950 1    50   Input ~ 0
VCC
$EndSCHEMATC
