EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Rotation Display Controller"
Date "2020-09-26"
Rev "v01"
Comp "BadGitZ"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U1
U 1 1 5F358D4E
P 3500 3000
F 0 "U1" H 3350 3550 50  0000 R CNN
F 1 "ATtiny85-20PU" H 4100 3550 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 3500 3000 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 3500 3000 50  0001 C CNN
	1    3500 3000
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:L293D U2
U 1 1 5F3599CB
P 5900 3400
F 0 "U2" H 5900 4581 50  0000 C CNN
F 1 "L293D" H 5900 4490 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 6150 2650 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/l293.pdf" H 5600 4100 50  0001 C CNN
	1    5900 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5F35BCBD
P 1950 2850
F 0 "J1" H 1868 2525 50  0000 C CNN
F 1 "Power_Terminal" H 1868 2616 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1950 2850 50  0001 C CNN
F 3 "~" H 1950 2850 50  0001 C CNN
	1    1950 2850
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5F35E059
P 4450 3450
F 0 "R1" H 4300 3500 50  0000 L CNN
F 1 "1k" H 4300 3400 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4380 3450 50  0001 C CNN
F 3 "~" H 4450 3450 50  0001 C CNN
	1    4450 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2850 2150 3600
Wire Wire Line
	2150 3600 2800 3600
Wire Wire Line
	2150 2750 2150 2400
Wire Wire Line
	2150 2400 2600 2400
Connection ~ 3500 3600
Wire Wire Line
	4450 3600 4450 4200
Wire Wire Line
	4450 4200 4950 4200
Wire Wire Line
	5700 4200 5800 4200
Connection ~ 5700 4200
Wire Wire Line
	5800 4200 6000 4200
Connection ~ 5800 4200
Wire Wire Line
	6000 4200 6100 4200
Connection ~ 6000 4200
NoConn ~ 5400 3800
Wire Wire Line
	4850 3100 4850 3200
Wire Wire Line
	4850 3200 5400 3200
Connection ~ 4450 3600
Wire Wire Line
	4450 3000 4450 3300
Wire Wire Line
	4600 2450 4600 2500
Wire Wire Line
	4600 2500 5050 2500
Wire Wire Line
	5050 2500 5050 3000
Connection ~ 4600 2500
Wire Wire Line
	4600 2500 4600 2550
Wire Wire Line
	4100 3000 4450 3000
Wire Wire Line
	3500 2400 3500 2050
Connection ~ 3500 2400
Wire Wire Line
	4300 2250 4300 2700
Connection ~ 4300 2700
Wire Wire Line
	4300 2700 4300 2750
Wire Wire Line
	4600 3600 4450 3600
Wire Wire Line
	4600 2950 4600 3600
NoConn ~ 5400 3400
NoConn ~ 5400 3600
Wire Wire Line
	5400 2900 5400 2800
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 5F373F07
P 7000 2850
F 0 "J5" H 7080 2842 50  0000 L CNN
F 1 "Motor_Terminal" H 7080 2751 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 7000 2850 50  0001 C CNN
F 3 "~" H 7000 2850 50  0001 C CNN
	1    7000 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 2800 6550 2800
Wire Wire Line
	6550 2800 6550 2850
Wire Wire Line
	6550 2850 6800 2850
Wire Wire Line
	6400 3000 6550 3000
Wire Wire Line
	6550 3000 6550 2950
Wire Wire Line
	6550 2950 6800 2950
$Comp
L Device:C C1
U 1 1 5F375986
P 2800 3000
F 0 "C1" H 2850 3100 50  0000 L CNN
F 1 "200nF" H 2550 3100 50  0000 L CNN
F 2 "Capacitor_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 2838 2850 50  0001 C CNN
F 3 "~" H 2800 3000 50  0001 C CNN
	1    2800 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2850 2800 2400
Connection ~ 2800 2400
Wire Wire Line
	2800 2400 3500 2400
Wire Wire Line
	2800 3150 2800 3600
Connection ~ 2800 3600
Wire Wire Line
	2800 3600 2900 3600
Text Label 2150 2400 0    50   ~ 0
VCC
Text Label 2150 3600 0    50   ~ 0
GND
$Comp
L Device:LED D1
U 1 1 5F37DD5F
P 4950 3550
F 0 "D1" V 4950 3700 50  0000 R CNN
F 1 "LED" V 4850 3750 50  0000 R CNN
F 2 "LED_THT:LED_D4.0mm" H 4950 3550 50  0001 C CNN
F 3 "~" H 4950 3550 50  0001 C CNN
	1    4950 3550
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D2
U 1 1 5F37FDD5
P 5100 3550
F 0 "D2" V 5100 3450 50  0000 R CNN
F 1 "LED" V 5000 3450 50  0000 R CNN
F 2 "LED_THT:LED_D4.0mm" H 5100 3550 50  0001 C CNN
F 3 "~" H 5100 3550 50  0001 C CNN
	1    5100 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5050 3000 5100 3000
Wire Wire Line
	5100 3400 5100 3000
Connection ~ 5100 3000
Wire Wire Line
	5100 3000 5400 3000
Wire Wire Line
	4950 2900 4950 3400
Connection ~ 4950 2900
Wire Wire Line
	4950 2900 5400 2900
$Comp
L Device:R R2
U 1 1 5F385F60
P 4950 3850
F 0 "R2" H 4800 3900 50  0000 L CNN
F 1 "22k" H 4750 3800 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4880 3850 50  0001 C CNN
F 3 "~" H 4950 3850 50  0001 C CNN
	1    4950 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5F3865FF
