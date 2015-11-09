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
LIBS:Misc_Poncho_Grande
LIBS:Poncho_Esqueleto
LIBS:Bluetooth_RN4020-cache
EELAYER 25 0
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
P 5400 4550
F 0 "R1" V 5480 4550 40  0000 C CNN
F 1 "R" V 5407 4551 40  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5300 4550 30  0001 C CNN
F 3 "~" H 5400 4550 30  0000 C CNN
	1    5400 4550
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 561FB9E9
P 5400 5200
F 0 "D1" H 5400 5300 50  0000 C CNN
F 1 "LED" H 5400 5100 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 5400 5200 60  0001 C CNN
F 3 "~" H 5400 5200 60  0000 C CNN
	1    5400 5200
	0    1    -1   0   
$EndComp
$Comp
L R R2
U 1 1 561FB9EB
P 5700 4550
F 0 "R2" V 5780 4550 40  0000 C CNN
F 1 "R" V 5707 4551 40  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5630 4550 30  0001 C CNN
F 3 "~" H 5700 4550 30  0000 C CNN
	1    5700 4550
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 561FB9EC
P 6000 4550
F 0 "R3" V 6080 4550 40  0000 C CNN
F 1 "R" V 6007 4551 40  0000 C CNN
F 2 "Resistors_SMD:R_1206" V 5930 4550 30  0001 C CNN
F 3 "~" H 6000 4550 30  0000 C CNN
	1    6000 4550
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 561FB9ED
P 5700 5200
F 0 "D2" H 5700 5300 50  0000 C CNN
F 1 "LED" H 5700 5100 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 5700 5200 60  0001 C CNN
F 3 "~" H 5700 5200 60  0000 C CNN
	1    5700 5200
	0    1    -1   0   
$EndComp
$Comp
L LED D3
U 1 1 561FB9EE
P 6000 5200
F 0 "D3" H 6000 5300 50  0000 C CNN
F 1 "LED" H 6000 5100 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 6000 5200 60  0001 C CNN
F 3 "~" H 6000 5200 60  0000 C CNN
	1    6000 5200
	0    1    -1   0   
$EndComp
$Comp
L +3.3V #PWR01
U 1 1 561FB9EF
P 7250 2100
F 0 "#PWR01" H 7250 2060 30  0001 C CNN
F 1 "+3.3V" H 7250 2210 30  0000 C CNN
F 2 "" H 7250 2100 60  0000 C CNN
F 3 "" H 7250 2100 60  0000 C CNN
	1    7250 2100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 561FCE9A
P 7250 2650
F 0 "#PWR02" H 7250 2400 50  0001 C CNN
F 1 "GND" H 7250 2500 50  0000 C CNN
F 2 "" H 7250 2650 60  0000 C CNN
F 3 "" H 7250 2650 60  0000 C CNN
	1    7250 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 561FD06E
P 6500 3900
F 0 "#PWR03" H 6500 3650 50  0001 C CNN
F 1 "GND" H 6500 3750 50  0000 C CNN
F 2 "" H 6500 3900 60  0000 C CNN
F 3 "" H 6500 3900 60  0000 C CNN
	1    6500 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 561FD154
P 5350 3900
F 0 "#PWR04" H 5350 3650 50  0001 C CNN
F 1 "GND" H 5350 3750 50  0000 C CNN
F 2 "" H 5350 3900 60  0000 C CNN
F 3 "" H 5350 3900 60  0000 C CNN
	1    5350 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 561FD233
P 5000 2050
F 0 "#PWR05" H 5000 1800 50  0001 C CNN
F 1 "GND" H 5000 1900 50  0000 C CNN
F 2 "" H 5000 2050 60  0000 C CNN
F 3 "" H 5000 2050 60  0000 C CNN
	1    5000 2050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR06
U 1 1 561FD25C
P 6800 2050
F 0 "#PWR06" H 6800 1800 50  0001 C CNN
F 1 "GND" H 6800 1900 50  0000 C CNN
F 2 "" H 6800 2050 60  0000 C CNN
F 3 "" H 6800 2050 60  0000 C CNN
	1    6800 2050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 561FD579
P 6150 5600
F 0 "#PWR07" H 6150 5350 50  0001 C CNN
F 1 "GND" H 6150 5450 50  0000 C CNN
F 2 "" H 6150 5600 60  0000 C CNN
F 3 "" H 6150 5600 60  0000 C CNN
	1    6150 5600
	1    0    0    -1  
