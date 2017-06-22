# roomMapping

**HARDWARE:**
- Arduino UNO
- Adafruit Motor Shield
- 2 DC Motors
- 2 Ultrasonic sensors
- 2 Battery Packs
  - 4 AA Battery Pack with barrel (for general board power)
  - 9V Battery Pack (for motor shield)
- microSD shield
- micrsoSD card
- microSD to USB reader
  
**Description:**
This repository contains the files nessesary for a robot assembled with the hardware listed above to navigate a room using the 
ultrasonic sensors and produce a map of the room. 

**Files**:
- roomMapping.ino runs the robot to navigate the room and saves the mapping data to the SD card
- mapRoom (file extension TBD as graphing library TBH) produces a map of the room given the data on the SD card
