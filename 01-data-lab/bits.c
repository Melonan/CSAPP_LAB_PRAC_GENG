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
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // x&y 得到 x和y中相同位置都是1的
  // ~x & ~y 得到x和y中相同位置都是0的
  // 上述位置xor之后都应该为0
  // 则将两者都取反, ~(x&y) and ~(~x&~y) 
  // 中的0的位置结果中都应该为0，都为1的位置结果中为1
  return (~(x&y)) & (~(~x&~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int tmp = 1;
  tmp<<=31;
  return tmp;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
// 0111 1111
// ~
// 1000 0000

// -1
// 1111 1111
// 0
// 0000 0000  
int isTmax(int x) {
   return !(~(x+1)^x)  &  !!(~x);
}

/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int num = 0xAA;
  num = (num<<8)+num;
  num = (num<<16)+num;
  return !((x&num)^num);
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
  *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}

/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */

/**
 * 0x30 0x39
 * 
 * 0011 0000
 * ~
 * 0011 1001
 * 
 * 1. assure  x>>6 should be 0   !(x>>6)
 * 
 * 2. then we just concerned about lower 6bit  
 * 
 * 3. assure 11**** form !( ( x >> 4 ) ^ 0b11 )
 *
 * 4. lower 4 bit assure 0000~1001
 *    define low4b = lower 4 bits
 *    ***res = low4b - 0xA should < 0 (illegal , use operator '-')
 *    ***(cuz 0xA is 1010)
 *    ***res>>31 check the sign bit should be 1
 *    res = low4b + 0b0110
 *    check the 5th bit should be 0
 *    cond3 = !(res >> 4)
*/

int isAsciiDigit(int x) {
  int cond1 = !(x>>6);
  int cond2 = !(x>>4 ^ 0x3);
  int cond3;
  int low4b = x & 0xF;
  // below used illegal operator 
  // int res = low4b - 0xA; 
  // cond3 = !!(res >> 31);
  int res = low4b + 0x6;
  cond3 = !(res >> 4);

  return cond1 & cond2 & cond3;
  // return cond1 & cond2 &  ( (!(x&0x8)) | !!((x+6)&0x8));
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int expr = ~(!x) + 1;
  return (~expr & y) | (expr & z);
}


/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */

// 会爆int: 判断异号的情况  确保x y是同号再相减
//  x-y -> x+(-y) >0 or <0
int isLessOrEqual(int x, int y) {
  int xmy = x+(~y + 1);  // (x - y)
  int signX = x>>31 & 1;
  int signY = y>>31 & 1;
  // int xpyn = ~signX & signY;
  int xnyp = signX & ~signY; 

  int sameSignSubNeg = (!(signX ^ signY)) & (xmy >> 31 & 1) ;
// 我们需要考虑写下来的是返回1的情况 , 否则最终默认返回0
  return !(x^y) | xnyp | sameSignSubNeg;
}




//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int negX = ~x+1; 
  int tmp = (x | negX) >> 31 ; // assure that all bit is 1 , we got -1
  return tmp + 1; // -1 + 1 = 0 , 0 + 1 = 1 
} 


/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int isZero = !x;
  // 只关注有效位 —— 最高有效位我们定为第一个非0位
  int flag = x >> 31; // sign bit  0x000..0 or 0x111..1

  int ans;

  int bit_16,bit_8,bit_4,bit_2,bit_1,bit_0;

  x = (~flag & x) | (flag & ~x); // 无论正负，都变成符号位为0的，第一有效位都为1了现在
  
  bit_16 = !!(x>>16) << 4;  // 如果高16位存在则:1 << 4  else  0 << 4
  x >>= bit_16;           
  // bit_16 == 16时，说明高16位存在，
  // 我们不看低16位了，否则，只看低16位，不看高16位了。
  
  bit_8 = !!(x>>8) << 3;
  x >>= bit_8;

  bit_4 = !!(x>>4) << 2;
  x >>= bit_4;

  bit_2 = !!(x>>2) << 1;
  x >>= bit_2;

  bit_1 = !!(x>>1) ;
  x >>= bit_1;

  bit_0 = x;

  // 1 represent sign bit
  ans = bit_16 +bit_8 + bit_4 + bit_2 + bit_1 + bit_0 + 1;
  return isZero | ans;
}


//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) 
{
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned sign = (uf & (1<<31));
  unsigned frac = (uf<<9)>>9;
  unsigned ans = 0;
  // NaN and Infinity
  if(!(exp^0xFF)) 
    return uf;
  
  // if(exp == 0 && frac == 0)
  // return uf;

  // denormalized number 
  if(exp == 0)
  {
    // E = 1-bias = 126 , definite 
    frac <<= 1;
    // frac = (frac << 9) >> 9;
    // frac = frac & 0x7fffff;
    // 为啥位操作都不限制frac 和 exp 是22位和8位呢 加了上述两行反而过不了
    return sign | frac;
  }
  else  // normalized number 
  {
    exp++ ;  // *2
    // exp = exp & (0xFF); 
    ans = (exp << 23) | sign | frac;
    return ans;
  }
  return 0;
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
int floatFloat2Int(unsigned uf) 
{
  int exp = (uf >> 23 ) & 0xff;
  int sign = (uf >> 31) & 1;
  int frac = (uf<<9) >> 9;
  int Exp = exp - 127;

  if(exp == 0xFF)
    return 1<<31;


  //denormalize
  if(exp == 0)
  {
    return 0;
  }
  
  // value = (-1)^sign * M * 2^E
  //normalize
  frac |= 0xFFFFFF; // 补充隐藏位的1
  
  if(Exp < 0 )
    return 0;
  
  if(Exp > 31) 
  {
    return 1<<31;
  }

  if(Exp >= 23)
    frac <<= (Exp - 23);
  else
  {
    Exp = 23 - Exp;
    frac = frac >> Exp;
  }

  if(sign) // negative
    return ~frac + 1;


  return frac;
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
  unsigned pINF = 0xFF << 23;
  unsigned exp = x + 127;
  int zero_exp = -23-126;
  // normalize : 2^-126 ~ 2^127
  unsigned ans = 0;
  signed posi;

  // less than smallest denormalize
  if(x < zero_exp)
    return 0;

  // INF 
  if(x > 127)
   return pINF;


  // denormalize
  if(x < -126)
  {
    posi = -126 - x;
    ans |= (0x1 << (23-posi));
    return ans;
  }

  // normalize 

  ans |= (exp << 23);

  return ans;
}
