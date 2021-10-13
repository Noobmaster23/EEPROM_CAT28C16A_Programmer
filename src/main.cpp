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

#define SHIFT_CLOCK 3 // T
#define SHIFT_DATA 13 // T

#define IO0 12 // T
#define IO1 8  // T
#define IO2 9  // T
#define IO3 11 // T
#define IO4 4  // T
#define IO5 10 // T
#define IO6 5  // T
#define IO7 2  // T

#define CE 7 // T

#define EEPROM_NUMBER 1
#define EEPROM_ADDRESS_SIZE 2048U

#define EEPROM_DATA_TYPE unsigned char

#define EEPROM_ADDRESS_TYPE unsigned short int

#define DEBUG_MODE 0 // 0 = off, 1 = print to serial, 2 = single write/read, 3 = Test Voltage, 4 = shift-register, 5 = check function

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
bool GetBit(unsigned int b, unsigned char bitNumber)
{
  return (1 & (b >> (bitNumber - 1)));
}

// reverses a byte
// https://stackoverflow.com/a/2602885/13556449
unsigned char reverse(unsigned char b)
{
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return b;
}

// sets the data in the shift registers
void setShiftRegisterData(unsigned int data, unsigned char data_length)
{
#if DEBUG_MODE == 4
  Serial.println(data, BIN);
#endif
  // Set address
  for (unsigned char i = 1; i < data_length + 1; i++)
  {
    digitalWrite(SHIFT_DATA, GetBit(data, i));
    delay(1);
    digitalWrite(SHIFT_CLOCK, LOW);
    delay(1);
    digitalWrite(SHIFT_CLOCK, HIGH);
    delay(1);
#if DEBUG_MODE == 4
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(GetBit(data, i));
    while (Serial.available() == 0)
    {
      delay(1);
    }
    Serial.read();
#endif
  }
#if DEBUG_MODE == 4
  Serial.println();
  // digitalWrite(SHIFT_DATA, 0);
  // delay(1);
  // digitalWrite(SHIFT_CLOCK, LOW);
  // delay(1);
  // digitalWrite(SHIFT_CLOCK, HIGH);
  // delay(1);
#endif
}

// sets the shift-registers to 0
void resetShiftRegisters()
{
  setShiftRegisterData(0, 16);
}

// sets the shift-reigsters to write data
void writeShiftRegister(EEPROM_ADDRESS_TYPE address)
{
  resetShiftRegisters();

  setShiftRegisterData(address, 11);

  setShiftRegisterData(0b000001, 6);
}

// sets the shift-reigsters to read data
void readShiftRegister(EEPROM_ADDRESS_TYPE address)
{
  resetShiftRegisters();

  setShiftRegisterData(address, 11);

  setShiftRegisterData(0b000010, 6);
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

  digitalWrite(SHIFT_CLOCK, HIGH);
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
  digitalWrite(SHIFT_CLOCK, LOW);
  delay(1);
  digitalWrite(SHIFT_CLOCK, HIGH);
}

