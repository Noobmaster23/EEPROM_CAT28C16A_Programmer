/*
How I'll do it:
shift-registers can save 2*8 bits of data.
Nano can output/input 9 bits of data. (TX/RX used, 13 Data pins, 2 pins for shift registers => 9 bits)
shift-registers save address (11 bits)
nano saves data (8 bits) so it can read/write
WE and OE is also controlled by the shift-registers (2 bits)
CE is controlled by the nano (1 bit)
so data in shift registers looks like this: 
ARDUINO NANO | [0][0][0][WE][OE][A10][A9][A8][A7][A6][A5][A4][A3][A2][A1][A0] | EEPROM
*/

#include <Arduino.h>

#define SHIFT_CLOCK 3
#define SHIFT_DATA 13

#define IO0 12
#define IO1 8
#define IO2 9
#define IO3 11
#define IO4 4
#define IO5 10
#define IO6 5
#define IO7 2

#define CE 7

#define EEPROM_NUMBER 1U
#define EEPROM_ADDRESS_SIZE 2048U

#define EEPROM_DATA_TYPE unsigned char

#define EEPROM_ADDRESS_TYPE unsigned short int

#define DEBUG_MODE 2 // 0 = off, 1 = print to serial, 2 = single write/read

const EEPROM_ADDRESS_TYPE eeprom_data[][2] = {
#if EEPROM_NUMBER == 1
    {0b00000001100, 0b00000001},
    {0b00000001010, 0b00000001},
    {0b00000001110, 0b01000000},
    // IB
    {0b00000010100, 0b00000001},
    {0b00000010010, 0b00000001},
    {0b00000010110, 0b00010000},
    // ADD
    {0b00000011100, 0b00000001},
    {0b00000011010, 0b00000001},
    {0b00000011110, 0b00001000},
    // SUB
    {0b00000100100, 0b00000001},
    {0b00000100010, 0b00000001},
    {0b00000100110, 0b00001000},
    // OA
    {0b00000101100, 0b00000001},
    {0b00000101010, 0b10000000},
    // OB
    {0b00000110100, 0b00000001},
    {0b00000110010, 0b00100000},
    // SA
    {0b00000111100, 0b00000001},
    {0b00000111010, 0b00000001},
    {0b00000111110, 0b00000000},
    {0b00000111001, 0b10000000},
    // SB
    {0b00001000100, 0b00000001},
    {0b00001000010, 0b00000001},
    {0b00001000110, 0b00000000},
    {0b00001000001, 0b00100000},
    // SADD
    {0b00001001100, 0b00000001},
    {0b00001001010, 0b00000001},
    {0b00001001110, 0b00000000},
    {0b00001001001, 0b00100000},
    // SSUB
    {0b00001010100, 0b00000001},
    {0b00001010010, 0b00000001},
    {0b00001010110, 0b00000000},
    {0b00001010001, 0b00100000},
    // O
    {0b00001011100, 0b00000001},
    {0b00001011010, 0b00000001},
    {0b00001011110, 0b00000000},
    // JUMP
    {0b00001100100, 0b00000001},
    {0b00001100010, 0b00000001},
    {0b00001100110, 0b00000100},
    // HALT
    {0b00001101100, 0b00000001},
    {0b00001101010, 0b00000000},
#elif EEPROM_NUMBER == 2
    // IA
    {0b00000001100, 0b00000000},
    {0b00000001010, 0b00111100},
    {0b00000001110, 0b00000110},
    // IB
    {0b00000010100, 0b00000000},
    {0b00000010010, 0b00111100},
    {0b00000010110, 0b00000110},
    // ADD
    {0b00000011100, 0b00000000},
    {0b00000011010, 0b00111100},
    {0b00000011110, 0b00000000},
    // SUB
    {0b00000100100, 0b00000000},
    {0b00000100010, 0b00111100},
    {0b00000100110, 0b10000000},
    // OA
    {0b00000101100, 0b00000000},
    {0b00000101010, 0b00000000},
    // OB
    {0b00000110100, 0b00000000},
    {0b00000110010, 0b00000000},
    // SA
    {0b00000111100, 0b00000000},
    {0b00000111010, 0b00111100},
    {0b00000111110, 0b00010110},
    {0b00000111001, 0b00000011},
    // SB
    {0b00001000100, 0b00000000},
    {0b00001000010, 0b00111100},
    {0b00001000110, 0b00010110},
    {0b00001000001, 0b00000011},
    // SADD
    {0b00001001100, 0b00000000},
    {0b00001001010, 0b00111100},
    {0b00001001110, 0b00010110},
    {0b00001001001, 0b00000011},
    // SSUB
    {0b00001010100, 0b00000000},
    {0b00001010010, 0b00111100},
    {0b00001010110, 0b00010110},
    {0b00001010001, 0b10000011},
    // O
    {0b00001011100, 0b00000000},
    {0b00001011010, 0b00111100},
    {0b00001011110, 0b00000110},
    // JUMP
    {0b00001100100, 0b00000000},
    {0b00001100010, 0b00111100},
    {0b00001100110, 0b00001100},
    // HALT
    {0b00001101100, 0b00000000},
    {0b00001101010, 0b01000000},
#elif EEPROM_NUMBER == 3
    // IA
    {0b00000001100, 0b10000000},
    {0b00000001010, 0b00000000},
    {0b00000001110, 0b00000000},
    // IB
    {0b00000010100, 0b10000000},
    {0b00000010010, 0b00000000},
    {0b00000010110, 0b00000000},
    // ADD
    {0b00000011100, 0b10000000},
    {0b00000011010, 0b00000000},
    {0b00000011110, 0b01000000},
    // SUB
    {0b00000100100, 0b10000000},
    {0b00000100010, 0b00000000},
    {0b00000100110, 0b01000000},
    // OA
    {0b00000101100, 0b10000000},
    {0b00000101010, 0b01000000},
    // OB
    {0b00000110100, 0b10000000},
    {0b00000110010, 0b01000000},
    // SA
    {0b00000111100, 0b10000000},
    {0b00000111010, 0b00000000},
    {0b00000111110, 0b00000000},
    {0b00000111001, 0b00000000},
    // SB
    {0b00001000100, 0b10000000},
    {0b00001000010, 0b00000000},
    {0b00001000110, 0b00000000},
    {0b00001000001, 0b00000000},
    // SADD
    {0b00001001100, 0b10000000},
    {0b00001001010, 0b00000000},
    {0b00001001110, 0b00000000},
    {0b00001001001, 0b00000000},
    // SSUB
    {0b00001010100, 0b10000000},
    {0b00001010010, 0b00000000},
    {0b00001010110, 0b00000000},
    {0b00001010001, 0b00000000},
    // O
    {0b00001011100, 0b10000000},
    {0b00001011010, 0b00000000},
    {0b00001011110, 0b01000000},
    // JUMP
    {0b00001100100, 0b10000000},
    {0b00001100010, 0b00000000},
    {0b00001100110, 0b00000000},
    // HALT
    {0b00001101100, 0b01000000},
    {0b00001101010, 0b00000000},
#endif
};

