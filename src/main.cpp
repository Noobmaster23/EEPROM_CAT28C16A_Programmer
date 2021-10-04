#include <Arduino.h>
#include <math.h>

// GPIO pin definitions
#define IO0 12
#define IO1 1
#define IO2 3
#define IO3 4
#define IO4 2
#define IO5 5
#define IO6 18
#define IO7 19

#define AD0 12
#define AD1 14
#define AD2 27
#define AD3 26
#define AD4 25
#define AD5 33
#define AD6 32
#define AD7 35
#define AD8 23
#define AD9 22
#define AD10 21

#define WE 16
#define OE 17
#define CE 19

// Data to write to EEPROM
#define EEPROM_DATA_LENGTH 8
#define EEPROM_ADDRESS_LENGTH 11
#define EEPROM_ADDRESS_SIZE 2048

const unsigned char eeprom_number = 1;

unsigned char eeprom_data[EEPROM_ADDRESS_SIZE];

// Functions
// Gets bit from an int
// https://www.studymite.com/cpp/examples/program-to-get-nth-bit-of-a-number-in-cpp/
bool GetBit(unsigned int b, unsigned int bitNumber)
{
  return (1 & (b >> (bitNumber - 1)));
}

void setup()
{
  // Set Array all to 0
  for (unsigned short int i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
    if (GetBit(i, 9) && !GetBit(i, 10) && !GetBit(i, 11))
    {
      // Because the Instruction has to be loaded every time set the instruction for the first step for every instruction to the same value
      switch (eeprom_number)
      {
      case 1:
        eeprom_data[i] = 0b00000001;
        break;
      case 2:
        eeprom_data[i] = 0b00000000;
        break;
      case 3:
        eeprom_data[i] = 0b10000000;
        break;
      default:
        break;
      }
    }
    else
    {
      eeprom_data[i] = 0;
    }
  }
  // Sets wanted EEPROM Data for the three EEPROMS
  switch (eeprom_number)
  {
  case 1:
    // IA
    eeprom_data[0b00000001100] = 0b00000001;
    eeprom_data[0b00000001010] = 0b00000001;
    eeprom_data[0b00000001110] = 0b01000000;
    // IB
    eeprom_data[0b00000010100] = 0b00000001;
    eeprom_data[0b00000010010] = 0b00000001;
    eeprom_data[0b00000010110] = 0b00010000;
    // ADD
    eeprom_data[0b00000011100] = 0b00000001;
    eeprom_data[0b00000011010] = 0b00000001;
    eeprom_data[0b00000011110] = 0b00001000;
    // SUB
    eeprom_data[0b00000100100] = 0b00000001;
    eeprom_data[0b00000100010] = 0b00000001;
    eeprom_data[0b00000100110] = 0b00001000;
    // OA
    eeprom_data[0b00000101100] = 0b00000001;
    eeprom_data[0b00000101010] = 0b10000000;
    // OB
    eeprom_data[0b00000110100] = 0b00000001;
    eeprom_data[0b00000110010] = 0b00100000;
    // SA
    eeprom_data[0b00000111100] = 0b00000001;
    eeprom_data[0b00000111010] = 0b00000001;
    eeprom_data[0b00000111110] = 0b00000000;
    eeprom_data[0b00000111001] = 0b10000000;
    // SB
    eeprom_data[0b00001000100] = 0b00000001;
    eeprom_data[0b00001000010] = 0b00000001;
    eeprom_data[0b00001000110] = 0b00000000;
    eeprom_data[0b00001000001] = 0b00100000;
    // SADD
    eeprom_data[0b00001001100] = 0b00000001;
    eeprom_data[0b00001001010] = 0b00000001;
    eeprom_data[0b00001001110] = 0b00000000;
    eeprom_data[0b00001001001] = 0b00100000;
    // SSUB
    eeprom_data[0b00001010100] = 0b00000001;
    eeprom_data[0b00001010010] = 0b00000001;
    eeprom_data[0b00001010110] = 0b00000000;
    eeprom_data[0b00001010001] = 0b00100000;
    // O
    eeprom_data[0b00001011100] = 0b00000001;
    eeprom_data[0b00001011010] = 0b00000001;
    eeprom_data[0b00001011110] = 0b00000000;
    // JUMP
    eeprom_data[0b00001100100] = 0b00000001;
    eeprom_data[0b00001100010] = 0b00000001;
    eeprom_data[0b00001100110] = 0b00000100;
    break;
  case 2:
    // IA
    eeprom_data[0b00000001100] = 0b00000000;
    eeprom_data[0b00000001010] = 0b00111100;
    eeprom_data[0b00000001110] = 0b00000110;
    // IB
    eeprom_data[0b00000010100] = 0b00000000;
    eeprom_data[0b00000010010] = 0b00111100;
    eeprom_data[0b00000010110] = 0b00000110;
    // ADD
    eeprom_data[0b00000011100] = 0b00000000;
    eeprom_data[0b00000011010] = 0b00111100;
    eeprom_data[0b00000011110] = 0b00000000;
    // SUB
    eeprom_data[0b00000100100] = 0b00000000;
    eeprom_data[0b00000100010] = 0b00111100;
    eeprom_data[0b00000100110] = 0b10000000;
    // OA
    eeprom_data[0b00000101100] = 0b00000000;
    eeprom_data[0b00000101010] = 0b00000000;
    // OB
    eeprom_data[0b00000110100] = 0b00000000;
    eeprom_data[0b00000110010] = 0b00000000;
    // SA
    eeprom_data[0b00000111100] = 0b00000000;
    eeprom_data[0b00000111010] = 0b00111100;
    eeprom_data[0b00000111110] = 0b00010110;
    eeprom_data[0b00000111001] = 0b00000011;
    // SB
    eeprom_data[0b00001000100] = 0b00000000;
    eeprom_data[0b00001000010] = 0b00111100;
    eeprom_data[0b00001000110] = 0b00010110;
    eeprom_data[0b00001000001] = 0b00000011;
    // SADD
    eeprom_data[0b00001001100] = 0b00000000;
    eeprom_data[0b00001001010] = 0b00111100;
    eeprom_data[0b00001001110] = 0b00010110;
    eeprom_data[0b00001001001] = 0b00000011;
    // SSUB
    eeprom_data[0b00001010100] = 0b00000000;
    eeprom_data[0b00001010010] = 0b00111100;
    eeprom_data[0b00001010110] = 0b00010110;
    eeprom_data[0b00001010001] = 0b10000011;
    // O
    eeprom_data[0b00001011100] = 0b00000000;
    eeprom_data[0b00001011010] = 0b00111100;
    eeprom_data[0b00001011110] = 0b00000110;
    // JUMP
    eeprom_data[0b00001100100] = 0b00000000;
    eeprom_data[0b00001100010] = 0b00111100;
    eeprom_data[0b00001100110] = 0b00001100;
    break;
  case 3:
    // IA
    eeprom_data[0b00000001100] = 0b10000000;
    eeprom_data[0b00000001010] = 0b00000000;
    eeprom_data[0b00000001110] = 0b00000000;
    // IB
    eeprom_data[0b00000010100] = 0b10000000;
    eeprom_data[0b00000010010] = 0b00000000;
    eeprom_data[0b00000010110] = 0b00000000;
    // ADD
    eeprom_data[0b00000011100] = 0b10000000;
    eeprom_data[0b00000011010] = 0b00000000;
    eeprom_data[0b00000011110] = 0b01000000;
    // SUB
    eeprom_data[0b00000100100] = 0b10000000;
    eeprom_data[0b00000100010] = 0b00000000;
    eeprom_data[0b00000100110] = 0b01000000;
    // OA
    eeprom_data[0b00000101100] = 0b10000000;
    eeprom_data[0b00000101010] = 0b01000000;
    // OB
    eeprom_data[0b00000110100] = 0b10000000;
    eeprom_data[0b00000110010] = 0b01000000;
    // SA
    eeprom_data[0b00000111100] = 0b10000000;
    eeprom_data[0b00000111010] = 0b00000000;
    eeprom_data[0b00000111110] = 0b00000000;
    eeprom_data[0b00000111001] = 0b00000000;
    // SB
    eeprom_data[0b00001000100] = 0b10000000;
    eeprom_data[0b00001000010] = 0b00000000;
    eeprom_data[0b00001000110] = 0b00000000;
    eeprom_data[0b00001000001] = 0b00000000;
    // SADD
    eeprom_data[0b00001001100] = 0b10000000;
    eeprom_data[0b00001001010] = 0b00000000;
    eeprom_data[0b00001001110] = 0b00000000;
    eeprom_data[0b00001001001] = 0b00000000;
    // SSUB
    eeprom_data[0b00001010100] = 0b10000000;
    eeprom_data[0b00001010010] = 0b00000000;
    eeprom_data[0b00001010110] = 0b00000000;
    eeprom_data[0b00001010001] = 0b00000000;
    // O
    eeprom_data[0b00001011100] = 0b10000000;
    eeprom_data[0b00001011010] = 0b00000000;
    eeprom_data[0b00001011110] = 0b01000000;
    // JUMP
    eeprom_data[0b00001100100] = 0b10000000;
    eeprom_data[0b00001100010] = 0b00000000;
    eeprom_data[0b00001100110] = 0b00000000;
    break;
  default:
    break;
  }
  // Sets up the GPIO pins
  pinMode(LED_BUILTIN, OUTPUT);

  // IO
  pinMode(IO0, OUTPUT);
  pinMode(IO1, OUTPUT);
  pinMode(IO2, OUTPUT);
  pinMode(IO3, OUTPUT);
  pinMode(IO4, OUTPUT);
  pinMode(IO5, OUTPUT);
  pinMode(IO6, OUTPUT);
  pinMode(IO7, OUTPUT);

  // AD
  pinMode(AD0, OUTPUT);
  pinMode(AD1, OUTPUT);
  pinMode(AD2, OUTPUT);
  pinMode(AD3, OUTPUT);
  pinMode(AD4, OUTPUT);
  pinMode(AD5, OUTPUT);
  pinMode(AD6, OUTPUT);
  pinMode(AD7, OUTPUT);
  pinMode(AD8, OUTPUT);
  pinMode(AD9, OUTPUT);
  pinMode(AD10, OUTPUT);

  // Controls
  pinMode(WE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(CE, OUTPUT);

  // Writes data to EEPROM
  for (unsigned short int i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
    // Sets controls
    digitalWrite(CE, LOW);
    digitalWrite(WE, LOW);
    digitalWrite(OE, HIGH);
    // Sets Adress
    digitalWrite(AD0, GetBit(i, 1) ? HIGH : LOW);
    digitalWrite(AD1, GetBit(i, 2) ? HIGH : LOW);
    digitalWrite(AD2, GetBit(i, 3) ? HIGH : LOW);
    digitalWrite(AD3, GetBit(i, 4) ? HIGH : LOW);
    digitalWrite(AD4, GetBit(i, 5) ? HIGH : LOW);
    digitalWrite(AD5, GetBit(i, 6) ? HIGH : LOW);
    digitalWrite(AD6, GetBit(i, 7) ? HIGH : LOW);
    digitalWrite(AD7, GetBit(i, 8) ? HIGH : LOW);
    digitalWrite(AD8, GetBit(i, 9) ? HIGH : LOW);
    digitalWrite(AD9, GetBit(i, 10) ? HIGH : LOW);
    digitalWrite(AD10, GetBit(i, 11) ? HIGH : LOW);
    // Writes data
    digitalWrite(IO0, GetBit(eeprom_data[i], 1) ? HIGH : LOW);
    digitalWrite(IO1, GetBit(eeprom_data[i], 2) ? HIGH : LOW);
    digitalWrite(IO2, GetBit(eeprom_data[i], 3) ? HIGH : LOW);
    digitalWrite(IO3, GetBit(eeprom_data[i], 4) ? HIGH : LOW);
    digitalWrite(IO4, GetBit(eeprom_data[i], 5) ? HIGH : LOW);
    digitalWrite(IO5, GetBit(eeprom_data[i], 6) ? HIGH : LOW);
    digitalWrite(IO6, GetBit(eeprom_data[i], 7) ? HIGH : LOW);
    digitalWrite(IO7, GetBit(eeprom_data[i], 8) ? HIGH : LOW);
    delay(50);
  }
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}