// Sets the pins for reading Data
void setReadPinMode()
{
  // set all pins to low before using them to be sure nothing gets wrongly set
  digitalWrite(SHIFT_CLOCK, HIGH);
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

  digitalWrite(SHIFT_CLOCK, LOW);
  delay(1);
  digitalWrite(SHIFT_CLOCK, HIGH);
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
  delay(1000 * 60);
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
    EEPROM_DATA_TYPE writeData;
    short checkAddressResult = checkAddress(i); // is the position in the eeprom_data array where the correct address and data is
    // checks if the address is defined
    if (checkAddressResult != -1)
    {
      writeData = reverse(eeprom_data[checkAddressResult][1]); // at 0 the address is stored, at 1 the data
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

// sets the eeprom to everywhere 0
void setEEPROMtoZero()
{
  // set mode for writing
  setWritePinMode();

  // write data
  for (EEPROM_ADDRESS_TYPE i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
    setPinData(0);
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
  delay(1);
  EEPROM_DATA_TYPE data = 0;
  data |= digitalRead(IO0) << 0;
  data |= digitalRead(IO1) << 1;
  data |= digitalRead(IO2) << 2;
  data |= digitalRead(IO3) << 3;
  data |= digitalRead(IO4) << 4;
  data |= digitalRead(IO5) << 5;
  data |= digitalRead(IO6) << 6;
  data |= digitalRead(IO7) << 7;
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
    delay(1);
    digitalWrite(CE, LOW);
    delay(1);
    Serial.print(readDataPins(), BIN);
    Serial.print(" at ");
    delay(1);
    Serial.println(i, BIN);
    digitalWrite(CE, HIGH);
    delay(1);
  }

  disableEEPROM();
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
#if DEBUG_MODE == 3
  while (Serial.available() == 0)
  {
    delay(1);
  }
  Serial.read();
#endif
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
  delay(1);
  digitalWrite(CE, LOW);
  delay(1);
  Serial.print(readDataPins(), BIN);
  Serial.print(" at ");
  digitalWrite(CE, HIGH);
  Serial.println(address, BIN);
  delay(1);
}

// checks if every address is saved correctely, if notify is = false, checkEEPROM will not print to serial and just return false if one or more addresses are not saved correctly
bool checkEEPROM(bool notify = true)
{
  bool return_val = true;
  EEPROM_DATA_TYPE expectedData;
  // set mode for reading
  setReadPinMode();
  Serial.println("Checking EEPROM");
  delay(1);

  // read data
  for (EEPROM_ADDRESS_TYPE i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
    expectedData = 0;
    readShiftRegister(i);
    delay(1);
    digitalWrite(CE, LOW);
    delay(1);
    EEPROM_DATA_TYPE readData = readDataPins();
#if DEBUG_MODE == 5
    Serial.println(readDataPins(), BIN);
#endif
    delay(1);
    digitalWrite(CE, HIGH);
    delay(1);
    short checkAddressResult = checkAddress(i); // is the position in the eeprom_data array where the correct address and data is
    // checks if the address is defined
    if (checkAddressResult != -1)
    {
#if DEBUG_MODE == 5
      Serial.print("Checking: ");
      Serial.print(readData, BIN);
      Serial.print(" checkAddressResult: ");
      Serial.print(checkAddressResult);
#endif
      expectedData = reverse(eeprom_data[checkAddressResult][1]); // at 0 the address is stored, at 1 the data
#if DEBUG_MODE == 5
      Serial.print(" Data: ");
      Serial.println(expectedData, BIN);
#endif
    }
    else if (GetBit(i, 3) && !GetBit(i, 2) && !GetBit(i, 1))
    {
#if DEBUG_MODE == 5
      Serial.print("Address: ");
      Serial.print(i, BIN);
      Serial.print(" Check: ");
      Serial.println((GetBit(i, 3) && !GetBit(i, 2) && !GetBit(i, 1)));
#endif
#if EEPROM_NUMBER == 1
      expectedData = 0b00000001;
#elif EEPROM_NUMBER == 2
      expectedData = 0b00000000;
#elif EEPROM_NUMBER == 3
      expectedData = 0b10000000;
#endif
    }
    if (readData != expectedData)
    {
      if (notify)
      {
        Serial.print("Data at address: ");
        Serial.print(i, BIN);
        Serial.print(" is not correct: ");
        Serial.print(readData, BIN);
        Serial.print(" should be: ");
        Serial.println(expectedData, BIN);
        return_val = false;
      }
      else
      {
        return false;
      }
    }
    else
    {
      if (notify)
      {
        Serial.print("Data at address: ");
        Serial.print(i, BIN);
        Serial.print(" is correct: ");
        Serial.println(readData, BIN);
      }
    }
#if DEBUG_MODE == 5
#endif
  }

  disableEEPROM();
  return return_val;
}

// gets called once on startup
void setup()
{
  // startup functions
  serialStart();

#if DEBUG_MODE == 0
  // write EEPROM
  fullEEPROMWrite();

  // // read EEPROM for verification
  // readFullEEPROM();

  // check EEPROM for verification
  checkEEPROM();
#elif DEBUG_MODE == 1
  fullEEPROMWrite();
  readFullEEPROM();
#elif DEBUG_MODE == 2 || DEBUG_MODE == 3
  for (int i; i < 100; i++)
  {
    // writeEEPROM(0b10101010101, 0b00000001);
    readEEPROM(0b10101010101);

    disableEEPROM();
  }
#elif DEBUG_MODE == 4
  readEEPROM(0b10101101101);
#elif DEBUG_MODE == 5
  checkEEPROM();
#endif
}

// gets called repeatedly
void loop()
{
  finishedMessage();
}
