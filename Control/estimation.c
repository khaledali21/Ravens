/*
 * estimation.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Khaled Ali
 */

#include "STD_TYPES.h"
#include "imu6050.h"
#include "quickmath.h"
//#include "Constants.h"
void update_IMU(parameters *ptr)
{
	bodyrate * gyro;
	accel * acc;
	//Read_IMU_Values(acc, gyro);
	f32 dt = 0.001; f32 taw=1;
		f32 R11 = 1;
		f32 R12 = sine(ptr->phi) * sine(ptr->theta) / cosine(ptr->theta);
		f32 R13= cosine(ptr->phi) * sine(ptr->theta) / cosine(ptr->theta);
		f32 R21 = 0;
		f32 R22 = cosine(ptr->phi);
		f32 R23= -sine(ptr->phi);
		f32 R31 = 0;
		f32 R32 = sine(ptr->phi) / cosine(ptr->theta);
		f32 R33 = cosine(ptr->phi) / cosine(ptr->theta);
		ptr->phi_dot = ptr->p + ptr->q * R12 + ptr->r * R13;
	    ptr->theta_dot = ptr->q * R22 - ptr->r * R23;
	    ptr->psi_dot = ptr-> q * R32 + ptr->r * R33;
	    f32 predictedphi = ptr->phi + ptr->phi_dot * dt;
	    f32 predictedtheta = ptr->theta + ptr->theta_dot * dt;
	    ptr->psi += ptr->psi_dot * dt;
	    if(ptr->psi > PI)
	    	ptr->psi -= 2*PI;
	    if(ptr->psi < -PI)
	    	ptr->psi += 2*PI;
	    f32 accelPhi = arctan(acc->y/acc->z);
	    f32 acceltheta = arctan(-acc->y/9.812);
	    ptr->phi = (taw/(taw + dt))* predictedphi + (dt/(taw + dt)) * accelPhi;
	    ptr->theta = (taw/(taw + dt))* predictedtheta + (dt/(taw + dt)) * acceltheta;
	    //................
	    ptr->x_dot_dot = acc->x;
	    ptr->y_dot_dot = acc->y;
	    ptr->z_dot_dot = acc->z;

}

void prediction(parameters *ptr)
{	f32 dt = 0.001;
	f32 euler[3]={ptr->phi, ptr->theta, ptr->psi};
	f32 q[4];
	Quaternion(q,euler);
	f32 acc[3] = {ptr->x_dot_dot, ptr->y_dot_dot, ptr->z_dot_dot};
	Rotate_BtoW(acc, q);
	ptr->x += dt * ptr->x_dot;
	ptr->y += dt * ptr->y_dot;
	ptr->z += dt * ptr->z_dot;
	ptr->x_dot += dt * acc[0];
	ptr->y_dot += dt * acc[1];
	ptr->z_dot += dt * acc[2] - dt * 9.812;
}

