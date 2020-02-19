/*
 * quickmath.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Khaled Ali
 */
#include "STD_TYPES.h"
#include "quickmath.h"


float power(float base, int exp) {
    if(exp < 0) {
        if(base == 0)
            return -0; // Error!!
        return 1 / (base * power(base, (-exp) - 1));
    }
    if(exp == 0)
        return 1;
    if(exp == 1)
        return base;
    return base * power(base, exp - 1);
}

int fact(int n) {
    return n <= 0 ? 1 : n * fact(n-1);
}
//new comment

float sine(f32 deg) {
    while(deg>360)
    {
    	deg-=360;
    }
    while(deg<-360)
    {
    	deg+=360;
    }
    float rad = deg * PI / 180;
    float sin = 0;

    int i;
    for(i = 0; i < TERMS; i++) { // That's Taylor series!!
        sin += power(-1, i) * power(rad, 2 * i + 1) / fact(2 * i + 1);
    }
    return sin;
}

float cosine(f32 deg) {
    while(deg>360)
    {
    	deg-=360;
    }
    while(deg<-360)
    {
    	deg+=360;
    }
    float rad = deg * PI / 180;
    float cos = 0;

    int i;
    for(i = 0; i < TERMS; i++) { // That's also Taylor series!!
        cos += power(-1, i) * power(rad, 2 * i) / fact(2 * i);
    }
    return cos;
}
float arctan(f32 x)
{	u8 flipflag=0;
	if(x>1)
		{x=1/x; flipflag=1;}
	float atan=0;
	int i;
	for(i=0; i< TERMS; i++){
		atan+=power(-1,i) * power(x, (2 *i) + 1) / ((2 *i) + 1);
	}
	if(flipflag==1)
		atan=(PI/2)-atan;
	return atan;
}

void Quaternion(f32 *q, f32 *euler)
{
	euler[0]/=2;
	euler[1]/=2;
	euler[2]/=2;
	q[0] = cosine(euler[0]) * cosine(euler[1]) * cosine(euler[2])   + sine(euler[0])  * sine(euler[1]) * sine(euler[2]);
	q[1] =-cosine(euler[0]) * sine(euler[1]) * sine(euler[2])   + cosine(euler[1]) * cosine(euler[2])   * sine(euler[0]);
	q[2] = cosine(euler[0]) * cosine(euler[2])   * sine(euler[1]) + sine(euler[0])  * cosine(euler[1]) * sine(euler[2]);
	q[3] = cosine(euler[0]) * cosine(euler[1]) * sine(euler[2])   - sine(euler[0])  * cosine(euler[2])   * sine(euler[1]);

}
void Rotate_BtoW(f32 *acc, f32 *q)
{	q[0]=-q[0];
	f32 R[9];

	f32 r0 = q[0]*q[0];
	f32 r1 = q[1]*q[1];
	f32 r2 = q[2]*q[2];
	f32 r3 = q[3]*q[3];
	R[0] = r0 + r1 - r2 - r3;
	R[1] = 2*q[1]*q[2] + 2*q[0]*q[3];
	R[2] = 2*q[1]*q[3] - 2*q[0]*q[2];
	R[3] = 2*q[1]*q[2] - 2*q[0]*q[3];
	R[4] = r0 - r1 + r2 - r3;
	R[5] = 2*q[2]*q[3] + 2*q[0]*q[1];
	R[6] = 2*q[1]*q[3] + 2*q[0]*q[2];
	R[7] = 2*q[2]*q[3] - 2*q[0]*q[1];
	R[8] = r0 - r1 - r2 + r3;
	acc[0] = R[0]*acc[0] + R[1]*acc[1] + R[2]*acc[2];
	acc[1] = R[3]*acc[0] + R[4]*acc[1] + R[5]*acc[2];
	acc[2] = R[6]*acc[0] + R[7]*acc[1] + R[8]*acc[2];
}
