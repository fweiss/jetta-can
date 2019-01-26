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
Frames that are emitted from the cluster

### 320 instrument cluster
typical
1A 01 FF FF FF CX FF A9
where X varies
also change after the speedometer resets

### 621 instrument cluster
typical
00 EF 5 FF 90 32 0 0
00 00 80 FF 90 7F 17 00

### 62D
typical
D0 47 15 80 1F 00 29 80
FE 4F 00 80 8D 00 FE BF
about one per second, but seems to com e in bursts
some of the values change

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

### 420
95 FF FF 00 08 7F FF 84 key on
91 FF FF 00 08 3A FF 80 key off
and some intermediate after turning on

## Connector pinouts
Source: http://www.polo6rfreunde.de/index.php/Thread/9562-Pinbelegung-Tacho-Stecker/

Verfied pins marked with asterisk.

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

## Fluttering speedometer
Trying to get the speedometer to hold a stady speed.



- PGN 5A0+1A0 (either of them), but goes to zero after ~5 sec
- PGN 5A0+1A0+DA0, steady for a few seconds at a time, flutters, goes to zero momentarily
- without DA0, goes to zero after ~5 sec
- moving 5A0 to 1 sec interval, smaller twiitches, but eventully zero