P 5100 3850
F 0 "R3" H 5170 3896 50  0000 L CNN
F 1 "22k" H 5170 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5030 3850 50  0001 C CNN
F 3 "~" H 5100 3850 50  0001 C CNN
	1    5100 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4000 5100 4200
Connection ~ 5100 4200
Wire Wire Line
	5100 4200 5700 4200
Wire Wire Line
	4950 4000 4950 4200
Connection ~ 4950 4200
Wire Wire Line
	4950 4200 5100 4200
$Comp
L Transistor_FET:2N7000 Q2
U 1 1 5F3C20AB
P 4500 2750
F 0 "Q2" H 4704 2796 50  0000 L CNN
F 1 "2N7000" H 4704 2705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4700 2675 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 4500 2750 50  0001 L CNN
	1    4500 2750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BS250 Q1
U 1 1 5F3C6086
P 4500 2250
F 0 "Q1" H 4704 2296 50  0000 L CNN
F 1 "BS250" H 4704 2205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4700 2175 50  0001 L CIN
F 3 "http://www.vishay.com/docs/70209/70209.pdf" H 4500 2250 50  0001 L CNN
	1    4500 2250
	1    0    0    -1  
$EndComp
NoConn ~ 6400 3400
NoConn ~ 6400 3600
Wire Wire Line
	4600 2050 5800 2050
Wire Wire Line
	5800 2050 5800 2400
Connection ~ 4600 2050
Wire Wire Line
	5800 2050 6000 2050
Wire Wire Line
	6000 2050 6000 2400
Connection ~ 5800 2050
Wire Wire Line
	4100 3200 4100 3700
Wire Wire Line
	4100 3700 3450 3700
Wire Wire Line
	4100 2900 4150 2900
Wire Wire Line
	4150 2900 4150 3750
Wire Wire Line
	4150 3750 3350 3750
Wire Wire Line
	4100 3100 4850 3100
Wire Wire Line
	4200 3800 3250 3800
Wire Wire Line
	4100 2700 4250 2700
Wire Wire Line
	4250 2700 4250 2900
Connection ~ 4250 2700
Wire Wire Line
	4250 2700 4300 2700
Wire Wire Line
	4250 2900 4950 2900
Wire Wire Line
	4100 2800 4200 2800
Wire Wire Line
	4200 2800 4200 3800
Wire Wire Line
	4250 2900 4250 3850
Connection ~ 4250 2900
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 5F405687
P 4700 1450
F 0 "J4" H 4672 1332 50  0000 R CNN
F 1 "Joy_Con" H 4672 1423 50  0000 R CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x02_P2.00mm_Vertical" H 4700 1450 50  0001 C CNN
F 3 "~" H 4700 1450 50  0001 C CNN
	1    4700 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 2050 4600 1650
Wire Wire Line
	4450 3000 4700 3000
Connection ~ 4450 3000
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 5F40C008
P 4050 1450
F 0 "J3" V 4112 1594 50  0000 L CNN
F 1 "LED_Con" V 4203 1594 50  0000 L CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x04_P2.00mm_Vertical" H 4050 1450 50  0001 C CNN
F 3 "~" H 4050 1450 50  0001 C CNN
	1    4050 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 1650 4700 3000
Wire Wire Line
	3500 2050 3950 2050
Wire Wire Line
	3950 1650 3950 2050
Connection ~ 3950 2050
Wire Wire Line
	3950 2050 4600 2050
Wire Wire Line
	3850 1650 3850 2000
Wire Wire Line
	3850 2000 2900 2000
Wire Wire Line
	2900 2000 2900 3600
Connection ~ 2900 3600
Wire Wire Line
	2900 3600 3150 3600
Wire Wire Line
	4150 2900 4150 2250
Wire Wire Line
	4150 2250 4050 2250
Wire Wire Line
	4050 2250 4050 1650
Connection ~ 4150 2900
Wire Wire Line
	4150 1650 4150 2200
Wire Wire Line
	4150 2200 4200 2200
Wire Wire Line
	4200 2200 4200 2800
Connection ~ 4200 2800
$Comp
L Connector:Conn_01x08_Male J2
U 1 1 5F6FCD72
P 3250 4800
F 0 "J2" V 3177 4728 50  0000 C CNN
F 1 "Prog_Con" V 3086 4728 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x08_P2.00mm_Vertical" H 3250 4800 50  0001 C CNN
F 3 "~" H 3250 4800 50  0001 C CNN
	1    3250 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2600 2400 2600 4550
Wire Wire Line
	2600 4550 3050 4550
Wire Wire Line
	3050 4550 3050 4600
Connection ~ 2600 2400
Wire Wire Line
	2600 2400 2800 2400
NoConn ~ 2950 4600
Wire Wire Line
	3250 3800 3250 4600
Wire Wire Line
	3350 4600 3350 3750
Wire Wire Line
	3450 4600 3450 3700
Wire Wire Line
	3550 3850 3550 4600
Wire Wire Line
	3550 3850 4250 3850
Connection ~ 3150 3600
Wire Wire Line
	3150 3600 3500 3600
Wire Wire Line
	3150 3600 3150 4600
Wire Wire Line
	3500 3600 4450 3600
NoConn ~ 3650 4600
Text Label 3700 3700 0    50   ~ 0
Reset
Text Label 4300 2500 0    50   ~ 0
Pin0
Text Label 4150 1900 0    50   ~ 0
Pin1
Text Label 4050 2000 0    50   ~ 0
Pin2
Text Label 4700 1850 0    50   ~ 0
Pin3
Text Label 4700 3100 0    50   ~ 0
Pin4
Text Label 5050 2600 0    50   ~ 0
NPin0
Text Label 6550 2850 0    50   ~ 0
Motor1
Text Label 6550 2950 0    50   ~ 0
Motor2
$EndSCHEMATC
