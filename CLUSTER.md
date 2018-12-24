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

### 62D
typical
D0 47 15 80 1F 0 29 80
about one per second, but seems to com e in bursts
some of the values change

### 727 instrument cluster
length 7
4 3 1 0 2 0 0 key on
1 1 4 0 6 0 0 key off
2 3 5 0 6 0 0 key on cluster starting
4 3 1 0 2 0 0 cluster ready




