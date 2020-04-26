#include "STD_TYPES.h"
#include "UTILS.h"
#include "quickmath.h"
#include "Blocks.h"
#include "Constants.h"
/* Implementation of Controller blocks
 * This part consists of an Inner loop and an Outer loop.
 * The inner loop consists of: Body rate, roll pitch and yaw controller.
 * The outer loop consists of: altitude control and lateral control
 * Body rate: 	Inputs 	= 	p, q, r, p_cmd, q_cmd, r_cmd
 * 				outputs	= 	Moments u2, u3, u4
 *
 * Roll pitch:	Inputs 	= 	U1 (Thrust force), x_dot_dot_cmd, y_dot_dot_cmd, phi, theta, psi
 * 				outputs	=	p_cmd, q_cmd
 *
 * Yaw:			Inputs 	= 	psi_cmd, psi
 * 				outputs	=	r_cmd
 *
 * Altitude:	Inputs 	= 	z, z_dot, phi, theta, psi, z_cmd, z_dot_cmd
 * 				outputs	=	U1 (Thrust force)
 *
 * Lateral:		Inputs 	= 	x, y, x_dot, y_dot, x_cmd, y_cmd, x_dot_cmd, y_dot_cmd, phi, theta, psi
 * 				outputs	= 	x_dot_dot_cmd, y_dot_dot_cmd
 *
 *
 */
void output_thrust(void *pt)
{
	parameters *ptr = pt;
	f32 l = L/1.4142135623;
	f32 t1 = ptr->u2/ l;
	f32 t2 = ptr->u3 / l;
	f32 t3 = - ptr->u4/ k_thrust;
	f32 t4 = ptr->u1;
	ptr->cmd_thrust[0] = (t1 + t2 + t3 + t4)/4.f; // front left
	ptr->cmd_thrust[1] = (-t1 + t2 - t3 + t4)/4.f; // front right
	ptr->cmd_thrust[2] = (t1 - t2 - t3 + t4)/4.f ; // rear left
	ptr->cmd_thrust[3] = (-t1 - t2 + t3 + t4)/4.f; // rear right
}



void body_rates(void *pt)
{	parameters *ptr=pt;
	while(1)
	{f32 p_error,q_error,r_error;
	p_error = ptr->p_cmd - ptr->p;
	q_error = ptr->q_cmd - ptr->q;
	r_error = ptr->r_cmd - ptr->r;
	ptr->p_dot = kp_p * p_error;
	ptr->q_dot = kp_q * q_error;
	ptr->r_dot = kp_r * r_error;
	ptr->u2 = Ixx * ptr->p_dot;
	ptr->u3 = Iyy * ptr->q_dot;
	ptr->u4 = Izz * ptr->r_dot;
	vTaskDelay(1);
	}
}
void roll_pitch(void *pt)
{
	parameters * ptr = pt;
	while(1)
	{f32 b_x_dot_cmd, b_y_dot_cmd, taw=1/kp_bank;
	f32 R11 = 1;
	f32 R12 = sin(ptr->phi) * sin(ptr->theta) / cos(ptr->theta);
	f32 R13= cos(ptr->phi) * sin(ptr->theta) / cos(ptr->theta);
	f32 R21 = 0;
	f32 R22 = cos(ptr->phi);
	f32 R23= -sin(ptr->phi);
	f32 R31 = 0;
	f32 R32 = sin(ptr->phi) / cos(ptr->theta);
	f32 R33 = cos(ptr->phi) / cos(ptr->theta);
	f32 R13_cmd= ptr->x_dot_dot_cmd*m/ptr->u1;
	f32 R23_cmd= ptr->y_dot_dot_cmd*m/ptr->u1;
    b_x_dot_cmd= (R13-R13_cmd)/taw;
    b_y_dot_cmd= (R23-R23_cmd)/taw;

    ptr->p_cmd = 1/R33 * (R21*b_x_dot_cmd - R11*b_y_dot_cmd);
    ptr->q_cmd = 1/R33 * (R22*b_x_dot_cmd - R12*b_y_dot_cmd);
	vTaskDelay(1);

	}
}
void yaw_controller(void *pt)
{
	parameters* ptr= pt;
	while(1)
	{ptr->r_cmd = kp_yaw*(ptr->psi_cmd - ptr->psi);
	vTaskDelay(100);

	}
}
void altitude_controller(void *pt)
{
	parameters* ptr= pt;
	while(1)
	{f32 R33 = cos(ptr->phi)/cos(ptr->theta);
	ptr->z_dot_dot_cmd= kp_z*(ptr->z_cmd- ptr->z) + kd_z*(ptr->z_dot_cmd-ptr->z_dot);

	ptr->u1 = m * (ptr->z_dot_dot_cmd - g)/R33;
	vTaskDelay(100);
	}
}
void lateral_controller(void *pt)
{
	parameters* ptr= pt;
	while(1)
	{
	ptr->x_dot_dot_cmd= kp_xy*(ptr->x_cmd- ptr->z) + kd_xy*(ptr->x_dot_cmd-ptr->x_dot);
	ptr->y_dot_dot_cmd= kp_xy*(ptr->y_cmd- ptr->z) + kd_xy*(ptr->y_dot_cmd-ptr->y_dot);
	vTaskDelay(100);
	}
}
