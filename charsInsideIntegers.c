/*
Name: Joshua Doucet
Date: 04-06-2019
Description: The program prompts the user for 4 characters. These characters are then printed
   as an integr representation, and a bit string of 1 byte. The binary value of the 4 individual characters
   is then packed into a single unsigned integer value. This integer is stored in 4 bytes and each 
   byte corresponds to the binary value of one of the 4 entered character.
   This integer is outputted to the application along with its binary value.
*/

#include <stdio.h>
#include <limits.h>

#define INPUT_SIZE 4

//displays the parameter aChar as a bit string
void dispCharsAsIntAndBits(unsigned int aChar);

//Packs 4 characters from chars2pack into an unsigned integer and returns it
//Ex: if chars2pack = { 'a', 'b', 'c', 'd' }, 
//    then the ascii values of the chars are 97 98 99 100, which corresponds to 
//    1100001 1100010 1100011 1100100 in binary.
//    Therefore the integer 1,633,837,924 is returned, which in binary is
//    1100001 1100010 1100011 1100100
unsigned int packCharacters(const char chars2pack[INPUT_SIZE + 1]);

int main() {
   printf_s("Packing Characters into an Integer\n-----------------------------\n");
   char exitFlag = 'y';
   _Bool hasLoopedOnce = 0;

   //Continue until user wishes to exit
   while (exitFlag != 'n' && exitFlag != 'N') {
      //Array to store 4 user inputted characters
      char userChars[INPUT_SIZE + 1] = { 0 };
      //Integer that will store the bit string value of the 4 character inputs
      unsigned int charPackage = 0;

      //Get 4 characters from user
      printf_s("Enter 4 characters with no spaces in-between.\nInput: ");
      if(hasLoopedOnce) //Clear empty white space from input stream
         while (getchar() != '\n' && getchar() != ' ');
      hasLoopedOnce = 1;
      fgets(userChars, INPUT_SIZE + 1, stdin);

      //Output each char in userChars as an integer and a bitstring
      for (unsigned int character = 0; character < INPUT_SIZE; character++) {
         printf_s("\nCharacter \"%c\" as an ASCII value and a bit string:\n", userChars[character]);
         dispCharsAsIntAndBits(userChars[character]);
      }

      //Pack the characters in userChars into the single integer charPackage
      charPackage = packCharacters(userChars);

      //Display packed characters as an integer and a bit string
      printf_s("\nCharacters \"%s\" as a character packed integer value and a bit string:\n", userChars);
      dispCharsAsIntAndBits(charPackage);

      while (getchar() != '\n');
      printf_s("\nPack another 4 characters? (Y/N): ");
      exitFlag = getchar();
   }

   return 0;
}

void dispCharsAsIntAndBits(unsigned int chars) {
   //10000000 00000000 00000000 00000000
   unsigned int dispMask = 1 << (sizeof(unsigned int) * CHAR_BIT - 1);

   printf_s("%8d = ", chars);

   //print each bit representing aChar
   for (unsigned int bit = 1; bit <= (sizeof(unsigned int) * CHAR_BIT); bit++) {
      //if aChar bitwiseAND dispMask is non-zero print 1, else print 0
      //Non-zero indicates that a bit of aChar has matched with the dispMask
      putchar(chars & dispMask ? '1' : '0');
      //Shift aChar bits by 1 place to the left for next bit comparision
      chars <<= 1;

      //Output space between every 8 bits
      if (bit % CHAR_BIT == 0)
         putchar(' ');
   }
   putchar('\n');
}

unsigned int packCharacters(const char chars2pack[INPUT_SIZE + 1]) {
   //Integer to pack characters into, initialize to first character in array
   //Ex: if chars2pack[0] = 'A', then charPackage is 65
   //Or in bits 65 = 00000000 00000000 00000000 10000001
   unsigned int charPackage = chars2pack[0];

   //Pack the other 3 characters into charPackage
   for (int character = 1; character <= INPUT_SIZE - 1; character++) {
      //Shift bits left by 8 bits for example above, the bit string becomes
      //00000000 00000000 10000001 00000000
      charPackage <<= 8;
      //Continuing with the ex above, if chars2pack[1] = 'B',
      //then the OR bitwise expression below will make charPackage 
      //00000000 00000000 10000001 10000010
      charPackage ^= chars2pack[character];
   }

   return charPackage;
}