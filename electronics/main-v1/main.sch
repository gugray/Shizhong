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
Connection ~ 6500 4100
Wire Wire Line
	6400 4100 6500 4100
Text GLabel 6400 4100 0    50   Input ~ 0
PIN-DQ
Wire Wire Line
	6500 4100 6700 4100
Wire Wire Line
	6500 3700 6500 4100
Wire Wire Line
	6600 3700 6500 3700
Wire Wire Line
	7000 3700 7000 3800
Connection ~ 7000 3700
Wire Wire Line
	6900 3700 7000 3700
Wire Wire Line
	7000 3600 7000 3700
$Comp
L Device:R R2
U 1 1 6405E32E
P 6750 3700
F 0 "R2" V 6850 3750 50  0000 C CNN
F 1 "5k" V 6650 3750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6680 3700 50  0001 C CNN
F 3 "~" H 6750 3700 50  0001 C CNN
	1    6750 3700
	0    -1   -1   0   
$EndComp
Text GLabel 7000 4400 3    50   Input ~ 0
GND
Text GLabel 7000 3600 1    50   Input ~ 0
VCC
$Comp
L Sensor_Temperature:DS18B20 U2
U 1 1 6405CC84
P 7000 4100
F 0 "U2" H 6900 4400 50  0000 R CNN
F 1 "DS18B20" H 6900 3800 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 6000 3850 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 6850 4350 50  0001 C CNN
	1    7000 4100
	-1   0    0    -1  
$EndComp
Text GLabel 8400 4450 3    50   Input ~ 0
GND
Text GLabel 8400 3800 1    50   Input ~ 0
VCC
Text GLabel 8050 4200 0    50   Input ~ 0
PIN-SCL
Text GLabel 8050 4050 0    50   Input ~ 0
PIN-SDA
$Comp
L CustomParts:LCD_Feather LCD1
U 1 1 64059638
P 8350 4850
F 0 "LCD1" H 8250 5800 50  0000 R CNN
F 1 "LCD_Feather" H 8250 5350 50  0000 R CNN
F 2 "Connector:LCD_Feather" H 8250 4850 50  0001 C CNN
F 3 "~" H 8250 4850 50  0001 C CNN
	1    8350 4850
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
Text GLabel 6550 2850 1    50   Input ~ 0
PIN-BTN-MODE
$Comp
L Switch:SW_Push SW2
U 1 1 6406A5EF
P 7150 3050
F 0 "SW2" V 7104 3198 50  0000 L CNN
F 1 "SW_Push" V 7195 3198 50  0000 L CNN
F 2 "Connector:PushButton5mm" H 7150 3250 50  0001 C CNN
F 3 "~" H 7150 3250 50  0001 C CNN
	1    7150 3050
	0    1    1    0   
$EndComp
Text GLabel 7150 2850 1    50   Input ~ 0
PIN-BTN-MINUS
$Comp
L Switch:SW_Push SW3
U 1 1 6406B3AA
P 7750 3050
F 0 "SW3" V 7704 3198 50  0000 L CNN
F 1 "SW_Push" V 7795 3198 50  0000 L CNN
F 2 "Connector:PushButton5mm" H 7750 3250 50  0001 C CNN
F 3 "~" H 7750 3250 50  0001 C CNN
	1    7750 3050
	0    1    1    0   
$EndComp
Text GLabel 7750 2850 1    50   Input ~ 0
PIN-BTN-PLUS
$Comp
L Switch:SW_Push SW1
U 1 1 6406336A
P 6550 3050
F 0 "SW1" V 6504 3198 50  0000 L CNN
F 1 "SW_Push" V 6595 3198 50  0000 L CNN
F 2 "Connector:PushButton5mm" H 6550 3250 50  0001 C CNN
F 3 "~" H 6550 3250 50  0001 C CNN
	1    6550 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 3250 7150 3250
Connection ~ 6550 3250
Wire Wire Line
	6550 3250 6400 3250
Connection ~ 7150 3250
Wire Wire Line
	7150 3250 6550 3250
Text GLabel 6400 3250 0    50   Input ~ 0
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
$EndSCHEMATC
