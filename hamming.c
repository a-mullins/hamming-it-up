/* hamming by Adam Mullins <adam.l.m@gmail.com> */

/*
 * Assignment:
 *     Write a procedure (in C or C++) hamming(ascii, code) that will
 *     convert the low-order 7 bits of ascii into an 11-bit integer
 *     codeword stored in code.
 */
#include <stdint.h>
/* for uint16_t */

/* uchar guaranteed >=8 bits, enough for ASCII */
void hamming(unsigned char ascii, uint16_t *code) {
  /*
   * ASCII: 12 345 678
   *        -- --- ---
   *         . ...  11   <- Which bit goes where.
   *         3 567 901    ascii[8] goes in code[11] (counting from 1)
   *
   * Code : __  __  __  __  __  __  __  __  __  __  __
   *         1   2   3   4   5   6   7   8   9  10  11
   *         P   P   .   P   .   .   .   P   .   .   .
   *         1   .   1   .   1   .   1   .   1   .   1
   *             2   2   .   .   2   2   .   .   2   2
   *                     4   4   4   4   .   .   .   .
   *                                     8   8   8   8
   */

  /*
   * 1. Set bits in `code` to coresponding bits in `ascii`.
   * 2. Calculate and set parity bits.
   * 3. Return.
   */
}

int main(int argc, char **argv) {
 /* FIXME: Stub. */
  return 0;
}
