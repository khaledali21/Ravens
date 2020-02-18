/*
 * quickmath.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Khaled Ali
 */
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


float sine(f32 deg) {
    deg %= 360; // make it less than 360
    float rad = deg * PI / 180;
    float sin = 0;

    int i;
    for(i = 0; i < TERMS; i++) { // That's Taylor series!!
        sin += power(-1, i) * power(rad, 2 * i + 1) / fact(2 * i + 1);
    }
    return sin;
}

float cosine(f32 deg) {
    deg %= 360; // make it less than 360
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
