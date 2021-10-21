# Description
In Found Bugs, all bugs are listed.
In Ideas to solve, the ways I try to find ways to fix the bugs.
In Modules to check, i list all modules I have to check if they work correctly.
In steps done, i list what I did.
The dates (except in steps done) are when I wrote the idea. The date in steps done is when i did it.
# Found Bugs
- [ ] Computer doesn't work (04.10.2021 16:27)
- [x] EEPROM Data is 1 everywhere (04.10.2021 17:45)
- -  EEPROM is programmable (tested it) (04.10.2021 17:45)
<!-- - [ ] code uptaded, still everything 1 -->
# Ideas to solve
- [x] Check if the EEPROM's output the correct data (04.10.2021 16:27)
- it doesn't
- [ ]   Program counter and Step counter could give wrong data (04.10.2021 16:29)
- [x] EEPROM Programmer Code has bus/doesn't write the EEPROM (04.10.2021 17:46)
- - [x] EEPROM array data (05.10.2021 16:05)
- - is correct
- - [x] pins in program are false (05.10.2021 17:06)
- [x] EEPROM Voltage is too low (even if according to [datasheet](https://www.jameco.com/Jameco/Products/ProdDS/74691.pdf) is should be enough) (05.10.2021 16:07) -> buy [EEPROM programmer](https://www.aliexpress.com/item/33018288982.html?spm=a2g0o.productlist.0.0.1dc06b01PdiLLZ&algo_pvid=98164855-4272-44a6-803e-b44267ea2aae&algo_exp_id=98164855-4272-44a6-803e-b44267ea2aae-1&pdp_ext_f=%7B%22sku_id%22%3A%2267501798640%22%7D) **not wort it**
- [x] use 24 transistors to control the 5V with the 3.3V (06.10.2021 22:25)
- - i checked everything else, and this is the only thing still possible to me
- [x] use arduino nano and shift-registers (as Ben Eater does)
# Modules to check
- EEPROM's
- - - [x] 04.10.2021 17:47 
- - - don't work, everything 1
- Program Counter
- Step Counter
- EEPROM Programmer Code
# Steps done
- [x] check one (the first) EEPROM and check, if it outputs the correct code
- - [x] EEPROM should have Data:
- - - [x] DOESN'T: 0b00000001 at 0b00000001100 (04.10.2021 17:39)
- - - [ ] 0b00000001 at 0b00000001010
- - - [ ] 0b01000000 at 0b00000001110
- - I didn't check the others, because it always is wrong (04.10.2021 17:40)
- [x] add better potentiometer to clock for easier controlling (04.10.2021 16:26)
- [x] check EEPROM programmer code (04.10.2021 19:23)
- [x] Check Code Step by step (make big delay and look if output is as expected)
- - [x] debugging code step by step (05.10.2021 15:07)
- - [x] check if data in eeprom array is correct (05.10.2021 15:38)
- - maybe found bug in
 ```cpp
if (GetBit(i, 9) && !GetBit(i, 10) && !GetBit(i, 11))
```
should be 
 ```cpp
if (GetBit(i, 3) && !GetBit(i, 2) && !GetBit(i, 1))
```
(05.10.2021 15:37)
- - data to array gets written correctly (05.10.2021 15:38)
- - [x] checking if program works after adjustments (05.10.2021 16:04)
- - still everything 0
- [x] check if  EEPROM outputs correct data (05.10.2021 17:03)
```cpp
for (unsigned short int j = 0; j < EEPROM_ADDRESS_LENGTH; j++)
    {
      Serial.print(GetBit(i, j) ? "1" : "0");
    }
    Serial.print(" : ");
    for (unsigned short int j = 0; j < EEPROM_DATA_LENGTH; j++)
    {
      Serial.print(GetBit(eeprom_data[i], j) ? "1" : "0");
    }
    Serial.println();
```
- counter = 12:
-  - Address: 000(1?)0001001
-  - Data: 00100000
-  - Controls:
-  - - CE: 0
-  - - WE: 0
-  - - OE: 1.
-  - problem: not expected data, EEPROM doesn't output correct data
- [x] check if EEPROM pins are assigned correctly (05.10.2021 17:46)
- found [correct pinout](https://www.electronicshub.org/wp-content/uploads/2021/02/ESP32-36-Pin-Pinout.jpg) (**wrong one**)
- [correct pinout](https://circuits4you.com/wp-content/uploads/2018/12/ESP32-Pinout.jpg)
- some pins are wrong:
```cpp
#define IO0 12 // F -> 13
#define IO1 1  // T
#define IO2 3  // T
#define IO3 4  // T
#define IO4 2  // T
#define IO5 5  // F -> 15
#define IO6 18 // F -> 5
#define IO7 19 // F -> 18

#define AD0 12  // T
#define AD1 14  // T
#define AD2 27  // T
#define AD3 26  // T
#define AD4 25  // T
#define AD5 33  // T
#define AD6 32  // T
#define AD7 35  // T
#define AD8 23  // T
#define AD9 22  // T
#define AD10 21 // T

#define WE 16 // T
#define OE 17 // T
#define CE 19 // T
```
- [x] I will correct them and look if the EEPROM still doesn't work (05.10.2021 18:03)
- - EEPROM still doesn't have the right data, is manually programmable
- [x] set time between writes higher (100ms) so that the EEPROM has more time (05.10.2021 18:19)
- still doesn't work
- [x] test direct output again (06.10.2021 15:38)
- - [x] COUNTER: 0
- - Measured:
- - - DATA: 00000000
- - - ADDRESS: 0000000(1?)000
- - - CE:  0
- -  - WE: 0
- -  - OE: 1
- - Expected: 
-  - -ADDRESS: 00000000000
-  - - Data: 00000000
-  - - CE: 0
-  - - WE: 0
-  - - OE: 1
- - [x] COUNTER: 10
- - Measured:
- - - DATA: 00000001
- - - ADDRESS: 00000001010
- - - CE:  0
- -  - WE: 0
- -  - OE: 1
- - Expected: 
-  - -ADDRESS: 00000001010
-  - - Data: 00000001
-  - - CE: 0
-  - - WE: 0
-  - - OE: 1
- - [ ] COUNTER: 102
- - Measured:
- - - DATA: 00000000
- - - ADDRESS: 00000000000
- - - CE:  0
- -  - WE: 0
- -  - OE: 1
- - Expected: 
-  - -ADDRESS: 00001100110
-  - - Data: 00000100
-  - - CE: 0
-  - - WE: 0
-  - - OE: 1
- [x] Reread documentation (06.10.2021 15:44):
-  - maybe set the timing wrong
-  - I understand it know so that data is written when CE goes form LOW to HIGH, which means that I have to make a atleast 10ms pause between CE switching and writing new data, have to change code for that (add delay)
```cpp
  for (unsigned short int i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
    // Sets controls (disable, until all pins are set)
    digitalWrite(CE, HIGH);
    // write data
    delay(50);
	  ....
		// enable when all pins are set
    digitalWrite(CE, LOW);
	  ...
		// give time to read address
    delay(50
  }
```
- - the problem that everything is set to 1 could very probably come from data polling, which is a feature that everything is set to 1 when the data hasn't been written (which it hasn't until now to my understanding
- [x] add halt command (06.10.2021 15:48)
- [x] update programm and check again (06.10.2021 16:03)
- - EEPROM still outputs only 0, except for manually programmed places
- - everything 1 could still have something to do with POLLING, have to look further into it
- [x] WE controlled write cycle instead of CE controlled (06.10.2021 17:29)
- - still doesn't work
- [x] make WE signal to very short pulse, address and data already has to be set (06.10.2021 17:45)
- - still wrong data
- [x] test another EEPROM (06.10.2021 17:51)
- - doesn't work, even manually not
- [x] testing single read/writes if the functions work (06.10.2021 21:22)
- [x] read eeprom programmatically (06.10.2021 21:22)
- - data nearly everywhere 1
- [x] change EEPROM data manually and check with program (06.10.2021 22:16)
- - program doesn't detect it -> program doesn't work correctely, have to check program again step by step
- [x] manually check voltage if it works or not --> doesn't work with 3.3V, works with 5V (06.10.2021 22:21)
- during checking, lost a leg of a EEPROM, soldered it back but not sure if it holds (06.10.2021 22:21)
- [x] build board to control 5V with the 3.3V of the Arduino (07.10.2021 17:05)
- - 2 Transistors have the same power (saves space)
- [x] test if idea with transistors even works (07.10.2021 15:36)
- [x] improve code so that Serial doesn't interfere with writing/reading (07.10.2021 16:45)
- [x] test new board (programm EEPROM) (07.10.2021 17:39)
- - *new board can't read data so have to check manually again (not that bad)*
- - still didn't work, but realised that to manually programm it needed about 5 seconds wait time so i'm implementing this now in code and let the programm run for this time, could something have to do with the capacitors or something else, but it's my last hope
- - i also always read the data after a write, maybe i also have to do this in the programm, like switching OE on, then off, then writing, then switich OE again on/off before the next write
- **NodeMCU has to be cut off from everything and boot has to be pressed to upload data (07.10.2021 17:10)**
- [x] make wait time a lot longer about (5 seconds) (07.10.2021 18:28)
- - in this configuration, writing would need about 8.4916667 hours to write a full EEPROM (could definitely be made more efficient it that really would be the bug)
- - let program run for 10 min and look if the first values are correct
- - didn't work again
- [x] trying method of turning OE on and off, making intervals shorter (1sec, worked manually so also should here) (07.10.2021 19:16)
- - still wrong data
- [x] check at one random data if the data is written correctely (07.10.2021 20:05):
- COUNTER:10
- - ADDRESS:
- - - A0:
- - - A1:
- - - A2:
- - - A3:
- - - A4:
- - - A5:
- - - A6:
- - - A7:
- - - A8: 2.5V
- - - A9: 2.5V
- - - A10: 2.7V
- - DATA:
- - - IO0:
- - - IO1:
- - - IO2:
- - - IO3:
- - - IO4:
- - - IO5:
- - - IO6: 2V
- - - IO7: 2V
- - CE: 2.5V
- - OE: 4.3V
- - WE: 4.2V
- **VOLTAGE TO HIGH**
- Setup with transistors doesn't work
- could use bus transceiver
- [x] use bus transceiver instead of Transistors (keep transistor setup for display purposes) (07.10.2021 22:05)
- - doesn't work with transceivers because they keep the voltage 
- programming by hand is not possible, it would take definitely too much time and i can't program only part of it because when the step is 001 it always has to load the next instruction otherwise it outputs gibberish
- only option I see here is to use shift-registers (according to Ben Eater)
- - watched his video just now because my own design didn't work out so I had to use his, didn't want to use it at first though
- using arduino nano instead, it has 5V, building it with shift-registers
- program to big for arduino nano (08.10.2021 15:05)
- [x] arduino nano has not enough space, have to make array smaller (08.10.2021 15:42)
- eeprom still not written to correctly (08.10.2021 17:23)
- [x] test if read function works (manually programming and checking) (08.10.2021 17:32)
- - [x] doesn't output correct values, check if pins are correctly assigned (08.10.2021 17:40)
- - pins directly connected to nano are correct
- - check for one write if values are as expected
- Address: 10101010101, Data: 01010101
- - ADDRESS:
- - - A0: 1
- - - A1: 0
- - - A2: 1
- - - A3: 0
- - - A4: 1
- - - A5: 0
- - - A6: 1
- - - A7: 0
- - - A8: 0
- - - A9: 0
- - - A10: 1
- - DATA:
- - - IO0: 1
- - - IO1: 0
- - - IO2: 1
- - - IO3: 0
- - - IO4: 1
- - - IO5: 0
- - - IO6: 1
- - - IO7: 0
- - CE: 0
- - OE: 0
- - WE: 0
- after restarting nano but not voltage, OE/WE are different -> shift-registers don't work as planned, IO/CE is as expected
- [x] add delay to shift-register
- [x] maybe fixed read problem, have to check manually (08.10.2021 20:03)
- - still wrong, after each repeat, new results get shown
- [ ] check if pins are correct when reading
- Address: 11000011100, Data: 00010001
- - ADDRESS:
- - - A0: 0
- - - A1: 0
- - - A2: 1
- - - A3: 1
- - - A4: 1
- - - A5: 0
- - - A6: 0
- - - A7: 0
- - - A8: 1 F -> 0
- - - A9: 1
- - - A10: 0 F -> 1
- - DATA:
- - - IO0: 1
- - - IO1: 0
- - - IO2: 0
- - - IO3: 0
- - - IO4: 1
- - - IO5: 0
- - - IO6: 0
- - - IO7: 0
- - CE: 0
- - OE: 1
- - WE: 0
- **Data is correct, control units too (could be coincidense tho), address isn't**
- probably fault with shift-registers
- only two address are wrong, could be that two cables are connected wrongly
- cables seemed to be connected wrongly, switched them (08.10.2021 23:04)
- [x] trying writing/reading one number again (08.10.2021 23:12)
- - OMG IT SEEMS TO WORK, TESTING WITH WHOLE ARRAY (08.10.2021 23:50)
- doesn't work, getting seemingly random results, have to test again manually (08.10.2021 23:51)
- Address: 100101, Data: 10011 (09.10.2021 00:03)
- - ADDRESS:
- - - A0: 1 **T**
- - - A1: 0 **T**
- - - A2: 1 **T**
- - - A3: 0 **T**
- - - A4: 0 **T**
- - - A5: 1 **T**
- - - A6: 0 **T**
- - - A7: 0 **T**
- - - A8: 0  **T**
- - - A9: 0 **T**
- - - A10: 0 **T**
- - DATA:
- - - IO0: 1 **T**
- - - IO1: 1 **T**
- - - IO2: 0 **T**
- - - IO3: 0 **T**
- - - IO4: 1 **T**
- - - IO5: 0 **T**
- - - IO6: 0 **T**
- - - IO7: 0 **T**
- - CE: 0 **T**
- - OE: 1 **T**
- - WE: 0 **T**
- everything seems to be ok
- writing seems to be working
- writing, then reading: writeEEPROM(0b10101010101, 0b10101010)
```
Serial started
10101010 at 10101010101
10100010 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10101011 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10101011 at 10101010101
10101011 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10101011 at 10101010101
10101011 at 10101010101
10101011 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10101011 at 10101010101
10101011 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10101011 at 10101010101
10101011 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10101011 at 10101010101
10101011 at 10101010101
10101011 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10101010 at 10101010101
Finished
```
- only reading:
```
Serial started
11111111 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10101010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10111011 at 10101010101
10101011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10111011 at 10101010101
10111011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
10101011 at 10101010101
10111011 at 10101010101
10101010 at 10101010101
10100010 at 10101010101
10100010 at 10101010101
Finished
```
- clearly, writing isn't the problem but rather reading/something they both share in common
- - they only share the address and io pins, so again have to check if those are really correct, then have to check if reading really works, if so... yeah idk anymore
- - 8th, 7th, 6th, 3rd and 2nd bits seem to work, only problems with 1st, 4th and 5th bit
- [x] reading EEPROM functions first reads EEPROM and then sets ce to low, which is wrong, make ce low first and then read the EEPROM (09.10.2021 13:56) 
- [x] full read shows that everything in EEPROM should be correct, therefore, check functions doesn't work correctly -> correct it (09.10.2021 17:06)
- - used pinMode instead of digitalWrite in checkData
- [x] run program again and check if it works this time
- IT WORKS, IT FUCKING WORKS, EEPROM IS WRITTEN TO CORRECTLY OMG