#include <Arduino.h>
#include <math.h>

// Debugging
#define DEBUG false
#define DEBUG_MODE 0 // 0 = Off, 1 = Array, 2 = Output, 3 = LED
#define DEBUG_COUNTER_VALUE 10

// Mode
#define EEPROM_NUMBER 1

// GPIO pin definitions
#define IO0 13 // F -> 13
#define IO1 1  // T
#define IO2 3  // T
#define IO3 4  // T
#define IO4 2  // T
#define IO5 15 // F -> 15
#define IO6 5  // F -> 5
#define IO7 18 // F -> 18

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

// Data to write to EEPROM
#define EEPROM_DATA_LENGTH 8
#define EEPROM_ADDRESS_LENGTH 11
#define EEPROM_ADDRESS_SIZE 2048

unsigned char eeprom_data[EEPROM_ADDRESS_SIZE];

// Functions
// Gets bit from an int
// https://www.studymite.com/cpp/examples/program-to-get-nth-bit-of-a-number-in-cpp/
bool GetBit(unsigned int b, unsigned int bitNumber)
{
  return (1 & (b >> (bitNumber - 1)));
}

// Debugging
// #if DEBUG
// #if DEBUG_MODE == 3
// unsigned int counter = 0;
// #endif
// #endif

void setup()
{
// Debuging
#if DEBUG
#if DEBUG_MODE != 3
  {
    Serial.begin(9600);
  }
#endif
#endif

  // Set Array all to 0
  for (unsigned short int i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
    if (GetBit(i, 3) && !GetBit(i, 2) && !GetBit(i, 1))
    {
// Because the Instruction has to be loaded every time set the instruction for the first step for every instruction to the same value
#if EEPROM_NUMBER == 1
      eeprom_data[i] = 0b00000001;
#elif EEPROM_NUMBER == 2
      eeprom_data[i] = 0b00000000;
#elif EEPROM_NUMBER == 3
      eeprom_data[i] = 0b10000000;
#endif
    }
    else
    {
      eeprom_data[i] = 0;
    }
  }
// Sets wanted EEPROM Data for the three EEPROMS
#if EEPROM_NUMBER == 1
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
  // HALT
  eeprom_data[0b00001101100] = 0b00000001;
  eeprom_data[0b00001101010] = 0b00000000;
#elif EEPROM_NUMBER == 2
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
  // HALT
  eeprom_data[0b00001101100] = 0b00000000;
  eeprom_data[0b00001101010] = 0b01000000;
#elif EEPROM_NUMBER == 3
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
  // HALT
  eeprom_data[0b00001101100] = 0b01000000;
  eeprom_data[0b00001101010] = 0b00000000;
#endif
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

  digitalWrite(CE, LOW);
  digitalWrite(OE, HIGH);
  digitalWrite(WE, HIGH);

  delay(25);

  // Writes data to EEPROM
  for (unsigned short int i = 0; i < EEPROM_ADDRESS_SIZE; i++)
  {
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

    // enable when all pins are set
    delay(25);
    digitalWrite(WE, LOW);
    // Debug
    // give time to read address
    delay(25);
    // Sets controls (disable, until all pins are set)
    digitalWrite(WE, HIGH);
    // write data
    delay(25);
#if DEBUG
#if DEBUG_MODE == 1
    Serial.print(i, BIN);
    Serial.print(" : ");
    Serial.println(eeprom_data[i], BIN);
#elif DEBUG_MODE == 2
    for (unsigned short int j = 0; j < EEPROM_ADDRESS_LENGTH; j++)
    {
      Serial.print(GetBit(i, j + 1) ? "1" : "0");
    }
    Serial.print(" : ");
    for (unsigned short int j = 0; j < EEPROM_DATA_LENGTH; j++)
    {
      Serial.print(GetBit(eeprom_data[i], j + 1) ? "1" : "0");
    }
    Serial.println();
#elif DEBUG_MODE == 3
    if (i == DEBUG_COUNTER_VALUE)
    {
      while (true)
      {
        delay(1000);
      }
    }
#endif
#endif
  }

  // Disable EEPROM
  digitalWrite(CE, HIGH);

  // #if DEBUG
  // #if DEBUG_MODE == 3
  //   counter++;
  // #endif
  // #endif
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}