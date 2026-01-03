/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
//1
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  return ~(~x & ~y);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return x & 1;
}
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  return ~x & ~y;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~(~x & y) & ~(x & ~y)) ;
}
//2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  int mask = 0x55;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  return mask;
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  int mask_odd_num = 0xAA;
  mask_odd_num = mask_odd_num << 8 | mask_odd_num;
  mask_odd_num = mask_odd_num << 16 | mask_odd_num;
    return !!(x & mask_odd_num);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int nByte;
  int mByte;
  int result;
  int nShift = n << 3;
  int mShift = m << 3;
  int mask = 0xFF;

  int nMask = mask << nShift;
  int mMask = mask << mShift;
  nByte = x & nMask;
  mByte = x & mMask;

  nByte = nByte >> nShift;
  mByte = mByte >> mShift;
  nByte = nByte & mask;
  mByte = mByte & mask;  
  nByte = nByte << mShift;
  mByte = mByte << nShift;

  result = x & ~(nMask | mMask);
  result = result | nByte | mByte;
  return result;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int shift = (32 + ~n + 1);
  int a = (x << shift);
  int b = (a >> shift);
  return (!(b ^ x));
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  int mask_odd_num = 0xAA;
  mask_odd_num = mask_odd_num << 8 | mask_odd_num;
  mask_odd_num = mask_odd_num << 16 | mask_odd_num;
  return mask_odd_num;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  int MSb = x >> 31;
  return MSb | (!!x);
}
//3
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int sum = x + y;
  int sign_x = (x >> 31);
  int sign_y = (y >> 31);
  int sign_sum = (sum >> 31);
  int same_sign = !(sign_x ^ sign_y);
  int dif_sign = (sign_x ^ sign_sum);
  return !(dif_sign & same_sign);
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  int mask_high = ~0;
  int mask_low = ~0;
  int mask_result = 0;
  int condition = highbit + (~lowbit + 1);

  mask_high = mask_high << highbit;
  mask_high = ~ (mask_high << 1);
  mask_low = mask_low << lowbit;
  mask_result = mask_high & mask_low;
  condition = ~(condition >> 31);

  return mask_result & condition;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int mask = !x;
  mask = mask << 1 | mask;
  mask = mask << 2 | mask;
  mask = mask << 4 | mask;
  mask = mask << 8 | mask;
  mask = mask << 16 | mask;
  return ((~mask) & y) | (mask & z);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int mask_1 = 0x55 | (0x55 << 8);
  int mask_2 = 0x33 | (0x33 << 8);
  int mask_3 = 0x0F | (0x0F << 8);
  int mask = 0x3F;
  int cont; 
  mask_1 = mask_1 | (mask_1 << 16);
  mask_2 = mask_2 | (mask_2 << 16);
  mask_3 = mask_3 | (mask_3 << 16);
  cont = (x & mask_1) + ((x >> 1) & mask_1);
  cont = (cont & mask_2) + ((cont >> 2) & mask_2);
  cont = ((cont + (cont >> 4)) & mask_3);
  cont = cont + (cont >> 8);
  cont = cont + (cont >> 16);
  return cont & mask;
}
/* 
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and & 
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y) {
  int mask_and = x & y;
  int mask_or = x|y;
  int bitMask = (~mask_or)|mask_and;
  return bitMask;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int mask = 0xFF;
  int result;
  mask = mask << (n << 3);
  c = c << (n << 3);
  result = x & (~mask);
  result = result | c;
  return result;
}
//4
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum negative value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  int MIN = 1 << 31;
  int MAX = ~MIN;
  int sum = x + y;
  int sign_x = (x >> 31);
  int sign_y = (y >> 31);
  int sign_sum = (sum >> 31);
  int same_sign = !(sign_x ^ sign_y);
  int overflow = same_sign & (sign_x ^ sign_sum);
  int neg_overflow = (sign_x << 31) >> 31;
  int overflow_mask = (overflow << 31) >> 31;
  int result = (neg_overflow & MIN) | (~neg_overflow & MAX);
  return (overflow_mask & result) | (~overflow_mask & sum);
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  int sign = x >> 31;
  int Mul = x << 1;
  int sign_mul = Mul >> 31;
  int TMin = 0x8 << 28;
  int TMax = ~TMin;
  int overflow = sign ^ sign_mul;
  int val_sign = (sign & TMin) | (~sign & TMax);

  return (overflow & val_sign) | (~overflow & Mul);
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
  int mask = 0x01;
  int result = x | (~x + 1);
  result = result >> 31;
  return result & mask;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  int left = x << (32 + (~n + 1));
  int mask = ~(((1 << 31) >> n) << 1);
  int right = (x >> n) & mask;
  x = left | right;
  return x;
}
//float
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  int num_negative = 0x8 << 28;
  int mask_positive = ~(num_negative);
  int mask_1 = 0xFF;
  int mask_2 = 0x7FFFFF;
  unsigned exp = (uf >> 23) & mask_1;
  unsigned mantisa = uf & mask_2;

  if (mantisa != 0 && exp == mask_1){
    return uf;
  }

  if (uf & num_negative){
    uf = uf & mask_positive;
  }

  return uf;
}
/* 
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
  int maskExp = 0x7F800000;
  int maskMantisa = 0x007FFFFF;

  int ufExp = uf & maskExp;
  int ugExp = ug & maskExp;
  int ufMantisa = uf & maskMantisa;
  int ugMantisa = ug & maskMantisa;

  if ((ufExp == maskExp && ufMantisa != 0) || (ugExp == maskExp && ugMantisa != 0)) {
    return 0;
  }
  if ((uf << 1) == 0 && (ug << 1) == 0) {
    return 1;
  }
  return uf == ug;
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  int mask_1 = 0xFF;
  int mask_2 = 0x7FFFFF;
  int change_sign = 0x80000000;
  unsigned exp = (uf >> 23) & mask_1;
  unsigned mantisa = uf & mask_2;
  if (mantisa != 0 && exp == mask_1){
    return uf;
  }
  return uf ^ change_sign;
}
/* 
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug) {
  int mask_1 = 0xFF;
  int mask_2 = 0x7FFFFF;
  unsigned exp_f = (uf >> 23) & mask_1;
  unsigned mantisa_f = uf & mask_2;
  unsigned exp_g = (ug >> 23) & mask_1;
  unsigned mantisa_g = ug & mask_2;
  int sign_f = uf >> 31;
  int sign_g = ug >> 31;
  
  if ((mantisa_f != 0 && exp_f == mask_1) || (mantisa_g != 0 && exp_g == mask_1)){
    return 0;
  }

  if ((uf << 1) == 0 && (ug << 1) == 0){
    return 0;
  }

  if (sign_f != sign_g){
    return sign_f > sign_g;
  }else if (sign_f == 0){
    return uf < ug;
  }else {
    return ug < uf;
  }
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int result;
  int maskSign = 0x80000000;
  int maskExp = 0x7F800000;
  int maskMantisa = 0x007FFFFF;
  int implicitoMantisa = 0x01 << 23;

  int sign = uf & maskSign;
  int exp = uf & maskExp;
  int mantisa = uf & maskMantisa;

  exp = (exp >> 23) - 127;
  if (exp < 0) {
    return 0;
  }
  if (exp > 31) {
    return 0x80000000u;
  }
  mantisa = mantisa | implicitoMantisa;
  if (exp >= 23) {
    result = mantisa << (exp - 23);
  } else {
    result = mantisa >> (23 - exp);
  }
  if (sign) {
    return -result;
  }
  return result;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  int INF = 0x7F800000;
  int tope = 127;
  int exp = x + tope;
  if (x > tope){
    return INF;
  } else if ( x < -(tope)){
    return 0;
  }

  return exp << 23;
}
