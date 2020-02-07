
#ifndef UTILS_128_H_
#define UTILS_128_H_

/*SET_BIT

 * 1. OR with a 1 in the desired BIT_NUMBER. The rest are ORed with 0 (No Effect).

 */
#define SET_BIT(reg , num)			reg|=(1 << num)


/*CLEAR_BIT

 * 1.AND with a 0 in the desired BIT_NUMBER. The rest are ANDed with 1 (No effect)

 */
#define CLEAR_BIT(reg , num)			reg&=~(1 << num)


/*TOGGLE_BIT

 * 1. XOR with 1 at the desired BIT_NUMBER. The rest are XORed with 0 (No effect)

 */
#define TOGGLE_BIT (reg , num)		reg^= (1 << num)


/*GET_BIT

 * 1. Shift right  BIT_NUMBER times (to the least significant bit)

 * 2. Mask out the least significant bit

 */

#define GET_BIT(reg,num)			    ((reg >> num) & 1)

#endif /* UTILS_128_H_ */
