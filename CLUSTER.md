# Cluster decoder

## Cluster components
- tachometer and indicaTORS
- speedometerand indicators
- central display
- audio

## Tachometer
- tachometer 0-8 (thousands)

 test |
------|
 abc  |

Starting from the bottom CW
- temp
- traction off
- lane sensing
- EPC
- fuel cap (Y)
- oil (R/Y)
- high beam (B)
- fog beam (Y)
- gas (Y)
- engine check

Inner CW
- washer level
- battery
- parking brake
- interior light
- steering

Extra
- over rev

## Spedometer
- speedometer 0-160 MPH

starting from bottom CW
- spill?
- airbag (Y)
- break wear
- ABS (Y)
- offroad (Y)
- brake
- cruise
- tire pressure (Y)
- lane
- DRL

inner CW
- door ajar
- trunk ajar
- mirror
- seatbelt
- brake

## Emitted frames
The following PIDs are emitted from the cluster when the ignition is on.

| PID   | Period       | Typical                 | Notes |
|---    |---           |---                      |---    |
| 0x320 | 20 ms        | 1A 01 FF FF FF CX FF A9 | byte 5 varies see notes |
| 0x420 | 200 ms       | 95 FF FF 00 08 7F FF 84 | |
| 0x460 | varies       | see notes               | burst of eight |
| 0x520 | 200 ms       | 61 43 00 00 80 09 F4 00 | Sometimes period 400 ms |
| 0x51A | 500 ms       | FF FF FF FF FF FF FF 03 | Period varies |
| 0X52A | 2000 ms      | 00 00 00 00 00 00 00 00 | period varies |
| 0x5d2 | varies       | 00 00 00 00 00 33 56 57 | period and payload varies |
| 0x5f3 | 500 ms       | 08 00 FF 0F 00 00 00 00 | period varies |
| 0x60E | 1000 ms      | 97 00                   | bursts of two vary 70 sec or so |
| 0x621 | 100 ms       | 00 EF 05 FF 90 32 00 00 | |
| 0X629 | 1000 ms      | FE 4F FE BF A2 97 80 FF | |
| 0x62B | 1000 ms      | FE 2F 00 80 46 00 FE BF | |
| 0x62D | 1000 ms      | D0 47 15 80 1F 00 29 80 | |
| 0x62E | 1000 ms      | 09 f4 30 f1 bd 32 01    | payload varies |
| 0x727 | 200 ms       | 04 03 01 00 02 00 00    | |

### 320 instrument cluster
20 ms
typical
1A 01 FF FF FF CX FF A9
12 01 FF FF FF CX FF BF
where X varies
also change after the speedometer resets

### 420
200 ms
95 FF FF 00 08 7F FF 84 key on
91 FF FF 00 08 3A FF 80 key off
and some intermediate after turning on

### 0x460
period varies
typical
45301: received id: 460 ext: 0 rtr: 0 length: 8 data: 00 E6 43 06 21 11 00 00
45402: received id: 460 ext: 0 rtr: 0 length: 8 data: 01 0E 1B 0C 04 14 73 F4
45501: received id: 460 ext: 0 rtr: 0 length: 8 data: 02 00 00 45 30 FA 10 18
45601: received id: 460 ext: 0 rtr: 0 length: 8 data: 03 30 93 11 06 20 00 00
45702: received id: 460 ext: 0 rtr: 0 length: 8 data: 04 00 00 00 20 00 00 00
45803: received id: 460 ext: 0 rtr: 0 length: 8 data: 05 00 00 00 00 00 02 00
45903: received id: 460 ext: 0 rtr: 0 length: 8 data: 06 00 00 FF FF 00 00 00
46003: received id: 460 ext: 0 rtr: 0 length: 8 data: 07 00 AA AA AA AA AA AA

### 51A
500 ms varies
typical 
FF FF FF FF FF FF FF 03
byte[0] cycles FE, FC, FF, FD

### 520
200 ms, varies
typical 
61 43 00 00 80 09 F4 0
byte[0-1] varies

