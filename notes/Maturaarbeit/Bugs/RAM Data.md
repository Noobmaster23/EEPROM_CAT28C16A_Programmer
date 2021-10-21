*16.10.2021 14:06*
* * *
ram data is actually directly at program counter address, at least that's written in the instruction code, correct program for it
# New Program
## 6+9 and output it
| **Program Counter** | **Instruction Name** | **Instruction RAM content** | **Memory RAM Data** | **Expected Behaviou** |
| --- | --- | --- | --- | --- | --- |
| 00000001 | IA  | 00000001 | 00000110  | Save 6 in Register A |
| 00000010 | IB  | 00000010 | 00001001  | Save 9 in Register B |
| 00000011 | ADD | 00000011 | XXXXXXXX  | Add 6 to 9 and Output it -> 15 -> 11111 |
| 00000100 | HALT | 00001101 | XXXXXXXX | Stop Program Counter |
* * *
*16.10.2021 14:16* \
wait or not, it seems like only for IA and IB there is a problem, the others have the address saved at the program counter location \
looking up what i programmed \
*16.10.2021 14:20* \
ok so, no, it really takes what is given at program counter value \
sa, sb, sadd and so on just take another address because they have to save, else the value at the address of the program counter is taken