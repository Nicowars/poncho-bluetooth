EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:RN4020
LIBS:Bluetooth_RN4020-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "29 oct 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R1
U 1 1 561FB9E7
P 2900 6250
F 0 "R1" V 2980 6250 40  0000 C CNN
F 1 "R" V 2907 6251 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 2800 6250 30  0000 C CNN
F 3 "~" H 2900 6250 30  0000 C CNN
	1    2900 6250
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 561FB9E8
P 4750 4100
F 0 "C1" H 4750 4200 40  0001 L CNN
F 1 "C" H 4756 4015 40  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeA_EIA-3216_HandSoldering" H 4788 3950 30  0000 C CNN
F 3 "~" H 4750 4100 60  0000 C CNN
	1    4750 4100
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 561FB9E9
P 2900 6900
F 0 "D1" H 2900 7000 50  0000 C CNN
F 1 "LED" H 2900 6800 50  0000 C CNN
F 2 "" H 2900 6900 60  0000 C CNN
F 3 "~" H 2900 6900 60  0000 C CNN
	1    2900 6900
	0    1    -1   0   
$EndComp
$Comp
L R R2
U 1 1 561FB9EB
P 3200 6250
F 0 "R2" V 3280 6250 40  0000 C CNN
F 1 "R" V 3207 6251 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3130 6250 30  0000 C CNN
F 3 "~" H 3200 6250 30  0000 C CNN
	1    3200 6250
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 561FB9EC
P 3500 6250
F 0 "R3" V 3580 6250 40  0000 C CNN
F 1 "R" V 3507 6251 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3430 6250 30  0000 C CNN
F 3 "~" H 3500 6250 30  0000 C CNN
	1    3500 6250
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 561FB9ED
P 3200 6900
F 0 "D2" H 3200 7000 50  0000 C CNN
F 1 "LED" H 3200 6800 50  0000 C CNN
F 2 "" H 3200 6900 60  0000 C CNN
F 3 "~" H 3200 6900 60  0000 C CNN
	1    3200 6900
	0    1    -1   0   
$EndComp
$Comp
L LED D3
U 1 1 561FB9EE
P 3500 6900
F 0 "D3" H 3500 7000 50  0000 C CNN
F 1 "LED" H 3500 6800 50  0000 C CNN
F 2 "" H 3500 6900 60  0000 C CNN
F 3 "~" H 3500 6900 60  0000 C CNN
	1    3500 6900
	0    1    -1   0   
$EndComp
$Comp
L +3.3V #PWR01
U 1 1 561FB9EF
P 4750 3800
F 0 "#PWR01" H 4750 3760 30  0001 C CNN
F 1 "+3.3V" H 4750 3910 30  0000 C CNN
F 2 "" H 4750 3800 60  0000 C CNN
F 3 "" H 4750 3800 60  0000 C CNN
	1    4750 3800
	1    0    0    -1  
$EndComp
Text GLabel 2350 4350 0    60   Input ~ 0
UART_TX
Text GLabel 2350 4500 0    60   Input ~ 0
UART_RX
Text GLabel 4600 4650 2    60   Input ~ 0
RTS
Text GLabel 3750 6050 3    60   Input ~ 0
CTS
Text GLabel 2350 4800 0    60   Input ~ 0
CMD
Text GLabel 2350 4650 0    60   Input ~ 0
SW
Text GLabel 3950 6050 3    60   Input ~ 0
HW
$Comp
L RN4020 U1
U 1 1 561FC38B
P 3450 4400
F 0 "U1" H 2800 5350 60  0001 C CNN
F 1 "RN4020" H 3950 5350 60  0000 C CNN
F 2 "" H 3950 5350 60  0001 C CNN
F 3 "" H 3950 5350 60  0000 C CNN
	1    3450 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 7250 3500 7100
Wire Wire Line
	2900 7100 2900 7250
Connection ~ 3500 7250
Wire Wire Line
	3200 7100 3200 7250
Connection ~ 3200 7250
Wire Wire Line
	2900 7250 3650 7250
Wire Wire Line
	4600 4650 4300 4650
$Comp
L GND #PWR02
U 1 1 561FCE9A
P 4750 4350
F 0 "#PWR02" H 4750 4100 50  0001 C CNN
F 1 "GND" H 4750 4200 50  0000 C CNN
F 2 "" H 4750 4350 60  0000 C CNN
F 3 "" H 4750 4350 60  0000 C CNN
	1    4750 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 561FD06E
P 4000 5550
F 0 "#PWR03" H 4000 5300 50  0001 C CNN
F 1 "GND" H 4000 5400 50  0000 C CNN
F 2 "" H 4000 5550 60  0000 C CNN
F 3 "" H 4000 5550 60  0000 C CNN
	1    4000 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 561FD154
P 2850 5550
F 0 "#PWR04" H 2850 5300 50  0001 C CNN
F 1 "GND" H 2850 5400 50  0000 C CNN
F 2 "" H 2850 5550 60  0000 C CNN
F 3 "" H 2850 5550 60  0000 C CNN
	1    2850 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 561FD233
P 2500 3750
F 0 "#PWR05" H 2500 3500 50  0001 C CNN
F 1 "GND" H 2500 3600 50  0000 C CNN
F 2 "" H 2500 3750 60  0000 C CNN
F 3 "" H 2500 3750 60  0000 C CNN
	1    2500 3750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR06
U 1 1 561FD25C
P 4300 3750
F 0 "#PWR06" H 4300 3500 50  0001 C CNN
F 1 "GND" H 4300 3600 50  0000 C CNN
F 2 "" H 4300 3750 60  0000 C CNN
F 3 "" H 4300 3750 60  0000 C CNN
	1    4300 3750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 561FD579
P 3650 7300
F 0 "#PWR07" H 3650 7050 50  0001 C CNN
F 1 "GND" H 3650 7150 50  0000 C CNN
F 2 "" H 3650 7300 60  0000 C CNN
F 3 "" H 3650 7300 60  0000 C CNN
	1    3650 7300
	1    0    0    -1  
$EndComp
NoConn ~ 4300 4500
NoConn ~ 4300 4800
NoConn ~ 3500 5550
NoConn ~ 2550 4200
NoConn ~ 2550 4050
NoConn ~ 2550 3900
Wire Wire Line
	4750 4300 4750 4350
Wire Wire Line
	3200 6000 3200 5550
Wire Wire Line
	2900 6000 2900 5800
Wire Wire Line
	2900 5800 3050 5800
Wire Wire Line
	3050 5800 3050 5550
Wire Wire Line
	3350 5550 3350 5800
Wire Wire Line
	3350 5800 3500 5800
Wire Wire Line
	3500 5800 3500 6000
Wire Wire Line
	3500 6700 3500 6500
Wire Wire Line
	3200 6500 3200 6700
Wire Wire Line
	2900 6700 2900 6500
Wire Wire Line
	3650 7250 3650 7300
Wire Wire Line
	3750 6050 3750 5800
Wire Wire Line
	3750 5800 3650 5800
Wire Wire Line
	3650 5800 3650 5550
Wire Wire Line
	3800 5550 3800 5800
Wire Wire Line
	3800 5800 3950 5800
Wire Wire Line
	3950 5800 3950 6050
Wire Wire Line
	2550 4350 2350 4350
Wire Wire Line
	2350 4500 2550 4500
Wire Wire Line
	2550 4650 2350 4650
Wire Wire Line
	2350 4800 2550 4800
Wire Wire Line
	4750 3800 4750 3900
Wire Wire Line
	4750 3900 4300 3900
Wire Wire Line
	2550 3750 2500 3750
$EndSCHEMATC