// Gets bit from an int
// https://www.studymite.com/cpp/examples/program-to-get-nth-bit-of-a-number-in-cpp/
bool GetBit(EEPROM_DATA_TYPE b, unsigned char bitNumber)
{
  return (1 & (b >> (bitNumber - 1)));
}

// sets the data in the shift registers
void setShiftRegisterData(EEPROM_DATA_TYPE data, unsigned char data_length = 11)
{
  // Set address
  for (unsigned char i = 0; i < data_length; i++)
  {
    digitalWrite(SHIFT_DATA, GetBit(data, i));
    digitalWrite(SHIFT_CLOCK, LOW);
    digitalWrite(SHIFT_CLOCK, HIGH);
  }
}

// sets the shift-reigsters to write data
void writeShiftRegister(EEPROM_ADDRESS_TYPE address)
{
  setShiftRegisterData(address);

  setShiftRegisterData(0b00001, 5);
}

// sets the shift-reigsters to read data
void readShiftRegister(EEPROM_ADDRESS_TYPE address)
{
  setShiftRegisterData(address);

  setShiftRegisterData(0b00010, 5);
}

// sets the data at the data pins
void setPinData(EEPROM_DATA_TYPE data)
{
  digitalWrite(IO0, GetBit(data, 1));
  digitalWrite(IO1, GetBit(data, 2));
  digitalWrite(IO2, GetBit(data, 3));
  digitalWrite(IO3, GetBit(data, 4));
  digitalWrite(IO4, GetBit(data, 5));
  digitalWrite(IO5, GetBit(data, 6));
  digitalWrite(IO6, GetBit(data, 7));
  digitalWrite(IO7, GetBit(data, 8));
}

