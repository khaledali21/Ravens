/*
 * UTILS.h
 *
 *  Created on: 26 Aug 2017
 *      Author: Abdulrahman
 */

#ifndef UTILS_H_
#define UTILS_H_



/*SET_BIT
 * 1. OR with a 1 in the desired BIT_NUMBER. The rest are ORed with 0 (No Effect).
 */
#define SET_BIT(REGISTER_NUMBER,BIT_NUMBER)			(REGISTER_NUMBER |= (1<<BIT_NUMBER))

/*CLEAR_BIT
 * 1.AND with a 0 in the desired BIT_NUMBER. The rest are ANDed with 1 (No effect)
 */
#define CLEAR_BIT(REGISTER_NUMBER,BIT_NUMBER)		(REGISTER_NUMBER &= ( ~(1<<BIT_NUMBER) ) )


/*GET_BIT
 * 1. Shift right  BIT_NUMBER times (to the least significant bit)
 * 2. Mask out the least significant bit
 */
#define GET_BIT(REGISTER_NUMBER,BIT_NUMBER)			( (REGISTER_NUMBER>>BIT_NUMBER) & 1)

/*TOGGLE_BIT
 * 1. XOR with 1 at the desired BIT_NUMBER. The rest are XORed with 0 (No effect)
 */
#define TOGGLE_BIT(REGISTER_NUMBER,BIT_NUMBER)		( REGISTER_NUMBER ^=  (1<<BIT_NUMBER) )
#endif /* UTILS_H_ */
