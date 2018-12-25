# Jetta CAN

Control the gauges and lights of a Jetta instrument cluster via CAN bus.

## Parts
Using the following hardware:

- 2014 Jetta instrument cluster (used, Ebay)
- Arduino UNO
- Seeed Studio CAN bus shield v2
- hookup wires and cables
- AC-DC 12V PSU (Velleman)

Using the following software:

- Eclipse Photon
- Sloeber
- CAN bus shield library https://github.com/Seeed-Studio/CAN_BUS_Shield

## Connections
Found a pretty good reference.

- 16 GND (31)
- 28 CANH
- 29 CANL
- 31 +12V ignition (15)
- 30 +12V battery (30)

### Quick connect
Until proper wiring harness:

TOP
27 11
28 12
29 13
30 14
31 15
32 16
BOTTOM

Use 8-pin F-F for pins 32-27=ROYGUB
Use 3 pin F-F for pins 16-14=BRW

### Cluster boot
16=GND, 32=B, 31=B




## received ids
The cluster emits the following:

- 320
- 420
- 621
- 727

## transmit ids
the cluster receives the following PGNs:

- 050 airbag
- 1A0 abs
- 280 tachometer
- 470 operating lights, warning lights, doors
- 480 engine malfunction, fuel cap
- 5A0 speed and drive mode


## Instrument indicators

### Gauges
Tachometer
Speedometer
Mileage
Trip mileage
Time of day
Fuel
Outside temperature

### Telltales
Oil *
Engine coolant temperature low/level low/malfunction *
Door mirror? *
Power steering malfunction/reduced/locked *
Engine check MIL *
Off road *
ABS *
Tire pressure *
Airbag *
Door open
Trunk open
High beam
Fog lamp
Left turn
Right turn
Clutch/park
Key battery
Glow plug preheating
Brake pedal not depressed
Handbrake *
ESC
CRUISE
Alternator malfunction
EPC engine control malfunction

Fuel low
Fuel cap not tight/missing

### Sounds

## Notes and references
Wikipedia gives the translation formulas
https://en.wikipedia.org/wiki/OBD-II_PIDs

Dashboard symbols
https://www.vwserviceandparts.com/service/volkswagen-dashboard-indicator-lights/
(different than the 2014)

A good resource including a sample ino file. Got a lot of the data details here.
https://hackaday.io/project/6288-volkswagen-can-bus-gaming

Volkswagen Communication
But does seem to have the CAN IDs
https://www.snapon.com/Files/Diagnostics/UserManuals/VolkswagenAudiVehicleCommunicationSoftwareManual_EAZ0031B01D.pdf

http://www.copperhilltechnologies.com/can-bus-guide-message-frame-format

Some very detailed overview of particular vehicles:
https://www.slideshare.net/soxxxcool/car-hacking

### Bitfields
We can use bit fields, shift masks, B-literal masks.
Bit fields are not very portable.
Here's some info on a C++ way to have portable bit fields: https://stackoverflow.com/questions/31726191/is-there-a-portable-alternative-to-c-bitfields

### Decoding the CAN bus

#### General decoding
https://hackaday.io/project/6288/instructions
https://christian-rossow.de/publications/vatican-ches2016.pdf
https://sites.google.com/view/dashboard-control/can-bus-hardware

#### Hacking 0x280: 
http://ev-a2.blogspot.com/2013/06/can-bus-analysis-started.html

### 0x470
Turning lights 2?
