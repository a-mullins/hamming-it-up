// hamming by Adam Mullins <adam.l.m@gmail.com>
//
// Assignment:
//     Write a procedure (in C or C++) hamming(ascii, code) that will
//     convert the low-order 7 bits of ascii into an 11-bit integer
//     codeword stored in code.
//
#include <climits>
#include <cstdint>
using std::uint8_t;
using std::uint16_t;

// Later we call __builtin_parityl( long ) with a uint16_t
// argument. If a uint16_t won't fit into a long, the program will
// have errors.
#if ULONG_MAX <= UINT16_MAX
#error "Can't compile using implementation types: uint16_t won't fit in long."
#endif

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

const char ALPHAS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // for demo later.



// (uint16_t *) code is an out-param.
void hamming(uint8_t ascii, uint16_t *code) {
  // Reference diagram.
  //
  //       ASCII byte | __  __  __  __  __  __  __  __
  //  index from left |	 1   2   3   4   5   6   7   8  
  // index from right |	 8   7   6   5   4   3   2   1
  //
  //        Codeword  | __  __  __  __  __  __  __  __  __  __  __
  //  index from left |	 1   2   3   4   5   6   7   8   9  10  11
  // index from right |	11  10   9   8   7   6   5   4   3   2   1
  //      parity bit? |	 P   P   .   P   .   .   .   P   .   .   .
  //                  |	 .   .   1   .   1   .   1   .   1   .   1
  // parity bit 'i'   |	 .   .   2   .   .   2   2   .   .   2   2
  //    checks this   |	 .   .   .   .   4   4   4   .   .   .   .
  //      data bit?   |	 .   .   .   .   .   .   .   .   8   8   8

  // Ensure everything is zeros.
  uint16_t temp = 0;
          *code = 0;

  // Copy ascii into temp. It should fit since temp is 16 bit, ascii is 8.
  temp = ascii;
  // Mask off everything but the 7th bit FROM THE RIGHT, then lshift 2,
  // so that it becomes the 9th bit from the right.
  temp &= 0b0000000001000000;
  temp <<= 2;
  *code |= temp;  // Now blit onto code using bitwise OR.
  temp = 0;       // Clear temp.

  // Again for the 6th, 5th, 4th bits from the right,
  // but shifting by so that they become the 7th, 6th, 5th.
  temp = ascii;
  temp &= 0b0000000000111000;
  temp <<= 1;
  *code |= temp;
  temp = 0;

  // And again, masking off all but the 1st, 2nd, and 3rd bits of `ascii`.
  temp = ascii;
  temp &= 0b0000000000000111;
  *code |= temp;
  temp = 0;

  // Now we set the parity bits.
  //
  // Ignore the five left-most bits of the sixteen bit word, so that the
  // sixth becomes index 1.
  //
  // Counting FROM THE LEFT bit 1 is a parity bit, and checks bits 3, 5, 7, 
  // 9, and 11. So, copy our code into temp, then mask off everything but
  // bits 3,5..11 and calculate the parity.
  //
  // If the parity is already even, leave bit 1 as a 0.
  // Otherwise set it to 1.
  temp = *code;
  temp &= 0b0000000101010101;
  if( __builtin_parityl(temp) ) { // 0 if even, 1 if odd.
    // Set the 10th bit from the right, COUNTING FROM 0.
    // So, the 11th for our usual numbering.
    *code |= (1 << 10);
  }
  temp = 0;

  // Again for bit 2. It checks bits 3, 6, 7, 10, and 11.
  temp = *code;
  temp &= 0b0000000100110011;
  if( __builtin_parityl(temp) ) {
    *code |= (1 << 9); // Set 10th from right.
  }
  temp = 0;

  // Again for bit 4. It checks bits 5, 6, and 7.
  temp = *code;
  temp &= 0b0000000001110000;
  if( __builtin_parityl(temp) ) {
    *code |= (1 << 7); // Set 8th from right.
  }
  temp = 0;

  // Again for bit 8. It checks bits 9, 10, and 11.
  temp = *code;
  temp &= 0b0000000000000111;
  if( __builtin_parityl(temp) ) {
    *code |= (1 << 3); // Set 4th from right.
  }
  temp = 0;
}

// adapted from C++ How To Program 6th ed. by Deitel & Deitel.
// pg 1013, fig 21.6
void display_bits(char alpha, uint16_t bits) {
  const int SHIFT = 10;
  const uint16_t MASK = 1 << SHIFT;

  cout << setw(4) << alpha << " | ";

  for(uint16_t i = 1; i <= SHIFT + 1; i++) {
    cout << (bits & MASK ? '1' : '0');
    bits <<= 1;

    if( i == 3 || i == 7 ) {
      cout << ' ';
    }
  }

  cout << endl;
}

int main(int argc, char **argv) {
  uint16_t code = 0;

  for(short i = 0; i < 26; i++) {
    hamming((uint8_t)ALPHAS[i], &code);
    display_bits(ALPHAS[i], code);
  }

  return 0;
}
