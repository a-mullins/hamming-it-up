/* hamming by Adam Mullins <adam.l.m@gmail.com> */

/*
 * Assignment:
 *     Write a procedure (in C or C++) hamming(ascii, code) that will
 *     convert the low-order 7 bits of ascii into an 11-bit integer
 *     codeword stored in code.
 */
#include <cstdint>
using std::uint8_t;
using std::uint16_t;


void hamming(uint8_t ascii, uint16_t *code) {
  // Diagram for reference:
  //
  // ASCII: 12 345 678
  //        -- --- ---
  //         . ...  11   <- Which bit goes where.
  //         3 567 901    ascii[8] goes in code[11] (counting from 1)

  // Code : __  __  __  __  __  __  __  __  __  __  __
  //         1   2   3   4   5   6   7   8   9  10  11
  //         P   P   .   P   .   .   .   P   .   .   .
  //         1   .   1   .   1   .   1   .   1   .   1
  //             2   2   .   .   2   2   .   .   2   2
  //                     4   4   4   4   .   .   .   .
  //                                     8   8   8   8

  // PSEUDO-CODE:
  //   1. Set bits in `code` to coresponding bits in `ascii`.
  //      a. copy `ascii` into temp, mask off all but ascii bit 2.
  //      b. l-shift 2.
  //      c. bitwise `temp` or onto `code`--if bit 7th is 1, set it.
  //         else leave 0.
  //
  //      d. Again for 4th, 5th, 6th bits from left.
  //
  //   2. Calculate and set parity bits.
  //   3. Return.


  // Ensure everything is zeros.
  uint16_t temp = 0;
          *code = 0;

  // Copy ascii into temp. It should fit since temp is 16 bit, ascii is 8.
  temp = ascii;
  // Mask off everything but the 7th bit from the right, then lshift 2,
  // so that it becomes the 9th bit from the right.
  temp &= 0b0000000001000000;
  temp <<= 2;
  // Copy onto code using bitwise OR.
  *code |= temp;
  // Clear temp.
  temp = 0;

  // Again for the 6th, 5th, 4th bits from left, but shifting by 1 so that
  // they become the 7th, 6th, 5th bits from left.
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

  // Now, parity bits.
  // Counting FROM THE RIGHT, bit 1 checks bits 3, 5, 7, 9, and 11.
  // So, copy our code into temp, then mask off everything but bits 3,5..11
  // and calculate the parity.
  //
  // If the parity is already even, leave 1 as 0. Otherwise set it to 1.
  temp = *code;
  temp &= 0b0000000101010101;
  // FIXME: Ensure long and uint16_t have the same bit-width.
  if( !__builtin_parityl(temp) ) { // 0 if even, 1 if odd.
    // Set the 10th bit from the right, COUNTING FROM 0.
    // So, the 11th for our usual numbering.
    *code |= (1 << 10);
  }
  temp = 0;

  // Again for bit 2. It checks bits 3, 6, 7, 10, and 11.
  temp = *code;
  temp &= 0b0000000100110011;
  if( !__builtin_parityl(temp) ) {
    *code |= (1 << 9); // Set 10th from right.
  }
  temp = 0;

  // Again for bit 4. It checks bits 5, 6, and 7.
  temp = *code;
  temp &= 0b0000000001110000;
  if( !__builtin_parityl(temp) ) {
    *code |= (1 << 7); // Set 8th from right.
  }
  temp = 0;

  // Again for bit 8. It checks bits 9, 10, and 11.
  temp = *code;
  temp &= 0b0000000000000111;
  if( !__builtin_parityl(temp) ) {
    *code |= (1 << 3); // Set 4th from right.
  }
  temp = 0;
}

int main(int argc, char **argv) {
 /* FIXME: Stub. */
  return 0;
}