### 621 instrument cluster
100 ms
typical
00 EF 05 FF 90 32 00 00
00 00 80 FF 90 7F 17 00
00 00 80 FF 90 7F 1C 00
byte[6] seems to increment, but jumps arround every few seconds

### 62D
1000 ms
typical
D0 47 15 80 1F 00 29 80
FE 4F 00 80 8D 00 FE BF
FE 4F 00 80 21 00 FE BF
about one per second, but seems to come in bursts?
some of the values change
byte[4] seems to increment slowly

### 62E
1000 ms
typical
09 f4 30 f1 bd 32 01
byte[5-6] vary

### 727 instrument cluster
200 ms
length 7
4 3 1 0 2 0 0 key on
1 1 4 0 6 0 0 key off
2 3 5 0 6 0 0 key on cluster starting
4 3 1 0 2 0 0 cluster ready

(no ecus)
         1 3 5 0 6 0 0 key on
+200 x4  1 3 5 0 6 0 0
+200 x10 4 3 1 0 6 0 0
+200     4 3 1 0 2 0 0

## Connector pinouts
Source: http://www.polo6rfreunde.de/index.php/Thread/9562-Pinbelegung-Tacho-Stecker/

Verified pins are marked with asterisk.

| Pin | Function DE | Function EN |
|---  |---          |---          |
| 1 | Geber für Kraftstoffvorratsanzeige 1 (voll) | |
| 2 | Geber für Kraftstoffvorratsanzeige 1 (leer) | |
| 3 | Geber für Kraftstoffvorratsanzeige 2 (voll) | |
| 4 | Geber für Kraftstoffvorratsanzeige 2 (leer) | |
| 5 | nicht belegt | |
| 6 | nicht belegt | |
| 7 | Lesespule für Wegfahrsicherung -D2- (1) | |
| 8 | Lesespule für Wegfahrsicherung -D2- (2) | |
| 9 | Geschwindigkeitssignal, Ausgang | |
| 10 | nicht belegt
| 11 | Ölstands- und Öltemperaturgeber -G266-
| 12 | nicht belegt
| 13 | Kontrollleuchte Nebelschlussleuchte
| 14 | Kontrollleuchte Fernlicht
| 15 | Geber für Bremsbelagverschleiß vorn links -G34- / Geber für Bremsbelagverschleiß hinten rechts
| 16* | Klemme 31
| 17 | Scheiben-Waschwasserstandsgeber -G33-
| 18 | Geber für Kühlmittelmangelanzeige -G32-
| 19 | Temperaturfühler für Außentemperatur -G17-
| 20 | Klemme 31, Sensormasse
| 21 | Abruftaste für Multifunktionsanzeige -E86- (	MFA +)
| 22 | Abruftaste für Multifunktionsanzeige -E86- (MFA-)
| 23 | Speicherschalter für Multifunktionsanzeige -E109- (MFA-R)
| 24 | nicht belegt
| 25 | Schalter für Handbremskontrolle -F9-
| 26 | Warnkontakt für Bremsflüssigkeitsstand -F34-
| 27 | Öldruckschalter -F1-
| 28* | Datenbus CAN-Kombi, High
| 29* | Datenbus CAN-Kombi, Low
| 30 | nicht belegt
| 31* | Spannungsversorgung Kl. 15
| 32* | Spannungsversorgung Kl. 30

Note that some of the contacts are labeled with DIN 72552 numbers (e.g. 15, 30, 31)

## Fluttering speedometer
Trying to get the speedometer to hold a stady speed.



- PGN 5A0+1A0 (either of them), but goes to zero after ~5 sec
- PGN 5A0+1A0+DA0, steady for a few seconds at a time, flutters, goes to zero momentarily
- without DA0, goes to zero after ~5 sec
- moving 5A0 to 1 sec interval, smaller twiitches, but eventully zero

## Buttons
There are two buttons. The left one controls mode and the right one select.

Mode 0
Select toggles etween odometer and trip odometer
Mode 1
Set hours
Mode 2
Set minutes
Mode 3
Display time 1 and service miles
Mode 4
Display time 2 and service miles



