#ifndef Microwave_H_
#define Microwave_H_

void microwave_Init(void);
void cook_Popcorn();
void cook_Beef_or_Chicken(char choose);
char* Int_to_char(int x);
int Char_to_int(char x);
void Cook_Time();
void Time_Display(char time[]);
#endif