// Sets the pins for writing Data
void setWritePinMode()
{
  // set all pins to low before using them to be sure nothing gets wrongly set
  digitalWrite(IO0, LOW);
  digitalWrite(IO1, LOW);
  digitalWrite(IO2, LOW);
  digitalWrite(IO3, LOW);
  digitalWrite(IO4, LOW);
  digitalWrite(IO5, LOW);
  digitalWrite(IO6, LOW);
  digitalWrite(IO7, LOW);

  digitalWrite(SHIFT_CLOCK, LOW);
  digitalWrite(SHIFT_DATA, LOW);

  digitalWrite(CE, HIGH);

  // set pins to the correct mode
  pinMode(IO0, OUTPUT);
  pinMode(IO1, OUTPUT);
  pinMode(IO2, OUTPUT);
  pinMode(IO3, OUTPUT);
  pinMode(IO4, OUTPUT);
  pinMode(IO5, OUTPUT);
  pinMode(IO6, OUTPUT);
  pinMode(IO7, OUTPUT);

  pinMode(SHIFT_CLOCK, OUTPUT);
  pinMode(SHIFT_DATA, OUTPUT);

  pinMode(CE, OUTPUT);

  delay(1);
}

// Sets the pins for reading Data
void setReadPinMode()
{
  // set all pins to low before using them to be sure nothing gets wrongly set
  digitalWrite(SHIFT_CLOCK, LOW);
  digitalWrite(SHIFT_DATA, LOW);

  digitalWrite(CE, HIGH);

  // set pins to the correct mode
  pinMode(IO0, INPUT);
  pinMode(IO1, INPUT);
  pinMode(IO2, INPUT);
  pinMode(IO3, INPUT);
  pinMode(IO4, INPUT);
  pinMode(IO5, INPUT);
  pinMode(IO6, INPUT);
  pinMode(IO7, INPUT);

  pinMode(SHIFT_CLOCK, OUTPUT);
  pinMode(SHIFT_DATA, OUTPUT);

  pinMode(CE, OUTPUT);

  delay(1);
}

// sets the shift-registers to 0
void resetShiftRegisters()
{
  setShiftRegisterData(0, 16);
}

void serialStart()
{
  Serial.begin(9600);
  while (!Serial)
  {
    delay(1);
  }
  Serial.println("Serial started");
  delay(100);
}

void finishedMessage()
{
  Serial.println("Finished");
  delay(5000);
}

// disable the EEPROM and set data and shift-registers to 0
void disableEEPROM()
{
  digitalWrite(CE, HIGH);

  delay(20);

  resetShiftRegisters();
  setPinData(0);
}

// checks if the address is in the eeprom address list
short checkAddress(EEPROM_ADDRESS_TYPE address)
{
  for (EEPROM_ADDRESS_TYPE i = 0; i < (sizeof(eeprom_data) / sizeof(eeprom_data[0])); i++)
  {
    if (eeprom_data[i][0] == address)
    {
      return i;
    }
  }
  return -1;
}

