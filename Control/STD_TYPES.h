/*
 * STD_TYPES.h
 *
 *  Created on: 26 Aug 2017
 *      Author: Abdulrahman
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef float f32;
typedef double f64;

typedef struct parameters{
	f32 x, y, z;
	f32 x_dot, y_dot, z_dot;
	f32 x_dot_dot;
	f32 y_dot_dot;
	f32 z_dot_dot;
	f32 phi;
	f32 theta ;
	f32 psi ;
	f32 phi_dot;//not sure
	f32 theta_dot;//
	f32 psi_dot;//
	f32 p;
	f32 q;
	f32 r;
	f32 p_dot;
	f32 q_dot;
	f32 r_dot;
	f32 x_cmd;
	f32 y_cmd;
	f32 z_cmd;
	f32 x_dot_cmd;
	f32 y_dot_cmd;
	f32 z_dot_cmd;
	f32 x_dot_dot_cmd;
	f32 y_dot_dot_cmd;
	f32 z_dot_dot_cmd;
	f32 psi_cmd;
	f32 p_cmd;
	f32 q_cmd;
	f32 r_cmd;
	f32 u1, u2, u3, u4;
} parameters;
typedef struct accel{
	f32 x;
	f32 y;
	f32 z;
}accel;
typedef struct bodyrate{
	f32 p;
	f32 q;
	f32 r;
}bodyrate;

#endif /* STD_TYPES_H_*/
