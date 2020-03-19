/*
 * quickmath.h
 *
 *  Created on: Feb 18, 2020
 *      Author: Khaled Ali
 */

#ifndef QUICKMATH_H_
#define QUICKMATH_H_

#define PI 3.14159
#define TERMS 7
float power(float base, int exp);
int fact(int n);
float sin(f32 deg);
float cos(f32 deg);
float arctan(f32 x);
void Quaternion(f32 *q, f32 *euler);
void Rotate_BtoW(f32 *acc, f32 *q);
void matrix_inverse(void);
#endif /* QUICKMATH_H_ */