void fullEEPROMWrite()
{
  // set mode for writing
  setWritePinMode();

  // write data
  for (EEPROM_ADDRESS_TYPE i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
    unsigned char writeData;
    short checkAddressResult = checkAddress(i); // is the position in the eeprom_data array where the correct address and data is
    // checks if the address is defined
    if (checkAddressResult != -1)
    {
      writeData = eeprom_data[checkAddressResult][1]; // at 0 the address is stored, at 1 the data
    }
    else if (GetBit(i, 3) && !GetBit(i, 2) && !GetBit(i, 1))
    {
// Because the Instruction has to be loaded every time set the instruction for the first step for every instruction to the same value
#if EEPROM_NUMBER == 1
      writeData = 0b00000001;
#elif EEPROM_NUMBER == 2
      writeData = 0b00000000;
#elif EEPROM_NUMBER == 3
      writeData = 0b10000000;
#endif
    }
    else // if nothing was predefined, set data to 0
    {
      writeData = 0;
    }
#if DEBUG_MODE == 1
    Serial.print("Writing: ");
    Serial.print(writeData, BIN);
    Serial.print(" at address: ");
    Serial.println(i, BIN);
#endif
    setPinData(writeData);
    delay(1);
    writeShiftRegister(i); // write the address
    delay(1);
    digitalWrite(CE, LOW);
    delay(1);
    digitalWrite(CE, HIGH);
    delay(20);
  }

  // finishing touches
  disableEEPROM();
}

EEPROM_DATA_TYPE readDataPins()
{
  EEPROM_DATA_TYPE data = 0;
  data |= digitalRead(IO0) << 1;
  data |= digitalRead(IO1) << 2;
  data |= digitalRead(IO2) << 3;
  data |= digitalRead(IO3) << 4;
  data |= digitalRead(IO4) << 5;
  data |= digitalRead(IO5) << 6;
  data |= digitalRead(IO6) << 7;
  data |= digitalRead(IO7) << 8;
  return data;
}

void readFullEEPROM()
{
  // set mode for reading
  setReadPinMode();

  Serial.println("Reading EEPROM");

  // read data
  for (EEPROM_ADDRESS_TYPE i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
    readShiftRegister(i);
    Serial.print(readDataPins(), BIN);
    delay(1);
    Serial.print(" at ");
    digitalWrite(CE, LOW);
    delay(1);
    Serial.println(i, BIN);
    digitalWrite(CE, HIGH);
    delay(1);
  }
}

// ride one byte of data to one address
void writeEEPROM(EEPROM_ADDRESS_TYPE address, EEPROM_DATA_TYPE data)
{
  // set mode for writing
  setWritePinMode();

  // write data
  setPinData(data);
  delay(1);
  writeShiftRegister(address); // write the address
  delay(1);
  digitalWrite(CE, LOW);
  delay(1);
  digitalWrite(CE, HIGH);
  delay(20);
}

// read one byte of data from one address
void readEEPROM(EEPROM_ADDRESS_TYPE address)
{
  // set mode for reading
  setReadPinMode();

  // read data
  readShiftRegister(address);
  Serial.print(readDataPins(), BIN);
  delay(1);
  Serial.print(" at ");
  digitalWrite(CE, LOW);
  delay(1);
  Serial.println(address, BIN);
  digitalWrite(CE, HIGH);
  delay(1);
}

// gets called once on startup
void setup()
{
  // startup functions
  serialStart();

#if DEBUG_MODE == 0
  // write EEPROM
  fullEEPROMWrite();

  // read EEPROM for verification
  readFullEEPROM();
#elif DEBUG_MODE == 2
  writeEEPROM(0, 210);
  readEEPROM(210);
#endif
}

// gets called repeatedly
void loop()
{
  finishedMessage();
}
