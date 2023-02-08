

# Data_lab

- 使用XOR进行判断两数相等
- 补码取相反数：<u>**取反加一**</u>
- ` !!(~x)` 两个感叹号——将数字规格化为True/False的结果

## bitXor

> 使用& , ~运算表达异或运算

​	主要就是针对德摩根定律的应用

​	首先
$$
A \bigoplus B  ={\bar{A} B \cup A \bar{B}}
$$
​	使用德摩根律：
$$
A \bigoplus B & ={\bar{A} B \cup A \bar{B}} \\
& =\overline{(A \cup \bar{B}) \cap(\bar{A} \cup B)} \\
& =\overline{((A \cup \bar{B}) \cap \bar{A}) \cup((A \cup \bar{B}) \cap B)} \\
& =\overline{(\bar{A} \bar{B})\cup(A B)} \\
&= \overline{\bar{A} \bar{B}} \cap \overline{AB}
$$

```c
int bitXor(int x, int y) {
  // x&y 得到 x和y中相同位置都是1的
  // ~x & ~y 得到x和y中相同位置都是0的
  // 上述位置xor之后都应该为0
  // 则将两者都取反, ~(x&y) and ~(~x&~y) 
  // 中的0的位置结果中都应该为0，都为1的位置结果中为1
  return (~(x&y)) & (~(~x&~y));
}
```



## tmin

```cpp
return 1<<31;
```

## isTmax

```c
/*
* isTmax - returns 1 if x is the maximum, two's complement number,
*     and 0 otherwise 
*   Legal ops: ! ~ & ^ | +
*   Max ops: 10
*   Rating: 1
*/
int isTmax(int x) {
   return !(~(x+1)^x)  &  !!(~x);
}
```

​	**判断是否为Tmax**

> 冷知识：
>
> - 补码取相反数：<u>**取反加一**</u>（没用到，这道题我们用加一再取反）
>
> - **判断两个数相等可以用XOR，相等的数异或之后得0**

- 讨论8位数——Tmax为：

​	0111 1111—— 对其**加一取反**——0111 1111 不变

​	因此，我们如此判断

```c
int isTmax(int x) {
  ~(x+1)^x;
}
```

​	当上述式子为0，则为Tmax；

- 但是**有特例**

> 对于1111 1111 加一取反之后 也不变，因此我们需要其特判

​	因为只有 1111 1111 取反后为 0，否则取反后8bit中含1，为其他什么数字

​	因此：

- ` !!(~x)`该式子返回1代表并非1111 1111
- `！(~(x+1)^x)`  返回1代表为Tmax or 1111 1111

那么and连接上面两个即可

```c
int isTmax(int x) {
  return !(~(x+1)^x)  &  !!(~x);
}
```

​		

## allOddBits

```c
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
```

​	先构造了奇数位全为1的数num == 0xAAAAAAAA

​	倘若x奇数位全为1，则 `num&x` 应该仍为 num，使用XOR进行判断两数相等。



## negate

```c
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}
```



## isAsciiDigit

```c
 /* isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
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
```

​	对于cond3——即判断后四位为 0b0000~0b1001 有两种方式

- ~~后四位 - 0xA 看是否小于0~~

  ```bash
  geng@6bbf66b56819:/usr/src/app/01-data-lab$ ./dlc ./bits.c
  dlc:./bits.c:244:isAsciiDigit: Illegal operator (-)
  ```

  

- 我的方式：

  - 先判断如果是 0b0*** 0开头，那么OK

    如果 0b1*** 型式，那么 后四位+6 根据进位判断 第四位为1还是0，若是0，说明发生进位，则原本的后四位大于0b1001

  - **后四位直接+6**

    如果发生进位——第五位为1，则不符合要求

    若没发生进位——第五位为0，符合要求



## conditional

```c
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
```

对于选择判断来说 return 必然以这种形式

```c
return ( ) | ( )
```

我们定义和x有关的expr    expr满足条件，返回y，否则 返回z :


```c
return ( expr & y ) | (~expr & z)
```
那么 expr 要么为1111111 要么 000000

我们使得
- x != 0x0   时 expr == 0000...
- x == 0x0  时 expr == 1111...

我们定义 

expr = ~(!x) + 1

其中 !x 后 变为0/1 

- 1取非——>取反 +1 ——> 0x00000000
- 0取非——>取反+1 ——>0xFFFFFFFF

```c
return (expr & y) | (~expr & z)
```



## isLessOrEqual

0x8000 0000 相反数 仍为自己 

X - 0x80000000 == X + 0x80000000

- 可能溢出
  - 同号相加
  - 异号相减

```c
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */

// 会爆int 0x8000 0000 : 判断异号的情况  确保x y是同号再相减
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
```

## logicalNeg

```c

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
```

使用了负数的sign是-1的性质（这样即使是tMin 这种数字也满足）

不论x正负与否，

x  , negX 两者中一定有一个负数 (若为tMin ，则x和negX都为负数) 

那么此时符号位一定有一个1

**则 `x|negX ` 的符号位此时一定为1**

`x|negX >> 31` 算数右移位，得到全为1——> -1

而若x为0，那么x,negX 都为0，符号位为0，>>31位后仍为0 



## howManyBits

```c

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
  x = (~flag & x) | (flag & ~x); // 无论正负，都变成符号位为0的，第一有效位都为1了现在
  
  
  int bit_16,bit_8,bit_4,bit_2,bit_1,bit_0;

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
  int ans = bit_16 +bit_8 + bit_4 + bit_2 + bit_1 + bit_0 + 1;
  return isZero | ans;
}
```

- 二进制的思想：
  - 32可以被1 2 4 8 16刚好表示 (1位符号位)



## floatScale2

```c
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
    unsigned ans = (exp << 23) | sign | frac;
    return ans;
  }
  return 0;
}

```

分别根据exp来判断其是规格化 / 非规格化 /特殊数字 三种情况。



但我有疑问： 不用担心 exp和frac 的数字变化后溢出原本8bin/22bit长度的情况吗





## floatFloat2Int

```c
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
  int Exp = exp - 127;
  
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

  // signed int type;  It's 2's complement number 
  if(sign) // negative
    return ~frac + 1;


  return frac;
}
```

把sign， frac， exp三个部分拆开

分类讨论exp的三种情况

值得注意的是 normalize数中， E = exp - 127 得到真正的次数

**然后直接对frac进行E个移位就能完成乘法**

但是考虑E的大小，若为负数，则frac在1～2之间 ， frac * 2^E 必然 小于 1，直接返回0

若E > 23 则移动后frac部分全部会移动到小数点左侧

若E < 23 则移动后frac部分 E - 23的长度仍在小数点右侧，需要舍弃





## floatPower2

```c

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
```

- Frac : 23bit

- exp : 8bit 
  - E = X = exp - bias(127)
  - range of E : `-126 ~ 127`

- sign : 因为是 2^X 则，必为正数



- denormalize 范围:
  - E = 1-127 = -126  
  - Frac 全为0  :  Value = 0*2^(-126) = 0
  - Denormalize Min --Frac 最低位为1 : Value = 2^-23 * 2^-126
  - Denormalize Max -- Frac 全1 , 真实值0.11...11,也不到1啊  ,因此0.11..11 * 2^-126 ， 逼近2^-126
- Normalize
  - E min = 1-127 = -126
  - Normalize Min:  Frac 全0   --Value = 2^-126
  - Normalize Max: Frac 全1.  E = 255-127 = 127； Value = 1.11...11 * 2^127  逼近2^128

因此分类讨论

题目中的X == E

True exp = E + 127

