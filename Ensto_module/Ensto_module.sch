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
L Connector:8P8C 8P8C_button1
U 1 1 5F241219
P 5650 5600
F 0 "8P8C_button1" V 5753 5170 50  0000 R CNN
F 1 "8P8C" V 5662 5170 50  0000 R CNN
F 2 "Connector_RJ:RJ45_Amphenol_54602-x08_Horizontal" V 5650 5625 50  0001 C CNN
F 3 "~" V 5650 5625 50  0001 C CNN
	1    5650 5600
	0    -1   -1   0   
$EndComp
$Comp
L Connector:8P8C 8P8C_MCU1
U 1 1 5F2422B7
P 4450 5600
F 0 "8P8C_MCU1" V 4553 5170 50  0000 R CNN
F 1 "8P8C" V 4462 5170 50  0000 R CNN
F 2 "Connector_RJ:RJ45_Amphenol_54602-x08_Horizontal" V 4450 5625 50  0001 C CNN
F 3 "~" V 4450 5625 50  0001 C CNN
	1    4450 5600
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x08_Male GPIO_button1
U 1 1 5F24774A
P 6650 4500
F 0 "GPIO_button1" H 6622 4382 50  0000 R CNN
F 1 "Conn_01x08_Male" H 6622 4473 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 6650 4500 50  0001 C CNN
F 3 "~" H 6650 4500 50  0001 C CNN
	1    6650 4500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x08_Male Support_pins1
U 1 1 5F249ADF
P 3450 3350
F 0 "Support_pins1" H 3558 3831 50  0000 C CNN
F 1 "Conn_01x08_Male" H 3558 3740 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 3450 3350 50  0001 C CNN
F 3 "~" H 3450 3350 50  0001 C CNN
	1    3450 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:R 220k_1
U 1 1 5F25119E
P 5200 3250
F 0 "220k_1" V 4993 3250 50  0000 C CNN
F 1 "R" V 5084 3250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 5130 3250 50  0001 C CNN
F 3 "~" H 5200 3250 50  0001 C CNN
	1    5200 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R 220_2
U 1 1 5F252959
P 4300 3500
F 0 "220_2" H 4370 3546 50  0000 L CNN
F 1 "R" H 4370 3455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 4230 3500 50  0001 C CNN
F 3 "~" H 4300 3500 50  0001 C CNN
	1    4300 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R 220_1
U 1 1 5F253046
P 4300 3200
F 0 "220_1" H 4370 3246 50  0000 L CNN
F 1 "R" H 4370 3155 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 4230 3200 50  0001 C CNN
F 3 "~" H 4300 3200 50  0001 C CNN
	1    4300 3200
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BS170 Down_transistor1
U 1 1 5F2539F0
P 5550 3250
F 0 "Down_transistor1" H 5754 3296 50  0000 L CNN
F 1 "BS170" H 5754 3205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5750 3175 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BS/BS170.pdf" H 5550 3250 50  0001 L CNN
	1    5550 3250
	1    0    0    -1  
$EndComp
Text GLabel 9700 5250 2    50   UnSpc ~ 0
power_1
Text GLabel 9700 4700 2    50   UnSpc ~ 0
power_1
Text GLabel 9700 4800 2    50   UnSpc ~ 0
power_2
Text GLabel 9700 4600 2    50   UnSpc ~ 0
encoder_GND
Text GLabel 9700 4500 2    50   UnSpc ~ 0
encoder_24V
Text GLabel 3650 4050 2    50   UnSpc ~ 0
encoder_3V
Text GLabel 5050 3250 0    50   UnSpc ~ 0
Button_GND
NoConn ~ 5350 5200
NoConn ~ 5450 5200
Text GLabel 5550 5200 1    50   UnSpc ~ 0
Button_up
NoConn ~ 5650 5200
NoConn ~ 5750 5200
Text GLabel 5650 4800 1    50   UnSpc ~ 0
Button_down
NoConn ~ 5950 5200
Text GLabel 5250 5200 1    50   UnSpc ~ 0
Button_GND
NoConn ~ 4150 5200
NoConn ~ 4250 5200
Text GLabel 4350 5200 1    50   UnSpc ~ 0
MCU_up
NoConn ~ 4450 5200
NoConn ~ 4550 5200
Text GLabel 4650 5200 1    50   UnSpc ~ 0
MCU_down
Text GLabel 4050 5200 1    50   UnSpc ~ 0
MCU_GND
Text GLabel 4750 5200 1    50   UnSpc ~ 0
MCU_5V
Text GLabel 5650 3450 2    50   UnSpc ~ 0
MCU_GND
Text GLabel 5700 4200 2    50   UnSpc ~ 0
MCU_GND
Text GLabel 5700 3800 2    50   UnSpc ~ 0
MCU_up
Text GLabel 5650 3050 2    50   UnSpc ~ 0
MCU_down
Text GLabel 6450 4500 0    50   UnSpc ~ 0
Output_up
Text GLabel 6450 4400 0    50   UnSpc ~ 0
Output_down
NoConn ~ 6450 4100
NoConn ~ 6450 4200
NoConn ~ 6450 4300
NoConn ~ 6450 4600
Text GLabel 5350 3250 1    50   UnSpc ~ 0
Output_down
NoConn ~ 6450 3050
NoConn ~ 6450 3150
NoConn ~ 6450 3250
NoConn ~ 6450 3450
NoConn ~ 6450 3550
NoConn ~ 6450 3650
NoConn ~ 6450 3750
NoConn ~ 6450 3850
NoConn ~ 6450 3950
NoConn ~ 3650 3050
NoConn ~ 3650 3150
NoConn ~ 3650 3250
NoConn ~ 3650 3450
NoConn ~ 3650 3550
NoConn ~ 3650 3750
NoConn ~ 3650 4150
NoConn ~ 3650 4250
NoConn ~ 3650 4350
NoConn ~ 3650 4450
NoConn ~ 3650 4550
Text GLabel 4300 3050 1    50   UnSpc ~ 0
Button_up
Text GLabel 6450 4800 0    50   UnSpc ~ 0
Button_up
Text GLabel 6450 4700 0    50   UnSpc ~ 0
Button_down
Text GLabel 4300 3650 3    50   UnSpc ~ 0
Button_down
Text GLabel 3650 3650 2    50   UnSpc ~ 0
Button_GND
Wire Wire Line
	3650 3350 4300 3350