$EndComp
NoConn ~ 6800 2800
NoConn ~ 6800 3100
NoConn ~ 6000 3850
NoConn ~ 5050 2500
NoConn ~ 5050 2350
NoConn ~ 5050 2200
$Comp
L RN4020 U1
U 1 1 561FC38B
P 5950 2700
F 0 "U1" H 5300 3650 60  0001 C CNN
F 1 "RN4020" H 6450 3650 60  0000 C CNN
F 2 "RN4020:RN4020" H 6450 3650 60  0001 C CNN
F 3 "" H 6450 3650 60  0000 C CNN
	1    5950 2700
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 5637C0B9
P 7250 2400
F 0 "C1" H 7275 2500 50  0000 L CNN
F 1 "CP1" H 7275 2300 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeB_EIA-3528_Reflow" H 7250 2400 60  0001 C CNN
F 3 "" H 7250 2400 60  0000 C CNN
	1    7250 2400
	1    0    0    -1  
$EndComp
$Comp
L Conn_PonchoMP_2x_20x2 XA1
U 6 1 563B682E
P 3550 2700
F 0 "XA1" H 3550 3250 60  0000 C CNN
F 1 "Conn_PonchoMP_2x_20x2" H 3550 3150 60  0000 C CNN
F 2 "" H 3400 3050 60  0000 C CNN
F 3 "" H 3400 3050 60  0000 C CNN
	6    3550 2700
	1    0    0    -1  
$EndComp
$Comp
L Conn_PonchoMP_2x_20x2 XA1
U 11 1 563B6FF4
P 8750 3450
F 0 "XA1" H 8750 4000 60  0000 C CNN
F 1 "Conn_PonchoMP_2x_20x2" H 8750 3900 60  0000 C CNN
F 2 "" H 8600 3800 60  0000 C CNN
F 3 "" H 8600 3800 60  0000 C CNN
	11   8750 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	6000 5550 6000 5400
Wire Wire Line
	5400 5400 5400 5550
Connection ~ 6000 5550
Wire Wire Line
	5700 5400 5700 5550
Connection ~ 5700 5550
Wire Wire Line
	5400 5550 6150 5550
Wire Wire Line
	7250 2550 7250 2650
Wire Wire Line
	5700 3850 5700 4400
Wire Wire Line
	5400 4100 5400 4400
Wire Wire Line
	5400 4100 5550 4100
Wire Wire Line
	5550 4100 5550 3850
Wire Wire Line
	5850 3850 5850 4100
Wire Wire Line
	5850 4100 6000 4100
Wire Wire Line
	6000 4100 6000 4400
Wire Wire Line
	6000 4700 6000 5000
Wire Wire Line
	5700 4700 5700 5000
Wire Wire Line
	5400 4700 5400 5000
Wire Wire Line
	6150 5550 6150 5600
Wire Wire Line
	5050 2050 5000 2050
Wire Wire Line
	7250 2250 7250 2100
Connection ~ 7250 2200
Wire Wire Line
	5350 3850 5350 3900
Wire Wire Line
	6500 3900 6500 3850
Wire Wire Line
	7250 2200 6800 2200
NoConn ~ 8300 3150
NoConn ~ 8300 3350
NoConn ~ 8300 3550
NoConn ~ 8300 3750
Text GLabel 5000 2950 0    60   Input ~ 0
SW
Text GLabel 8200 3650 0    60   Input ~ 0
SW
Wire Wire Line
	8200 3650 8300 3650
Text GLabel 6300 3900 3    60   Input ~ 0
HW
Text GLabel 6150 3900 3    60   Input ~ 0
CTS
Wire Wire Line
	6150 3900 6150 3850
Wire Wire Line
	6300 3900 6300 3850
Wire Wire Line
	5000 2950 5050 2950
Text GLabel 5000 3100 0    60   Input ~ 0
CMD
Text GLabel 8200 3450 0    60   Input ~ 0
CMD
Text GLabel 8200 3050 0    60   Input ~ 0
HW
Text GLabel 8200 3250 0    60   Input ~ 0
CTS
Text GLabel 3950 2800 2    60   Input ~ 0
TX
Text GLabel 3950 2600 2    60   Input ~ 0
RX
Text GLabel 5000 2650 0    60   Input ~ 0
TX
Text GLabel 5000 2800 0    60   Input ~ 0
RX
Wire Wire Line
	3850 2750 3900 2750
Wire Wire Line
	3900 2750 3900 2800
Wire Wire Line
	3900 2800 3950 2800
Wire Wire Line
	3850 2650 3900 2650
Wire Wire Line
	3900 2650 3900 2600
Wire Wire Line
	3900 2600 3950 2600
Wire Wire Line
	5000 2650 5050 2650
Wire Wire Line
	5000 2800 5050 2800
Wire Wire Line
	5000 3100 5050 3100
Text GLabel 6850 2950 2    60   Input ~ 0
RTS
Text GLabel 8200 2900 0    60   Input ~ 0
RTS
Wire Wire Line
	6850 2950 6800 2950
Wire Wire Line
	8250 2950 8300 2950
Wire Wire Line
	8250 2950 8250 2900
Wire Wire Line
	8250 2900 8200 2900
Wire Wire Line
	8200 3050 8300 3050
Wire Wire Line
	8300 3250 8200 3250
Wire Wire Line
	8200 3450 8300 3450
$EndSCHEMATC
