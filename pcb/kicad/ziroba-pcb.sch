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
LIBS:SN754410
LIBS:ziroba-pcb-cache
EELAYER 25 0
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
L SN754410 IC1
U 1 1 59138FD8
P 3350 2100
F 0 "IC1" H 2950 2800 50  0000 L BNN
F 1 "SN754410" H 3550 1700 50  0000 L BNN
F 2 "HBridge-DIP16" H 3350 2250 50  0001 C CNN
F 3 "" H 3350 2100 60  0001 C CNN
	1    3350 2100
	1    0    0    -1  
$EndComp
$Comp
L SN754410 IC?
U 1 1 59139045
P 5900 2100
F 0 "IC?" H 5500 2800 50  0000 L BNN
F 1 "SN754410" H 6100 1700 50  0000 L BNN
F 2 "HBridge-DIP16" H 5900 2250 50  0001 C CNN
F 3 "" H 5900 2100 60  0001 C CNN
	1    5900 2100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59139156
P 5700 2750
F 0 "#PWR?" H 5700 2500 50  0001 C CNN
F 1 "GND" H 5700 2600 50  0000 C CNN
F 2 "" H 5700 2750 50  0001 C CNN
F 3 "" H 5700 2750 50  0001 C CNN
	1    5700 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5913916E
P 3150 2750
F 0 "#PWR?" H 3150 2500 50  0001 C CNN
F 1 "GND" H 3150 2600 50  0000 C CNN
F 2 "" H 3150 2750 50  0001 C CNN
F 3 "" H 3150 2750 50  0001 C CNN
	1    3150 2750
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 591393EC
P 2300 1900
F 0 "R1" V 2380 1900 50  0000 C CNN
F 1 "10K" V 2300 1900 50  0000 C CNN
F 2 "" V 2230 1900 50  0001 C CNN
F 3 "" H 2300 1900 50  0001 C CNN
	1    2300 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5913941D
P 2300 2200
F 0 "#PWR?" H 2300 1950 50  0001 C CNN
F 1 "GND" H 2300 2050 50  0000 C CNN
F 2 "" H 2300 2200 50  0001 C CNN
F 3 "" H 2300 2200 50  0001 C CNN
	1    2300 2200
	1    0    0    -1  
$EndComp
Text GLabel 3250 650  0    60   Input ~ 0
VM
Text GLabel 3250 800  0    60   Input ~ 0
Pi5V
Text GLabel 1900 1700 0    60   Input ~ 0
PWM1
$Comp
L CONN_01X02 J?
U 1 1 5915A944
P 2650 2550
F 0 "J?" H 2650 2700 50  0000 C CNN
F 1 "CONN_01X02" V 2750 2550 50  0000 C CNN
F 2 "" H 2650 2550 50  0001 C CNN
F 3 "" H 2650 2550 50  0001 C CNN
	1    2650 2550
	0    1    1    0   
$EndComp
$Comp
L CONN_01X02 J?
U 1 1 5915A963
P 4250 2550
F 0 "J?" H 4250 2700 50  0000 C CNN
F 1 "CONN_01X02" V 4350 2550 50  0000 C CNN
F 2 "" H 4250 2550 50  0001 C CNN
F 3 "" H 4250 2550 50  0001 C CNN
	1    4250 2550
	0    1    1    0   
$EndComp
$Comp
L CONN_01X02 J?
U 1 1 5915E15F
P 1600 1350
F 0 "J?" H 1600 1500 50  0000 C CNN
F 1 "CONN_01X02" V 1700 1350 50  0000 C CNN
F 2 "" H 1600 1350 50  0001 C CNN
F 3 "" H 1600 1350 50  0001 C CNN
	1    1600 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 2600 3150 2750
Wire Wire Line
	3150 2700 3450 2700
Wire Wire Line
	3250 2700 3250 2600
Connection ~ 3150 2700
Wire Wire Line
	3350 2700 3350 2600
Connection ~ 3250 2700
Wire Wire Line
	3450 2700 3450 2600
Connection ~ 3350 2700
Wire Wire Line
	5700 2600 5700 2750
Wire Wire Line
	5800 2600 5800 2650
Wire Wire Line
	5700 2650 6000 2650
Connection ~ 5700 2650
Wire Wire Line
	5900 2650 5900 2600
Connection ~ 5800 2650
Wire Wire Line
	6000 2650 6000 2600
Connection ~ 5900 2650
Wire Wire Line
	2300 2050 2300 2200
Wire Wire Line
	1900 1700 2750 1700
Wire Wire Line
	2300 1700 2300 1750
Connection ~ 2300 1700
Wire Wire Line
	2450 1700 2450 1000
Wire Wire Line
	2450 1000 4400 1000
Wire Wire Line
	4400 1000 4400 1700
Wire Wire Line
	4400 1700 4050 1700
Connection ~ 2450 1700
Wire Wire Line
	2750 1150 2750 1800
Wire Wire Line
	2750 1150 4050 1150
Wire Wire Line
	4050 1150 4050 1800
Wire Wire Line
	2650 1900 2750 1900
Wire Wire Line
	2650 1100 2650 1900
Wire Wire Line
	2650 1100 4150 1100
Wire Wire Line
	4150 1100 4150 1900
Wire Wire Line
	4150 1900 4050 1900
Wire Wire Line
	1800 1300 2750 1300
Connection ~ 2750 1300
Wire Wire Line
	3450 650  3450 1200
Wire Wire Line
	3350 800  3350 1200
Wire Wire Line
	3450 650  3250 650 
Wire Wire Line
	3250 800  3350 800 
Wire Wire Line
	2700 2350 2700 2200
Wire Wire Line
	2700 2200 2750 2200
Wire Wire Line
	2600 2350 2600 2100
Wire Wire Line
	2600 2100 2750 2100
Wire Wire Line
	4300 2350 4300 2200
Wire Wire Line
	4300 2200 4050 2200
Wire Wire Line
	4200 2350 4200 2100
Wire Wire Line
	4200 2100 4050 2100
Wire Wire Line
	1800 1400 2650 1400
Connection ~ 2650 1400
$EndSCHEMATC