Connection ~ 4300 3350
$Comp
L Connector:Conn_01x02_Male J11
U 1 1 5F2ACE47
P 3950 4650
F 0 "J11" H 4058 4831 50  0000 C CNN
F 1 "Conn_01x02_Male" H 4058 4740 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3950 4650 50  0001 C CNN
F 3 "~" H 3950 4650 50  0001 C CNN
	1    3950 4650
	1    0    0    -1  
$EndComp
Text GLabel 4150 4650 2    50   UnSpc ~ 0
MCU_5V
Wire Wire Line
	4150 4750 4150 4650
$Comp
L Transistor_FET:BS170 Up_transistor1
U 1 1 5F253F90
P 5600 4000
F 0 "Up_transistor1" H 5805 4046 50  0000 L CNN
F 1 "BS170" H 5805 3955 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5800 3925 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BS/BS170.pdf" H 5600 4000 50  0001 L CNN
	1    5600 4000
	1    0    0    -1  
$EndComp
Text GLabel 5400 4000 1    50   UnSpc ~ 0
Output_up
Text GLabel 5100 4000 0    50   UnSpc ~ 0
Button_GND
$Comp
L Device:R 220k_2
U 1 1 5F252766
P 5250 4000
F 0 "220k_2" V 5043 4000 50  0000 C CNN
F 1 "R" V 5134 4000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 5180 4000 50  0001 C CNN
F 3 "~" H 5250 4000 50  0001 C CNN
	1    5250 4000
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x04_Male Minifit_motor1
U 1 1 5F2B3C42
P 9500 4600
F 0 "Minifit_motor1" H 9608 4881 50  0000 C CNN
F 1 "Conn_01x04_Male" H 9608 4790 50  0000 C CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-04A2_2x02_P4.20mm_Horizontal" H 9500 4600 50  0001 C CNN
F 3 "~" H 9500 4600 50  0001 C CNN
	1    9500 4600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J8
U 1 1 5F2B7950
P 9500 5150
F 0 "J8" H 9608 5431 50  0000 C CNN
F 1 "Minifit_MCU" H 9608 5340 50  0000 C CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-04A2_2x02_P4.20mm_Horizontal" H 9500 5150 50  0001 C CNN
F 3 "~" H 9500 5150 50  0001 C CNN
	1    9500 5150
	1    0    0    -1  
$EndComp
Text GLabel 9700 5350 2    50   UnSpc ~ 0
power_2
Text GLabel 9700 5050 2    50   UnSpc ~ 0
encoder_24V
Text GLabel 9700 5150 2    50   UnSpc ~ 0
encoder_GND
$Comp
L Connector:Conn_01x10_Male GPIO_extra1
U 1 1 5F24BAE3
P 6650 3550
F 0 "GPIO_extra1" V 6650 2800 50  0000 C CNN
F 1 "Conn_01x10_Male" H 6576 3478 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 6650 3550 50  0001 C CNN
F 3 "~" H 6650 3550 50  0001 C CNN
	1    6650 3550
	-1   0    0    1   
$EndComp
NoConn ~ 6450 3350
Text GLabel 8700 5400 0    50   UnSpc ~ 0
encoder_GND
Text GLabel 8700 4200 0    50   UnSpc ~ 0
encoder_24V
Text GLabel 8700 4800 2    50   UnSpc ~ 0
encoder_3V
$Comp
L Device:R 10k1
U 1 1 5F252628
P 8700 5250
F 0 "10k1" H 8770 5296 50  0000 L CNN
F 1 "R" H 8770 5205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 8630 5250 50  0001 C CNN
F 3 "~" H 8700 5250 50  0001 C CNN
	1    8700 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:R 1k1
U 1 1 5F252403
P 8700 4950
F 0 "1k1" H 8770 4996 50  0000 L CNN
F 1 "R" H 8770 4905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 8630 4950 50  0001 C CNN
F 3 "~" H 8700 4950 50  0001 C CNN
	1    8700 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:R 56k1
U 1 1 5F251B9E
P 8700 4650
F 0 "56k1" H 8770 4696 50  0000 L CNN
F 1 "R" H 8770 4605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 8630 4650 50  0001 C CNN
F 3 "~" H 8700 4650 50  0001 C CNN
	1    8700 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R 22k1
U 1 1 5F2516C0
P 8700 4350
F 0 "22k1" H 8630 4304 50  0000 R CNN
F 1 "R" H 8630 4395 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P15.24mm_Horizontal" V 8630 4350 50  0001 C CNN
F 3 "~" H 8700 4350 50  0001 C CNN
	1    8700 4350
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Male Analog_pins1
U 1 1 5F24AD47
P 3450 4250
F 0 "Analog_pins1" H 3558 4631 50  0000 C CNN
F 1 "Conn_01x06_Male" H 3558 4540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3450 4250 50  0001 C CNN
F 3 "~" H 3450 4250 50  0001 C CNN
	1    3450 4250
	1    0    0    -1  
$EndComp
$EndSCHEMATC
