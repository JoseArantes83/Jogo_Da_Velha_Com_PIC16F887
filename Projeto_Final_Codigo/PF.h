#include <16F887.h>
#device ADC = 10

#FUSES PUT        // Power Up Timer
#FUSES NOMCLR     // Master Clear pin used for I/O
#FUSES NOPROTECT  // Code not protected from reading
#FUSES NOCPD      // No EE protection
#FUSES NOBROWNOUT // No brownout reset
#FUSES IESO       // Internal External Switch Over mode enabled
#FUSES FCMEN      // Fail-safe clock monitor enabled
#FUSES NOLVP      // No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES BORV40     // Brownout reset at 4.0V
#FUSES NOWRT      // Program memory not write protected

#use delay(crystal = 8MHz)
#use FIXED_IO(A_outputs = PIN_A5)
#use FIXED_IO(B_outputs = PIN_B7, PIN_B6, PIN_B5, PIN_B4, PIN_B3, PIN_B2, PIN_B1, PIN_B0)
#use FIXED_IO(C_outputs = PIN_C7, PIN_C6, PIN_C5, PIN_C4, PIN_C3, PIN_C2, PIN_C1, PIN_C0)
#use FIXED_IO(D_outputs = PIN_D7, PIN_D6, PIN_D5, PIN_D4, PIN_D3, PIN_D2, PIN_D1, PIN_D0)
#use FIXED_IO(E_outputs = PIN_E0)
#define B_CONFIRM PIN_A0
#define B_MOVE PIN_A1
#define B_RESET PIN_A2
#define RED1 PIN_A5
#define RED2 PIN_B0
#define RED3 PIN_B1
#define GREEN1 PIN_B2
#define GREEN2 PIN_B3
#define GREEN3 PIN_B4
#define LIN1 PIN_B7
#define LIN2 PIN_B6
#define LIN3 PIN_B5
// #define GND PIN_E0
#define A1 PIN_C0
#define A2 PIN_C1
#define A3 PIN_C2
#define A4 PIN_C3
#define A5 PIN_C4
#define A6 PIN_C5
#define A7 PIN_C6
#define A8 PIN_C7
#define B1 PIN_D0
#define B2 PIN_D1
#define B3 PIN_D2
#define B4 PIN_D3
#define B5 PIN_D4
#define B6 PIN_D5
#define B7 PIN_D6
#define B8 PIN_D7
