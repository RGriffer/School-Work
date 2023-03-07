/**
 *  @author  Ryan Griffin @ rgriffer@colostate.edu
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int2char (int radix, int value) {
    char character;
    if(value <= radix - 1 && value >= 0) {
        if(value <= 9) {
            character = value + 48;
            return character;
        }
        else {
            character = 'A';
            character = character + (value - 10);
            return character;
        }
    }
    return '?';
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char2int (int radix, char digit) {
  int value = -1;
  int temp;
/*test digit for strictly numbers*/
  if (digit <= '9' && digit >= '0') {
      value = digit - '0';
  }
/*test for all characters between a and z*/
  else {
      if (digit <= 'z' && digit >= 'a') {
          temp = digit - 32;
          value = temp - 'A' + 10;
      }
      else {
          value = digit -'A' + 10;
      }
  }
/*test to see if proper parameters, WHY WONT IT TAKE '!' WHY*/
  if (radix < 2 || radix > 36 || (value < 0) || (value >= radix))
 {
      return -1;
  }
  return value;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void divRem (int numerator, int divisor, int* quotient, int* remainder) {
    *quotient = 0;
    while(numerator >= divisor) {
        numerator = numerator - divisor;
        *quotient += 1;
    }
    *remainder = numerator;
        
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii2int (int radix, int valueOfPrefix) {
  char next = getchar();
  if(next == '\n') {
      return valueOfPrefix;
  }
  return ascii2int(radix,valueOfPrefix*radix + char2int(radix,next));
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int2ascii (int radix, int value) {
    int x = 0;
    int y = 0;
    divRem(value, radix, &x, &y);
    if(x > 0) {
        int2ascii(radix, x);
    }
    putchar(int2char(radix, y));
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac2double (int radix) {
    //look at on monday. 270 and 253 is a lot of work :(((((((
    return -1.0;
}

