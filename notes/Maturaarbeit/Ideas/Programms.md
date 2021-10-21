# Additional Information

- the value in memory points to another memory address where the actually value is saved
- address of memory ram and instruction ram is just the program counter
- https://tableconvert.com/ good website

# Old Programs
## 6+9 and output it

| **Program Counter** | **Instruction Name** | **Instruction RAM content** | **Memory RAM Address** | **Memory RAM Data** | **Expected Behavioru** |
| --- | --- | --- | --- | --- | --- |
| 00000001 | IA  | 00000001 | 11111111 | 00000110 | Save 6 in Register A |
| 00000010 | IB  | 00000010 | 11111110 | 00001001 | Save 9 in Register B |
| 00000011 | ADD | 00000011 | XXXXXXXX | XXXXXXXX | Add 6 to 9 and Output it -> 15 -> 11111 |
| 00000100 | HALT | 00001101 | XXXXXXXX | XXXXXXXX | Stop Program Counter |
# New Programs
According to: [RAM Data](../../Maturaarbeit/Bugs/RAM%20Data.md)
## 6+9 and output it
| **Program Counter** | **Instruction Name** | **Instruction RAM content** | **Memory RAM Data** | **Expected Behaviour** |
| --- | --- | --- | --- | --- | --- |
| 00000001 | IA  | 00000001 | 00000110  | Save 6 in Register A |
| 00000010 | IB  | 00000010 | 00001001  | Save 9 in Register B |
| 00000011 | ADD | 00000011 | XXXXXXXX  | Add 6 to 9 and Output it -> 15 -> 11111 |
| 00000100 | HALT | 00001101 | XXXXXXXX | Stop Program Counter |