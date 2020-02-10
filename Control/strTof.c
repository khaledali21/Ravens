/*
 * this is an implementation of string to f32 function
 * the accuracy isnt perfect due to weakness of C in f32ing operations
 */

#include "strTof.h"

u8 pow(u8 base, u8 exponent)
{
u8 result=1;
for (exponent; exponent>0; exponent--)
{
result = result * base;
}
return result;
}

f32  strTof(u8 x[20] )
{
    f32 y=0;
    u8 i;
    u8 pointIndex; // the index of the po u8 in the number
    // 1st for loop to get index of the po u8 in the number
    for(i=0 ;i<strlen(x);i++ )
    {
        // once we get the pou8 break the loop
        if(x[i]=='.')
        {
            pointIndex=i;
            break;
        }

    }



    u8 k=pointIndex;
    k=k-1;

    // 2nd for loop to get numbers before the pou8 by multiplying each number by its weight
    for(i =0;i<pointIndex;i++)
    {
        y+=(x[i]-48)*pow(10,k);
        k--;
    }

    k=pointIndex;
    u8 h =1;
    u8 j;
    f32 z=0;

    // 3rd loop to get numbers after the pou8 also by multiplying each number by its weight
    for (j =k+1  ;j<strlen(x); j++ )
    {
        z+=(x[j]-48)/pow(10,h);
        h++;
    }
    y+=z;
     //return by the f32 number
    return y ;
}

